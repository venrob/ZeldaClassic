#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_CHEATS
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

Library::Cheat& Library::Cheat::instance()
{
	static Library::Cheat instance(REFCHEATS, table);
	return instance;
}

void Library::Cheat::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
