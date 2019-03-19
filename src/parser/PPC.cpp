#include "PPC.h"

using namespace ZScript;

// PPC
void PPC::execute(ASTVisitor& visitor, void* param){}

//PPCDefine
void PPCDefine::replace(ASTString* str)
{
	owning_vector<ASTString> params = parameters.get()->getList();
	if(params.empty())
	{
		str->replace(identifier.get()->getValue(), definition.get()->getValue());
	}
	else
	{
		ASTString* def = definition.get()->clone();
		ASTString* iden = identifier.get()->clone();
		
		//Want to replace "def", the definition, to give it the parameters; replace each param in `parameters` when found in the text.
		//Originally done for regex using capture groups (easy way). Except regex doesn't work, so, time for hard way.
		
		/* Couldn't get regex working!
		iden->append("[ \t\r]*\\([ \t\r]*");
		bool first = true;
		int i = 0;
		for (vector<ASTString*>::iterator it2 = params.begin();
			 it2 != params.end(); ++it2)
		{
			ASTString param = **it2;
			if(first) first = false;
			else iden->append(",[ \t\r]*");
			iden->append("([_a-zA-Z][_a-zA-Z0-9]*)[ \t\r]*");
			std::stringstream temp;
			temp << "$" << ++i;
			def->replace(param.getValue(), temp.str());
		}
		iden->append("\\)");
		str->regexreplace(iden->getValue(), def->getValue());*/
		
		
	}
}

//PPCIdentifierList
void PPCIdentifierList::push_back(ASTString* str)
{
	identifiers.push_back(str);
}