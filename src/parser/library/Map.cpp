#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_MAPDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,				rettype,type,		var,			num     params
		{ "GetEnemy",			tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetEnemy",			tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetDoor",			tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetDoor",			tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "SetWidth",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetWidth",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetHeight",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetHeight",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetViewX",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetViewX",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetViewY",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetViewY",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetGuy",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetGuy",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetString",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetString",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetRoomType",		tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetRoomType",		tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetEntryX",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetEntryX",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetEntryY",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetEntryY",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetItem",			tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetItem",			tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetUndercombo",		tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetUndercombo",		tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetUnderCSet",		tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetUnderCSet",		tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetCatchall",		tVoid,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetCatchall",		tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetLayerOpacity",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetLayerOpacity",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetSecretCombo",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetSecretCombo",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetSecretCSet",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetSecretCSet",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetSecretFlag",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetSecretFlag",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetLayerMap",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetLayerMap",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetLayerScreen",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetLayerScreen",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetPath",			tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetPath",			tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetWarpReturnX",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetWarpReturnX",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetWarpReturnY",		tVoid,	FUNCTION,	0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetWarpReturnY",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		// mapdata m-> class variables					
		{ "getValid",			tFlt,	GETTER,		MAPDATAVALID,		1,	P0					  },
		{ "setValid",			tVoid,	SETTER,		MAPDATAVALID,		1,	P1(	tFlt				) },
		{ "getGuy",			tFlt,	GETTER,		MAPDATAGUY,		1,	P0					  },
		{ "setGuy",			tVoid,	SETTER,		MAPDATAGUY,		1,	P1(	tFlt				) },
		{ "getString",			tFlt,	GETTER,		MAPDATASTRING,		1,	P0					  },
		{ "setString",			tVoid,	SETTER,		MAPDATASTRING,		1,	P1(	tFlt				) },
		{ "getRoomType",		tFlt,	GETTER,		MAPDATAROOM,		1,	P0					  },
		{ "setRoomType",		tVoid,	SETTER,		MAPDATAROOM,		1,	P1(	tFlt				) },
		{ "getItem",			tFlt,	GETTER,		MAPDATAITEM,		1,	P0					  },
		{ "setItem",			tVoid,	SETTER,		MAPDATAITEM,		1,	P1(	tFlt				) },
		{ "getHasItem",			tFlt,	GETTER,		MAPDATAHASITEM,		1,	P0					  },
		{ "setHasItem",			tVoid,	SETTER,		MAPDATAHASITEM,		1,	P1(	tFlt				) },
		{ "getTileWarpType[]",		tFlt,	GETTER,		MAPDATATILEWARPTYPE,	4,	P1(	tFlt				) },
		{ "setTileWarpType[]",		tVoid,	SETTER,		MAPDATATILEWARPTYPE,	4,	P2(	tFlt,	tFlt			) },
		{ "getTileWarpOverlayFlags",	tFlt,	GETTER,		MAPDATATILEWARPOVFLAGS, 1,	P0					  },
		{ "setTileWarpOverlayFlags",	tVoid,	SETTER,		MAPDATATILEWARPOVFLAGS, 1,	P1(	tFlt				) },
		{ "getDoorComboSet",		tFlt,	GETTER,		MAPDATADOORCOMBOSET,	1,	P0					  },
		{ "setDoorComboSet",		tVoid,	SETTER,		MAPDATADOORCOMBOSET,	1,	P1(	tFlt				) },
		{ "getWarpReturnX[]",		tFlt,	GETTER,		MAPDATAWARPRETX,	4,	P1(	tFlt				) },
		{ "setWarpReturnX[]",		tVoid,	SETTER,		MAPDATAWARPRETX,	4,	P2(	tFlt,	tFlt			) },
		{ "getWarpReturnY[]",		tFlt,	GETTER,		MAPDATAWARPRETY,	4,	P1(	tFlt				) },
		{ "setWarpReturnY[]",		tVoid,	SETTER,		MAPDATAWARPRETY,	4,	P2(	tFlt,	tFlt			) },
		{ "getWarpReturnC",		tFlt,	GETTER,		MAPDATAWARPRETURNC,	1,	P0					  },
		{ "setWarpReturnC",		tVoid,	SETTER,		MAPDATAWARPRETURNC,	1,	P1(	tFlt				) },
		{ "getStairsX",			tFlt,	GETTER,		MAPDATASTAIRX,		1,	P0					  },
		{ "setStairsX",			tVoid,	SETTER,		MAPDATASTAIRX,		1,	P1(	tFlt				) },
		{ "getStairsY",			tFlt,	GETTER,		MAPDATASTAIRY,		1,	P0					  },
		{ "setStairsY",			tVoid,	SETTER,		MAPDATASTAIRY,		1,	P1(	tFlt				) },
		{ "getItemX",			tFlt,	GETTER,		MAPDATAITEMX,		1,	P0					  },
		{ "setItemX",			tVoid,	SETTER,		MAPDATAITEMX,		1,	P1(	tFlt				) },
		{ "getItemY",			tFlt,	GETTER,		MAPDATAITEMY,		1,	P0					  },
		{ "setItemY",			tVoid,	SETTER,		MAPDATAITEMY,		1,	P1(	tFlt				) },
		{ "getCSet",			tFlt,	GETTER,		MAPDATACOLOUR,		1,	P0					  },
		{ "setCSet",			tVoid,	SETTER,		MAPDATACOLOUR,		1,	P1(	tFlt				) },
		{ "getEnemyFlags",		tFlt,	GETTER,		MAPDATAENEMYFLAGS,	1,	P0					  },
		{ "setEnemyFlags",		tVoid,	SETTER,		MAPDATAENEMYFLAGS,	1,	P1(	tFlt				) },
		{ "getDoor[]",			tFlt,	GETTER,		MAPDATADOOR,		4,	P1(	tFlt				) },
		{ "setDoor[]",			tVoid,	SETTER,		MAPDATADOOR,		4,	P2(	tFlt,	tFlt			) },
		{ "getTileWarpDMap[]",		tFlt,	GETTER,		MAPDATATILEWARPDMAP,	4,	P1(	tFlt				) },
		{ "setTileWarpDMap[]",		tVoid,	SETTER,		MAPDATATILEWARPDMAP,	4,	P2(	tFlt,	tFlt			) },
		{ "getTileWarpScreen[]",	tFlt,	GETTER,		MAPDATATILEWARPSCREEN,	4,	P1(	tFlt				) },
		{ "setTileWarpScreen[]",	tVoid,	SETTER,		MAPDATATILEWARPSCREEN,	4,	P2(	tFlt,	tFlt			) },
		{ "getExitDir",			tFlt,	GETTER,		MAPDATAEXITDIR,		1,	P0					  },
		{ "setExitDir",			tVoid,	SETTER,		MAPDATAEXITDIR,		1,	P1(	tFlt				) },
		{ "getEnemy[]",			tFlt,	GETTER,		MAPDATAENEMY,		10,	P1(	tFlt				) },
		{ "setEnemy[]",			tVoid,	SETTER,		MAPDATAENEMY,		10,	P2(	tFlt,	tFlt			) },
		{ "getPattern",			tFlt,	GETTER,		MAPDATAPATTERN,		1,	P0					  },
		{ "setPattern",			tVoid,	SETTER,		MAPDATAPATTERN,		1,	P1(	tFlt				) },
		{ "getSideWarpType[]",		tFlt,	GETTER,		MAPDATASIDEWARPTYPE,	4,	P1(	tFlt				) },
		{ "setSideWarpType[]",		tVoid,	SETTER,		MAPDATASIDEWARPTYPE,	4,	P2(	tFlt,	tFlt			) },
		{ "getSideWarpOverlayFlags",	tFlt,	GETTER,		MAPDATASIDEWARPOVFLAGS, 1,	P0					  },
		{ "setSideWarpOverlayFlags",	tVoid,	SETTER,		MAPDATASIDEWARPOVFLAGS, 1,	P1(	tFlt				) },
		{ "getWarpArrivalX",		tFlt,	GETTER,		MAPDATAWARPARRIVALX,	1,	P0					  },
		{ "setWarpArrivalX",		tVoid,	SETTER,		MAPDATAWARPARRIVALX,	1,	P1(	tFlt				) },
		{ "getWarpArrivalY",		tFlt,	GETTER,		MAPDATAWARPARRIVALY,	1,	P0					  },
		{ "setWarpArrivalY",		tVoid,	SETTER,		MAPDATAWARPARRIVALY,	1,	P1(	tFlt				) },
		{ "getMazePath[]",		tFlt,	GETTER,		MAPDATAPATH,		4,	P1(	tFlt				) },
		{ "setMazePath[]",		tVoid,	SETTER,		MAPDATAPATH,		4,	P2(	tFlt,	tFlt			) },
		{ "getSideWarpScreen[]",	tFlt,	GETTER,		MAPDATASIDEWARPSC,	4,	P1(	tFlt				) },
		{ "setSideWarpScreen[]",	tVoid,	SETTER,		MAPDATASIDEWARPSC,	4,	P2(	tFlt,	tFlt			) },
		{ "getSideWarpDMap[]",		tFlt,	GETTER,		MAPDATASIDEWARPDMAP,	4,	P1(	tFlt				) },
		{ "setSideWarpDMap[]",		tVoid,	SETTER,		MAPDATASIDEWARPDMAP,	4,	P2(	tFlt,	tFlt			) },
		{ "getSideWarpIndex",		tFlt,	GETTER,		MAPDATASIDEWARPINDEX,	1,	P0					  },
		{ "setSideWarpIndex",		tVoid,	SETTER,		MAPDATASIDEWARPINDEX,	1,	P1(	tFlt				) },
		{ "getUndercombo",		tFlt,	GETTER,		MAPDATAUNDERCOMBO,	1,	P0					  },
		{ "setUndercombo",		tVoid,	SETTER,		MAPDATAUNDERCOMBO,	1,	P1(	tFlt				) },
		{ "getUnderCSet",		tFlt,	GETTER,		MAPDATAUNDERCSET,	1,	P0					  },
		{ "setUnderCSet",		tVoid,	SETTER,		MAPDATAUNDERCSET,	1,	P1(	tFlt				) },
		{ "getCatchall",		tFlt,	GETTER,		MAPDATACATCHALL,	1,	P0					  },
		{ "setCatchall",		tVoid,	SETTER,		MAPDATACATCHALL,	1,	P1(	tFlt				) },
		{ "getCSensitive",		tFlt,	GETTER,		MAPDATACSENSITIVE,	1,	P0					  },
		{ "setCSensitive",		tVoid,	SETTER,		MAPDATACSENSITIVE,	1,	P1(	tFlt				) },
		{ "getNoReset",			tFlt,	GETTER,		MAPDATANORESET,		1,	P0					  },
		{ "setNoReset",			tVoid,	SETTER,		MAPDATANORESET,		1,	P1(	tFlt				) },
		{ "getNoCarry",			tFlt,	GETTER,		MAPDATANOCARRY,		1,	P0					  },
		{ "setNoCarry",			tVoid,	SETTER,		MAPDATANOCARRY,		1,	P1(	tFlt				) },
		{ "getLayerMap[]",		tFlt,	GETTER,		MAPDATALAYERMAP,	6,	P1(	tFlt				) },
		{ "setLayerMap[]",		tVoid,	SETTER,		MAPDATALAYERMAP,	6,	P2(	tFlt,	tFlt			) },
		{ "getLayerScreen[]",		tFlt,	GETTER,		MAPDATALAYERSCREEN,	6,	P1(	tFlt				) },
		{ "setLayerScreen[]",		tVoid,	SETTER,		MAPDATALAYERSCREEN,	6,	P2(	tFlt,	tFlt			) },
		{ "getLayerOpacity[]",		tFlt,	GETTER,		MAPDATALAYEROPACITY,	6,	P1(	tFlt				) },
		{ "setLayerOpacity[]",		tVoid,	SETTER,		MAPDATALAYEROPACITY,	6,	P2(	tFlt,	tFlt			) },
		{ "getTimedWarpTimer",		tFlt,	GETTER,		MAPDATATIMEDWARPTICS,	1,	P0					  },
		{ "setTimedWarpTimer",		tVoid,	SETTER,		MAPDATATIMEDWARPTICS,	1,	P1(	tFlt				) },
		{ "getNextMap",			tFlt,	GETTER,		MAPDATANEXTMAP,		1,	P0					  },
		{ "setNextMap",			tVoid,	SETTER,		MAPDATANEXTMAP,		1,	P1(	tFlt				) },
		{ "getNextScreen",		tFlt,	GETTER,		MAPDATANEXTSCREEN,	1,	P0					  },
		{ "setNextScreen",		tVoid,	SETTER,		MAPDATANEXTSCREEN,	1,	P1(	tFlt				) },
		{ "getSecretCombo[]",		tFlt,	GETTER,		MAPDATASECRETCOMBO,	128,	P1(	tFlt				) },
		{ "setSecretCombo[]",		tVoid,	SETTER,		MAPDATASECRETCOMBO,	128,	P2(	tFlt,	tFlt			) },
		{ "getSecretCSet[]",		tFlt,	GETTER,		MAPDATASECRETCSET,	128,	P1(	tFlt				) },
		{ "setSecretCSet[]",		tVoid,	SETTER,		MAPDATASECRETCSET,	128,	P2(	tFlt,	tFlt			) },
		{ "getSecretFlags[]",		tFlt,	GETTER,		MAPDATASECRETFLAG,	128,	P1(	tFlt				) },
		{ "setSecretFlags[]",		tVoid,	SETTER,		MAPDATASECRETFLAG,	128,	P2(	tFlt,	tFlt			) },
		{ "getViewX",			tFlt,	GETTER,		MAPDATAVIEWX,		1,	P0					  },
		{ "setViewX",			tVoid,	SETTER,		MAPDATAVIEWX,		1,	P1(	tFlt				) },
		{ "getViewY",			tFlt,	GETTER,		MAPDATAVIEWY,		1,	P0					  },
		{ "setViewY",			tVoid,	SETTER,		MAPDATAVIEWY,		1,	P1(	tFlt				) },
		{ "getWidth",			tFlt,	GETTER,		MAPDATASCREENWIDTH,	1,	P0					  },
		{ "setWidth",			tVoid,	SETTER,		MAPDATASCREENWIDTH,	1,	P1(	tFlt				) },
		{ "getHeight",			tFlt,	GETTER,		MAPDATASCREENHEIGHT,	1,	P0					  },
		{ "setHeight",			tVoid,	SETTER,		MAPDATASCREENHEIGHT,	1,	P1(	tFlt				) },
		{ "getEntryX",			tFlt,	GETTER,		MAPDATAENTRYX,		1,	P0					  },
		{ "setEntryX",			tVoid,	SETTER,		MAPDATAENTRYX,		1,	P1(	tFlt				) },
		{ "getEntryY",			tFlt,	GETTER,		MAPDATAENTRYY,		1,	P0					  },
		{ "setEntryY",			tVoid,	SETTER,		MAPDATAENTRYY,		1,	P1(	tFlt				) },
		{ "getNumFFCs",			tFlt,	GETTER,		MAPDATANUMFF,		1,	P0					  },
		{ "setNumFFCs",			tVoid,	SETTER,		MAPDATANUMFF,		1,	P1(	tFlt				) },
		{ "getFFCData[]",		tFlt,	GETTER,		MAPDATAFFDATA,		32,	P1(	tFlt				) },
		{ "setFFCData[]",		tVoid,	SETTER,		MAPDATAFFDATA,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCCSet[]",		tFlt,	GETTER,		MAPDATAFFCSET,		32,	P1(	tFlt				) },
		{ "setFFCCSet[]",		tVoid,	SETTER,		MAPDATAFFCSET,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCDelay[]",		tFlt,	GETTER,		MAPDATAFFDELAY,		32,	P1(	tFlt				) },
		{ "setFFCDelay[]",		tVoid,	SETTER,		MAPDATAFFDELAY,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCX[]",			tFlt,	GETTER,		MAPDATAFFX,		32,	P1(	tFlt				) },
		{ "setFFCX[]",			tVoid,	SETTER,		MAPDATAFFX,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCY[]",			tFlt,	GETTER,		MAPDATAFFY,		32,	P1(	tFlt				) },
		{ "setFFCY[]",			tVoid,	SETTER,		MAPDATAFFY,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCVx[]",			tFlt,	GETTER,		MAPDATAFFXDELTA,	32,	P1(	tFlt				) },
		{ "setFFCVx[]",			tVoid,	SETTER,		MAPDATAFFXDELTA,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCVy[]",			tFlt,	GETTER,		MAPDATAFFYDELTA,	32,	P1(	tFlt				) },
		{ "setFFCVy[]",			tVoid,	SETTER,		MAPDATAFFYDELTA,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCAx[]",			tFlt,	GETTER,		MAPDATAFFXDELTA2,	32,	P1(	tFlt				) },
		{ "setFFCAx[]",			tVoid,	SETTER,		MAPDATAFFXDELTA2,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCAy[]",			tFlt,	GETTER,		MAPDATAFFYDELTA2,	32,	P1(	tFlt				) },
		{ "setFFCAy[]",			tVoid,	SETTER,		MAPDATAFFYDELTA2,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCFlags[]",		tFlt,	GETTER,		MAPDATAFFFLAGS,		32,	P1(	tFlt				) },
		{ "setFFCFlags[]",		tVoid,	SETTER,		MAPDATAFFFLAGS,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCEffectWidth[]",	tFlt,	GETTER,		MAPDATAFFEFFECTWIDTH,	32,	P1(	tFlt				) },
		{ "setFFCEffectWidth[]",	tVoid,	SETTER,		MAPDATAFFEFFECTWIDTH,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCEffectHeight[]",	tFlt,	GETTER,		MAPDATAFFEFFECTHEIGHT,	32,	P1(	tFlt				) },
		{ "setFFCEffectHeight[]",	tVoid,	SETTER,		MAPDATAFFEFFECTHEIGHT,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCTileWidth[]",		tFlt,	GETTER,		MAPDATAFFWIDTH,		32,	P1(	tFlt				) },
		{ "setFFCTileWidth[]",		tVoid,	SETTER,		MAPDATAFFWIDTH,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCTileHeight[]",		tFlt,	GETTER,		MAPDATAFFHEIGHT,	32,	P1(	tFlt				) },
		{ "setFFCTileHeight[]",		tVoid,	SETTER,		MAPDATAFFHEIGHT,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCLink[]",		tFlt,	GETTER,		MAPDATAFFLINK,		32,	P1(	tFlt				) },
		{ "setFFCLink[]",		tVoid,	SETTER,		MAPDATAFFLINK,		32,	P2(	tFlt,	tFlt			) },
		{ "getFFCScript[]",		tFlt,	GETTER,		MAPDATAFFSCRIPT,	32,	P1(	tFlt				) },
		{ "setFFCScript[]",		tVoid,	SETTER,		MAPDATAFFSCRIPT,	32,	P2(	tFlt,	tFlt			) },
		{ "getFFCRunning[]",		tBool,	GETTER,		MAPDATAFFINITIALISED,	32,	P1(	tFlt				) },
		{ "setFFCRunning[]",		tVoid,	SETTER,		MAPDATAFFINITIALISED,	32,	P2(	tBool,	tFlt			) },
		{ "getScriptEntry",		tFlt,	GETTER,		MAPDATASCRIPTENTRY,	1,	P0					  },
		{ "setScriptEntry",		tVoid,	SETTER,		MAPDATASCRIPTENTRY,	1,	P1(	tFlt				) },
		{ "getScriptOccupancy",		tFlt,	GETTER,		MAPDATASCRIPTOCCUPANCY, 1,	P0					  },
		{ "setScriptOccupancy",		tVoid,	SETTER,		MAPDATASCRIPTOCCUPANCY, 1,	P1(	tFlt				) },
		{ "getExitScript",		tFlt,	GETTER,		MAPDATASCRIPTEXIT,	1,	P0					  },
		{ "setExitScript",		tVoid,	SETTER,		MAPDATASCRIPTEXIT,	1,	P1(	tFlt				) },
		{ "getOceanSFX",		tFlt,	GETTER,		MAPDATAOCEANSFX,	1,	P0					  },
		{ "setOceanSFX",		tVoid,	SETTER,		MAPDATAOCEANSFX,	1,	P1(	tFlt				) },
		{ "getBossSFX",			tFlt,	GETTER,		MAPDATABOSSSFX,		1,	P0					  },
		{ "setBossSFX",			tVoid,	SETTER,		MAPDATABOSSSFX,		1,	P1(	tFlt				) },
		{ "getSecretSFX",		tFlt,	GETTER,		MAPDATASECRETSFX,	1,	P0					  },
		{ "setSecretSFX",		tVoid,	SETTER,		MAPDATASECRETSFX,	1,	P1(	tFlt				) },
		{ "getItemSFX",			tFlt,	GETTER,		MAPDATAHOLDUPSFX,	1,	P0					  },
		{ "setItemSFX",			tVoid,	SETTER,		MAPDATAHOLDUPSFX,	1,	P1(	tFlt				) },
		{ "getMIDI",			tFlt,	GETTER,		MAPDATASCREENMIDI,	1,	P0					  },
		{ "setMIDI",			tVoid,	SETTER,		MAPDATASCREENMIDI,	1,	P1(	tFlt				) },
		{ "getLensLayer",		tFlt,	GETTER,		MAPDATALENSLAYER,	1,	P0					  },
		{ "setLensLayer",		tVoid,	SETTER,		MAPDATALENSLAYER,	1,	P1(	tFlt				) },
		{ "getFlags[]",			tFlt,	GETTER,		MAPDATAFLAGS,		10,	P1(	tFlt				) },
		{ "setFlags[]",			tVoid,	SETTER,		MAPDATAFLAGS,		10,	P2(	tFlt,	tFlt			) },
		// array of 11							
		{ "getD[]",			tAny,	GETTER,		MAPDATAMISCD,		8,	P1(	tFlt				) },
		{ "setD[]",			tVoid,	SETTER,		MAPDATAMISCD,		8,	P2(	tAny,	tFlt			) },
		// array of 10 MAPDATAMISCD					
		{ "getComboD[]",		tFlt,	GETTER,		MAPDATACOMBODD,		176,	P1(	tFlt				) },
		{ "setComboD[]",		tVoid,	SETTER,		MAPDATACOMBODD,		176,	P2(	tFlt,	tFlt			) },
		{ "getComboC[]",		tFlt,	GETTER,		MAPDATACOMBOCD,		176,	P1(	tFlt				) },
		{ "setComboC[]",		tVoid,	SETTER,		MAPDATACOMBOCD,		176,	P2(	tFlt,	tFlt			) },
		{ "getComboF[]",		tFlt,	GETTER,		MAPDATACOMBOFD,		176,	P1(	tFlt				) },
		{ "setComboF[]",		tVoid,	SETTER,		MAPDATACOMBOFD,		176,	P2(	tFlt,	tFlt			) },
		{ "getComboI[]",		tFlt,	GETTER,		MAPDATACOMBOID,		176,	P1(	tFlt				) },
		{ "setComboI[]",		tVoid,	SETTER,		MAPDATACOMBOID,		176,	P2(	tFlt,	tFlt			) },
		{ "getComboT[]",		tFlt,	GETTER,		MAPDATACOMBOTD,		176,	P1(	tFlt				) },
		{ "setComboT[]",		tVoid,	SETTER,		MAPDATACOMBOTD,		176,	P2(	tFlt,	tFlt			) },
		{ "getComboS[]",		tFlt,	GETTER,		MAPDATACOMBOSD,		176,	P1(	tFlt				) },
		{ "setComboS[]",		tVoid,	SETTER,		MAPDATACOMBOSD,		176,	P2(	tFlt,	tFlt			) },
		{ "getState[]",			tBool,	GETTER,		MAPDATASCREENSTATED,	32,	P1(	tFlt				) },
		{ "setState[]",			tVoid,	SETTER,		MAPDATASCREENSTATED,	32,	P2(	tBool,	tFlt			) },
		{ "getFlags[]",			tFlt,	GETTER,		MAPDATASCREENFLAGSD,	10,	P1(	tFlt				) },
	//	{ "setFlags[]",			tVoid,	SETTER,		MAPDATASCREENFLAGSD,	10,	P2(	tFlt,	tFlt			) },
		// This is read-only, but it was not previously blocked! -Z
		{ "getEFlags[]",		tFlt,	GETTER,		MAPDATASCREENEFLAGSD,	3,	P1(	tFlt				) },
		// This is read-only, but it was not previously blocked! -Z
	//	{ "setEFlags[]",		tVoid,	SETTER,		MAPDATASCREENEFLAGSD,	3,	P2(	tFlt,	tFlt			) },
		{ "GetFFCInitD",		tAny,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetFFCInitD",		tVoid,	FUNCTION,	0,			1,	P3(	tAny,	tFlt,	tFlt		) },
		{ "GetFFCInitA",		tFlt,	FUNCTION,	0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetFFCInitA",		tFlt,	FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Map& Library::Map::instance()
{
	static Library::Map instance(REFMAPDATA, table);
	return instance;
}

//Dataclass member with two inputs, one return 
#define GET_DATACLASS_MEMBER(flabel, ffins) \
{ \
	int id = memberids[flabel]; \
	int label = lt.functionToLabel(id); \
	vector<Opcode *> code; \
	Opcode *first = new OPopRegister(new VarArgument(INDEX2)); \
	first->setLabel(label); \
	code.push_back(first); \
	code.push_back(new OPopRegister(new VarArgument(INDEX))); \
	code.push_back(new OPopRegister(new VarArgument(NUL))); \
	code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(ffins))); \
	code.push_back(new OPopRegister(new VarArgument(EXP2))); \
	code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
	rval[label] = code; \
}

//Dataclass member with three inputs, one return
#define GET_DATACLASS_ARRAY(flabel, ocode) \
{ \
	int id = memberids[flabel]; \
	int label = lt.functionToLabel(id); \
	vector<Opcode *> code; \
	Opcode *first = new OPopRegister(new VarArgument(INDEX)); \
	first->setLabel(label); \
	code.push_back(first); \
	code.push_back(new OPopRegister(new VarArgument(INDEX2))); \
	code.push_back(new OPopRegister(new VarArgument(EXP1))); \
	code.push_back(new OPopRegister(new VarArgument(NUL))); \
	code.push_back(new ocode(new VarArgument(EXP1))); \
	code.push_back(new OPopRegister(new VarArgument(EXP2))); \
	code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
	rval[label] = code; \
} 

// Dataclass member with three inputs
#define SET_DATACLASS_MEMBER(flabel, ffins) \
{ \
	int id = memberids[flabel]; \
	int label = lt.functionToLabel(id); \
	vector<Opcode *> code; \
	Opcode *first = new OPopRegister(new VarArgument(SFTEMP)); \
	first->setLabel(label); \
	code.push_back(first); \
	code.push_back(new OPopRegister(new VarArgument(INDEX2))); \
	code.push_back(new OPopRegister(new VarArgument(INDEX))); \
	code.push_back(new OPopRegister(new VarArgument(NUL))); \
	code.push_back(new OSetRegister(new VarArgument(ffins), new VarArgument(SFTEMP))); \
	code.push_back(new OPopRegister(new VarArgument(EXP2))); \
	code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
	rval[label] = code; \
}

//Dataclass Member with four inputs (int, int, int, int)
#define SET_DATACLASS_ARRAY(flabel, ffins) \
{ \
	int id = memberids[flabel]; \
	int label = lt.functionToLabel(id); \
	vector<Opcode *> code; \
	Opcode *first = new OPopRegister(new VarArgument(EXP2)); \
	first->setLabel(label); \
	code.push_back(first); \
	code.push_back(new OPopRegister(new VarArgument(INDEX))); \
	code.push_back(new OPopRegister(new VarArgument(EXP1))); \
	code.push_back(new OPopRegister(new VarArgument(INDEX2))); \
	code.push_back(new OPopRegister(new VarArgument(NUL))); \
	code.push_back(new OSetRegister(new VarArgument(ffins), new VarArgument(EXP2))); \
	code.push_back(new OPopRegister(new VarArgument(EXP2))); \
	code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
	rval[label] = code; \
} 

void Library::Map::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

        // float GetEnemy(float, float, float)
	GET_DATACLASS_ARRAY("GetEnemy", OGetScreenEnemy);

        // float GetDoor(float, float, float)
	GET_DATACLASS_ARRAY("GetDoor", OGetScreenDoor);

        // void SetEnemy(float, float, float, float)
	SET_DATACLASS_ARRAY("SetEnemy", SETSCREENENEMY);

        // void SetDoor(float, float, float, float)
	SET_DATACLASS_ARRAY("SetDoor", SETSCREENDOOR);

        // void SetWidth(float, float, float)
	SET_DATACLASS_MEMBER("SetWidth", SCREENWIDTH);

        // float GetWidth(float, float)
	GET_DATACLASS_MEMBER("GetWidth", SCREENWIDTH);

        // void SetHeight(float, float, float)
	SET_DATACLASS_MEMBER("SetHeight", SCREENHEIGHT);

        // float GetHeight(float, float)
	GET_DATACLASS_MEMBER("GetHeight", SCREENHEIGHT);

        // void SetViewX(float, float, float)
	SET_DATACLASS_MEMBER("SetViewX", SCREENVIEWX);

        // float GetViewX(float, float)
	GET_DATACLASS_MEMBER("GetViewX", SCREENVIEWX);

        // void SetViewY(float, float, float)
	SET_DATACLASS_MEMBER("SetViewY", SCREENVIEWY);

        // float GetViewY(float, float)
	GET_DATACLASS_MEMBER("GetViewY", SCREENVIEWY);

        // void SetGuy(float, float, float)
	SET_DATACLASS_MEMBER("SetGuy", SCREENGUY);

        // float GetGuy(float, float)
	GET_DATACLASS_MEMBER("GetGuy", SCREENGUY);

        // void SetString(float, float, float)
	SET_DATACLASS_MEMBER("SetString", SCREENSTRING);

        // float GetString(float, float)
	GET_DATACLASS_MEMBER("GetString", SCREENSTRING);

        // void SetRoomType(float, float, float)
	SET_DATACLASS_MEMBER("SetRoomType", SCREENROOM);

        // float GetRoomType(float, float)
	GET_DATACLASS_MEMBER("GetRoomType", SCREENROOM);

        // void SetEntryX(float, float, float)
	SET_DATACLASS_MEMBER("SetEntryX", SCREENENTX);

        // float GetEntryX(float, float)
	GET_DATACLASS_MEMBER("GetEntryX", SCREENENTX);

        // void SetEntryY(float, float, float)
	SET_DATACLASS_MEMBER("SetEntryY", SCREENENTY);

        // float GetEntryY(float, float)
	GET_DATACLASS_MEMBER("GetEntryY", SCREENENTY);

        // void SetItem(float, float, float)
	SET_DATACLASS_MEMBER("SetItem", SCREENITEM);

        // float GetItem(float, float)
	GET_DATACLASS_MEMBER("GetItem", SCREENITEM);

        // void SetUndercombo(float, float, float)
	SET_DATACLASS_MEMBER("SetUndercombo", SCREENUNDCMB);

        // float GetUndercombo(float, float)
	GET_DATACLASS_MEMBER("GetUndercombo", SCREENUNDCMB);

        // void SetUnderCSet(float, float, float)
	SET_DATACLASS_MEMBER("SetUnderCSet", SCREENUNDCST);

        // float GetUnderCSet(float, float)
	GET_DATACLASS_MEMBER("GetUnderCSet", SCREENUNDCST);

        // void SetCatchall(float, float, float)
	SET_DATACLASS_MEMBER("SetCatchall", SCREENCATCH);

        // float GetCatchall(float, float)
	GET_DATACLASS_MEMBER("GetCatchall", SCREENCATCH);

        // void SetLayerOpacity(float, float, float, float)
	SET_DATACLASS_ARRAY("SetLayerOpacity", SETSCREENLAYOP); 

        // float GetLayerOpacity(float, float, float)
	GET_DATACLASS_ARRAY("GetLayerOpacity", OGetScreenLayerOpacity);

        // void SetSecretCombo(float, float, float, float)
	SET_DATACLASS_ARRAY("SetSecretCombo", SETSCREENSECCMB); 

        // float GetSecretCombo(float, float, float)
	GET_DATACLASS_ARRAY("GetSecretCombo", OGetScreenSecretCombo);

        // void SetSecretCSet(float, float, float, float)
	SET_DATACLASS_ARRAY("SetSecretCSet", SETSCREENSECCST);

        // float GetSecretCSet(float, float, float)
	GET_DATACLASS_ARRAY("GetSecretCSet", OGetScreenSecretCSet);

        // void SetSecretFlag(float, float, float, float)
	SET_DATACLASS_ARRAY("SetSecretFlag", SETSCREENSECFLG);

        // float GetSecretFlag(float, float, float)
	GET_DATACLASS_ARRAY("GetSecretFlag", OGetScreenSecretFlag);

        // void SetLayerMap(float, float, float, float)
	SET_DATACLASS_ARRAY("SetLayerMap", SETSCREENLAYMAP);

        // float GetLayerMap(float, float, float)
	GET_DATACLASS_ARRAY("GetLayerMap", OGetScreenLayerMap);

        // void SetLayerScreen(float, float, float, float)
	SET_DATACLASS_ARRAY("SetLayerScreen", SETSCREENLAYSCR);

        // float GetLayerScreen(float, float, float)
	GET_DATACLASS_ARRAY("GetLayerScreen", OGetScreenLayerScreen);

        // void SetPath(float, float, float, float)
	SET_DATACLASS_ARRAY("SetPath", SETSCREENPATH);

        // float GetPath(float, float, float)
	GET_DATACLASS_ARRAY("GetPath", OGetScreenPath);

        // void SetWarpReturnX(float, float, float, float)
	SET_DATACLASS_ARRAY("SetWarpReturnX", SETSCREENWARPRX);

        // float GetWarpReturnX(float, float, float)
	GET_DATACLASS_ARRAY("GetWarpReturnX", OGetScreenWarpReturnX);

        // void SetWarpReturnY(float, float, float, float)
	SET_DATACLASS_ARRAY("SetWarpReturnY", SETSCREENWARPRY);

        // float GetWarpReturnY(float, float, float)
	GET_DATACLASS_ARRAY("GetWarpReturnY", OGetScreenWarpReturnY);

	// float GetFFCInitD(float, float, float)
	{
		int id = memberids["GetFFCInitD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(MAPDATAINTID)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	
	}
    
	// void SetFFCInitD(float, float, float, float)
	{
		int id = memberids["SetFFCInitD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(MAPDATAINTID), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
    
	// float GetFFCInitA(float, float, float)
	{
		int id = memberids["GetFFCInitA"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(MAPDATAINITA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	
	}
    
	// void SetFFCInitA(float, float, float, float)
	{
		int id = memberids["SetFFCInitA"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(MAPDATAINITA), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

#undef GET_DATACLASS_MEMBER
#undef GET_DATACLASS_ARRAY
#undef SET_DATACLASS_MEMBER
#undef SET_DATACLASS_ARRAY

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
