#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_ITEMCLASS
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,				rettype,	type,		var,			num,				params
		{ "getFamily",			tFlt,		GETTER,		ITEMCLASSFAMILY,	1,				P0			  },
		{ "setFamily",			tVoid,		SETTER,		ITEMCLASSFAMILY,	1,				P1(	tFlt		) },
		{ "getLevel",			tFlt,		GETTER,		ITEMCLASSFAMTYPE,	1,				P0			  },
		{ "setLevel",			tVoid,		SETTER,		ITEMCLASSFAMTYPE,	1,				P1(	tFlt		) },
		{ "getAmount",			tFlt,		GETTER,		ITEMCLASSAMOUNT,	1,				P0			  },
		{ "setAmount",			tVoid,		SETTER,		ITEMCLASSAMOUNT,	1,				P1(	tFlt		) },
		{ "getMax",			tFlt,		GETTER,		ITEMCLASSMAX,		1,				P0			  },
		{ "setMax",			tVoid,		SETTER,		ITEMCLASSMAX,		1,				P1(	tFlt		) },
		{ "getMaxIncrement",		tFlt,		GETTER,		ITEMCLASSSETMAX,	1,				P0			  },
		{ "setMaxIncrement",		tVoid,		SETTER,		ITEMCLASSSETMAX,	1,				P1(	tFlt		) },
		{ "getKeep",			tBool,		GETTER,		ITEMCLASSSETGAME,	1,				P0			  },
		{ "setKeep",			tVoid,		SETTER,		ITEMCLASSSETGAME,	1,				P1(	tBool		) },
		{ "getCounter",			tFlt,		GETTER,		ITEMCLASSCOUNTER,	1,				P0			  },
		{ "setCounter",			tVoid,		SETTER,		ITEMCLASSCOUNTER,	1,				P1(	tFlt		) },
		{ "getUseSound",		tFlt,		GETTER,		ITEMCLASSUSESOUND,	1,				P0			  },
		{ "setUseSound",		tVoid,		SETTER,		ITEMCLASSUSESOUND,	1,				P1(	tFlt		) },
		{ "getID",			tFlt,		GETTER,		ITEMCLASSID,		1,				P0			  },
		{ "getPower",			tFlt,		GETTER,		ITEMCLASSPOWER,		1,				P0			  },
		{ "setPower",			tVoid,		SETTER,		ITEMCLASSPOWER,		1,				P1(	tFlt		) },
		{ "getInitD[]",			tAny,		GETTER,		ITEMCLASSINITDD,	2,				P1(	tFlt		) },
		{ "setInitD[]",			tVoid,		SETTER,		ITEMCLASSINITDD,	2,				P2(	tFlt,	tAny	) },
		{ "GetName",			tVoid,		FUNCTION,	0,			1,				P1(	tFlt		) },
		{ "getModifier",		tFlt,		GETTER,		IDATALTM,		1,				P0			  },
		{ "setModifier",		tVoid,		SETTER,		IDATALTM,		1,				P1(	tFlt		) },
		{ "getScript",			tFlt,		GETTER,		IDATASCRIPT,		1,				P0			  },
		{ "setScript",			tVoid,		SETTER,		IDATASCRIPT,		1,				P1(	tFlt		) },
		{ "getPScript",			tFlt,		GETTER,		IDATAPSCRIPT,		1,				P0			  },
		{ "setPScript",			tVoid,		SETTER,		IDATAPSCRIPT,		1,				P1(	tFlt		) },
		{ "getPString",			tFlt,		GETTER,		IDATAPSTRING,		1,				P0			  },
		{ "setPString",			tVoid,		SETTER,		IDATAPSTRING,		1,				P1(	tFlt		) },
		{ "getMagicCost",		tFlt,		GETTER,		IDATAMAGCOST,		1,				P0			  },
		{ "setMagicCost",		tVoid,		SETTER,		IDATAMAGCOST,		1,				P1(	tFlt		) },
		{ "getCost",			tFlt,		GETTER,		IDATAMAGCOST,		1,				P0			  },
		{ "setCost",			tVoid,		SETTER,		IDATAMAGCOST,		1,				P1(	tFlt		) },
		{ "getCostCounter",		tFlt,		GETTER,		IDATACOSTCOUNTER,	1,				P0			  },
		{ "setCostCounter",		tVoid,		SETTER,		IDATACOSTCOUNTER,	1,				P1(	tFlt		) },
		{ "getMinHearts",		tFlt,		GETTER,		IDATAMINHEARTS,		1,				P0			  },
		{ "setMinHearts",		tVoid,		SETTER,		IDATAMINHEARTS,		1,				P1(	tFlt		) },
		{ "getTile",			tFlt,		GETTER,		IDATATILE,		1,				P0			  },
		{ "setTile",			tVoid,		SETTER,		IDATATILE,		1,				P1(	tFlt		) },
		{ "getFlash",			tFlt,		GETTER,		IDATAMISC,		1,				P0			  },
		{ "setFlash",			tVoid,		SETTER,		IDATAMISC,		1,				P1(	tFlt		) },
		{ "getCSet",			tFlt,		GETTER,		IDATACSET,		1,				P0			  },
		{ "setCSet",			tVoid,		SETTER,		IDATACSET,		1,				P1(	tFlt		) },
	//	{ "getFrame",			tFlt,		GETTER,		IDATAFRAME,		1,				P0			  },
	//	{ "setFrame",			tVoid,		SETTER,		IDATAFRAME,		1,				P1(	tFlt		) },
		{ "getAFrames",			tFlt,		GETTER,		IDATAFRAMES,		1,				P0			  },
		{ "setAFrames",			tVoid,		SETTER,		IDATAFRAMES,		1,				P1(	tFlt		) },
		{ "getASpeed",			tFlt,		GETTER,		IDATAASPEED,		1,				P0			  },
		{ "setASpeed",			tVoid,		SETTER,		IDATAASPEED,		1,				P1(	tFlt		) },
		{ "getDelay",			tFlt,		GETTER,		IDATADELAY,		1,				P0			  },
		{ "setDelay",			tVoid,		SETTER,		IDATADELAY,		1,				P1(	tFlt		) },
		{ "getCombine",			tBool,		GETTER,		IDATACOMBINE,		1,				P0			  },
		{ "setCombine",			tVoid,		SETTER,		IDATACOMBINE,		1,				P1(	tBool		) },
		{ "getDowngrade",		tBool,		GETTER,		IDATADOWNGRADE,		1,				P0			  },
		{ "setDowngrade",		tVoid,		SETTER,		IDATADOWNGRADE,		1,				P1(	tBool		) },
		{ "getKeepOld",			tBool,		GETTER,		IDATAKEEPOLD,		1,				P0			  },
		{ "setKeepOld",			tVoid,		SETTER,		IDATAKEEPOLD,		1,				P1(	tBool		) },
		{ "getRupeeCost",		tBool,		GETTER,		IDATARUPEECOST,		1,				P0			  },
		{ "setRupeeCost",		tVoid,		SETTER,		IDATARUPEECOST,		1,				P1(	tBool		) },
		{ "getEdible",			tBool,		GETTER,		IDATAEDIBLE,		1,				P0			  },
		{ "setEdible",			tVoid,		SETTER,		IDATAEDIBLE,		1,				P1(	tBool		) },
		{ "getUnused",			tBool,		GETTER,		IDATAFLAGUNUSED,	1,				P0			  },
		{ "setUnused",			tVoid,		SETTER,		IDATAFLAGUNUSED,	1,				P1(	tBool		) },
		{ "getGainLower",		tBool,		GETTER,		IDATAGAINLOWER,		1,				P0			  },
		{ "setGainLower",		tVoid,		SETTER,		IDATAGAINLOWER,		1,				P1(	tBool		) },
		{ "getAttributes[]",		tFlt,		GETTER,		IDATAATTRIB,		15,				P1(	tFlt		) },
		{ "setAttributes[]",		tVoid,		SETTER,		IDATAATTRIB,		15,				P2(	tFlt,	tFlt	) },
		{ "getMisc[]",			tFlt,		GETTER,		IDATAATTRIB,		10,				P1(	tFlt		) },
		{ "setMisc[]",			tVoid,		SETTER,		IDATAATTRIB,		10,				P2(	tFlt,	tFlt	) },
		{ "getFlags[]",			tBool,		GETTER,		IDATAFLAGS,		5,				P1(	tFlt		) },
		{ "setFlags[]",			tVoid,		SETTER,		IDATAFLAGS,		5,				P2(	tFlt,	tBool	) },
		{ "getSprites[]",		tFlt,		GETTER,		IDATASPRITE,		10,				P1(	tFlt		) },
		{ "setSprites[]",		tVoid,		SETTER,		IDATASPRITE,		10,				P2(	tFlt,	tFlt	) },
		{ "getWeapon",			tFlt,		GETTER,		IDATAUSEWPN,		1,				P0			  },
		{ "setWeapon",			tVoid,		SETTER,		IDATAUSEWPN,		1,				P1(	tFlt		) },
		{ "getDefense",			tFlt,		GETTER,		IDATAUSEDEF,		1,				P0			  },
		{ "setDefense",			tVoid,		SETTER,		IDATAUSEDEF,		1,				P1(	tFlt		) },
		{ "getRange",			tFlt,		GETTER,		IDATAWRANGE,		1,				P0			  },
		{ "setRange",			tVoid,		SETTER,		IDATAWRANGE,		1,				P1(	tFlt		) },
		{ "getDuration",		tFlt,		GETTER,		IDATADURATION,		1,				P0			  },
		{ "setDuration",		tVoid,		SETTER,		IDATADURATION,		1,				P1(	tFlt		) },
	//	{ "getMovement[]",		tFlt,		GETTER,		IDATAUSEMVT,		ITEM_MOVEMENT_PATTERNS,		P1(	tFlt		) },
	//	{ "setMovement[]",		tVoid,		SETTER,		IDATAUSEMVT,		ITEM_MOVEMENT_PATTERNS,		P2(	tFlt,	tFlt	) },
		{ "getWeaponD[]",		tAny,		GETTER,		IDATAWPNINITD,		8,				P1(	tFlt		) },
		{ "setWeaponD[]",		tVoid,		SETTER,		IDATAWPNINITD,		8,				P2(	tFlt,	tAny	) },
		{ "getWeaponMisc[]",		tAny,		GETTER,		IDATAMISCD,		32,				P1(	tFlt		) },
		{ "setWeaponMisc[]",		tVoid,		SETTER,		IDATAMISCD,		32,				P2(	tFlt,	tAny	) },
		{ "getDuplicates",		tFlt,		GETTER,		IDATADUPLICATES,	1,				P0			  },
		{ "setDuplicates",		tVoid,		SETTER,		IDATADUPLICATES,	1,				P1(	tFlt		) },
		{ "getDrawLayer",		tFlt,		GETTER,		IDATADRAWLAYER,		1,				P0			  },
		{ "setDrawLayer",		tVoid,		SETTER,		IDATADRAWLAYER,		1,				P1(	tFlt		) },
		{ "getCollectFlags",		tFlt,		GETTER,		IDATACOLLECTFLAGS,	1,				P0			  },
		{ "setCollectFlags",		tVoid,		SETTER,		IDATACOLLECTFLAGS,	1,				P1(	tFlt		) },
		{ "getWeaponScript",		tFlt,		GETTER,		IDATAWEAPONSCRIPT,	1,				P0			  },
		{ "setWeaponScript",		tVoid,		SETTER,		IDATAWEAPONSCRIPT,	1,				P1(	tFlt		) },
		{ "getWeaponHitXOffset",	tFlt,		GETTER,		IDATAWEAPHXOFS,		1,				P0			  },
		{ "setWeaponHitXOffset",	tVoid,		SETTER,		IDATAWEAPHXOFS,		1,				P1(	tFlt		) },
		{ "getWeaponHitYOffset",	tFlt,		GETTER,		IDATAWEAPHYOFS,		1,				P0			  },
		{ "setWeaponHitYOffset",	tVoid,		SETTER,		IDATAWEAPHYOFS,		1,				P1(	tFlt		) },
		{ "getWeaponHitWidth",		tFlt,		GETTER,		IDATAWEAPHXSZ,		1,				P0			  },
		{ "setWeaponHitWidth",		tVoid,		SETTER,		IDATAWEAPHXSZ,		1,				P1(	tFlt		) },
		{ "getWeaponHitHeight",		tFlt,		GETTER,		IDATAWEAPHYSZ,		1,				P0			  },
		{ "setWeaponHitHeight",		tVoid,		SETTER,		IDATAWEAPHYSZ,		1,				P1(	tFlt		) },
		{ "getWeaponHitZHeight",	tFlt,		GETTER,		IDATAWEAPHZSZ,		1,				P0			  },
		{ "setWeaponHitZHeight",	tVoid,		SETTER,		IDATAWEAPHZSZ,		1,				P1(	tFlt		) },
		{ "getWeaponDrawXOffset",	tFlt,		GETTER,		IDATAWEAPXOFS,		1,				P0			  },
		{ "setWeaponDrawXOffset",	tVoid,		SETTER,		IDATAWEAPXOFS,		1,				P1(	tFlt		) },
		{ "getWeaponDrawYOffset",	tFlt,		GETTER,		IDATAWEAPYOFS,		1,				P0			  },
		{ "setWeaponDrawYOffset",	tVoid,		SETTER,		IDATAWEAPYOFS,		1,				P1(	tFlt		) },
		{ "getWeaponDrawZOffset",	tFlt,		GETTER,		IDATAWEAPZOFS,		1,				P0			  },
		{ "setWeaponDrawZOffset",	tVoid,		SETTER,		IDATAWEAPZOFS,		1,				P1(	tFlt		) },
		{ "getMagicCostTimer",		tFlt,		GETTER,		IDATAMAGICTIMER,	1,				P0			  },
		{ "setMagicCostTimer",		tVoid,		SETTER,		IDATAMAGICTIMER,	1,				P1(	tFlt		) },
		{ "getCostTimer",		tFlt,		GETTER,		IDATAMAGICTIMER,	1,				P0			  },
		{ "setCostTimer",		tVoid,		SETTER,		IDATAMAGICTIMER,	1,				P1(	tFlt		) },
		{ "getHitXOffset",		tFlt,		GETTER,		IDATAHXOFS,		1,				P0			  },
		{ "setHitXOffset",		tVoid,		SETTER,		IDATAHXOFS,		1,				P1(	tFlt		) },
		{ "getHitYOffset",		tFlt,		GETTER,		IDATAHYOFS,		1,				P0			  },
		{ "setHitYOffset",		tVoid,		SETTER,		IDATAHYOFS,		1,				P1(	tFlt		) },
		{ "getDrawXOffset",		tFlt,		GETTER,		IDATADXOFS,		1,				P0			  },
		{ "setDrawXOffset",		tVoid,		SETTER,		IDATADXOFS,		1,				P1(	tFlt		) },
		{ "getDrawYOffset",		tFlt,		GETTER,		IDATADYOFS,		1,				P0			  },
		{ "setDrawYOffset",		tVoid,		SETTER,		IDATADYOFS,		1,				P1(	tFlt		) },
		{ "getHitWidth",		tFlt,		GETTER,		IDATAHXSZ,		1,				P0			  },
		{ "setHitWidth",		tVoid,		SETTER,		IDATAHXSZ,		1,				P1(	tFlt		) },
		{ "getHitHeight",		tFlt,		GETTER,		IDATAHYSZ,		1,				P0			  },
		{ "setHitHeight",		tVoid,		SETTER,		IDATAHYSZ,		1,				P1(	tFlt		) },
		{ "getHitZHeight",		tFlt,		GETTER,		IDATAHZSZ,		1,				P0			  },
		{ "setHitZHeight",		tVoid,		SETTER,		IDATAHZSZ,		1,				P1(	tFlt		) },
		{ "getTileWidth",		tFlt,		GETTER,		IDATATILEW,		1,				P0			  },
		{ "setTileWidth",		tVoid,		SETTER,		IDATATILEW,		1,				P1(	tFlt		) },
		{ "getTileHeight",		tFlt,		GETTER,		IDATATILEH,		1,				P0			  },
		{ "setTileHeight",		tVoid,		SETTER,		IDATATILEH,		1,				P1(	tFlt		) },
		{ "getPickup",			tFlt,		GETTER,		IDATAPICKUP,		1,				P0			  },
		{ "setPickup",			tVoid,		SETTER,		IDATAPICKUP,		1,				P1(	tFlt		) },
		{ "getOverrideFlags",		tFlt,		GETTER,		IDATAOVERRIDEFL,	1,				P0			  },
		{ "setOverrideFlags",		tVoid,		SETTER,		IDATAOVERRIDEFL,	1,				P1(	tFlt		) },
		// Weapon-forwarded Variables
		{ "getWeaponTileWidth",		tFlt,		GETTER,		IDATATILEWWEAP,		1,				P0			  },
		{ "setWeaponTileWidth",		tVoid,		SETTER,		IDATATILEWWEAP,		1,				P1(	tFlt		) },
		{ "getWeaponTileHeight",	tFlt,		GETTER,		IDATATILEHWEAP,		1,				P0			  },
		{ "setWeaponTileHeight",	tVoid,		SETTER,		IDATATILEHWEAP,		1,				P1(	tFlt		) },
		{ "getWeaponOverrideFlags",	tFlt,		GETTER,		IDATAOVERRIDEFLWEAP,	1,				P0			  },
		{ "setWeaponOverrideFlags",	tVoid,		SETTER,		IDATAOVERRIDEFLWEAP,	1,				P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::ItemClass& Library::ItemClass::instance()
{
	static Library::ItemClass instance(REFITEMCLASS, table);
	return instance;
}

void Library::ItemClass::generateFunctionCode(
		LinkTable* linktable, std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// void GetName(int)
	{
		int id = memberids["GetName"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetItemName(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
