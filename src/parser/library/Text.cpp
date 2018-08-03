#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_TEXT
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	name,		rettype,	setorget,	var,		num,	params
	//	{ "getTest",	tFlt,	        GETTER,         DEBUGREFFFC,    1,      P0      },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Text& Library::Text::instance()
{
	static Library::Text instance(NUL, table);
	return instance;
}

void Library::Text::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
