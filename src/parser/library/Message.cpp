#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_ZMESSAGE
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,			rettype,	type,		var,			num,	params
		// All of these return a function label error when used:
		{ "Get",		tVoid,		FUNCTION,	0,			1,	P1(	tFlt	) },
		{ "Set",		tVoid,		FUNCTION,	0,			1,	P1(	tFlt	) },

		{ "getNext",		tFlt,		GETTER,		MESSAGEDATANEXT,	1,	P0		  },
		{ "setNext",		tVoid,		SETTER,		MESSAGEDATANEXT,	1,	P1(	tFlt	) },
		{ "getTile",		tFlt,		GETTER,		MESSAGEDATATILE,	1,	P0		  },
		{ "setTile",		tVoid,		SETTER,		MESSAGEDATATILE,	1,	P1(	tFlt	) },
		{ "getCSet",		tFlt,		GETTER,		MESSAGEDATACSET,	1,	P0		  },
		{ "setCSet",		tVoid,		SETTER,		MESSAGEDATACSET,	1,	P1(	tFlt	) },
		{ "getTransparent",	tBool,		GETTER,		MESSAGEDATATRANS,	1,	P0		  },
		{ "setPransparent",	tVoid,		SETTER,		MESSAGEDATATRANS,	1,	P1(	tBool	) },
		{ "getFont",		tFlt,		GETTER,		MESSAGEDATAFONT,	1,	P0		  },
		{ "setFont",		tVoid,		SETTER,		MESSAGEDATAFONT,	1,	P1(	tFlt	) },
		{ "getX",		tFlt,		GETTER,		MESSAGEDATAX,		1,	P0		  },
		{ "setX",		tVoid,		SETTER,		MESSAGEDATAX,		1,	P1(	tFlt	) },
		{ "getY",		tFlt,		GETTER,		MESSAGEDATAY,		1,	P0		  },
		{ "setY",		tVoid,		SETTER,		MESSAGEDATAY,		1,	P1(	tFlt	) },
		{ "getWidth",		tFlt,		GETTER,		MESSAGEDATAW,		1,	P0		  },
		{ "setWidth",		tVoid,		SETTER,		MESSAGEDATAW,		1,	P1(	tFlt	) },
		{ "getHeight",		tFlt,		GETTER,		MESSAGEDATAH,		1,	P0		  },
		{ "setHeight",		tVoid,		SETTER,		MESSAGEDATAH,		1,	P1(	tFlt	) },
		{ "getSound",		tFlt,		GETTER,		MESSAGEDATASFX,		1,	P0		  },
		{ "setSound",		tVoid,		SETTER,		MESSAGEDATASFX,		1,	P1(	tFlt	) },
		{ "getListPosition",	tFlt,		GETTER,		MESSAGEDATALISTPOS,	1,	P0		  },
		{ "setListPosition",	tVoid,		SETTER,		MESSAGEDATALISTPOS,	1,	P1(	tFlt	) },
		{ "getVSpace",		tFlt,		GETTER,		MESSAGEDATAVSPACE,	1,	P0		  },
		{ "setVSpace",		tVoid,		SETTER,		MESSAGEDATAVSPACE,	1,	P1(	tFlt	) },
		{ "getHSpace",		tFlt,		GETTER,		MESSAGEDATAHSPACE,	1,	P0		  },
		{ "setHSpace",		tVoid,		SETTER,		MESSAGEDATAHSPACE,	1,	P1(	tFlt	) },
		{ "getFlags",		tFlt,		GETTER,		MESSAGEDATAFLAGS,	1,	P0		  },
		{ "setFlags",		tVoid,		SETTER,		MESSAGEDATAFLAGS,	1,	P1(	tFlt	) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Message& Library::Message::instance()
{
	static Library::Message instance(REFMSGDATA, table);
	return instance;
}

void Library::Message::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// void Get(float output_string)
	{	
		int id = memberids["Get"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new OMessageDataSetStringRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	//void Set(float string)
	{	
		int id = memberids["Set"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new OMessageDataSetStringRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
