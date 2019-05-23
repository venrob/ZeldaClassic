#include "../precompiled.h" // Always first.
#include "ASTVisitors.h"

#include "../zsyssimple.h"
#include "CompileError.h"
#include "Scope.h"
#include <assert.h>
#include <cstdarg>

using std::list;
using std::vector;
using namespace ZScript;

////////////////////////////////////////////////////////////////
// RecursiveVisitor

bool RecursiveVisitor::breakRecursion(AST& host, void* param) const
{
	return host.errorDisabled || failure || breakNode;
}

bool RecursiveVisitor::breakRecursion(void* param) const
{
	return failure || breakNode;
}

void RecursiveVisitor::syncDisable(AST& parent, AST const& child)
{
	if(child.errorDisabled) parent.errorDisabled = true;
	if(child.isDisabled()) parent.disable();
}

void RecursiveVisitor::syncDisable(AST& parent, AST const* child)
{
	if(child->errorDisabled) parent.errorDisabled = true;
	if(child->isDisabled()) parent.disable();
}

void RecursiveVisitor::handleError(CompileError const& error)
{
	bool skipError = (scope && *ZScript::lookupOption(*scope, CompileOption::OPT_NO_ERROR_HALT) != 0);
	if(recursionStack.size()) recursionStack.back()->errorDisabled = true;
	// Scan through the node stack looking for a handler.
	for (vector<AST*>::const_reverse_iterator it = recursionStack.rbegin();
		 it != recursionStack.rend(); ++it)
	{
		AST& ancestor = **it;
		for (vector<ASTExprConst*>::iterator it =
				 ancestor.compileErrorCatches.begin();
			 it != ancestor.compileErrorCatches.end(); ++it)
		{
			ASTExprConst& idNode = **it;
			optional<long> errorId = idNode.getCompileTimeValue();
			assert(errorId);
			// If we've found a handler, remove that handler from the node's
			// list of handlers and disable the current node (if not a
			// warning).
			if (*errorId == *error.getId() * 10000L)
			{
				ancestor.compileErrorCatches.erase(it);
				if (error.isStrict()) //Let errors be caught, if expected; don't disable this on skipError -V
				{
					ancestor.errorDisabled = true;
					breakNode = &ancestor;
				}
				return;
			}
		}
	}

	// Actually handle the error.
	if (error.isStrict())
		if(skipError) failure_skipped = true;
		else failure = true;
	box_out_err(error);
}

void RecursiveVisitor::visit(AST& node, void* param)
{
	if(node.isDisabled()) return; //Don't visit disabled nodes.
	if (breakRecursion(node, param)) return;
	recursionStack.push_back(&node);
	node.execute(*this, param);
	recursionStack.pop_back();
	if (breakNode == &node) breakNode = NULL;
}

void RecursiveVisitor::visit(AST* node, void* param)
{
	if (node) visit(*node, param);
}

////////////////////////////////////////////////////////////////
// Cases

void RecursiveVisitor::caseFile(ASTFile& host, void* param)
{
	visit(host, host.options, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.use, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.dataTypes, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.scriptTypes, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.imports, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.variables, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.functions, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.namespaces, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.scripts, param);
}

void RecursiveVisitor::caseSetOption(ASTSetOption& host, void* param)
{
	visit(host.expr.get(), param);
}

// Statements

void RecursiveVisitor::caseBlock(ASTBlock& host, void* param)
{
	visit(host, host.options, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.statements, param);
}

void RecursiveVisitor::caseStmtIf(ASTStmtIf& host, void* param)
{
	visit(host.condition.get(), param);
	syncDisable(host, *host.condition);
	if (breakRecursion(host, param)) return;
	visit(host.thenStatement.get(), param);
}

void RecursiveVisitor::caseStmtIfElse(ASTStmtIfElse& host, void* param)
{
	caseStmtIf(host, param);
	if (breakRecursion(host, param)) return;
	visit(host.elseStatement.get(), param);
}

void RecursiveVisitor::caseStmtSwitch(ASTStmtSwitch& host, void* param)
{
	visit(host.key.get(), param);
	syncDisable(host, *host.key);
	if (breakRecursion(host, param)) return;
	visit(host, host.cases, param);
}

void RecursiveVisitor::caseSwitchCases(ASTSwitchCases& host, void* param)
{
	visit(host, host.cases, param);
	if (breakRecursion(host, param)) return;
	visit(host.block.get(), param);
}

void RecursiveVisitor::caseStmtFor(ASTStmtFor& host, void* param)
{
	visit(host.setup.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host.test.get(), param);
	syncDisable(host, *host.test);
	if (breakRecursion(host, param)) return;
	visit(host.increment.get(), param);
	syncDisable(host, *host.increment);
	if (breakRecursion(host, param)) return;
	visit(host.body.get(), param);
}

void RecursiveVisitor::caseStmtWhile(ASTStmtWhile& host, void* param)
{
	visit(host.test.get(), param);
	syncDisable(host, *host.test);
	if (breakRecursion(host, param)) return;
	visit(host.body.get(), param);
}

void RecursiveVisitor::caseStmtDo(ASTStmtDo& host, void* param)
{
	visit(host.body.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host.test.get(), param);
	syncDisable(host, *host.test);
}

void RecursiveVisitor::caseStmtRepeat(ASTStmtRepeat& host, void* param)
{
	visit(*host.iter, param);
	syncDisable(host, *host.iter);
	if(breakRecursion(host, param)) return;
	optional<long> repeats = (*host.iter).getCompileTimeValue(this, scope);
	if(repeats)
	{
		int rep = *repeats / 10000L;
		if(rep>0)
		{
			for(int q = rep - 1; q > 0; --q)
			{
				visit((*host.body).clone(), param);
			}
			visit(&*host.body, param);
		}
		else if(rep < 0)
		{
			handleError(CompileError::ConstantBadSize(&*host.iter, ">= 0"));
		}
	}
	else
	{
		handleError(CompileError::ExprNotConstant(&*host.iter));
	}
}

void RecursiveVisitor::caseStmtReturnVal(ASTStmtReturnVal& host, void* param)
{
	visit(host.value.get(), param);
}

// Declarations

void RecursiveVisitor::caseScript(ASTScript& host, void* param)
{
	visit(host.type.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host, host.options, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.use, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.types, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.variables, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.functions, param);
}

void RecursiveVisitor::caseNamespace(ASTNamespace& host, void* param)
{
	visit(host, host.options, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.dataTypes, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.scriptTypes, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.use, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.variables, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.functions, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.namespaces, param);
	if (breakRecursion(host, param)) return;
	visit(host, host.scripts, param);
}

void RecursiveVisitor::caseImportDecl(ASTImportDecl& host, void* param)
{
	visit(host.getTree(), param);
}

void RecursiveVisitor::caseFuncDecl(ASTFuncDecl& host, void* param)
{
	if(host.getFlag(FUNCFLAG_INVALID))
	{
		handleError(CompileError::BadFuncModifiers(&host, host.invalidMsg));
		return;
	}
	visit(host.returnType.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host, host.parameters, param);
	if (breakRecursion(host, param)) return;
	visit(host.block.get(), param);
}

void RecursiveVisitor::caseDataDeclList(ASTDataDeclList& host, void* param)
{
	visit(host.baseType.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host, host.getDeclarations(), param);
}

void RecursiveVisitor::caseDataEnum(ASTDataEnum& host, void* param)
{
	visit(host.baseType.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host, host.getDeclarations(), param);
}

void RecursiveVisitor::caseDataDecl(ASTDataDecl& host, void* param)
{
	visit(host.baseType.get(), param);
	if(host.baseType) syncDisable(host, *host.baseType);
	if (breakRecursion(host, param)) return;
	visit(host, host.extraArrays, param);
	for(vector<ASTDataDeclExtraArray*>::iterator it = host.extraArrays.begin();
		it != host.extraArrays.end(); ++it)
	{
		syncDisable(host, *it);
	}
	if (breakRecursion(host, param)) return;
	visit(host.getInitializer(), param);
	syncDisable(host, host.getInitializer());
}

void RecursiveVisitor::caseDataDeclExtraArray(
		ASTDataDeclExtraArray& host, void* param)
{
	visit(host, host.dimensions, param);
}

void RecursiveVisitor::caseDataTypeDef(ASTDataTypeDef& host, void* param)
{
	visit(host.type.get(), param);
}

void RecursiveVisitor::caseCustomDataTypeDef(ASTCustomDataTypeDef& host, void* param)
{
	visit(host.type.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host.definition.get(), param);
}

// Expressions

void RecursiveVisitor::caseExprConst(ASTExprConst& host, void* param)
{
	visit(host.content.get(), param);
	syncDisable(host, *host.content);
}

void RecursiveVisitor::caseExprAssign(ASTExprAssign& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprArrow(ASTExprArrow& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.index.get(), param);
	syncDisable(host, *host.index);
}

void RecursiveVisitor::caseExprIndex(ASTExprIndex& host, void* param)
{
	visit(host.array.get(), param);
	syncDisable(host, *host.array);
	if (breakRecursion(host, param)) return;
	visit(host.index.get(), param);
	syncDisable(host, *host.index);
}

void RecursiveVisitor::caseExprCall(ASTExprCall& host, void* param)
{
	//visit(host.left, param);
	//if (breakRecursion(host, param)) return;
	visit(host, host.parameters, param);
	for(vector<ASTExpr*>::iterator it = host.parameters.begin();
		it != host.parameters.end(); ++it)
	{
		syncDisable(host, *it);
	}
}

void RecursiveVisitor::caseExprNegate(ASTExprNegate& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprNot(ASTExprNot& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprBitNot(ASTExprBitNot& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprIncrement(ASTExprIncrement& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprPreIncrement(
		ASTExprPreIncrement& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprDecrement(ASTExprDecrement& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprPreDecrement(
		ASTExprPreDecrement& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprCast(ASTExprCast& host, void* param)
{
	visit(host.operand.get(), param);
	syncDisable(host, *host.operand);
}

void RecursiveVisitor::caseExprAnd(ASTExprAnd& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprOr(ASTExprOr& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprGT(ASTExprGT& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprGE(ASTExprGE& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprLT(ASTExprLT& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprLE(ASTExprLE& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprEQ(ASTExprEQ& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprNE(ASTExprNE& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprPlus(ASTExprPlus& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprMinus(ASTExprMinus& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprTimes(ASTExprTimes& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprDivide(ASTExprDivide& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprModulo(ASTExprModulo& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprBitAnd(ASTExprBitAnd& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprBitOr(ASTExprBitOr& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprBitXor(ASTExprBitXor& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprLShift(ASTExprLShift& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprRShift(ASTExprRShift& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

void RecursiveVisitor::caseExprTernary(ASTTernaryExpr& host, void* param)
{
	visit(host.left.get(), param);
	syncDisable(host, *host.left);
	if (breakRecursion(host, param)) return;
	visit(host.middle.get(), param);
	syncDisable(host, *host.middle);
	if (breakRecursion(host, param)) return;
	visit(host.right.get(), param);
	syncDisable(host, *host.right);
}

// Literals

void RecursiveVisitor::caseNumberLiteral(ASTNumberLiteral& host, void* param)
{
	visit(host.value.get(), param);
}

void RecursiveVisitor::caseArrayLiteral(ASTArrayLiteral& host, void* param)
{
	visit(host.type.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host.size.get(), param);
	if (breakRecursion(host, param)) return;
	visit(host, host.elements, param);
}
