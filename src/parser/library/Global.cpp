#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	include "EntryHelper.h"
	
	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//    	  name,				rettype,	type,		var,	num,	params
		{ "Rand",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Quit",			tVoid,		FUNCTION,	0,	1,	P0													  },
		{ "Waitframe",			tVoid,		FUNCTION,	0,	1,	P0													  },
		{ "Waitdraw",			tVoid,		FUNCTION,	0,	1,	P0													  },
		{ "Trace",			tVoid,		FUNCTION,	0,	1,	P1(	tAny												) },
		{ "TraceB",			tVoid,		FUNCTION,	0,	1,	P1(	tBool												) },
		{ "TraceS",			tVoid,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "TraceNL",			tVoid,		FUNCTION,	0,	1,	P0													  },
		{ "ClearTrace",			tVoid,		FUNCTION,	0,	1,	P0													  },
		{ "TraceToBase",		tVoid,		FUNCTION,	0,	1,	P3(	tFlt,	tFlt,	tFlt										) },
		{ "Sin",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Cos",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Tan",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "ArcTan",			tFlt,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "ArcSin",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "ArcCos",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "RadianSin",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "RadianCos",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "RadianTan",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Max",			tFlt,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "Min",			tFlt,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "Pow",			tFlt,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "InvPow",			tFlt,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "Factorial",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Abs",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Log10",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Ln",				tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "Sqrt",			tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
	//	{ "CalculateSpline",		tFlt,		FUNCTION,	0,	1,	P7(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt						) },
	//	{ "CollisionRect",		tBool,		FUNCTION,	0,	1,	P8(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt					) },
	//	{ "CollisionBox",		tBool,		FUNCTION,	0,	1,	P12(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "CopyTile",			tVoid,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "SwapTile",			tVoid,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "ClearTile",			tVoid,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "GetScriptRAM",		tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "SetScriptRAM",		tVoid,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "GetGlobalRAM",		tFlt,		FUNCTION,	0,	1,	P1(	tFlt												) },
		{ "SetGlobalRAM",		tVoid,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "SetColorBuffer",		tVoid,		FUNCTION,	0,	1,	P4(	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "SetDepthBuffer",		tVoid,		FUNCTION,	0,	1,	P4(	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "GetColorBuffer",		tVoid,		FUNCTION,	0,	1,	P4(	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "GetDepthBuffer",		tVoid,		FUNCTION,	0,	1,	P4(	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "SizeOfArray",		tFlt,		FUNCTION,	0,	1,	P1(	tAny												) },
		{ "SizeOfArrayBool",		tFlt,		FUNCTION,	0,	1,	P1(	tBool												) },
		{ "SizeOfArrayFFC",		tFlt,		FUNCTION,	0,	1,	P1(	tFfc												) },
		{ "SizeOfArrayItem",		tFlt,		FUNCTION,	0,	1,	P1(	tItm												) },
		{ "SizeOfArrayLWeapon",		tFlt,		FUNCTION,	0,	1,	P1(	tLW												) },
		{ "SizeOfArrayEWeapon",		tFlt,		FUNCTION,	0,	1,	P1(	tEW												) },
		{ "SizeOfArrayNPC",		tFlt,		FUNCTION,	0,	1,	P1(	tNpc												) },
		{ "SizeOfArrayItemdata",	tFlt,		FUNCTION,	0,	1,	P1(	tItmC												) },
		{ "OverlayTile",		tVoid,		FUNCTION,	0,	1,	P2(	tFlt,	tFlt											) },
		{ "NULL",			tAny,		FUNCTION,	0,	1,	P0													  },
	//	{ "Null",			tAny,		FUNCTION,	0,	1,	P1(	tAny												) },
		{ "Untype",			tAny,		FUNCTION,	0,	1,	P1(	tAny												) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Global& Library::Global::instance()
{
	static Library::Global instance(NUL, table);
    return instance;
}

namespace // file local
{
	int const radsperdeg = 572958;
}

void Library::Global::generateFunctionCode(
		LinkTable* linktable, std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
	int id;
	
	// float Rand(float maxval)
	{
		id = memberids["Rand"];
		int label  = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop maxval
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new ORandRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void Quit()
	{
		id = memberids["Quit"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OQuit());
		rval[label]=code;
	}
	
	// void Waitframe()
	{
		id = memberids["Waitframe"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OWaitframe();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Waitdraw()
	{
		id = memberids["Waitdraw"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OWaitdraw();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Trace(float val)
	{
		id = memberids["Trace"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OTraceRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void TraceB(bool val)
	{
		id = memberids["TraceB"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OTrace2Register(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void TraceS(bool val)
	{
		id = memberids["TraceS"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OTrace6Register(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void TraceNL()
	{
		id = memberids["TraceNL"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OTrace3();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void ClearTrace()
	{
		id = memberids["ClearTrace"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OTrace4();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void TraceToBase(float, float, float)
	{
		id = memberids["TraceToBase"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OTrace5Register();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float Sin(float val)
	{
		id = memberids["Sin"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OSinRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float RadianSin(float val)
	{
		id = memberids["RadianSin"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OMultImmediate(new VarArgument(EXP2), new LiteralArgument(radsperdeg)));
		code.push_back(new OSinRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float ArcSin(float val)
	{
		id = memberids["ArcSin"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArcSinRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float Cos(float val)
	{
		id = memberids["Cos"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OCosRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float RadianCos(float val)
	{
		id = memberids["RadianCos"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OMultImmediate(new VarArgument(EXP2), new LiteralArgument(radsperdeg)));
		code.push_back(new OCosRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float ArcCos(float val)
	{
		id = memberids["ArcCos"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArcCosRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float Tan(float val)
	{
		id = memberids["Tan"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OTanRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float ArcTan(float X, float Y)
	{
		id = memberids["ArcTan"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OATanRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float RadianTan(float val)
	{
		id = memberids["RadianTan"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OMultImmediate(new VarArgument(EXP2), new LiteralArgument(radsperdeg)));
		code.push_back(new OTanRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Max(float first, float second)
	{
		id = memberids["Max"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OMaxRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Min(float first, float second)
	{
		id = memberids["Min"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OMinRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Pow(float first, float second)
	{
		id = memberids["Pow"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPowRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float InvPow(float first, float second)
	{
		id = memberids["InvPow"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OInvPowRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Factorial(float val)
	{
		id = memberids["Factorial"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OFactorial(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Abs(float val)
	{
		id = memberids["Abs"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OAbsRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Log10(float val)
	{
		id = memberids["Log10"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OLog10Register(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Ln(float val)
	{
		id = memberids["Ln"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OLogERegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float Sqrt(float val)
	{
		id = memberids["Sqrt"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OSqrtRegister(new VarArgument(EXP1), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float CopyTile(float source, float dest)
	{
		id = memberids["CopyTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OCopyTileRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SwapTile(float first, float second)
	{
		id = memberids["SwapTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OSwapTileRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float SwapTile(float first, float second)
	{
		id = memberids["OverlayTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OOverlayTileRegister(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void ClearTile(float tile)
	{
		id = memberids["ClearTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OClearTileRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void GetGlobalRAM(float)
	{
		int id2 = memberids["GetGlobalRAM"];
		int label = lt.functionToLabel(id2);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(GLOBALRAMD)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetGlobalRAM(float, float)
	{
		int id2 = memberids["SetGlobalRAM"];
		int label = lt.functionToLabel(id2);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OSetRegister(new VarArgument(GLOBALRAMD), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void GetScriptRAM(float)
	{
		int id2 = memberids["GetScriptRAM"];
		int label = lt.functionToLabel(id2);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		//code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCRIPTRAMD)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScriptRAM(float, float)
	{
		int id2 = memberids["SetScriptRAM"];
		int label = lt.functionToLabel(id2);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OSetRegister(new VarArgument(SCRIPTRAMD), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetColorBuffer(float amount, float offset, float stride, float *ptr)
	{
		id = memberids["SetColorBuffer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetColorBufferRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void SetDepthBuffer(float amount, float offset, float stride, float *ptr)
	{
		id = memberids["SetDepthBuffer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetDepthBufferRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void GetColorBuffer(float amount, float offset, float stride, float *ptr)
	{
		id = memberids["GetColorBuffer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OGetColorBufferRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void GetDepthBuffer(float amount, float offset, float stride, float *ptr)
	{
		id = memberids["GetDepthBuffer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OGetDepthBufferRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArray(float val)
	{
		id = memberids["SizeOfArray"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySize(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayFFC(ffc *ptr)
	{
		id = memberids["SizeOfArrayFFC"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeF(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float SizeOfArrayNPC(npc *ptr)
	{
		id = memberids["SizeOfArrayNPC"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeN(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayBool(bool *ptr)
	{
		id = memberids["SizeOfArrayBool"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeB(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayItem(item *ptr)
	{
		id = memberids["SizeOfArrayItem"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeI(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayItemdata(itemdata *ptr)
	{
		id = memberids["SizeOfArrayItemdata"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeID(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayLWeapon(lweapon *ptr)
	{
		id = memberids["SizeOfArrayLWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeL(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// float SizeOfArrayEWeapon(eweapon *ptr)
	{
		id = memberids["SizeOfArrayEWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OArraySizeE(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// untyped NULL()
	{
		int id = memberids["NULL"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(0)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// untyped Untype(untype)
	{
		int id = memberids["Untype"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		//code.push_back(new OSetImmediate(new VarArgument(EXP1), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OGotoRegister(new VarArgument(EXP1))); //Just return it?
		rval[label]=code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
