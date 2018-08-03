#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_INPUT
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,                 rettype,type,		var,            num,    params
		{ "GetType",		tFlt,	FUNCTION,	0,		1,	P1(	tFlt		) },
		{ "SetType",		tVoid,	FUNCTION,	0,		1,	P2(	tFlt,	tFlt	) },
		{ "getJoypad[]",	tFlt,	GETTER,		JOYPADPRESS,	18,	P1(	tFlt		) },
		{ "getPress[]",		tBool,	GETTER,		BUTTONPRESS,	18,	P1(	tFlt		) },
		{ "setPress[]",		tVoid,	SETTER,		BUTTONPRESS,	18,	P2(	tBool,	tFlt	) },
		{ "getButton[]",	tBool,	GETTER,		BUTTONINPUT,	18,	P1(	tFlt		) },
		{ "setButton[]",	tVoid,	SETTER,		BUTTONINPUT,	18,	P2(	tBool,	tFlt	) },
		{ "getHold[]",		tBool,	GETTER,		BUTTONHELD,	18,	P1(	tFlt		) },
		{ "setHold[]",		tVoid,	SETTER,		BUTTONHELD,	18,	P2(	tBool,	tFlt	) },
		{ "getReadKey[]",	tBool,	GETTER,		READKEY,	127,	P1(	tFlt		) },
		{ "getKey[]",		tBool,	GETTER,		KEYPRESS,	127,	P1(	tFlt		) },
		{ "setKey[]",		tVoid,	SETTER,		KEYPRESS,	127,	P2(	tBool,	tFlt	) },
		{ "getMouse[]",		tFlt,	GETTER,		MOUSEARR,	6,	P1(	tFlt		) },
		{ "setMouse[]",		tVoid,	SETTER,		MOUSEARR,	6,	P2(	tFlt,	tFlt	) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Input& Library::Input::instance()
{
	static Library::Input instance(NUL, table);
	return instance;
}

void Library::Input::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// float GetType(float)
	{
		int id = memberids["GetType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataType(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetType(float, float)
	{
		int id = memberids["SetType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataType(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
