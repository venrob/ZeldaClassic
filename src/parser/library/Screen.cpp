#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_SCREEN
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,				rettype,	type,		var,				num,	params
		{ "getD[]",			tAny,		GETTER,		SDD,				8,	P1(	tFlt																) },
		{ "setD[]",			tVoid,		SETTER,		SDD,				8,	P2(	tFlt,	tAny															) },
		{ "getComboD[]",		tFlt,		GETTER,		COMBODD,			176,	P1(	tFlt																) },
		{ "setComboD[]",		tVoid,		SETTER,		COMBODD,			176,	P2(	tFlt,	tFlt															) },
		{ "getComboC[]",		tFlt,		GETTER,		COMBOCD,			176,	P1(	tFlt																) },
		{ "setComboC[]",		tVoid,		SETTER,		COMBOCD,			176,	P2(	tFlt,	tFlt															) },
		{ "getComboF[]",		tFlt,		GETTER,		COMBOFD,			176,	P1(	tFlt																) },
		{ "setComboF[]",		tVoid,		SETTER,		COMBOFD,			176,	P2(	tFlt,	tFlt															) },
		{ "getComboI[]",		tFlt,		GETTER,		COMBOID,			176,	P1(	tFlt																) },
		{ "setComboI[]",		tVoid,		SETTER,		COMBOID,			176,	P2(	tFlt,	tFlt															) },
		{ "getComboT[]",		tFlt,		GETTER,		COMBOTD,			176,	P1(	tFlt																) },
		{ "setComboT[]",		tVoid,		SETTER,		COMBOTD,			176,	P2(	tFlt,	tFlt															) },
		{ "getComboS[]",		tFlt,		GETTER,		COMBOSD,			176,	P1(	tFlt																) },
		{ "setComboS[]",		tVoid,		SETTER,		COMBOSD,			176,	P2(	tFlt,	tFlt															) },
		{ "getDoor[]",			tFlt,		GETTER,		SCRDOORD,			4,	P1(	tFlt																) },
		{ "setDoor[]",			tVoid,		SETTER,		SCRDOORD,			4,	P2(	tFlt,	tFlt															) },
		{ "getState[]",			tBool,		GETTER,		SCREENSTATED,			32,	P1(	tFlt																) },
		{ "setState[]",			tVoid,		SETTER,		SCREENSTATED,			32,	P2(	tFlt,	tBool															) },
		{ "getLit",			tBool,		GETTER,		LIT,				1,	P0																	  },
		{ "setLit",			tVoid,		SETTER,		LIT,				1,	P1(	tBool																) },
		{ "getWavy",			tFlt,		GETTER,		WAVY,				1,	P0																	  },
		{ "setWavy",			tVoid,		SETTER,		WAVY,				1,	P1(	tFlt																) },
		{ "getQuake",			tFlt,		GETTER,		QUAKE,				1,	P0																	  },
		{ "setQuake",			tVoid,		SETTER,		QUAKE,				1,	P1(	tFlt																) },
		{ "NumItems",			tFlt,		GETTER,		ITEMCOUNT,			1,	P0																	  },
		{ "LoadItem",			tItm,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "CreateItem",			tItm,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "LoadFFC",			tFfc,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "NumNPCs",			tFlt,		GETTER,		NPCCOUNT,			1,	P0																	  },
		{ "LoadNPC",			tNpc,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "CreateNPC",			tNpc,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "ClearSprites",		tVoid,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "Rectangle",			tVoid,		FUNCTION,	0,				1,	P12(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tFlt					) },
		{ "Circle",			tVoid,		FUNCTION,	0,				1,	P11(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tFlt						) },
		{ "Arc",			tVoid,		FUNCTION,	0,				1,	P14(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tBool,	tFlt			) },
		{ "Ellipse",			tVoid,		FUNCTION,	0,				1,	P12(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tFlt					) },
		{ "Line",			tVoid,		FUNCTION,	0,				1,	P11(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt						) },
		{ "Spline",			tVoid,		FUNCTION,	0,				1,	P11(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt						) },
		{ "PutPixel",			tVoid,		FUNCTION,	0,				1,	P8(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "DrawCharacter",		tVoid,		FUNCTION,	0,				1,	P10(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt							) },
		{ "DrawInteger",		tVoid,		FUNCTION,	0,				1,	P11(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt						) },
		{ "DrawTile",			tVoid,		FUNCTION,	0,				1,	P15(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tFlt		) },
		{ "DrawCombo",			tVoid,		FUNCTION,	0,				1,	P16(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool,	tFlt	) },
		{ "Quad",			tVoid,		FUNCTION,	0,				1,	P15(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt		) },
		{ "Triangle",			tVoid,		FUNCTION,	0,				1,	P13(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt				) },
		{ "Quad3D",			tVoid,		FUNCTION,	0,				1,	P8(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "Triangle3D",			tVoid,		FUNCTION,	0,				1,	P8(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "FastTile",			tVoid,		FUNCTION,	0,				1,	P6(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt											) },
		{ "FastCombo",			tVoid,		FUNCTION,	0,				1,	P6(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt											) },
		{ "DrawString",			tVoid,		FUNCTION,	0,				1,	P9(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt								) },
		{ "DrawLayer",			tVoid,		FUNCTION,	0,				1,	P8(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt									) },
		{ "DrawScreen",			tVoid,		FUNCTION,	0,				1,	P6(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt											) },
		{ "DrawBitmap",			tVoid,		FUNCTION,	0,				1,	P12(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool					) },
		{ "DrawBitmapEx",		tVoid,		FUNCTION,	0,				1,	P16(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tBool	) },
		{ "SetRenderTarget",		tVoid,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "Message",			tVoid,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "NumLWeapons",		tFlt,		GETTER,		LWPNCOUNT,			1,	P0																	  },
		{ "LoadLWeapon",		tLW,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "CreateLWeapon",		tLW,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "NumEWeapons",		tFlt,		GETTER,		EWPNCOUNT,			1,	P0																	  },
		{ "LoadEWeapon",		tEW,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "CreateEWeapon",		tEW,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "isSolid",			tBool,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt															) },
		{ "SetSideWarp",		tVoid,		FUNCTION,	0,				1,	P4(	tFlt,	tFlt,	tFlt,	tFlt													) },
		{ "SetTileWarp",		tVoid,		FUNCTION,	0,				1,	P4(	tFlt,	tFlt,	tFlt,	tFlt													) },
		{ "LayerScreen",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "LayerMap",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "getFlags[]",			tFlt,		GETTER,		SCREENFLAGSD,			10,	P1(	tFlt																) },
		{ "setFlags[]",			tVoid,		SETTER,		SCREENFLAGSD,			10,	P2(	tFlt,	tFlt															) },
		// This is read-only, but it was not previously blocked! -Z
		{ "getEFlags[]",		tFlt,		GETTER,		SCREENEFLAGSD,			3,	P1(	tFlt																) },
		// This is read-only, but it was not previously blocked! -Z
		{ "setEFlags[]",		tVoid,		SETTER,		SCREENEFLAGSD,			3,	P2(	tFlt,	 tFlt															) },
		{ "TriggerSecrets",		tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "getRoomType",		tFlt,		GETTER,		ROOMTYPE,			1,	P0																	  },
		{ "setRoomType",		tVoid,		SETTER,		ROOMTYPE,			1,	P1(	tFlt																) },
		{ "getRoomData",		tFlt,		GETTER,		ROOMDATA,			1,	P0																	  },
		{ "setRoomData",		tVoid,		SETTER,		ROOMDATA,			1,	P1(	tFlt																) },
		{ "getMovingBlockX",		tFlt,		GETTER,		PUSHBLOCKX,			1,	P0																	  },
		{ "setMovingBlockX",		tVoid,		SETTER,		PUSHBLOCKX,			1,	P1(	tFlt																) },
		{ "getMovingBlockY",		tFlt,		GETTER,		PUSHBLOCKY,			1,	P0																	  },
		{ "setMovingBlockY",		tVoid,		SETTER,		PUSHBLOCKY,			1,	P1(	tFlt																) },
		{ "getMovingBlockCombo",	tFlt,		GETTER,		PUSHBLOCKCOMBO,			1,	P0																	  },
		{ "setMovingBlockCombo",	tVoid,		SETTER,		PUSHBLOCKCOMBO,			1,	P1(	tFlt																) },
		{ "getMovingBlockCSet",		tFlt,		GETTER,		PUSHBLOCKCSET,			1,	P0																	  },
		{ "setMovingBlockCSet",		tVoid,		SETTER,		PUSHBLOCKCSET,			1,	P1(	tFlt																) },
		{ "getUnderCombo",		tFlt,		GETTER,		UNDERCOMBO,			1,	P0																	  },
		{ "setUnderCombo",		tVoid,		SETTER,		UNDERCOMBO,			1,	P1(	tFlt																) },
		{ "getUnderCSet",		tFlt,		GETTER,		UNDERCSET,			1,	P0																	  },
		{ "setUnderCSet",		tVoid,		SETTER,		UNDERCSET,			1,	P1(	tFlt																) },
		{ "GetSideWarpDMap",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "GetSideWarpScreen",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "GetSideWarpType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "GetTileWarpDMap",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "GetTileWarpScreen",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "GetTileWarpType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt																) },
		{ "ZapIn",			tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "ZapOut",			tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "WavyIn",			tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "WavyOut",			tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "OpeningWipe",		tVoid,		FUNCTION,	0,				1,	P0																	  },
		{ "CreateLWeaponDx",		tLW,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt															) },
	//	{ "Polygon",			tVoid,		FUNCTION,	0,				1,	P15(	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt,	tFlt		) },
		{ "TriggerSecret",		tVoid,		FUNCTION,	0,				1,	P1(	tFlt																) },
		// mapdata m-> class variables copied to Screen->
		{ "getValid",			tFlt,		GETTER,		SCREENDATAVALID,		1,	P0																	  },
		{ "setValid",			tVoid,		SETTER,		SCREENDATAVALID,		1,	P1(	tFlt																) },
		{ "getGuy",			tFlt,		GETTER,		SCREENDATAGUY,			1,	P0																	  },
		{ "setGuy",			tVoid,		SETTER,		SCREENDATAGUY,			1,	P1(	tFlt																) },
		{ "getString",			tFlt,		GETTER,		SCREENDATASTRING,		1,	P0																	  },
		{ "setString",			tVoid,		SETTER,		SCREENDATASTRING,		1,	P1(	tFlt																) },
		{ "getRoomType",		tFlt,		GETTER,		SCREENDATAROOM,			1,	P0																	  },
		{ "setRoomType",		tVoid,		SETTER,		SCREENDATAROOM,			1,	P1(	tFlt																) },
		{ "getItem",			tFlt,		GETTER,		SCREENDATAITEM,			1,	P0																	  },
		{ "setItem",			tVoid,		SETTER,		SCREENDATAITEM,			1,	P1(	tFlt																) },
		{ "getHasItem",			tFlt,		GETTER,		SCREENDATAHASITEM,		1,	P0																	  },
		{ "setHasItem",			tVoid,		SETTER,		SCREENDATAHASITEM,		1,	P1(	tFlt																) },
		{ "getTileWarpType[]",		tFlt,		GETTER,		SCREENDATATILEWARPTYPE,		4,	P1(	tFlt																) },
		{ "setTileWarpType[]",		tVoid,		SETTER,		SCREENDATATILEWARPTYPE,		4,	P2(	tFlt,	tFlt															) },
		{ "getTileWarpOverlayFlags",	tFlt,		GETTER,		SCREENDATATILEWARPOVFLAGS,	1,	P0																	  },
		{ "setTileWarpOverlayFlags",	tVoid,		SETTER,		SCREENDATATILEWARPOVFLAGS,	1,	P1(	tFlt																) },
		{ "getDoorComboSet",		tFlt,		GETTER,		SCREENDATADOORCOMBOSET,		1,	P0																	  },
		{ "setDoorComboSet",		tVoid,		SETTER,		SCREENDATADOORCOMBOSET,		1,	P1(	tFlt																) },
		{ "getWarpReturnX[]",		tFlt,		GETTER,		SCREENDATAWARPRETX,		4,	P1(	tFlt																) },
		{ "setWarpReturnX[]",		tVoid,		SETTER,		SCREENDATAWARPRETX,		4,	P2(	tFlt,	tFlt															) },
		{ "getWarpReturnY[]",		tFlt,		GETTER,		SCREENDATAWARPRETY,		4,	P1(	tFlt																) },
		{ "setWarpReturnY[]",		tVoid,		SETTER,		SCREENDATAWARPRETY,		4,	P2(	tFlt,	tFlt															) },
		{ "getWarpReturnC",		tFlt,		GETTER,		SCREENDATAWARPRETURNC,		1,	P0																	  },
		{ "setWarpReturnC",		tVoid,		SETTER,		SCREENDATAWARPRETURNC,		1,	P1(	tFlt																) },
		{ "getStairsX",			tFlt,		GETTER,		SCREENDATASTAIRX,		1,	P0																	  },
		{ "setStairsX",			tVoid,		SETTER,		SCREENDATASTAIRX,		1,	P1(	tFlt																) },
		{ "getStairsY",			tFlt,		GETTER,		SCREENDATASTAIRY,		1,	P0																	  },
		{ "setStairsY",			tVoid,		SETTER,		SCREENDATASTAIRY,		1,	P1(	tFlt																) },
		{ "getItemX",			tFlt,		GETTER,		SCREENDATAITEMX,		1,	P0																	  },
		{ "setItemX",			tVoid,		SETTER,		SCREENDATAITEMX,		1,	P1(	tFlt																) },
		{ "getItemY",			tFlt,		GETTER,		SCREENDATAITEMY,		1,	P0																	  },
		{ "setItemY",			tVoid,		SETTER,		SCREENDATAITEMY,		1,	P1(	tFlt																) },
		{ "getCSet",			tFlt,		GETTER,		SCREENDATACOLOUR,		1,	P0																	  },
		{ "setCSet",			tVoid,		SETTER,		SCREENDATACOLOUR,		1,	P1(	tFlt																) },
		{ "getEnemyFlags",		tFlt,		GETTER,		SCREENDATAENEMYFLAGS,		1,	P0																	  },
		{ "setEnemyFlags",		tVoid,		SETTER,		SCREENDATAENEMYFLAGS,		1,	P1(	tFlt																) },
		{ "getTileWarpDMap[]",		tFlt,		GETTER,		SCREENDATATILEWARPDMAP,		4,	P1(	tFlt																) },
		{ "setTileWarpDMap[]",		tVoid,		SETTER,		SCREENDATATILEWARPDMAP,		4,	P2(	tFlt,	tFlt															) },
		{ "getTileWarpScreen[]",	tFlt,		GETTER,		SCREENDATATILEWARPSCREEN,	4,	P1(	tFlt																) },
		{ "setTileWarpScreen[]",	tVoid,		SETTER,		SCREENDATATILEWARPSCREEN,	4,	P2(	tFlt,	tFlt															) },
		{ "getExitDir",			tFlt,		GETTER,		SCREENDATAEXITDIR,		1,	P0																	  },
		{ "setExitDir",			tVoid,		SETTER,		SCREENDATAEXITDIR,		1,	P1(	tFlt																) },
		{ "getEnemy[]",			tFlt,		GETTER,		SCREENDATAENEMY,		10,	P1(	tFlt																) },
		{ "setEnemy[]",			tVoid,		SETTER,		SCREENDATAENEMY,		10,	P2(	tFlt,	tFlt															) },
		{ "getPattern",			tFlt,		GETTER,		SCREENDATAPATTERN,		1,	P0																	  },
		{ "setPattern",			tVoid,		SETTER,		SCREENDATAPATTERN,		1,	P1(	tFlt																) },
		{ "getSideWarpType[]",		tFlt,		GETTER,		SCREENDATASIDEWARPTYPE,		4,	P1(	tFlt																) },
		{ "setSideWarpType[]",		tVoid,		SETTER,		SCREENDATASIDEWARPTYPE,		4,	P2(	tFlt,	tFlt															) },
		{ "getSideWarpOverlayFlags",	tFlt,		GETTER,		SCREENDATASIDEWARPOVFLAGS,	1,	P0																	  },
		{ "setSideWarpOverlayFlags",	tVoid,		SETTER,		SCREENDATASIDEWARPOVFLAGS,	1,	P1(	tFlt																) },
		{ "getWarpArrivalX",		tFlt,		GETTER,		SCREENDATAWARPARRIVALX,		1,	P0																	  },
		{ "setWarpArrivalX",		tVoid,		SETTER,		SCREENDATAWARPARRIVALX,		1,	P1(	tFlt																) },
		{ "getWarpArrivalY",		tFlt,		GETTER,		SCREENDATAWARPARRIVALY,		1,	P0																	  },
		{ "setWarpArrivalY",		tVoid,		SETTER,		SCREENDATAWARPARRIVALY,		1,	P1(	tFlt																) },
		{ "getMazePath[]",		tFlt,		GETTER,		SCREENDATAPATH,			4,	P1(	tFlt																) },
		{ "setMazePath[]",		tVoid,		SETTER,		SCREENDATAPATH,			4,	P2(	tFlt,	tFlt															) },
		{ "getSideWarpScreen[]",	tFlt,		GETTER,		SCREENDATASIDEWARPSC,		4,	P1(	tFlt																) },
		{ "setSideWarpScreen[]",	tVoid,		SETTER,		SCREENDATASIDEWARPSC,		4,	P2(	tFlt,	tFlt															) },
		{ "getSideWarpDMap[]",		tFlt,		GETTER,		SCREENDATASIDEWARPDMAP,		4,	P1(	tFlt																) },
		{ "setSideWarpDMap[]",		tVoid,		SETTER,		SCREENDATASIDEWARPDMAP,		4,	P2(	tFlt,	tFlt															) },
		{ "getSideWarpIndex",		tFlt,		GETTER,		SCREENDATASIDEWARPINDEX,	1,	P0																	  },
		{ "setSideWarpIndex",		tVoid,		SETTER,		SCREENDATASIDEWARPINDEX,	1,	P1(	tFlt																) },
		{ "getUnderCombo",		tFlt,		GETTER,		SCREENDATAUNDERCOMBO,		1,	P0																	  },
		{ "setUnderCombo",		tVoid,		SETTER,		SCREENDATAUNDERCOMBO,		1,	P1(	tFlt																) },
		{ "getUnderCSet",		tFlt,		GETTER,		SCREENDATAUNDERCSET,		1,	P0																	  },
		{ "setUnderCSet",		tVoid,		SETTER,		SCREENDATAUNDERCSET,		1,	P1(	tFlt																) },
		{ "getCatchall",		tFlt,		GETTER,		SCREENDATACATCHALL,		1,	P0																	  },
		{ "setCatchall",		tVoid,		SETTER,		SCREENDATACATCHALL,		1,	P1(	tFlt																) },
		{ "getCSensitive",		tFlt,		GETTER,		SCREENDATACSENSITIVE,		1,	P0																	  },
		{ "setCSensitive",		tVoid,		SETTER,		SCREENDATACSENSITIVE,		1,	P1(	tFlt																) },
		{ "getNoReset",			tFlt,		GETTER,		SCREENDATANORESET,		1,	P0																	  },
		{ "setNoReset",			tVoid,		SETTER,		SCREENDATANORESET,		1,	P1(	tFlt																) },
		{ "getNoCarry",			tFlt,		GETTER,		SCREENDATANOCARRY,		1,	P0																	  },
		{ "setNoCarry",			tVoid,		SETTER,		SCREENDATANOCARRY,		1,	P1(	tFlt																) },
		{ "getLayerMap[]",		tFlt,		GETTER,		SCREENDATALAYERMAP,		6,	P1(	tFlt																) },
		{ "setLayerMap[]",		tVoid,		SETTER,		SCREENDATALAYERMAP,		6,	P2(	tFlt,	tFlt															) },
		{ "getLayerScreen[]",		tFlt,		GETTER,		SCREENDATALAYERSCREEN,		6,	P1(	tFlt																) },
		{ "setLayerScreen[]",		tVoid,		SETTER,		SCREENDATALAYERSCREEN,		6,	P2(	tFlt,	tFlt															) },
		{ "getLayerOpacity[]",		tFlt,		GETTER,		SCREENDATALAYEROPACITY,		6,	P1(	tFlt																) },
		{ "setLayerOpacity[]",		tVoid,		SETTER,		SCREENDATALAYEROPACITY,		6,	P2(	tFlt,	tFlt															) },
		{ "getTimedWarpTimer",		tFlt,		GETTER,		SCREENDATATIMEDWARPTICS,	1,	P0																	  },
		{ "setTimedWarpTimer",		tVoid,		SETTER,		SCREENDATATIMEDWARPTICS,	1,	P1(	tFlt																) },
		{ "getNextMap",			tFlt,		GETTER,		SCREENDATANEXTMAP,		1,	P0																	  },
		{ "setNextMap",			tVoid,		SETTER,		SCREENDATANEXTMAP,		1,	P1(	tFlt																) },
		{ "getNextScreen",		tFlt,		GETTER,		SCREENDATANEXTSCREEN,		1,	P0																	  },
		{ "setNextScreen",		tVoid,		SETTER,		SCREENDATANEXTSCREEN,		1,	P1(	tFlt																) },
		{ "getSecretCombo[]",		tFlt,		GETTER,		SCREENDATASECRETCOMBO,		128,	P1(	tFlt																) },
		{ "setSecretCombo[]",		tVoid,		SETTER,		SCREENDATASECRETCOMBO,		128,	P2(	tFlt,	tFlt															) },
		{ "getSecretCSet[]",		tFlt,		GETTER,		SCREENDATASECRETCSET,		128,	P1(	tFlt																) },
		{ "setSecretCSet[]",		tVoid,		SETTER,		SCREENDATASECRETCSET,		128,	P2(	tFlt,	tFlt															) },
		{ "getSecretFlags[]",		tFlt,		GETTER,		SCREENDATASECRETFLAG,		128,	P1(	tFlt																) },
		{ "setSecretFlags[]",		tVoid,		SETTER,		SCREENDATASECRETFLAG,		128,	P2(	tFlt,	tFlt															) },
		{ "getViewX",			tFlt,		GETTER,		SCREENDATAVIEWX,		1,	P0																	  },
		{ "setViewX",			tVoid,		SETTER,		SCREENDATAVIEWX,		1,	P1(	tFlt																) },
		{ "getViewY",			tFlt,		GETTER,		SCREENDATAVIEWY,		1,	P0																	  },
		{ "setViewY",			tVoid,		SETTER,		SCREENDATAVIEWY,		1,      P1(	tFlt																) },
		{ "getWidth",			tFlt,		GETTER,		SCREENDATASCREENWIDTH,		1,	P0																	  },
		{ "setWidth",			tVoid,		SETTER,		SCREENDATASCREENWIDTH,		1,	P1(	tFlt																) },
		{ "getHeight",			tFlt,		GETTER,		SCREENDATASCREENHEIGHT,		1,	P0																	  },
		{ "setHeight",			tVoid,		SETTER,		SCREENDATASCREENHEIGHT,		1,	P1(	tFlt																) },
		{ "getEntryX",			tFlt,		GETTER,		SCREENDATAENTRYX,		1,	P0																	  },
		{ "setEntryX",			tVoid,		SETTER,		SCREENDATAENTRYX,		1,	P1(	tFlt																) },
		{ "getEntryY",			tFlt,		GETTER,		SCREENDATAENTRYY,		1,	P0																	  },
		{ "setEntryY",			tVoid,		SETTER,		SCREENDATAENTRYY,		1,	P1(	tFlt																) },
		{ "getNumFFCs",			tFlt,		GETTER,		SCREENDATANUMFF,		1,	P0																	  },
		{ "setNumFFCs",			tVoid,		SETTER,		SCREENDATANUMFF,		1,	P1(	tFlt																) },
		{ "getScriptEntry",		tFlt,		GETTER,		SCREENDATASCRIPTENTRY,		1,	P0																	  },
		{ "setScriptEntry",		tVoid,		SETTER,		SCREENDATASCRIPTENTRY,		1,	P1(	tFlt																) },
		{ "getScriptOccupancy",		tFlt,		GETTER,		SCREENDATASCRIPTOCCUPANCY,	1,	P0																	  },
		{ "setScriptOccupancy",		tVoid,		SETTER,		SCREENDATASCRIPTOCCUPANCY,	1,	P1(	tFlt																) },
		{ "getExitScript",		tFlt,		GETTER,		SCREENDATASCRIPTEXIT,		1,	P0																	  },
		{ "setExitScript",		tVoid,		SETTER,		SCREENDATASCRIPTEXIT,		1,	P1(	tFlt																) },
		{ "getOceanSFX",		tFlt,		GETTER,		SCREENDATAOCEANSFX,		1,	P0																	  },
		{ "setOceanSFX",		tVoid,		SETTER,		SCREENDATAOCEANSFX,		1,	P1(	tFlt																) },
		{ "getBossSFX",			tFlt,		GETTER,		SCREENDATABOSSSFX,		1,	P0																	  },
		{ "setBossSFX",			tVoid,		SETTER,		SCREENDATABOSSSFX,		1,	P1(	tFlt																) },
		{ "getSecretSFX",		tFlt,		GETTER,		SCREENDATASECRETSFX,		1,	P0																	  },
		{ "setSecretSFX",		tVoid,		SETTER,		SCREENDATASECRETSFX,		1,	P1(	tFlt																) },
		{ "getItemSFX",			tFlt,		GETTER,		SCREENDATAHOLDUPSFX,		1,	P0	   },
		{ "setItemSFX",			tVoid,		SETTER,		SCREENDATAHOLDUPSFX,		1,	P1(	tFlt																) },
		{ "getMIDI",			tFlt,		GETTER,		SCREENDATASCREENMIDI,		1,	P0																	  },
		{ "setMIDI",			tVoid,		SETTER,		SCREENDATASCREENMIDI,		1,	P1(	tFlt																) },
		{ "getLensLayer",		tFlt,		GETTER,		SCREENDATALENSLAYER,		1,	P0																	  },
		{ "setLensLayer",		tVoid,		SETTER,		SCREENDATALENSLAYER,		1,	P1(	tFlt																) },
		{ "getScreenFlags[]",		tFlt,		GETTER,		SCREENDATAFLAGS,		10,	P1(	tFlt																) },
		{ "setScreenFlags[]",		tVoid,		SETTER,		SCREENDATAFLAGS,		10,	P2(	tFlt,	tFlt															) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Screen& Library::Screen::instance()
{
	static Library::Screen instance(NUL, table);
	return instance;
}

#define POP_ARGS(num_args, t) \
	for (int _i(0); _i < num_args; ++_i) \
		code.push_back(new OPopRegister(new VarArgument(t)))

void Library::Screen::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// item LoadItem(int)
	{
		int id = memberids["LoadItem"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		//convert from 1-index to 0-index
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OLoadItemRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFITEM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// item CreateItem(int)
	{
		int id = memberids["CreateItem"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OCreateItemRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFITEM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// ffc LoadFFC(int)
	{
		int id = memberids["LoadFFC"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		//code.push_back(new OSetRegister(new VarArgument(REFFFC), new VarArgument(EXP1)));
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// npc LoadNPC(int)
	{
		int id = memberids["LoadNPC"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		//convert from 1-index to 0-index
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OLoadNPCRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFNPC)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// npc CreateNPC(int)
	{
		int id = memberids["CreateNPC"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OCreateNPCRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFNPC)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// lwpn LoadLWeapon(int)
	{
		int id = memberids["LoadLWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		//convert from 1-index to 0-index
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OLoadLWpnRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFLWPN)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// lwpn CreateLWeapon(int)
	{
		int id = memberids["CreateLWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OCreateLWpnRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFLWPN)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	// ewpn LoadEWeapon(int)
	{
		int id = memberids["LoadEWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		//convert from 1-index to 0-index
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OLoadEWpnRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFEWPN)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	// ewpn CreateEWeapon(int)
	{
		int id = memberids["CreateEWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OCreateEWpnRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFEWPN)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void ClearSprites(int)
	{
		int id = memberids["ClearSprites"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OClearSpritesRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFNPC)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void Rectangle(float, float, float, float, float, float, float, float, float, float, bool, float)
	{
		int id = memberids["Rectangle"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ORectangleRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(12, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Circle(float, float, float, float, float, float, float, float, float, bool, float)
	{
		int id = memberids["Circle"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OCircleRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(11, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Arc(float, float, float, float, float, float, float, float, float, float, float, bool, bool, float)
	{
		int id = memberids["Arc"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OArcRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(14, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Ellipse(float, float, float, float, float, bool, float, float, float)
	{
		int id = memberids["Ellipse"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OEllipseRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(12, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Line(float, float, float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Line"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OLineRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(11, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Spline(float, float, float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Spline"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSplineRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(11, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void PutPixel(float, float, float, float, float, float, float, float)
	{
		int id = memberids["PutPixel"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPutPixelRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(8, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawCharacter(float, float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["DrawCharacter"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawCharRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(10, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawInteger(float, float, float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["DrawInteger"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawIntRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(11, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawTile(float, float, float, float, float, bool, float, float, float)
	{
		int id = memberids["DrawTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawTileRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(15, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawCombo(float, float, float, float, float, bool, float, float, float)
	{
		int id = memberids["DrawCombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawComboRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(16, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Quad(float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Quad"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OQuadRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(15, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Triangle(float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Triangle"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OTriangleRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(13, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void Quad3D(float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Quad3D"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OQuad3DRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(8, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Triangle3D(float, float, float, float, float, float, float, float, float)
	{
		int id = memberids["Triangle3D"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OTriangle3DRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(8, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}

	// void FastTile(float, float, float, float, float)
	{
		int id = memberids["FastTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OFastTileRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void FastCombo(float, float, float, float, float)
	{
		int id = memberids["FastCombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OFastComboRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawString(float, float, float, float, float, float, float, int *string)
	{
		int id = memberids["DrawString"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawStringRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(9, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawLayer(float, float, float, float, float, float, float, float)
	{
		int id = memberids["DrawLayer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawLayerRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(8, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawScreen(float, float, float, float, float, float)
	{
		int id = memberids["DrawScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawScreenRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void DrawBitmap(float, float, float, float, float, float, float, float, float, bool)
	{
		int id = memberids["DrawBitmap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawBitmapRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(12, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void SetRenderTarget(bitmap)
	{
		int id = memberids["SetRenderTarget"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetRenderTargetRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void Message(float)
	{
		int id = memberids["Message"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OMessageRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// bool isSolid(int, int)
	{
		int id = memberids["isSolid"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OIsSolid(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSideWarp(float, float, float, float)
	{
		int id = memberids["SetSideWarp"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetSideWarpRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void SetTileWarp(float, float, float, float)
	{
		int id = memberids["SetTileWarp"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetTileWarpRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float LayerScreen(float)
	{
		int id = memberids["LayerScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLayerScreenRegister(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float LayerMap(float)
	{
		int id = memberids["LayerMap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLayerMapRegister(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void TriggerSecrets()
	{
		int id = memberids["TriggerSecrets"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OTriggerSecrets());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetSideWarpDMap(int)
	{
		int id = memberids["GetSideWarpDMap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetSideWarpDMap(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetSideWarpScreen(int)
	{
		int id = memberids["GetSideWarpScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetSideWarpScreen(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetSideWarpType(int)
	{
		int id = memberids["GetSideWarpType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetSideWarpType(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetTileWarpDMap(int)
	{
		int id = memberids["GetTileWarpDMap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetTileWarpDMap(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetTileWarpScreen(int)
	{
		int id = memberids["GetTileWarpScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetTileWarpScreen(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// int GetTileWarpType(int)
	{
		int id = memberids["GetTileWarpType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetTileWarpType(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void ZapIn()
	{
		int id = memberids["ZapIn"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OZapIn());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void ZapOut()
	{
		int id = memberids["ZapOut"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OZapOut());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void WavyIn()
	{
		int id = memberids["WavyIn"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OWavyIn());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void WavyOut()
	{
		int id = memberids["WavyOut"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OWavyOut());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void OpeningWipe()
	{
		int id = memberids["OpeningWipe"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OOpenWipe());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
}

#undef POP_ARGS

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
