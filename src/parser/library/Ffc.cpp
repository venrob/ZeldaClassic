#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_FFC
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	  name,			    rettype,	type,		var,		num,	params
		{ "getData",		    tFlt,	GETTER,		DATA,		1,	P0			  },
		{ "setData",		    tVoid,	SETTER,		DATA,		1,	P1(	tFlt		) },
		{ "getScript",		    tFlt,	GETTER,		FFSCRIPT,	1,	P0			  },
		{ "setScript",		    tVoid,	SETTER,		FFSCRIPT,	1,	P1(	tFlt		) },
		{ "getCSet",		    tFlt,	GETTER,		FCSET,		1,	P0			  },
		{ "setCSet",		    tVoid,	SETTER,		FCSET,		1,	P1(	tFlt		) },
		{ "getDelay",		    tFlt,	GETTER,		DELAY,		1,	P0			  },
		{ "setDelay",		    tVoid,	SETTER,		DELAY,		1,	P1(	tFlt		) },
		{ "getX",		    tFlt,	GETTER,		FX,		1,	P0			  },
		{ "setX",		    tVoid,	SETTER,		FX,		1,	P1(	tFlt		) },
		{ "getY",		    tFlt,	GETTER,		FY,		1,	P0			  },
		{ "setY",		    tVoid,	SETTER,		FY,		1,	P1(	tFlt		) },
		{ "getVx",		    tFlt,	GETTER,		XD,		1,	P0			  },
		{ "setVx",		    tVoid,	SETTER,		XD,		1,	P1(	tFlt		) },
		{ "getVy",		    tFlt,	GETTER,		YD,		1,	P0			  },
		{ "setVy",		    tVoid,	SETTER,		YD,		1,	P1(	tFlt		) },
		{ "getAx",		    tFlt,	GETTER,		XD2,		1,	P0			  },
		{ "setAx",		    tVoid,	SETTER,		XD2,		1,	P1(	tFlt		) },
		{ "getAy",		    tFlt,	GETTER,		YD2,		1,	P0			  },
		{ "setAy",		    tVoid,	SETTER,		YD2,		1,	P1(	tFlt		) },
	//	{ "WasTriggered",	    tBool,	FUNCTION,	0,		1,	P0			  },
		{ "getFlags[]",		    tBool,	GETTER,		FFFLAGSD,	2,	P1(	tFlt		) },
		{ "setFlags[]",		    tVoid,	SETTER,		FFFLAGSD,	2,	P2(	tFlt,	tBool	) },
		{ "getTileWidth",	    tFlt,	GETTER,		FFTWIDTH,	1,	P0			  },
		{ "setTileWidth",	    tVoid,	SETTER,		FFTWIDTH,	1,	P1(	tFlt		) },
		{ "getTileHeight",	    tFlt,	GETTER,		FFTHEIGHT,	1,	P0			  },
		{ "setTileHeight",	    tVoid,	SETTER,		FFTHEIGHT,	1,	P1(	tFlt		) },
		{ "getEffectWidth",	    tFlt,	GETTER,		FFCWIDTH,	1,	P0			  },
		{ "setEffectWidth",	    tVoid,	SETTER,		FFCWIDTH,	1,	P1(	tFlt		) },
		{ "getEffectHeight",	    tFlt,	GETTER,		FFCHEIGHT,	1,	P0			  },
		{ "setEffectHeight",	    tVoid,	SETTER,		FFCHEIGHT,	1,	P1(	tFlt		) },
		{ "getLink",		    tFlt,	GETTER,		FFLINK,		1,	P0			  },
		{ "setLink",		    tVoid,	SETTER,		FFLINK,		1,	P1(	tFlt		) },
		{ "getMisc[]",		    tAny,	GETTER,		FFMISCD,	16,	P1(	tFlt		) },
		{ "setMisc[]",		    tVoid,	SETTER,		FFMISCD,	16,	P2(	tFlt,	tAny	) },
		{ "getInitD[]",		    tAny,	GETTER,		FFINITDD,	8,	P1(	tFlt		) },
		{ "setInitD[]",		    tVoid,	SETTER,		FFINITDD,	8,	P2(	tFlt,	tAny	) },
	//	{ "getD[]",		    tFlt,	GETTER,		FFDD,		8,	P1(	tFlt		) },
	//	{ "setD[]",		    tVoid,	SETTER,		FFDD,		8,	P2(	tFlt,	tFlt	) },
		{ "getID",		    tFlt,	GETTER,		FFCID,		1,	P0			  },
		{ "setID",		    tVoid,	SETTER,		FFCID,		1,	P1(	tFlt		) },
		{ "ChangeFFCScript",	    tVoid,	SETTER,		FFCID,		1,	P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Ffc& Library::Ffc::instance()
{
	static Library::Ffc instance(REFFFC, table);
	return instance;
}

void Library::Ffc::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	/*
	// bool WasTriggered()
	{
		int id = memberids["WasTriggered"];
		int label  = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop ffc
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//if ffc = -1, it is "this"
		int thislabel = ScriptParser::getUniqueLabelID();
		code.push_back(new OCompareImmediate(new VarArgument(EXP2), new LiteralArgument(-1)));
		code.push_back(new OGotoTrueImmediate(new LabelArgument(thislabel)));
		//if not this
		//NOT POSSIBLE YET
		//QUIT
		code.push_back(new OQuit());
		//if "this"
		code.push_back(new OCheckTrig());
		int truelabel = ScriptParser::getUniqueLabelID();
		code.push_back(new OGotoTrueImmediate(new LabelArgument(truelabel)));
		code.push_back(new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(0)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		Opcode *next = new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(1));
		next->setLabel(truelabel);
		code.push_back(next);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	*/

	// void ChangeFFCScript(int)
	{
		int id = memberids["ChangeFFCScript"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OChangeFFCScriptRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
