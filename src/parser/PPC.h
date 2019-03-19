#ifndef ZSCRIPT_PPC_H
#define ZSCRIPT_PPC_H

namespace ZScript
{
	class PPC : public AST
	{
	public:
		PPC(LocationData const& location = LocationData::NONE)
			: AST(location)
		{}
		
		PPC* clone() const {return new PPC(*this);}
	
		void execute(ASTVisitor& visitor, void* param = NULL);
	};
	
	class PPCIdentifierList : public PPC
	{
	public:
		PPCIdentifierList(LocationData const& location = LocationData::NONE)
			: PPC(location)
		{}
		
		PPCIdentifierList* clone() const {return new PPCIdentifierList(*this);}
		
		void push_back(ASTString* str);
		owning_vector<ASTString> getList() {return identifiers;}
		
		owning_vector<ASTString> identifiers;
	};
	
	class PPCDefine : public PPC
	{
	public:
		PPCDefine(ASTString* iden, ASTString* defn, LocationData const& location = LocationData::NONE)
			: identifier(iden), definition(defn), PPC(location)
		{}
		
		PPCDefine(ASTString* iden, ASTString* defn, PPCIdentifierList* params, LocationData const& location = LocationData::NONE)
			: identifier(iden), definition(defn), parameters(params), PPC(location)
		{}
		
		PPCDefine* clone() const {return new PPCDefine(*this);}
		void replace(ASTString* str);
		
		owning_ptr<ASTString> identifier;
		owning_ptr<ASTString> definition;
		owning_ptr<PPCIdentifierList> parameters;
	};
}

#endif