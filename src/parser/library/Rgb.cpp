#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_RGBDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,		rettype,	type,		var,		num,	params
		{ "getTest",	tFlt,		GETTER,		DEBUGREFFFC,	1,	P0	  },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Rgb& Library::Rgb::instance()
{
	static Library::Rgb instance(REFRGB, table);
	return instance;
}

void Library::Rgb::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
