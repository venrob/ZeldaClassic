#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_SHOPDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,			rettype,	type,	var,			num,	params
		{ "getItem[]",		tFlt,		GETTER, SHOPDATAITEM,		3,	P1(	tFlt		) },
		{ "setItem[]",		tVoid,		SETTER, SHOPDATAITEM,		3,	P2(	tFlt,	tFlt	) },
		{ "getHasItem[]",	tBool,		GETTER, SHOPDATAHASITEM,	3,	P1(	tFlt		) },
		{ "setHasItem[]",	tVoid,		SETTER, SHOPDATAHASITEM,	3,	P2(	tBool,	tFlt	) },
		{ "getPrice[]",		tFlt,		GETTER, SHOPDATAPRICE,		3,	P1(	tFlt		) },
		{ "setPrice[]",		tVoid,		SETTER, SHOPDATAPRICE,		3,	P2(	tFlt,	tFlt	) },
		{ "getString[]",	tFlt,		GETTER, SHOPDATASTRING,		3,	P1(	tFlt		) },
		{ "setString[]",	tVoid,		SETTER, SHOPDATASTRING,		3,	P2(	tFlt,	tFlt	) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}
	
Library::Shop& Library::Shop::instance()
{
	static Library::Shop instance(REFSHOPDATA, table);
	return instance;
}

void Library::Shop::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
