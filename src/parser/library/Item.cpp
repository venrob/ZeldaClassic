#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_ITEM
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,				rettype,	type,		var,			num,	params
		{ "getUID",			tFlt,		GETTER,		ITEMSCRIPTUID,		1,	P0			  },
		{ "getX",			tFlt,		GETTER,		ITEMX,			1,	P0			  },
		{ "setX",			tVoid,		SETTER,		ITEMX,			1,	P1(	tFlt		) },
		{ "getY",			tFlt,		GETTER,		ITEMY,			1,	P0			  },
		{ "setY",			tVoid,		SETTER,		ITEMY,			1,	P1(	tFlt		) },
		{ "getZ",			tFlt,		GETTER,		ITEMZ,			1,	P0			  },
		{ "setZ",			tVoid,		SETTER,		ITEMZ,			1,	P1(	tFlt		) },
		{ "getJump",			tFlt,		GETTER,		ITEMJUMP,		1,	P0			  },
		{ "setJump",			tVoid,		SETTER,		ITEMJUMP,		1,	P1(	tFlt		) },
		{ "getDrawStyle",		tFlt,		GETTER,		ITEMDRAWTYPE,		1,	P0			  },
		{ "setDrawStyle",		tVoid,		SETTER,		ITEMDRAWTYPE,		1,	P1(	tFlt		) },
		{ "getID",			tFlt,		GETTER,		ITEMID,			1,	P0			  },
		{ "setID",			tVoid,		SETTER,		ITEMID,			1,	P1(	tFlt		) },
		{ "getTile",			tFlt,		GETTER,		ITEMTILE,		1,	P0			  },
		{ "setTile",			tVoid,		SETTER,		ITEMTILE,		1,	P1(	tFlt		) },
		{ "getOriginalTile",		tFlt,		GETTER,		ITEMOTILE,		1,	P0			  },
		{ "setOriginalTile",		tVoid,		SETTER,		ITEMOTILE,		1,	P1(	tFlt		) },
		{ "getCSet",			tFlt,		GETTER,		ITEMCSET,		1,	P0			  },
		{ "setCSet",			tVoid,		SETTER,		ITEMCSET,		1,	P1(	tFlt		) },
		{ "getFlashCSet",		tFlt,		GETTER,		ITEMFLASHCSET,		1,	P0			  },
		{ "setFlashCSet",		tVoid,		SETTER,		ITEMFLASHCSET,		1,	P1(	tFlt		) },
		{ "getNumFrames",		tFlt,		GETTER,		ITEMFRAMES,		1,	P0			  },
		{ "setNumFrames",		tVoid,		SETTER,		ITEMFRAMES,		1,	P1(	tFlt		) },
		{ "getFrame",			tFlt,		GETTER,		ITEMFRAME,		1,	P0			  },
		{ "setFrame",			tVoid,		SETTER,		ITEMFRAME,		1,	P1(	tFlt		) },
		{ "getASpeed",			tFlt,		GETTER,		ITEMASPEED,		1,	P0			  },
		{ "setASpeed",			tVoid,		SETTER,		ITEMASPEED,		1,	P1(	tFlt		) },
		{ "getDelay",			tFlt,		GETTER,		ITEMDELAY,		1,	P0			  },
		{ "setDelay",			tVoid,		SETTER,		ITEMDELAY,		1,	P1(	tFlt		) },
		{ "getFlash",			tBool,		GETTER,		ITEMFLASH,		1,	P0			  },
		{ "setFlash",			tVoid,		SETTER,		ITEMFLASH,		1,	P1(	tBool		) },
		{ "getFlip",			tFlt,		GETTER,		ITEMFLIP,		1,	P0			  },
		{ "setFlip",			tVoid,		SETTER,		ITEMFLIP,		1,	P1(	tFlt		) },
		{ "getExtend",			tFlt,		GETTER,		ITEMEXTEND,		1,	P0			  },
		{ "setExtend",			tVoid,		SETTER,		ITEMEXTEND,		1,	P1(	tFlt		) },
		{ "getHitWidth",		tFlt,		GETTER,		ITEMHXSZ,		1,	P0			  },
		{ "setHitWidth",		tVoid,		SETTER,		ITEMHXSZ,		1,	P1(	tFlt		) },
		{ "getHitHeight",		tFlt,		GETTER,		ITEMHYSZ,		1,	P0			  },
		{ "setHitHeight",		tVoid,		SETTER,		ITEMHYSZ,		1,	P1(	tFlt		) },
		{ "getHitZHeight",		tFlt,		GETTER,		ITEMHZSZ,		1,	P0			  },
		{ "setHitZHeight",		tVoid,		SETTER,		ITEMHZSZ,		1,	P1(	tFlt		) },
		{ "getTileWidth",		tFlt,		GETTER,		ITEMTXSZ,		1,	P0			  },
		{ "setTileWidth",		tVoid,		SETTER,		ITEMTXSZ,		1,	P1(	tFlt		) },
		{ "getTileHeight",		tFlt,		GETTER,		ITEMTYSZ,		1,	P0			  },
		{ "setTileHeight",		tVoid,		SETTER,		ITEMTYSZ,		1,	P1(	tFlt		) },
		{ "getDrawXOffset",		tFlt,		GETTER,		ITEMXOFS,		1,	P0			  },
		{ "setDrawXOffset",		tVoid,		SETTER,		ITEMXOFS,		1,	P1(	tFlt		) },
		{ "getDrawYOffset",		tFlt,		GETTER,		ITEMYOFS,		1,	P0			  },
		{ "setDrawYOffset",		tVoid,		SETTER,		ITEMYOFS,		1,	P1(	tFlt		) },
		{ "getDrawZOffset",		tFlt,		GETTER,		ITEMZOFS,		1,	P0			  },
		{ "setDrawZOffset",		tVoid,		SETTER,		ITEMZOFS,		1,	P1(	tFlt		) },
		{ "getHitXOffset",		tFlt,		GETTER,		ITEMHXOFS,		1,	P0			  },
		{ "setHitXOffset",		tVoid,		SETTER,		ITEMHXOFS,		1,	P1(	tFlt		) },
		{ "getHitYOffset",		tFlt,		GETTER,		ITEMHYOFS,		1,	P0			  },
		{ "setHitYOffset",		tVoid,		SETTER,		ITEMHYOFS,		1,	P1(	tFlt		) },
		{ "getPickup",			tFlt,		GETTER,		ITEMPICKUP,		1,	P0			  },
		{ "setPickup",			tVoid,		SETTER,		ITEMPICKUP,		1,	P1(	tFlt		) },
		{ "isValid",			tBool,		FUNCTION,	0,			1,	P0			  },
		{ "getMisc[]",			tAny,		GETTER,		ITEMMISCD,		32,	P1(	tFlt		) },
		{ "setMisc[]",			tVoid,		SETTER,		ITEMMISCD,		32,	P2(	tFlt,	tAny	) },
		{ "getAClock",			tFlt,		GETTER,		ITEMACLK,		1,	P0			  },
		{ "setAClock",			tVoid,		SETTER,		ITEMACLK,		1,	P1(	tFlt		) },
		{ "getPickupString",		tFlt,		GETTER,		ITEMPSTRING,		1,	P0			  },
		{ "setPickupString",		tVoid,		SETTER,		ITEMPSTRING,		1,	P1(	tFlt		) },
		{ "getPickupStringFlags",	tFlt,		GETTER,		ITEMPSTRINGFLAGS,	1,	P0			  },
		{ "setPickupStringFlags",	tVoid,		SETTER,		ITEMPSTRINGFLAGS,	1,	P1(	tFlt		) },
		{ "getSizeFlags",		tFlt,		GETTER,		ITEMOVERRIDEFLAGS,	1,	P0			  },
		{ "setSizeFlags",		tVoid,		SETTER,		ITEMOVERRIDEFLAGS,	1,	P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Item& Library::Item::instance()
{
	static Library::Item instance(REFITEM, table);
	return instance;
}

void Library::Item::generateFunctionCode(
		LinkTable* linktable, std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// bool isValid()
	{
		int id = memberids["isValid"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the pointer
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//Check validity
		code.push_back(new OIsValidItem(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
