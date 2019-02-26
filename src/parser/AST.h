#ifndef ZSCRIPT_AST_H
#define ZSCRIPT_AST_H

// Declare for flex and bison.
namespace ZScript
{
	class AST;
}
#define YYSTYPE ZScript::AST*

#ifdef _MSC_VER
#if (_MSC_VER <= 1600)
#define snprintf _snprintf
#endif
#endif

#include <list>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "y.tab.hpp"
#include "Compiler.h"
#include "CompileOption.h"
#include "owning_ptr.h"
#include "owning_vector.h"

////////////////////////////////////////////////////////////////

extern std::string curfilename;

namespace ZScript
{
	////////////////////////////////////////////////////////////////
	// Forward Declarations
	
	// ASTVisitors.h
	class ASTVisitor;
	// CompileError.h
	class CompileError;
	class CompileErrorHandler;
	// Scope.h
	class Scope;
	class ZClass;
	// ZScript.h
	class Datum;
	class Literal;
	class Function;

	// Local
	class AST; // virtual
	class ASTFile;
	class ASTNamespace;
	class ASTFloat;
	class ASTString;
	class ASTSetOption;
	// Statements
	class ASTStmt; // virtual
	class ASTBlock;
	class ASTStmtIf;
	class ASTStmtIfElse;
	class ASTStmtSwitch;
	class ASTSwitchCases;
	class ASTStmtFor;
	class ASTStmtWhile;
	class ASTStmtDo;
	class ASTStmtReturn;
	class ASTStmtReturnVal;
	class ASTStmtBreak;
	class ASTStmtContinue;
	class ASTStmtEmpty;
	// Declarations
	class ASTDecl; // virtual
	class ASTScript;
	class ASTImportDecl;
	class ASTFuncDecl;
	class ASTDataDeclList;
	class ASTDataDecl;
	class ASTDataDeclExtraArray;
	class ASTDataTypeDef;
	class ASTScriptTypeDef;
	// Expressions
	class ASTExpr; // virtual
	class ASTExprConst;
	class ASTExprAssign;
	class ASTExprIdentifier;
	class ASTExprArrow;
	class ASTExprIndex;
	class ASTExprCall;
	class ASTUnaryExpr; // virtual
	class ASTExprNegate;
	class ASTExprNot;
	class ASTExprBitNot;
	class ASTExprIncrement;
	class ASTExprPreIncrement;
	class ASTExprDecrement;
	class ASTExprPreDecrement;
	class ASTBinaryExpr; // virtual
	class ASTLogExpr; // virtual
	class ASTExprAnd;
	class ASTExprOr;
	class ASTRelExpr; // virtual
	class ASTExprGT;
	class ASTExprGE;
	class ASTExprLT;
	class ASTExprLE;
	class ASTExprEQ;
	class ASTExprNE;
	class ASTAddExpr; // virtual
	class ASTExprPlus;
	class ASTExprMinus;
	class ASTMultExpr; // virtual
	class ASTExprTimes;
	class ASTExprDivide;
	class ASTExprModulo;
	class ASTBitExpr; // virtual
	class ASTExprBitAnd;
	class ASTExprBitOr;
	class ASTExprBitXor;
	class ASTShiftExpr; // virtual
	class ASTExprLShift;
	class ASTExprRShift;
	class ASTTernaryExpr;
	// Literals
	class ASTLiteral; // virtual
	class ASTNumberLiteral;
	class ASTBoolLiteral;
	class ASTStringLiteral;
	class ASTArrayLiteral;
	class ASTOptionValue;
	// Types
	class ASTScriptType;
	class ASTDataType;

	//////////////////////////////////////////////////////////////////////////////
	class LocationData
	{
	public:
		static LocationData const NONE;

		int first_line;
		int last_line;
		int first_column;
		int last_column;
		std::string fname;

		LocationData()
			: first_line(-1), last_line(-1),
			  first_column(-1), last_column(-1),
			  fname(curfilename)
		{}

		LocationData(YYLTYPE loc)
			: first_line(loc.first_line), last_line(loc.last_line),
			  first_column(loc.first_column), last_column(loc.last_column),
			  fname(curfilename)
		{}

		std::string asString() const;
	};

	////////////////////////////////////////////////////////////////

	class AST
	{
	public:
		// Clone a single node pointer.
		template <class Node>
		static Node* clone(Node* node) {return node ? node->clone() : NULL;}
		// Clone a single node auto pointer.
		template <class Node>
		static std::auto_ptr<Node> clone(std::auto_ptr<Node> const& node) {
			return node.get()
				? std::auto_ptr<Node>(node->clone())
				: std::auto_ptr<Node>();}
		// Clone a vector of AST nodes.
		template <class Node>
		static std::vector<Node*> clone(std::vector<Node*> const& nodes)
		{
			std::vector<Node*> clones;
			for (typename std::vector<Node*>::const_iterator it = nodes.begin();
			     it != nodes.end(); ++it)
				clones.push_back((*it)->clone());
			return clones;
		}	
		// Clone a list of AST nodes.
		template <class Node> static std::list<Node*> clone(std::list<Node*> const& nodes)
		{
			std::list<Node*> clones;
			for (typename std::list<Node*>::const_iterator it = nodes.begin();
			     it != nodes.end(); ++it)
				clones.push_back((*it)->clone());
			return clones;
		}
		// Execute a single node pointer.
		template <class Node>
		static void execute(Node* node, ASTVisitor& visitor, void* param = NULL)
		{
			if (node) node->execute(visitor, param);
		}
		// Execute a vector of AST nodes.
		template <class Node>
		static void execute(
				std::vector<Node*> const& nodes, ASTVisitor& visitor,
				void* param = NULL)
		{
			for (typename std::vector<Node*>::const_iterator it = nodes.begin();
			     it != nodes.end(); ++it)
				(*it)->execute(visitor, param);
		}
		// Execute a list of AST nodes.
		template <class Node>
		static void execute(
				std::list<Node*> const& nodes, ASTVisitor& visitor,
				void* param = NULL)
		{
			for (typename std::list<Node*>::const_iterator it = nodes.begin();
			     it != nodes.end(); ++it)
				(*it)->execute(visitor, param);
		}

		AST(LocationData const& location = LocationData::NONE);
		virtual ~AST() {}
		// Calls subclass's copy constructor on self.
		virtual AST* clone() const = 0;

		virtual void execute(ASTVisitor& visitor, void* param = NULL) = 0;
		virtual std::string asString() const {return "unknown";}

		// Filename and linenumber.
		LocationData location;

		// List of expected compile error ids for this node. They are
		// removed as they are encountered.
		owning_vector<ASTExprConst> compileErrorCatches;

		// If this node has been disabled due to an error.
		bool disabled;
	
		// Subclass Predicates (replacing typeof and such).
		virtual bool isTypeArrow() const {return false;}
		virtual bool isTypeIndex() const {return false;}
		virtual bool isTypeIdentifier() const {return false;}
		virtual bool isTypeVarDecl() const {return false;}
		virtual bool isTypeArrayDecl() const {return false;}
		virtual bool isStringLiteral() const {return false;}
		virtual bool isArrayLiteral() const {return false;}
	};


	////////////////////////////////////////////////////////////////

	class ASTFile : public AST
	{
	public:
		ASTFile(LocationData const& location = LocationData::NONE);
		virtual ASTFile* clone() const {return new ASTFile(*this);}
    
		virtual void execute(ASTVisitor& visitor, void* param = NULL);
		virtual std::string asString() const;

		// Add a declaration to the proper list based on its type.
		void addDeclaration(ASTDecl* declaration);
		bool hasDeclarations() const;

		owning_vector<ASTSetOption> options;
		owning_vector<ASTImportDecl> imports;
		owning_vector<ASTDataDeclList> variables;
		owning_vector<ASTFuncDecl> functions;
		owning_vector<ASTDataTypeDef> dataTypes;
		owning_vector<ASTScriptTypeDef> scriptTypes;
		owning_vector<ASTScript> scripts;
		owning_vector<ASTNamespace> namespaces;
	};
	
	class ASTNamespace : public AST
	{
	public:
		ASTNamespace(LocationData const& location = LocationData::NONE);
		ASTNamespace* clone() const {return new ASTNamespace(*this);}
		
		void execute(ASTVisitor& visitor, void* param = NULL);
		
		//owning_vector<ASTSetOption> options; //Currently disallowed -V
		owning_vector<ASTDataDeclList> variables;
		owning_vector<ASTFuncDecl> functions;
		owning_vector<ASTDataTypeDef> dataTypes;
		owning_vector<ASTScriptTypeDef> scriptTypes;
		owning_vector<ASTScript> scripts;
	}

	class ASTFloat : public AST
	{
	public:
		enum Type {TYPE_DECIMAL, TYPE_BINARY, TYPE_HEX};
	
		ASTFloat(char* value, Type type,
		         LocationData const& location = LocationData::NONE);
		ASTFloat(char const* value, Type type,
		         LocationData const& location = LocationData::NONE);
		ASTFloat(std::string const& value, Type type,
		         LocationData const& location = LocationData::NONE);
		ASTFloat(long value, Type type,
		         LocationData const& location = LocationData::NONE);
		ASTFloat* clone() const {return new ASTFloat(*this);}
	
		void execute(ASTVisitor& visitor, void* param = NULL);
    	
		std::pair<std::string,std::string> parseValue() const;

		Type type;
		std::string value;
		bool negative;
	};

	class ASTString : public AST
	{
	public:
		ASTString(const char* str,
		          LocationData const& location = LocationData::NONE);
		ASTString(std::string const& str,
		          LocationData const& location = LocationData::NONE);
		ASTString* clone() const {return new ASTString(*this);}
	
		void execute(ASTVisitor& visitor, void* param = NULL);

		std::string getValue() const {return str;}
	private:
		std::string str;
	};

	class ASTSetOption : public AST
	{
	public:
		ASTSetOption(std::string const& name, ASTExprConst* expr,
		             LocationData const& location = LocationData::NONE);
		ASTSetOption(std::string const& name,
		             CompileOptionSetting setting,
		             LocationData const& location = LocationData::NONE);
		virtual ASTSetOption* clone() const {return new ASTSetOption(*this);}

		virtual void execute(ASTVisitor& visitor, void* param = NULL);
		virtual std::string asString() const;

		CompileOptionSetting getSetting(
				CompileErrorHandler* = NULL) const;
	
		std::string name;
		CompileOption option;
		owning_ptr<ASTExprConst> expr;
		CompileOptionSetting setting;
	};

	////////////////////////////////////////////////////////////////
	// Statements

	class ASTStmt : public AST
	{
	public:
		ASTStmt(LocationData const& location = LocationData::NONE);
		virtual ASTStmt* clone() const = 0;

		bool isDisabled() const {return disabled_;}
		void disable() {disabled_ = true;}
	
	private:
		bool disabled_;
	};
    
	class ASTBlock : public ASTStmt
	{
	public:
		ASTBlock(LocationData const& location = LocationData::NONE);
		ASTBlock* clone() const {return new ASTBlock(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_vector<ASTSetOption> options;
		owning_vector<ASTStmt> statements;
	};
    
	class ASTStmtIf : public ASTStmt
	{
	public:
		ASTStmtIf(ASTExpr* condition, ASTStmt* thenStatement,
		          LocationData const& location = LocationData::NONE);
		ASTStmtIf* clone() const {return new ASTStmtIf(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTExpr> condition;
		owning_ptr<ASTStmt> thenStatement;
	};

	class ASTStmtIfElse : public ASTStmtIf
	{
	public:
		ASTStmtIfElse(
				ASTExpr* condition, ASTStmt* thenStatement, ASTStmt* elseStatement,
				LocationData const& location = LocationData::NONE);
		ASTStmtIfElse* clone() const {return new ASTStmtIfElse(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTStmt> elseStatement;
	};

	// A switch statement.
	class ASTStmtSwitch : public ASTStmt
	{
	public:
		ASTStmtSwitch(LocationData const& location = LocationData::NONE);
		ASTStmtSwitch* clone() const {return new ASTStmtSwitch(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		// The key expression used to switch.
		owning_ptr<ASTExpr> key;
		// A vector of case groupings.
		owning_vector<ASTSwitchCases> cases;
	private:
	};

	// A grouping of switch statement labels, and the code for the group.
	class ASTSwitchCases : public AST
	{
	public:
		ASTSwitchCases(LocationData const& location = LocationData::NONE);
		ASTSwitchCases* clone() const {return new ASTSwitchCases(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		// The list of case labels.
		owning_vector<ASTExprConst> cases;
		// If the default case is included in this grouping.
		bool isDefault;
		// The block to run.
		owning_ptr<ASTBlock> block;
	};


	class ASTStmtFor : public ASTStmt
	{
	public:
		ASTStmtFor(ASTStmt* setup = NULL,
		           ASTExpr* test = NULL,
		           ASTStmt* increment = NULL,
		           ASTStmt* body = NULL,
		           LocationData const& location = LocationData::NONE);
		ASTStmtFor* clone() const {return new ASTStmtFor(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTStmt> setup;
		owning_ptr<ASTExpr> test;
		owning_ptr<ASTStmt> increment;
		owning_ptr<ASTStmt> body;
	};

	class ASTStmtWhile : public ASTStmt
	{
	public:
		ASTStmtWhile(ASTExpr* test = NULL,
		             ASTStmt* body = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTStmtWhile* clone() const {return new ASTStmtWhile(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTExpr> test;
		owning_ptr<ASTStmt> body;
	};

	class ASTStmtDo : public ASTStmt
	{
	public:
		ASTStmtDo(ASTExpr* test = NULL,
		          ASTStmt* body = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTStmtDo* clone() const {return new ASTStmtDo(*this);}
	
		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTExpr> test;
		owning_ptr<ASTStmt> body;
	};

	class ASTStmtReturn : public ASTStmt
	{
	public:
		ASTStmtReturn(LocationData const& location = LocationData::NONE);
		ASTStmtReturn* clone() const {return new ASTStmtReturn(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
	};

	class ASTStmtReturnVal : public ASTStmtReturn
	{
	public:
		ASTStmtReturnVal(ASTExpr* value = NULL,
		                 LocationData const& location = LocationData::NONE);
		ASTStmtReturnVal* clone() const {return new ASTStmtReturnVal(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		owning_ptr<ASTExpr> value;
	};

	class ASTStmtBreak : public ASTStmt
	{
	public:
		ASTStmtBreak(LocationData const& location = LocationData::NONE);
		ASTStmtBreak* clone() const {return new ASTStmtBreak(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
	};

	class ASTStmtContinue : public ASTStmt
	{
	public:
		ASTStmtContinue(LocationData const& location = LocationData::NONE);
		ASTStmtContinue* clone() const {return new ASTStmtContinue(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
	};

	class ASTStmtEmpty : public ASTStmt
	{
	public:
		ASTStmtEmpty(LocationData const& location = LocationData::NONE);
		ASTStmtEmpty* clone() const {return new ASTStmtEmpty(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
	};

	////////////////////////////////////////////////////////////////
	// Declarations

	// virtual
	class ASTDecl : public ASTStmt
	{
	public:
		// Different declaration types.
		enum Type
		{
			TYPE_VOID,
			TYPE_SCRIPT,
			TYPE_IMPORT,
			TYPE_CONSTANT,
			TYPE_FUNCTION,
			TYPE_DATALIST,
			TYPE_DATA,
			TYPE_DATATYPE,
			TYPE_SCRIPTTYPE
		};

		ASTDecl(LocationData const& location = LocationData::NONE);
		ASTDecl* clone() const /*override*/ = 0;

		// Return the subclass id.
		virtual Type getDeclarationType() const = 0;
	};

	// Declares a script.
	class ASTScript : public ASTDecl
	{
	public:
		ASTScript(LocationData const& location = LocationData::NONE);
		ASTScript* clone() const /*override*/ {return new ASTScript(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {return TYPE_SCRIPT;}
    
		// Adds a declaration to the proper vector.
		void addDeclaration(ASTDecl& declaration);

		owning_ptr<ASTScriptType> type;
		std::string name;
		owning_vector<ASTSetOption> options;
		owning_vector<ASTDataDeclList> variables;
		owning_vector<ASTFuncDecl> functions;
		owning_vector<ASTDataTypeDef> types;
	};

	class ASTImportDecl : public ASTDecl
	{
	public:
		ASTImportDecl(std::string const& filename,
		              LocationData const& location = LocationData::NONE);
		ASTImportDecl* clone() /*override*/ const {
			return new ASTImportDecl(*this);}
    
		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {return TYPE_IMPORT;}

		std::string const& getFilename() const {return filename_;}
		ASTFile* getTree() {return tree_.get();}
		ASTFile const* getTree() const {return tree_.get();}
		void giveTree(ASTFile* tree) {tree_ = tree;}
	
	private:
		std::string filename_;
		owning_ptr<ASTFile> tree_;
	};

	class ASTFuncDecl : public ASTDecl
	{
	public:
		ASTFuncDecl(LocationData const& location = LocationData::NONE);
		ASTFuncDecl* clone() const /*override*/ {
			return new ASTFuncDecl(*this);}
    
		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {return TYPE_FUNCTION;}

		owning_ptr<ASTDataType> returnType;
		owning_vector<ASTDataDecl> parameters;
		std::string name;
		owning_ptr<ASTBlock> block;
	};

	// A line of variable/constant declarations:
	// int a, b, c[];
	class ASTDataDeclList : public ASTDecl
	{
	public:
		ASTDataDeclList(LocationData const& location = LocationData::NONE);
		ASTDataDeclList(ASTDataDeclList const&);
		ASTDataDeclList& operator=(ASTDataDeclList const& rhs);
		ASTDataDeclList* clone() const /*override*/ {
			return new ASTDataDeclList(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;
		Type getDeclarationType() const /*override*/ {return TYPE_DATALIST;}

		std::vector<ASTDataDecl*> const& getDeclarations() const {
			return declarations_.data();}
		void addDeclaration(ASTDataDecl* declaration);

		// The base type at the start of the line shared by all the declarations.
		owning_ptr<ASTDataType> baseType;

	private:
		// The list of individual data declarations.
		owning_vector<ASTDataDecl> declarations_;
	};

	// Declares a single variable or constant. May or may not be inside an
	// ASTDataDeclList.
	class ASTDataDecl : public ASTDecl
	{
	public:
		ASTDataDecl(LocationData const& location = LocationData::NONE);
		ASTDataDecl(ASTDataDecl const&);
		ASTDataDecl& operator=(ASTDataDecl const& rhs);
		ASTDataDecl* clone() const /*override*/ {return new ASTDataDecl(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {return TYPE_DATA;}

		ASTExpr* getInitializer() {return initializer_.get();}
		ASTExpr const* getInitializer() const {return initializer_.get();}
		void setInitializer(ASTExpr* initializer);

		// Resolves the type, using either the list's or this node's own base type
		// as appropriate.
		DataType const* resolveType(Scope* scope);

		// The list containing this declaration. Should be set by that list when
		// this is added.
		ASTDataDeclList* list;

		// Reference back to the datum manager for this node. Should be set by
		// that Datum when it is created.
		Datum* manager;

		// This type of this data (minus the extra arrays). This should only be
		// set if this declaration is not part of a list, as the list's base type
		// should be used instead in that case.
		owning_ptr<ASTDataType> baseType;

		// The symbol this declaration is binding.
		std::string name;

		// Extra array type for this specific declaration. The final type is the
		// list's base type combined with these.
		owning_vector<ASTDataDeclExtraArray> extraArrays;

	private:
		// The initialization expression. Optional.
		owning_ptr<ASTExpr> initializer_;
	};

	bool hasSize(ASTDataDecl const&);

	// The extra array parameters appended to a data declaration name.
	class ASTDataDeclExtraArray : public AST
	{
	public:
		ASTDataDeclExtraArray(LocationData const& location = LocationData::NONE);
		ASTDataDeclExtraArray* clone() const /*override*/ {
			return new ASTDataDeclExtraArray(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		// The vector of array dimensions. Empty means unspecified.
		owning_vector<ASTExpr> dimensions;

		// If this declares an a sized array.
		bool hasSize() const {return (dimensions.size());}

		// Get the total size of this array at compile time.
		optional<int> getCompileTimeSize(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTDataTypeDef : public ASTDecl
	{
	public:
		ASTDataTypeDef(ASTDataType* type = NULL,
		           std::string const& name = "",
		           LocationData const& location = LocationData::NONE);
		ASTDataTypeDef* clone() const /*override*/ {
			return new ASTDataTypeDef(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {return TYPE_DATATYPE;}

		owning_ptr<ASTDataType> type;
		std::string name;
	};

	class ASTScriptTypeDef : public ASTDecl
	{
	public:
		ASTScriptTypeDef(
			ASTScriptType* oldType,
			std::string const& newName,
			LocationData const& location = LocationData::NONE);
		ASTScriptTypeDef* clone() const /*override*/ {
			return new ASTScriptTypeDef(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;

		Type getDeclarationType() const /*override*/ {
			return TYPE_SCRIPTTYPE;}

		owning_ptr<ASTScriptType> oldType;
		std::string newName;
	};

	////////////////////////////////////////////////////////////////
	// Expressions

	class ASTExpr : public ASTStmt
	{
	public:
		ASTExpr(LocationData const& location = LocationData::NONE);
		virtual ASTExpr* clone() const = 0;

		virtual bool isConstant() const = 0;

		// Return this expression's value if it has already been resolved at
		// compile time.
		virtual optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const
		{return nullopt;}

		// Returns the read or write type for this expression. Null for either
		// means that it can't be read from/written to.
		virtual DataType const* getReadType() const {return NULL;}
		virtual DataType const* getWriteType() const {return NULL;}
	};

	// Wrap around an expression to type it as constant.
	class ASTExprConst : public ASTExpr
	{
	public:
		ASTExprConst(ASTExpr* content = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTExprConst* clone() const {return new ASTExprConst(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return true;}

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {
			return content ? content->getReadType() : NULL;}
		DataType const* getWriteType() const {return NULL;}
	
		owning_ptr<ASTExpr> content;
	};

	class ASTExprAssign : public ASTExpr
	{
	public:
		ASTExprAssign(ASTExpr* left = NULL,
		              ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprAssign* clone() const {return new ASTExprAssign(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return right && right->isConstant();}

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {
			return right ? right->getReadType() : NULL;}
		DataType const* getWriteType() const {
			return right ? right->getWriteType() : NULL;}
	
		owning_ptr<ASTExpr> left;
		owning_ptr<ASTExpr> right;
	};

	class ASTExprIdentifier : public ASTExpr
	{
	public:
		ASTExprIdentifier(std::string const& name = "",
		                  LocationData const& location = LocationData::NONE);
		ASTExprIdentifier* clone() const {return new ASTExprIdentifier(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
		std::string asString() const;
		bool isTypeIdentifier() const {return true;}

		bool isConstant() const {return constant_;}
		void markConstant() {constant_ = true;}

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const;
		DataType const* getWriteType() const;
	
		// The identifier components separated by '.'.
		std::vector<std::string> components;

		// What this identifier refers to.
		Datum* binding;
		
	private:
		bool constant_;
	};

	class ASTExprArrow : public ASTExpr
	{
	public:
		ASTExprArrow(ASTExpr* left = NULL,
		             std::string const& right = "",
		             LocationData const& location = LocationData::NONE);
		ASTExprArrow* clone() const {return new ASTExprArrow(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);
		std::string asString() const;
		bool isTypeArrow() const {return true;}

		bool isConstant() const {return false;}

		DataType const* getReadType() const;
		DataType const* getWriteType() const;
	
		owning_ptr<ASTExpr> left;
		std::string right;
		owning_ptr<ASTExpr> index;

		ZClass* leftClass;
		Function* readFunction;
		Function* writeFunction;
	};

	class ASTExprIndex : public ASTExpr
	{
	public:
		ASTExprIndex(ASTExpr* array = NULL,
		             ASTExpr* index = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTExprIndex* clone() const /*override*/ {
			return new ASTExprIndex(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL) /*override*/;
		bool isTypeIndex() const /*override*/ {return true;}
    
		bool isConstant() const /*override*/;

		DataType const* getReadType() const /*override*/;
		DataType const* getWriteType() const /*override*/;
	
		owning_ptr<ASTExpr> array;
		owning_ptr<ASTExpr> index;
	};

	class ASTExprCall : public ASTExpr
	{
	public:
		ASTExprCall(LocationData const& location = LocationData::NONE);
		ASTExprCall* clone() const {return new ASTExprCall(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return false;}

		DataType const* getReadType() const;
		DataType const* getWriteType() const;
	
		owning_ptr<ASTExpr> left;
		owning_vector<ASTExpr> parameters;

		Function* binding;
	};

	// virtual
	class ASTUnaryExpr : public ASTExpr
	{
	public:
		ASTUnaryExpr(LocationData const& location = LocationData::NONE);
		virtual ASTUnaryExpr* clone() const = 0;

		virtual bool isConstant() const {return operand->isConstant();}

		owning_ptr<ASTExpr> operand;
	};

	class ASTExprNegate : public ASTUnaryExpr
	{
	public:
		ASTExprNegate(LocationData const& location = LocationData::NONE);
		ASTExprNegate* clone() const {return new ASTExprNegate(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprNot : public ASTUnaryExpr
	{
	public:
		ASTExprNot(LocationData const& location = LocationData::NONE);
		ASTExprNot* clone() const {return new ASTExprNot(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {return &DataType::BOOL;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprBitNot : public ASTUnaryExpr
	{
	public:
		ASTExprBitNot(LocationData const& location = LocationData::NONE);
		ASTExprBitNot* clone() const {return new ASTExprBitNot(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprIncrement : public ASTUnaryExpr
	{
	public:
		ASTExprIncrement(LocationData const& location = LocationData::NONE);
		ASTExprIncrement* clone() const {return new ASTExprIncrement(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return false;}

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {
			return operand ? operand->getWriteType() : NULL;}
	};

	class ASTExprPreIncrement : public ASTUnaryExpr
	{
	public:
		ASTExprPreIncrement(LocationData const& location = LocationData::NONE);
		ASTExprPreIncrement* clone() const {return new ASTExprPreIncrement(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return false;}

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {
			return operand ? operand->getWriteType() : NULL;}
	};

	class ASTExprDecrement : public ASTUnaryExpr
	{
	public:
		ASTExprDecrement(LocationData const& location = LocationData::NONE);
		ASTExprDecrement* clone() const {return new ASTExprDecrement(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return false;}

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {
			return operand ? operand->getWriteType() : NULL;}
	};

	class ASTExprPreDecrement : public ASTUnaryExpr
	{
	public:
		ASTExprPreDecrement(LocationData const& location = LocationData::NONE);
		ASTExprPreDecrement* clone() const {
			return new ASTExprPreDecrement(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return false;}

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {
			return operand ? operand->getWriteType() : NULL;}
	};

	// virtual
	class ASTBinaryExpr : public ASTExpr
	{
	public:
		ASTBinaryExpr(ASTExpr* left = NULL,
		              ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		virtual ASTBinaryExpr* clone() const = 0;

		bool isConstant() const;

		owning_ptr<ASTExpr> left;
		owning_ptr<ASTExpr> right;

	protected:
		ASTBinaryExpr& operator=(ASTBinaryExpr const& rhs);
	};

	// virtual
	class ASTLogExpr : public ASTBinaryExpr
	{
	public:
		ASTLogExpr(ASTExpr* left = NULL,
		           ASTExpr* right = NULL,
		           LocationData const& location = LocationData::NONE);
		virtual ASTLogExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::BOOL;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprAnd : public ASTLogExpr
	{
	public:
		ASTExprAnd(ASTExpr* left = NULL,
		           ASTExpr* right = NULL,
		           LocationData const& location = LocationData::NONE);
		ASTExprAnd* clone() const {return new ASTExprAnd(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprOr : public ASTLogExpr
	{
	public:
		ASTExprOr(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprOr* clone() const {return new ASTExprOr(*this);}
    
		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	// virtual
	class ASTRelExpr : public ASTBinaryExpr
	{
	public:
		ASTRelExpr(ASTExpr* left = NULL,
		           ASTExpr* right = NULL,
		           LocationData const& location = LocationData::NONE);
		virtual ASTRelExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::BOOL;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprGT : public ASTRelExpr
	{
	public:
		ASTExprGT(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprGT* clone() const {return new ASTExprGT(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprGE : public ASTRelExpr
	{
	public:
		ASTExprGE(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprGE* clone() const {return new ASTExprGE(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprLT : public ASTRelExpr
	{
	public:
		ASTExprLT(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprLT* clone() const {return new ASTExprLT(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprLE : public ASTRelExpr
	{
	public:
		ASTExprLE(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprLE* clone() const {return new ASTExprLE(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprEQ : public ASTRelExpr
	{
	public:
		ASTExprEQ(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprEQ* clone() const {return new ASTExprEQ(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprNE : public ASTRelExpr
	{
	public:
		ASTExprNE(ASTExpr* left = NULL,
		          ASTExpr* right = NULL,
		          LocationData const& location = LocationData::NONE);
		ASTExprNE* clone() const {return new ASTExprNE(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	// virtual
	class ASTAddExpr : public ASTBinaryExpr
	{
	public:
		ASTAddExpr(ASTExpr* left = NULL,
		           ASTExpr* right = NULL,
		           LocationData const& location = LocationData::NONE);
		virtual ASTAddExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprPlus : public ASTAddExpr
	{
	public:
		ASTExprPlus(ASTExpr* left = NULL,
		            ASTExpr* right = NULL,
		            LocationData const& location = LocationData::NONE);
		ASTExprPlus* clone() const {return new ASTExprPlus(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprMinus : public ASTAddExpr
	{
	public:
		ASTExprMinus(ASTExpr* left = NULL,
		             ASTExpr* right = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTExprMinus* clone() const {return new ASTExprMinus(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	// virtual
	class ASTMultExpr : public ASTBinaryExpr
	{
	public:
		ASTMultExpr(ASTExpr* left = NULL,
		            ASTExpr* right = NULL,
		            LocationData const& location = LocationData::NONE);
		virtual ASTMultExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprTimes : public ASTMultExpr
	{
	public:
		ASTExprTimes(ASTExpr* left = NULL,
		             ASTExpr* right = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTExprTimes* clone() const {return new ASTExprTimes(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprDivide : public ASTMultExpr
	{
	public:
		ASTExprDivide(ASTExpr* left = NULL,
		              ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprDivide* clone() const {return new ASTExprDivide(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprModulo : public ASTMultExpr
	{
	public:
		ASTExprModulo(ASTExpr* left = NULL,
		              ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprModulo* clone() const {return new ASTExprModulo(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	// virtual
	class ASTBitExpr : public ASTBinaryExpr
	{
	public:
		ASTBitExpr(ASTExpr* left = NULL, ASTExpr* right = NULL,
		           LocationData const& location = LocationData::NONE);
		virtual ASTBitExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprBitAnd : public ASTBitExpr
	{
	public:
		ASTExprBitAnd(ASTExpr* left = NULL, ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprBitAnd* clone() const {return new ASTExprBitAnd(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprBitOr : public ASTBitExpr
	{
	public:
		ASTExprBitOr(ASTExpr* left = NULL, ASTExpr* right = NULL,
		             LocationData const& location = LocationData::NONE);
		ASTExprBitOr* clone() const {return new ASTExprBitOr(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprBitXor : public ASTBitExpr
	{
	public:
		ASTExprBitXor(ASTExpr* left = NULL, ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprBitXor* clone() const {return new ASTExprBitXor(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	// virtual
	class ASTShiftExpr : public ASTBinaryExpr
	{
	public:
		ASTShiftExpr(
				ASTExpr* left = NULL, ASTExpr* right = NULL,
				LocationData const& location = LocationData::NONE);
		virtual ASTShiftExpr* clone() const = 0;

		DataType const* getReadType() const {return &DataType::FLOAT;}
		DataType const* getWriteType() const {return NULL;}
	};

	class ASTExprLShift : public ASTShiftExpr
	{
	public:
		ASTExprLShift(ASTExpr* left = NULL, ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprLShift* clone() const {return new ASTExprLShift(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};

	class ASTExprRShift : public ASTShiftExpr
	{
	public:
		ASTExprRShift(ASTExpr* left = NULL, ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTExprRShift* clone() const {return new ASTExprRShift(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
	};
	
	class ASTTernaryExpr : public ASTExpr
	{
	public:
		ASTTernaryExpr(ASTExpr* left = NULL,
		              ASTExpr* middle = NULL,
		              ASTExpr* right = NULL,
		              LocationData const& location = LocationData::NONE);
		ASTTernaryExpr* clone() const {return new ASTTernaryExpr(*this);};

		bool isConstant() const;

		void execute(ASTVisitor& visitor, void* param = NULL);

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;

		owning_ptr<ASTExpr> left;
		owning_ptr<ASTExpr> middle;
		owning_ptr<ASTExpr> right;

		DataType const* getReadType() const {return middle->getReadType();}
		DataType const* getWriteType() const {return NULL;}
	};

	// Literals

	// virtual
	class ASTLiteral : public ASTExpr
	{
	public:
		ASTLiteral(LocationData const& location = LocationData::NONE);
		virtual ASTLiteral* clone() const = 0;

		DataType const* getWriteType() const {return NULL;}

		Literal* manager;
	};

	class ASTNumberLiteral : public ASTLiteral
	{
	public:
		ASTNumberLiteral(
				ASTFloat* value = NULL,
				LocationData const& location = LocationData::NONE);
		ASTNumberLiteral* clone() const {return new ASTNumberLiteral(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return true;}

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const;
		DataType const* getReadType() const {return &DataType::FLOAT;}
	
		owning_ptr<ASTFloat> value;
	};

	class ASTBoolLiteral : public ASTLiteral
	{
	public:
		ASTBoolLiteral(
				bool value = false,
				LocationData const& location = LocationData::NONE);
		ASTBoolLiteral* clone() const {return new ASTBoolLiteral(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		bool isConstant() const {return true;}

		optional<long> getCompileTimeValue(
				CompileErrorHandler* errorHandler = NULL)
				const {
			return value ? 10000L : 0L;}
		DataType const* getReadType() const {return &DataType::BOOL;}
	
		bool value;
	};

	class ASTStringLiteral : public ASTLiteral
	{
	public:
		ASTStringLiteral(
				char const* str = "",
				LocationData const& location = LocationData::NONE);
		ASTStringLiteral(
				std::string const& str,
				LocationData const& location = LocationData::NONE);
		ASTStringLiteral(ASTString const& raw);
		ASTStringLiteral(ASTStringLiteral const& base);
		ASTStringLiteral& operator=(ASTStringLiteral const& rhs);
		ASTStringLiteral* clone() const /*override*/ {
			return new ASTStringLiteral(*this);}

		void execute (ASTVisitor& visitor, void* param = NULL) /*override*/;
		bool isStringLiteral() const /*override*/ {return true;}

		bool isConstant() const /*override*/ {return true;}

		DataTypeArray const* getReadType() const /*override*/;
		
		// The data declaration that this literal may be part of. If NULL that
		// means this is not part of a data declaration. This should be managed by
		// that declaration and not modified by this object at all.
		ASTDataDecl* declaration;

		std::string value;
	};

	class ASTArrayLiteral : public ASTLiteral
	{
	public:
		ASTArrayLiteral(LocationData const& location = LocationData::NONE);
		ASTArrayLiteral(ASTArrayLiteral const& base);
		ASTArrayLiteral& operator=(ASTArrayLiteral const& rhs);
		ASTArrayLiteral* clone() const {return new ASTArrayLiteral(*this);}

		void execute (ASTVisitor& visitor, void* param = NULL);
		bool isArrayLiteral() const {return true;}

		bool isConstant() const {return true;}

		DataTypeArray const* getReadType() const {return readType_;}
		void setReadType(DataTypeArray const* type) {readType_ = type;}

		// The data declaration that this literal may be part of. If NULL that
		// means this is not part of a data declaration. This should be managed by
		// that declaration and not modified by this object at all.
		ASTDataDecl* declaration;

		// Optional type specification.
		owning_ptr<ASTDataType> type;
		// Optional size specification.
		owning_ptr<ASTExpr> size;
		// The array elements.
		owning_vector<ASTExpr> elements;

	private:
		// Cached read type.
		DataTypeArray const* readType_;
	};

	class ASTOptionValue : public ASTLiteral
	{
	public:
		ASTOptionValue(std::string const& name = "",
		               LocationData const& location = LocationData::NONE);
		ASTOptionValue* clone() const {return new ASTOptionValue(*this);}

		virtual void execute(ASTVisitor& visitor, void* param = NULL);
		virtual std::string asString() const;

		virtual bool isConstant() const {return true;}

		virtual DataType const* getReadType() const {
			return &DataType::FLOAT;}

		std::string name;
		CompileOption option;
		optional<long> value;
	};

	// Types

	class ASTScriptType : public AST
	{
	public:
		ASTScriptType(ScriptType type, LocationData const& location);
		ASTScriptType(std::string const& name, LocationData const& location);
		ASTScriptType* clone() const {return new ASTScriptType(*this);}

		void execute(ASTVisitor& visitor, void* param = NULL);

		// If type is invalid, try to resolve using name.
		ScriptType type;
		std::string name;
	};

	ScriptType resolveScriptType(ASTScriptType const&, Scope const&);

	class ASTDataType : public AST
	{
	public:
		// Takes ownership of type.
		ASTDataType(
				DataType* type = NULL,
				LocationData const& location = LocationData::NONE);
		// Clones type.
		ASTDataType(
				DataType const& type,
				LocationData const& location = LocationData::NONE);
		ASTDataType* clone() const {return new ASTDataType(*this);}
	
		void execute(ASTVisitor& visitor, void* param = NULL);

		DataType const& resolve(Scope& scope);

		owning_ptr<DataType> type;
	};
}

#endif

