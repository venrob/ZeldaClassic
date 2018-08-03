#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_SPRITEDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	name,           rettype,        type,		var,			num,    params
		// All of these return a function label error when used:
	//	{ "GetTile",    tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "GetMisc",    tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "GetCSets",   tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "GetFrames",  tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "GetSpeed",   tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "GetType",    tFlt,		FUNCTION,	0,			1,      P1(	tFlt		) },
	//	{ "SetTile",    tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
	//	{ "SetMisc",    tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
	//	{ "SetCSets",   tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
	//	{ "SetFrames",  tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
	//	{ "SetSpeed",   tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
	//	{ "SetType",    tVoid,		FUNCTION,	0,			1,      P2(	tFlt,	tFlt	) },
		// Datatype variables spritedata sd->Var;					                            
		{ "getTile",    tFlt,		GETTER,		SPRITEDATATILE,         1,      P0			  },
		{ "setTile",    tVoid,          SETTER,		SPRITEDATATILE,         1,      P1(	tFlt		) },
		{ "getMisc",    tFlt,		GETTER,		SPRITEDATAMISC,         1,      P0			  },
		{ "setMisc",    tVoid,          SETTER,		SPRITEDATAMISC,         1,      P1(	tFlt		) },
		{ "getCSet",    tFlt,		GETTER,		SPRITEDATACSETS,        1,      P0			  },
		{ "setCSet",    tVoid,          SETTER,		SPRITEDATACSETS,        1,      P1(	tFlt		) },
		{ "getFrames",  tFlt,		GETTER,		SPRITEDATAFRAMES,       1,      P0			  },
		{ "setFrames",  tVoid,          SETTER,		SPRITEDATAFRAMES,       1,      P1(	tFlt		) },
		{ "getSpeed",   tFlt,		GETTER,		SPRITEDATASPEED,        1,      P0			  },
		{ "setSpeed",   tVoid,          SETTER,		SPRITEDATASPEED,        1,      P1(	tFlt		) },
		{ "getType",    tFlt,		GETTER,		SPRITEDATATYPE,         1,      P0			  },
		{ "setType",    tVoid,          SETTER,		SPRITEDATATYPE,         1,      P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"	
}

Library::Sprite& Library::Sprite::instance()
{
	static Library::Sprite instance(REFSPRITEDATA, table);
	return instance;
}

void Library::Sprite::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// float GetTile()
	{
		int id = memberids["GetTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataTile(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetTile(float)
	{
		int id = memberids["SetTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataTile(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetMisc()
	{
		int id = memberids["GetMisc"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataMisc(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetMisc(float)
	{
		int id = memberids["SetMisc"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataMisc(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetCSet()
	{
		int id = memberids["GetCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataCSets(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetCSet(float)
	{
		int id = memberids["SetCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataCSets(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetFrames()
	{
		int id = memberids["GetFrames"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataFrames(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetFrames(float)
	{
		int id = memberids["SetFrames"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataFrames(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetSpeed()
	{
		int id = memberids["GetSpeed"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSDataSpeed(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSpeed(float)
	{
		int id = memberids["SetSpeed"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSSetDataSpeed(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetType()
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

	// void SetType(float)
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
