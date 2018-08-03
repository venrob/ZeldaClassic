#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_GRAPHICS
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	name,		rettype,	type,		var,		num,    params
	//	{ "getTest",	tFlt,		GETTER,		DEBUGREFFFC,	1,	P0		  },
		{ "Wavy",	tVoid,		FUNCTION,	0,		1,	P1(	tBool	) },
		{ "Zap",	tVoid,		FUNCTION,	0,		1,	P1(	tBool	) },
		{ "Greyscale",	tVoid,		FUNCTION,	0,		1,	P1(	tBool	) },
                ENTRY_END
        };

#	include "EntryHelperUnload.h"
}

Library::Graphics& Library::Graphics::instance()
{
	static Library::Graphics instance(REFGRAPHICS, table);
	return instance;
}

void Library::Graphics::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// void Wavy(float)
	{
		int id = memberids["Wavy"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OWavyR(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void Zap(float)
	{
		int id = memberids["Zap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OZapR(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void Greyscale(float)
	{
		int id = memberids["Greyscale"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OGreyscaleR(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
