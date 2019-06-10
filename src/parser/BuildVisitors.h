#ifndef BUILDVISITORS_H //2.53 Updated to 16th Jan, 2017
#define BUILDVISITORS_H

#include "ASTVisitors.h"
#include "ByteCode.h"
#include "ZScript.h"
#include "Scope.h"
#include <algorithm>
#include <vector>
#include <set>

namespace ZScript
{
	class BuildOpcodes : public RecursiveVisitor
	{
	public:
		BuildOpcodes(Scope* curScope);

		using RecursiveVisitor::visit;
		void visit(AST& node, void* param = NULL);
		void literalVisit(AST& node, void* param = NULL);
		void literalVisit(AST* node, void* param = NULL);
	
		virtual void caseDefault(AST& host, void* param);
		virtual void caseSetOption(ASTSetOption& host, void* param);
		virtual void caseUsing(ASTUsingDecl& host, void* param = NULL);
		// Statements
		virtual void caseBlock(ASTBlock &host, void *param);
		virtual void caseStmtIf(ASTStmtIf &host, void *param);
		virtual void caseStmtIfElse(ASTStmtIfElse &host, void *param);
		virtual void caseStmtSwitch(ASTStmtSwitch &host, void* param);
		virtual void caseStmtFor(ASTStmtFor &host, void *param);
		virtual void caseStmtWhile(ASTStmtWhile &host, void *param);
		virtual void caseStmtDo(ASTStmtDo &host, void *param);
		virtual void caseStmtReturn(ASTStmtReturn &host, void *param);
		virtual void caseStmtReturnVal(ASTStmtReturnVal &host, void *param);
		virtual void caseStmtBreak(ASTStmtBreak &host, void *param);
		virtual void caseStmtContinue(ASTStmtContinue &host, void *param);
		virtual void caseStmtEmpty(ASTStmtEmpty &host, void *param);
		// Declarations
		virtual void caseFuncDecl(ASTFuncDecl &host, void *param);
		virtual void caseDataDecl(ASTDataDecl& host, void* param);
		virtual void caseDataTypeDef(ASTDataTypeDef& host, void* param);
		virtual void caseCustomDataTypeDef(ASTDataTypeDef& host, void* param);
		// Expressions
		virtual void caseExprAssign(ASTExprAssign &host, void *param);
		virtual void caseExprIdentifier(ASTExprIdentifier &host, void *param);
		virtual void caseExprArrow(ASTExprArrow &host, void *param);
		virtual void caseExprIndex(ASTExprIndex &host, void *param);
		virtual void caseExprCall(ASTExprCall &host, void *param);
		virtual void caseExprNegate(ASTExprNegate &host, void *param);
		virtual void caseExprNot(ASTExprNot &host, void *param);
		virtual void caseExprBitNot(ASTExprBitNot &host, void *param);
		virtual void caseExprIncrement(ASTExprIncrement &host, void *param);
		virtual void caseExprPreIncrement(ASTExprPreIncrement &host, void *param);
		virtual void caseExprDecrement(ASTExprDecrement &host, void *param);
		virtual void caseExprPreDecrement(ASTExprPreDecrement &host, void *param);
		virtual void caseExprAnd(ASTExprAnd &host, void *param);
		virtual void caseExprOr(ASTExprOr &host, void *param);
		virtual void caseExprGT(ASTExprGT &host, void *param);
		virtual void caseExprGE(ASTExprGE &host, void *param);
		virtual void caseExprLT(ASTExprLT &host, void *param);
		virtual void caseExprLE(ASTExprLE &host, void *param);
		virtual void caseExprEQ(ASTExprEQ &host, void *param);
		virtual void caseExprNE(ASTExprNE &host, void *param);
		virtual void caseExprPlus(ASTExprPlus &host, void *param);
		virtual void caseExprMinus(ASTExprMinus &host, void *param);
		virtual void caseExprTimes(ASTExprTimes &host, void *param);
		virtual void caseExprDivide(ASTExprDivide &host, void *param);
		virtual void caseExprModulo(ASTExprModulo &host, void *param);
		virtual void caseExprBitAnd(ASTExprBitAnd &host, void *param);
		virtual void caseExprBitOr(ASTExprBitOr &host, void *param);
		virtual void caseExprBitXor(ASTExprBitXor &host, void *param);
		virtual void caseExprLShift(ASTExprLShift &host, void *param);
		virtual void caseExprRShift(ASTExprRShift &host, void *param);
		virtual void caseExprTernary(ASTTernaryExpr &host, void *param);
		// Literals
		virtual void caseNumberLiteral(ASTNumberLiteral& host, void* param);
		virtual void caseBoolLiteral(ASTBoolLiteral& host, void* param);
		virtual void caseStringLiteral(ASTStringLiteral& host, void* param);
		virtual void caseArrayLiteral(ASTArrayLiteral& host, void* param);
		virtual void caseOptionValue(ASTOptionValue& host, void* param);
		// Types
		void caseDataType(ASTDataType& host, void* param) {}

		vector<Opcode *> getResult() const {return result;}
		int getReturnLabelID() const {return returnlabelid;}
		list<long> *getArrayRefs() {return &arrayRefs;}
		list<long> const *getArrayRefs() const {return &arrayRefs;}

	private:
		void addOpcode(Opcode* code);

		template <class Container>
		void addOpcodes(Container const& container);
	
		void deallocateArrayRef(long arrayRef);
		void deallocateRefsUntilCount(int count);
		
		vector<Opcode *> result;
		int returnlabelid;
		int returnRefCount;
		int continuelabelid;
		int continueRefCount;
		int breaklabelid;
		int breakRefCount;
		list<long> arrayRefs;
		// Stack of opcode targets. Only the latest is used.
		vector<vector<Opcode*>*> opcodeTargets;

		// Helper Functions.

		// For when ASTDataDecl is for a single variable.
		void buildVariable(ASTDataDecl& host, OpcodeContext& context);
		// For when ASTDataDecl is an initialized array.
		void buildArrayInit(ASTDataDecl& host, OpcodeContext& context);
		// For when ASTDataDecl is an uninitialized array.
		void buildArrayUninit(ASTDataDecl& host, OpcodeContext& context);
		// For when ASTStringLiteral is a declaration initializer.
		void stringLiteralDeclaration(
				ASTStringLiteral& host, OpcodeContext& context);
		// For when ASTStringLiteral is not a declaration initializer.
		void stringLiteralFree(ASTStringLiteral& host, OpcodeContext& context);
		// For when ASTArrayLiteral is a declaration initializer.
		void arrayLiteralDeclaration(
				ASTArrayLiteral& host, OpcodeContext& context);
		// For when ASTArrayLiteral is not a declaration initializer.
		void arrayLiteralFree(ASTArrayLiteral& host, OpcodeContext& context);
	};

	class LValBOHelper : public ASTVisitor
	{
	public:
		virtual void caseDefault(void *param);
		//virtual void caseDataDecl(ASTDataDecl& host, void* param);
		virtual void caseExprIdentifier(ASTExprIdentifier &host, void *param);
		virtual void caseExprArrow(ASTExprArrow &host, void *param);
		virtual void caseExprIndex(ASTExprIndex &host, void *param);
		vector<Opcode *> getResult() {return result;}
	private:
		void addOpcode(Opcode* code);

		template <class Container>
		void addOpcodes(Container const& container);
	
		vector<Opcode *> result;
	};



	class GetLabels : public ArgumentVisitor
	{
	public:
		GetLabels(std::set<int>& usedLabels) : usedLabels(usedLabels) {}

		std::set<int>& usedLabels;
		std::vector<int> newLabels;
			
		void caseLabel(LabelArgument& host, void*)
		{
			int id = host.getID();
			if (find<int>(usedLabels, id)) return;
			usedLabels.insert(id);
			newLabels.push_back(id);
		}
	};

	class SetLabels : public ArgumentVisitor
	{
	public:
		void caseLabel(LabelArgument &host, void *param)
		{
			map<int, int> *labels = (map<int, int> *)param;
			int lineno = (*labels)[host.getID()];
        
			if(lineno==0)
			{
				char temp[200];
				sprintf(temp,"Internal error: couldn't find function label %d", host.getID());
				box_out(temp);
				box_eol();
			}
        
			host.setLineNo(lineno);
		}
	};
}
#endif

