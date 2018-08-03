#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_COMBOS
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	  name,				rettype,	type,		var,				num,	params
		{ "getTile",			tFlt,		GETTER,		COMBODTILE,			1,	P0				  },
		{ "setTile",			tVoid,		SETTER,		COMBODTILE,			1,	P1(	tFlt			) },
		{ "getFlip",			tFlt,		GETTER,		COMBODFLIP,			1,	P0				  },
		{ "setFlip",			tVoid,		SETTER,		COMBODFLIP,			1,	P1(	tFlt			) },
		{ "getWalk",			tFlt,		GETTER,		COMBODWALK,			1,	P0				  },
		{ "setWalk",			tVoid,		SETTER,		COMBODWALK,			1,	P1(	tFlt			) },
		{ "getType",			tFlt,		GETTER,		COMBODTYPE,			1,	P0				  },
		{ "setType",			tVoid,		SETTER,		COMBODTYPE,			1,	P1(	tFlt			) },
		{ "getCSet",			tFlt,		GETTER,		COMBODCSET,			1,	P0				  },
		{ "setCSet",			tVoid,		SETTER,		COMBODCSET,			1,	P1(	tFlt			) },
		{ "getFoo",			tFlt,		GETTER,		COMBODFOO,			1,	P0				  },
		{ "setFoo",			tVoid,		SETTER,		COMBODFOO,			1,	P1(	tFlt			) },
		{ "getFrames",			tFlt,		GETTER,		COMBODFRAMES,			1,	P0				  },
		{ "setFrames",			tVoid,		SETTER,		COMBODFRAMES,			1,	P1(	tFlt			) },
		{ "getNextData",		tFlt,		GETTER,		COMBODNEXTD,			1,	P0				  },
		{ "setNextData",		tVoid,		SETTER,		COMBODNEXTD,			1,	P1(	tFlt			) },
		{ "getNextCSet",		tFlt,		GETTER,		COMBODNEXTC,			1,	P0				  },
		{ "setNextCSet",		tVoid,		SETTER,		COMBODNEXTC,			1,	P1(	tFlt			) },
		{ "getFlag",			tFlt,		GETTER,		COMBODFLAG,			1,	P0				  },
		{ "setFlag",			tVoid,		SETTER,		COMBODFLAG,			1,	P1(	tFlt			) },
		{ "getSkipAnim",		tFlt,		GETTER,		COMBODSKIPANIM,			1,	P0				  },
		{ "setSkipAnim",		tVoid,		SETTER,		COMBODSKIPANIM,			1,	P1(	tFlt			) },
		{ "getNextTimer",		tFlt,		GETTER,		COMBODNEXTTIMER,		1,	P0				  },
		{ "setNextTimer",		tVoid,		SETTER,		COMBODNEXTTIMER,		1,	P1(	tFlt			) },
		{ "getSkipAnimY",		tFlt,		GETTER,		COMBODAKIMANIMY,		1,	P0				  },
		{ "setSkipAnimY",		tVoid,		SETTER,		COMBODAKIMANIMY,		1,	P1(	tFlt			) },
		{ "getAnimFlags",		tFlt,		GETTER,		COMBODANIMFLAGS,		1,	P0				  },
		{ "setAnimFlags",		tVoid,		SETTER,		COMBODANIMFLAGS,		1,	P1(	tFlt			) },
		{ "getExpansion[]",		tFlt,		GETTER,		COMBODEXPANSION,		6,	P0				  },
		{ "setExpansion[]",		tVoid,		SETTER,		COMBODEXPANSION,		6,	P1(	tFlt			) },
		{ "getAttributes[]",		tFlt,		GETTER,		COMBODATTRIBUTES,		4,	P0				  },
		{ "setAttributes[]",		tVoid,		SETTER,		COMBODATTRIBUTES,		4,	P1(	tFlt			) },
		{ "getTriggerFlags[]",		tFlt,		GETTER,		COMBODTRIGGERFLAGS,		3,	P0				  },
		{ "setTriggerFlags[]",		tVoid,		SETTER,		COMBODTRIGGERFLAGS,		3,	P1(	tFlt			) },
		{ "getUserFlags",		tFlt,		GETTER,		COMBODUSRFLAGS,			1,	P0				  },
		{ "setUserFlags",		tVoid,		SETTER,		COMBODUSRFLAGS,			1,	P1(	tFlt			) },
		{ "getTriggerLevel",		tFlt,		GETTER,		COMBODTRIGGERLEVEL,		1,	P0				  },
		{ "setTriggerLevel",		tVoid,		SETTER,		COMBODTRIGGERLEVEL,		1,	P1(	tFlt			) },
		{ "getBlockNPC",		tFlt,		GETTER,		COMBODBLOCKNPC,			1,	P0				  },
		{ "setBlockNPC",		tVoid,		SETTER,		COMBODBLOCKNPC,			1,	P1(	tFlt			) },
		{ "getBlockHole",		tFlt,		GETTER,		COMBODBLOCKHOLE,		1,	P0				  },
		{ "setBlockHole",		tVoid,		SETTER,		COMBODBLOCKHOLE,		1,	P1(	tFlt			) },
		{ "getBlockTrigger",		tFlt,		GETTER,		COMBODBLOCKTRIG,		1,	P0				  },
		{ "setBlockTrigger",		tVoid,		SETTER,		COMBODBLOCKTRIG,		1,	P1(	tFlt			) },
		{ "getBlockWeapon[]",		tFlt,		GETTER,		COMBODBLOCKWEAPON,		32,	P0				  },
		{ "setBlockWeapon[]",		tVoid,		SETTER,		COMBODBLOCKWEAPON,		32,	P1(	tFlt			) },
		{ "getConveyorSpeedX",		tFlt,		GETTER,		COMBODCONVXSPEED,		1,	P0				  },
		{ "setConveyorSpeedX",		tVoid,		SETTER,		COMBODCONVXSPEED,		1,	P1(	tFlt			) },
		{ "getConveyorSpeedY",		tFlt,		GETTER,		COMBODCONVYSPEED,		1,	P0				  },
		{ "setConveyorSpeedY",		tVoid,		SETTER,		COMBODCONVYSPEED,		1,	P1(	tFlt			) },
		{ "getSpawnNPC",		tFlt,		GETTER,		COMBODSPAWNNPC,			1,	P0				  },
		{ "setSpawnNPC",		tVoid,		SETTER,		COMBODSPAWNNPC,			1,	P1(	tFlt			) },
		{ "getSpawnNPCWhen",		tFlt,		GETTER,		COMBODSPAWNNPCWHEN,		1,	P0				  },
		{ "setSpawnNPCWhen",		tVoid,		SETTER,		COMBODSPAWNNPCWHEN,		1,	P1(	tFlt			) },
		{ "getSpawnNPCCHange",		tFlt,		GETTER,		COMBODSPAWNNPCCHANGE,		1,	P0				  },
		{ "setSpawnNPCChange",		tVoid,		SETTER,		COMBODSPAWNNPCCHANGE,		1,	P1(	tFlt			) },
		{ "getDirChange",		tFlt,		GETTER,		COMBODDIRCHANGETYPE,		1,	P0				  },
		{ "setDirChange",		tVoid,		SETTER,		COMBODDIRCHANGETYPE,		1,	P1(	tFlt			) },
		{ "getDistanceChangeTiles",	tFlt,		GETTER,		COMBODDISTANCECHANGETILES,	1,	P0				  },
		{ "setDistanceChangeTiles",	tVoid,		SETTER,		COMBODDISTANCECHANGETILES,	1,	P1(	tFlt			) },
		{ "getDiveItem",		tFlt,		GETTER,		COMBODDIVEITEM,			1,	P0				  },
		{ "setDiveItem",		tVoid,		SETTER,		COMBODDIVEITEM,			1,	P1(	tFlt			) },
		{ "getDock",			tFlt,		GETTER,		COMBODDOCK,			1,	P0				  },
		{ "setDock",			tVoid,		SETTER,		COMBODDOCK,			1,	P1(	tFlt			) },
		{ "getFairy",			tFlt,		GETTER,		COMBODFAIRY,			1,	P0				  },
		{ "setFairy",			tVoid,		SETTER,		COMBODFAIRY,			1,	P1(	tFlt			) },
		{ "getFFCAttributeChange",	tFlt,		GETTER,		COMBODFFATTRCHANGE,		1,	P0				  },
		{ "setFFCAttributeChange",	tVoid,		SETTER,		COMBODFFATTRCHANGE,		1,	P1(	tFlt			) },
		{ "getDecorationTile",		tFlt,		GETTER,		COMBODFOORDECOTILE,		1,	P0				  },
		{ "setDecorationTile",		tVoid,		SETTER,		COMBODFOORDECOTILE,		1,	P1(	tFlt			) },
		{ "getDecorationType",		tFlt,		GETTER,		COMBODFOORDECOTYPE,		1,	P0				  },
		{ "setDecorationType",		tVoid,		SETTER,		COMBODFOORDECOTYPE,		1,	P1(	tFlt			) },
		{ "getHookshot",		tFlt,		GETTER,		COMBODHOOKSHOTPOINT,		1,	P0				  },
		{ "setHookshot",		tVoid,		SETTER,		COMBODHOOKSHOTPOINT,		1,	P1(	tFlt			) },
		{ "getLadder",			tFlt,		GETTER,		COMBODLADDERPASS,		1,	P0				  },
		{ "setLadder",			tVoid,		SETTER,		COMBODLADDERPASS,		1,	P1(	tFlt			) },
		{ "getLockBlock",		tFlt,		GETTER,		COMBODLOCKBLOCK,		1,	P0				  },
		{ "setLockBlock",		tVoid,		SETTER,		COMBODLOCKBLOCK,		1,	P1(	tFlt			) },
		{ "getLockBlockChange",		tFlt,		GETTER,		COMBODLOCKBLOCKCHANGE,		1,	P0				  },
		{ "setLockBlockChange",		tVoid,		SETTER,		COMBODLOCKBLOCKCHANGE,		1,	P1(	tFlt			) },
		{ "getMirror",			tFlt,		GETTER,		COMBODMAGICMIRROR,		1,	P0				  },
		{ "setMirror",			tVoid,		SETTER,		COMBODMAGICMIRROR,		1,	P1(	tFlt			) },
		{ "getDamageAmount",		tFlt,		GETTER,		COMBODMODHPAMOUNT,		1,	P0				  },
		{ "setDamageAmount",		tVoid,		SETTER,		COMBODMODHPAMOUNT,		1,	P1(	tFlt			) },
		{ "getDamageDelay",		tFlt,		GETTER,		COMBODMODHPDELAY,		1,	P0				  },
		{ "setDamageDelay",		tVoid,		SETTER,		COMBODMODHPDELAY,		1,	P1(	tFlt			) },
		{ "getDamageType",		tFlt,		GETTER,		COMBODMODHPTYPE,		1,	P0				  },
		{ "setDamageType",		tVoid,		SETTER,		COMBODMODHPTYPE,		1,	P1(	tFlt			) },
		{ "getMagicAmount",		tFlt,		GETTER,		COMBODNMODMPAMOUNT,		1,	P0				  },
		{ "setMagicAmount",		tVoid,		SETTER,		COMBODNMODMPAMOUNT,		1,	P1(	tFlt			) },
		{ "getMagicDelay",		tFlt,		GETTER,		COMBODMODMPDELAY,		1,	P0				  },
		{ "setMagicDelay",		tVoid,		SETTER,		COMBODMODMPDELAY,		1,	P1(	tFlt			) },
		{ "getMagicType",		tFlt,		GETTER,		COMBODMODMPTYPE,		1,	P0				  },
		{ "setMagicType",		tVoid,		SETTER,		COMBODMODMPTYPE,		1,	P1(	tFlt			) },
		{ "getNoPushBlocks",		tFlt,		GETTER,		COMBODNOPUSHBLOCK,		1,	P0				  },
		{ "setNoPushBlocks",		tVoid,		SETTER,		COMBODNOPUSHBLOCK,		1,	P1(	tFlt			) },
		{ "getOverhead",		tFlt,		GETTER,		COMBODOVERHEAD,			1,	P0				  },
		{ "setOverhead",		tVoid,		SETTER,		COMBODOVERHEAD,			1,	P1(	tFlt			) },
		{ "getPlaceNPC",		tFlt,		GETTER,		COMBODPLACENPC,			1,	P0				  },
		{ "setPlaceNPC",		tVoid,		SETTER,		COMBODPLACENPC,			1,	P1(	tFlt			) },
		{ "getPushDir",			tFlt,		GETTER,		COMBODPUSHDIR,			1,	P0				  },
		{ "setPushDir",			tVoid,		SETTER,		COMBODPUSHDIR,			1,	P1(	tFlt			) },
		{ "getPushDelay",		tFlt,		GETTER,		COMBODPUSHWAIT,			42,	P1(	tFlt			) },
		{ "setPushDelay",		tVoid,		SETTER,		COMBODPUSHWAIT,			42,	P2(	tFlt,	tFlt		) },
		{ "getPushHeavy",		tFlt,		GETTER,		COMBODPUSHHEAVY,		1,	P0				  },
		{ "setPushHeavy",		tVoid,		SETTER,		COMBODPUSHHEAVY,		1,	P1(	tFlt			) },
		{ "getPushed",			tFlt,		GETTER,		COMBODPUSHED,			1,	P0				  },
		{ "setPushed",			tVoid,		SETTER,		COMBODPUSHED,			1,	P1(	tFlt			) },
		{ "getRaft",			tFlt,		GETTER,		COMBODRAFT,			1,	P0				  },
		{ "setRaft",			tVoid,		SETTER,		COMBODRAFT,			1,	P1(	tFlt			) },
		{ "getResetRoom",		tFlt,		GETTER,		COMBODRESETROOM,		1,	P0				  },
		{ "setResetRoom",		tVoid,		SETTER,		COMBODRESETROOM,		1,	P1(	tFlt			) },
		{ "getSavePoint",		tFlt,		GETTER,		COMBODSAVEPOINTTYPE,		1,	P0				  },
		{ "setSavePoint",		tVoid,		SETTER,		COMBODSAVEPOINTTYPE,		1,	P1(	tFlt			) },
		{ "getFreezeScreen",		tFlt,		GETTER,		COMBODSCREENFREEZETYPE,		1,	P0				  },
		{ "setFreezeScreen",		tVoid,		SETTER,		COMBODSCREENFREEZETYPE,		1,	P1(	tFlt			) },
		{ "getSecretCombo",		tFlt,		GETTER,		COMBODSECRETCOMBO,		1,	P0				  },
		{ "setSecretCombo",		tVoid,		SETTER,		COMBODSECRETCOMBO,		1,	P1(	tFlt			) },
		{ "getSingular",		tFlt,		GETTER,		COMBODSINGULAR,			1,	P0				  },
		{ "setSingular",		tVoid,		SETTER,		COMBODSINGULAR,			1,	P1(	tFlt			) },
		{ "getSlowWalk",		tFlt,		GETTER,		COMBODSLOWWALK,			1,	P0				  },
		{ "setSlowWalk",		tVoid,		SETTER,		COMBODSLOWWALK,			1,	P1(	tFlt			) },
		{ "getStatue",			tFlt,		GETTER,		COMBODSTATUETYPE,		1,	P0				  },
		{ "setStatue",			tVoid,		SETTER,		COMBODSTATUETYPE,		1,	P1(	tFlt			) },
		{ "getStep",			tFlt,		GETTER,		COMBODSTEPTYPE,			1,	P0				  },
		{ "setStep",			tVoid,		SETTER,		COMBODSTEPTYPE,			1,	P1(	tFlt			) },
		{ "getStepChange",		tFlt,		GETTER,		COMBODSTEPCHANGEINTO,		1,	P0				  },
		{ "setStepChange",		tVoid,		SETTER,		COMBODSTEPCHANGEINTO,		1,	P1(	tFlt			) },
		{ "getStrike[]",		tFlt,		GETTER,		COMBODSTRIKEWEAPONS,		32,	P0				  },
		{ "setStrike[]",		tVoid,		SETTER,		COMBODSTRIKEWEAPONS,		32,	P1(	tFlt			) },
		{ "getStrikeRemnants",		tFlt,		GETTER,		COMBODSTRIKEREMNANTS,		1,	P0				  },
		{ "setStrikeRemnants",		tVoid,		SETTER,		COMBODSTRIKEREMNANTS,		1,	P1(	tFlt			) },
		{ "getStrikeRemnantsType",	tFlt,		GETTER,		COMBODSTRIKEREMNANTSTYPE,	1,	P0				  },
		{ "setStrikeRemnantsType",	tVoid,		SETTER,		COMBODSTRIKEREMNANTSTYPE,	1,	P1(	tFlt			) },
		{ "getStrikeChange",		tFlt,		GETTER,		COMBODSTRIKECHANGE,		1,	P0				  },
		{ "setStrikeChange",		tVoid,		SETTER,		COMBODSTRIKECHANGE,		1,	P1(	tFlt			) },
		{ "getStrikeItem",		tFlt,		GETTER,		COMBODTOUCHITEM,		1,	P0				  },
		{ "setStrikeItem",		tVoid,		SETTER,		COMBODTOUCHITEM,		1,	P1(	tFlt			) },
		{ "getTouchItem",		tFlt,		GETTER,		COMBODTOUCHITEM,		1,	P0				  },
		{ "setTouchItem",		tVoid,		SETTER,		COMBODTOUCHITEM,		1,	P1(	tFlt			) },
		{ "getTouchStairs",		tFlt,		GETTER,		COMBODTOUCHSTAIRS,		1,	P0				  },
		{ "setTouchStairs",		tVoid,		SETTER,		COMBODTOUCHSTAIRS,		1,	P1(	tFlt			) },
		{ "getTriggerType",		tFlt,		GETTER,		COMBODTRIGGERTYPE,		1,	P0				  },
		{ "setTriggerType",		tVoid,		SETTER,		COMBODTRIGGERTYPE,		1,	P1(	tFlt			) },
		{ "getTriggerSensitivity",	tFlt,		GETTER,		COMBODTRIGGERSENS,		1,	P0				  },
		{ "setTriggerSensitivity",	tVoid,		SETTER,		COMBODTRIGGERSENS,		1,	P1(	tFlt			) },
		{ "getWarp",			tFlt,		GETTER,		COMBODWARPTYPE,			1,	P0				  },
		{ "setWarp",			tVoid,		SETTER,		COMBODWARPTYPE,			1,	P1(	tFlt			) },
		{ "getWarpSensitivity",		tFlt,		GETTER,		COMBODWARPSENS,			1,	P0				  },
		{ "setWarpSensitivity",		tVoid,		SETTER,		COMBODWARPSENS,			1,	P1(	tFlt			) },
		{ "getWarpDirect",		tFlt,		GETTER,		COMBODWARPDIRECT,		1,	P0				  },
		{ "setWarpDirect",		tVoid,		SETTER,		COMBODWARPDIRECT,		1,	P1(	tFlt			) },
		{ "getWarpLocation",		tFlt,		GETTER,		COMBODWARPLOCATION,		1,	P0				  },
		{ "setWarpLocation",		tVoid,		SETTER,		COMBODWARPLOCATION,		1,	P1(	tFlt			) },
		{ "getWater",			tFlt,		GETTER,		COMBODWATER,			1,	P0				  },
		{ "setWater",			tVoid,		SETTER,		COMBODWATER,			1,	P1(	tFlt			) },
		{ "getWhistle",			tFlt,		GETTER,		COMBODWHISTLE,			1,	P0				  },
		{ "setWhistle",			tVoid,		SETTER,		COMBODWHISTLE,			1,	P1(	tFlt			) },
		{ "getWinGame",			tFlt,		GETTER,		COMBODWINGAME,			1,	P0				  },
		{ "setWinGame",			tVoid,		SETTER,		COMBODWINGAME,			1,	P1(	tFlt			) },
		{ "getBlockWeaponLevel",	tFlt,		GETTER,		COMBODBLOCKWPNLEVEL,		1,	P0				  },
		{ "setBlockWeaponLevel",	tVoid,		SETTER,		COMBODBLOCKWPNLEVEL,		1,	P1(	tFlt			) },
	//	{ "GetName",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
	//	{ "SetName",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetBlockEnemies",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetBlockHole",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetBlockTrigger",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetConveyorSpeedX",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetConveyorSpeedY",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetCreateEnemy",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetCreateEnemyWhen",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetCreateEnemyChnge",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetDirChangeType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetDistanceChangeTiles",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetDiveItem",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetDock",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFairy",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFFComboChangeAttrib",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFootDecorationsTile",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFootDecorationsType",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetHookshotGrab",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetLadderPass",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetLockBlockType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetLockBlockChange",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetMagicMirror",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyHPAmount",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyHPDelay",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyHPType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyMPAmount",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyMPDelay",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetModifyMPType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetNoPushBlocks",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetOverhead",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetPlaceEnemy",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetPushDirection",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetPushWeight",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetPushWait",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetPushed",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetRaft",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetResetRoom",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSavePoint",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetScreenFreeze",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSecretCombo",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSingular",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSlowMove",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStatue",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStepType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStepChangeTo",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStrikeRemnants",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStrikeRemnantsType",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStrikeChange",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetStrikeItem",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetTouchItem",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetTouchStairs",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetTriggerType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetTriggerSens",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWarpType",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWarpSens",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWarpDirect",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWarpLocation",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWater",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWhistle",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWinGame",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetBlockWeaponLevel",	tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetTile",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFlip",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetWalkability",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetType",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetCSets",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFoo",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFrames",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSpeed",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetNextCombo",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetNextCSet",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetFlag",			tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSkipAnim",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetNextTimer",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetSkipAnimY",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetAnimFlags",		tFlt,		FUNCTION,	0,				1,	P1(	tFlt			) },
		{ "GetBlockWeapon",		tFlt,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "GetExpansion",		tFlt,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "GetStrikeWeapons",		tFlt,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetBlockEnemies",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetBlockHole",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetBlockTrigger",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetConveyorSpeedX",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetConveyorSpeedY",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetCreateEnemy",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetCreateEnemyWhen",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetCreateEnemyChnge",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetDirChangeType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetDistanceChangeTiles",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetDiveItem",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetDock",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFairy",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFFComboChangeAttrib",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFootDecorationsTile",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFootDecorationsType",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetHookshotGrab",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetLadderPass",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetLockBlockType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetLockBlockChange",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetMagicMirror",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyHPAmount",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyHPDelay",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyHPType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyMPAmount",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyMPDelay",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetModifyMPType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetNoPushBlocks",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetOverhead",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetPlaceEnemy",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetPushDirection",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetPushWeight",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetPushWait",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetPushed",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetRaft",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetResetRoom",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSavePoint",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetScreenFreeze",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSecretCombo",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSingular",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSlowMove",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStatue",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStepType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStepChangeTo",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStrikeRemnants",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStrikeRemnantsType",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStrikeChange",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetStrikeItem",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetTouchItem",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetTouchStairs",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetTriggerType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetTriggerSens",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWarpType",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWarpSens",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWarpDirect",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWarpLocation",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWater",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWhistle",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWinGame",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetBlockWeaponLevel",	tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetTile",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFlip",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetWalkability",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetType",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetCSets",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFoo",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFrames",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSpeed",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetNextCombo",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetNextCSet",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetFlag",			tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSkipAnim",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetNextTimer",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetSkipAnimY",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetAnimFlags",		tVoid,		FUNCTION,	0,				1,	P2(	tFlt,	tFlt		) },
		{ "SetBlockWeapon",		tVoid,		FUNCTION,	0,				1,	P3(	tFlt,	tFlt,	tFlt	) },
		{ "GetExpansion",		tVoid,		FUNCTION,	0,				1,	P3(	tFlt,	tFlt,	tFlt	) },
		{ "SetStrikeWeapons",		tVoid,		FUNCTION,	0,				1,	P3(	tFlt,	tFlt,	tFlt	) },
		ENTRY_END
	};
	
#	include "EntryHelperUnload.h"
}

Library::Combo& Library::Combo::instance()
{
	static Library::Combo instance(REFCOMBODATA, table);
	return instance;
}

// float function(float)
#define ONE_INPUT_ONE_RETURN(flabel, ocode) \
{ \
	int id = memberids[flabel]; \
	int label = lt.functionToLabel(id); \
        vector<Opcode *> code; \
        Opcode *first = new OPopRegister(new VarArgument(EXP1)); \
        first->setLabel(label); \
        code.push_back(first); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OPopRegister(new VarArgument(NUL))); \
        code.push_back(new ocode(new VarArgument(EXP1),new VarArgument(EXP2))); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
        rval[label] = code; \
}

// void function(float, float)
#define TWO_INPUT_NO_RETURN(flabel, ocode) \
{ \
	int id = memberids[flabel]; \
        int label = lt.functionToLabel(id); \
        vector<Opcode *> code; \
        Opcode *first = new OPopRegister(new VarArgument(INDEX2)); \
        first->setLabel(label); \
        code.push_back(first); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OPopRegister(new VarArgument(SFTEMP))); \
        code.push_back(new ocode(new VarArgument(EXP2), new VarArgument(EXP1))); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
        rval[label] = code; \
}

// float function(float, float)
#define TWO_INPUT_ONE_RETURN(flabel, ocode) \
{ \
        int id = memberids[flabel]; \
        int label = lt.functionToLabel(id); \
        vector<Opcode *> code; \
        Opcode *first = new OPopRegister(new VarArgument(INDEX2)); \
        first->setLabel(label); \
        code.push_back(first); \
        code.push_back(new OPopRegister(new VarArgument(INDEX))); \
        code.push_back(new OPopRegister(new VarArgument(NUL))); \
        code.push_back(new ocode(new VarArgument(EXP1))); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
        rval[label] = code; \
} \

// void function(float, float, float)
#define THREE_INPUT_NO_RETURN(flabel,zasmid) \
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
        code.push_back(new OSetRegister(new VarArgument(zasmid), new VarArgument(SFTEMP))); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
        rval[label] = code; \
}

void Library::Combo::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// float GetBlockEnemies(float)
	ONE_INPUT_ONE_RETURN("GetBlockEnemies", OCDataBlockEnemy);

	// float GetBlockHole(float)
	ONE_INPUT_ONE_RETURN("GetBlockHole", OCDataBlockHole);

	// float GetBlockTrigger(float)
	ONE_INPUT_ONE_RETURN("GetBlockTrigger", OCDataBlockTrig);

	// float GetConveyorSpeedX(float)
	ONE_INPUT_ONE_RETURN("GetConveyorSpeedX", OCDataConveyX);

	// float GetConveyorSpeedY(float)
	ONE_INPUT_ONE_RETURN("GetConveyorSpeedY", OCDataConveyY);

	// float GetCreateEnemy(float)
	ONE_INPUT_ONE_RETURN("GetCreateEnemy", OCDataCreateNPC);

	// float GetCreateEnemyWhen(float)
	ONE_INPUT_ONE_RETURN("GetCreateEnemyWhen", OCDataCreateEnemW);

	// float GetCreateEnemyChnge(float)
	ONE_INPUT_ONE_RETURN("GetCreateEnemyChnge", OCDataCreateEnemC);

	// float GetDirChangeType(float)
	ONE_INPUT_ONE_RETURN("GetDirChangeType", OCDataDirch);

	// float GetDistanceChangeTiles(float)
	ONE_INPUT_ONE_RETURN("GetDistanceChangeTiles", OCDataDistTiles);

	// float GetDiveItem(float)
	ONE_INPUT_ONE_RETURN("GetDiveItem", OCDataDiveItem);

	// float GetDock(float)
	ONE_INPUT_ONE_RETURN("GetDock", OCDataDock);

	// float GetFairy(float)
	ONE_INPUT_ONE_RETURN("GetFairy", OCDataFairy);

	// float GetFFComboChangeAttrib(float)
	ONE_INPUT_ONE_RETURN("GetFFComboChangeAttrib", OCDataAttrib);

	// float GetFootDecorationsTile(float)
	ONE_INPUT_ONE_RETURN("GetFootDecorationsTile", OCDataDecoTile);

	// float GetFootDecorationsType(float)
	ONE_INPUT_ONE_RETURN("GetFootDecorationsType", OCDataDecoType);

	// float GetHookshotGrab(float)
	ONE_INPUT_ONE_RETURN("GetHookshotGrab", OCDataHookshotGrab);

	// float GetLadderPass(float)
	ONE_INPUT_ONE_RETURN("GetLadderPass", OCDataLadderPass);

	// float GetLockBlockType(float)
	ONE_INPUT_ONE_RETURN("GetLockBlockType", OCDataLockBlock);

	// float GetLockBlockChange(float)
	ONE_INPUT_ONE_RETURN("GetLockBlockChange", OCDataLockBlockChange);

	// float GetMagicMirror(float)
	ONE_INPUT_ONE_RETURN("GetMagicMirror", OCDataMagicMirror);

	// float GetModifyHPAmount(float)
	ONE_INPUT_ONE_RETURN("GetModifyHPAmount", OCDataModHP);

	// float GetModifyHPDelay(float)
	ONE_INPUT_ONE_RETURN("GetModifyHPDelay", OCDataModHPDelay);

	// float GetModifyHPType(float)
	ONE_INPUT_ONE_RETURN("GetModifyHPType", OCDataModHpType);

	// float GetModifyMPAmount(float)
	ONE_INPUT_ONE_RETURN("GetModifyMPAmount", OCDataModMP);

	// float GetModifyMPDelay(float)
	ONE_INPUT_ONE_RETURN("GetModifyMPDelay", OCDataMpdMPDelay);

	// float GetModifyMPType(float)
	ONE_INPUT_ONE_RETURN("GetModifyMPType", OCDataModMPType);

	// float GetNoPushBlocks(float)
	ONE_INPUT_ONE_RETURN("GetNoPushBlocks", OCDataNoPush);

	// float GetOverhead(float)
	ONE_INPUT_ONE_RETURN("GetOverhead", OCDataOverhead);

	// float GetPlaceEnemy(float)
	ONE_INPUT_ONE_RETURN("GetPlaceEnemy", OCDataEnemyLoc);

	// float GetPushDirection(float)
	ONE_INPUT_ONE_RETURN("GetPushDirection", OCDataPushDir);

	// float GetPushWeight(float)
	ONE_INPUT_ONE_RETURN("GetPushWeight", OCDataPushWeight);

	// float GetPushWait(float)
	ONE_INPUT_ONE_RETURN("GetPushWait", OCDataPushWait);

	// float GetPushed(float)
	ONE_INPUT_ONE_RETURN("GetPushed", OCDataPushed);

	// float GetRaft(float)
	ONE_INPUT_ONE_RETURN("GetRaft", OCDataRaft);

	// float GetResetRoom(float)
	ONE_INPUT_ONE_RETURN("GetResetRoom", OCDataResetRoom);

	// float GetSavePoint(float)
	ONE_INPUT_ONE_RETURN("GetSavePoint", OCDataSavePoint);

	// float GetScreenFreeze(float)
	ONE_INPUT_ONE_RETURN("GetScreenFreeze", OCDataFreeezeScreen);

	// float GetSecretCombo(float)
	ONE_INPUT_ONE_RETURN("GetSecretCombo", OCDataSecretCombo);

	// float GetSingular(float)
	ONE_INPUT_ONE_RETURN("GetSingular", OCDataSingular);

	// float GetSlowMove(float)
	ONE_INPUT_ONE_RETURN("GetSlowMove", OCDataSlowMove);

	// float GetStatue(float)
	ONE_INPUT_ONE_RETURN("GetStatue", OCDataStatue);

	// float GetStepType(float)
	ONE_INPUT_ONE_RETURN("GetStepType", OCDataStepType);

	// float GetStepChangeTo(float)
	ONE_INPUT_ONE_RETURN("GetStepChangeTo", OCDataSteoChange);

	// float GetStrikeRemnants(float)
	ONE_INPUT_ONE_RETURN("GetStrikeRemnants", OCDataStrikeRem);

	// float GetStrikeRemnantsType(float)
	ONE_INPUT_ONE_RETURN("GetStrikeRemnantsType", OCDataStrikeRemType);

	// float GetStrikeChange(float)
	ONE_INPUT_ONE_RETURN("GetStrikeChange", OCDataStrikeChange);

	// float GetStrikeItem(float)
	ONE_INPUT_ONE_RETURN("GetStrikeItem", OCDataStrikeChangeItem);

	// float GetTouchItem(float)
	ONE_INPUT_ONE_RETURN("GetTouchItem", OCDataTouchItem);

	// float GetTouchStairs(float)
	ONE_INPUT_ONE_RETURN("GetTouchStairs", OCDataTouchStairs);

	// float GetTriggerType(float)
	ONE_INPUT_ONE_RETURN("GetTriggerType", OCDataTriggerType);

	// float GetTriggerSens(float)
	ONE_INPUT_ONE_RETURN("GetTriggerSens", OCDataTriggerSens);

	// float GetWarpType(float)
	ONE_INPUT_ONE_RETURN("GetWarpType", OCDataWarpType);

	// float GetWarpSens(float)
	ONE_INPUT_ONE_RETURN("GetWarpSens", OCDataWarpSens);

	// float GetWarpDirect(float)
	ONE_INPUT_ONE_RETURN("GetWarpDirect", OCDataWarpDirect);

	// float GetWarpLocation(float)
	ONE_INPUT_ONE_RETURN("GetWarpLocation", OCDataWarpLoc);

	// float GetWater(float)
	ONE_INPUT_ONE_RETURN("GetWater", OCDataWater);

	// float GetWhistle(float)
	ONE_INPUT_ONE_RETURN("GetWhistle", OCDataWhistle);

	// float GetWinGame(float)
	ONE_INPUT_ONE_RETURN("GetWinGame", OCDataWinGame);

	// float GetBlockWeaponLevel(float)
	ONE_INPUT_ONE_RETURN("GetBlockWeaponLevel", OCDataWeapBlockLevel);

	// float GetTile(float)
	ONE_INPUT_ONE_RETURN("GetTile", OCDataTile);

	// float GetFlip(float)
	ONE_INPUT_ONE_RETURN("GetFlip", OCDataFlip);

	// float GetWalkability(float)
	ONE_INPUT_ONE_RETURN("GetWalkability", OCDataWalkability);

	// float GetType(float)
	ONE_INPUT_ONE_RETURN("GetType", OCDataType);

	// float GetCSets(float)
	ONE_INPUT_ONE_RETURN("GetCSets", OCDataCSets);

	// float GetFoo(float)
	ONE_INPUT_ONE_RETURN("GetFoo", OCDataFoo);

	// float GetFrames(float)
	ONE_INPUT_ONE_RETURN("GetFrames", OCDataFrames);

	// float GetSpeed(float)
	ONE_INPUT_ONE_RETURN("GetSpeed", OCDataSpeed);

	// float GetNextCombo(float)
	ONE_INPUT_ONE_RETURN("GetNextCombo", OCDataNext);

	// float GetNextCSet(float)
	ONE_INPUT_ONE_RETURN("GetNextCSet", OCDataNextCSet);

	// float GetFlag(float)
	ONE_INPUT_ONE_RETURN("GetFlag", OCDataFlag);

	// float GetSkipAnim(float)
	ONE_INPUT_ONE_RETURN("GetSkipAnim", OCSetDataSkipAnim);

	// float GetNextTimer(float)
	ONE_INPUT_ONE_RETURN("GetNextTimer", OCDataTimer);

	// float GetSkipAnimY(float)
	ONE_INPUT_ONE_RETURN("GetSkipAnimY", OCDataAnimY);

	// float GetAnimFlags(float)
	ONE_INPUT_ONE_RETURN("GetAnimFlags", OCDataAnimFlags);
	{
		TWO_INPUT_NO_RETURN("SetBlockEnemies",OCSetDataBlockEnemy);
	}
	// void SetBlockHole(float, float)
	TWO_INPUT_NO_RETURN("SetBlockHole", OCSetDataBlockHole);

	// void SetBlockTrigger(float, float)
	TWO_INPUT_NO_RETURN("SetBlockTrigger", OCSetDataBlockTrig);

	// void SetConveyorSpeedX(float, float)
	TWO_INPUT_NO_RETURN("SetConveyorSpeedX", OCSetDataConveyX);

	// void SetConveyorSpeedY(float, float)
	TWO_INPUT_NO_RETURN("SetConveyorSpeedY", OCSetDataConveyY);

	// void SetCreateEnemy(float, float)
	TWO_INPUT_NO_RETURN("SetCreateEnemy", OCSetDataCreateNPC);

	// void SetCreateEnemyWhen(float, float)
	TWO_INPUT_NO_RETURN("SetCreateEnemyWhen", OCSetDataCreateEnemW);

	// void SetCreateEnemyChnge(float, float)
	TWO_INPUT_NO_RETURN("SetCreateEnemyChnge", OCSetDataCreateEnemC);

	// void SetDirChangeType(float, float)
	TWO_INPUT_NO_RETURN("SetDirChangeType", OCSetDataDirch);

	// void SetDistanceChangeTiles(float, float)
	TWO_INPUT_NO_RETURN("SetDistanceChangeTiles", OCSetDataDistTiles);

	// void SetDiveItem(float, float)
	TWO_INPUT_NO_RETURN("SetDiveItem", OCSetDataDiveItem);

	// void SetDock(float, float)
	TWO_INPUT_NO_RETURN("SetDock", OCSetDataDock);

	// void SetFairy(float, float)
	TWO_INPUT_NO_RETURN("SetFairy", OCSetDataFairy);

	// void SetFFComboChangeAttrib(float, float)
	TWO_INPUT_NO_RETURN("SetFFComboChangeAttrib", OCSetDataAttrib);

	// void SetFootDecorationsTile(float, float)
	TWO_INPUT_NO_RETURN("SetFootDecorationsTile", OCSetDataDecoTile);

	// void SetFootDecorationsType(float, float)
	TWO_INPUT_NO_RETURN("SetFootDecorationsType", OCSetDataDecoType);

	// void SetHookshotGrab(float, float)
	TWO_INPUT_NO_RETURN("SetHookshotGrab", OCSetDataHookshotGrab);

	// void SetLadderPass(float, float)
	TWO_INPUT_NO_RETURN("SetLadderPass", OCSetDataLadderPass);

	// void SetLockBlockType(float, float)
	TWO_INPUT_NO_RETURN("SetLockBlockType", OCSetDataLockBlock);

	// void SetLockBlockChange(float, float)
	TWO_INPUT_NO_RETURN("SetLockBlockChange", OCSetDataLockBlockChange);

	// void SetMagicMirror(float, float)
	TWO_INPUT_NO_RETURN("SetMagicMirror", OCSetDataMagicMirror);

	// void SetModifyHPAmount(float, float)
	TWO_INPUT_NO_RETURN("SetModifyHPAmount", OCSetDataModHP);

	// void SetModifyHPDelay(float, float)
	TWO_INPUT_NO_RETURN("SetModifyHPDelay", OCSetDataModHPDelay);

	// void SetModifyHPType(float, float)
	TWO_INPUT_NO_RETURN("SetModifyHPType", OCSetDataModHpType);

	// void SetModifyMPAmount(float, float)
	TWO_INPUT_NO_RETURN("SetModifyMPAmount", OCSetDataModMP);

	// void SetModifyMPDelay(float, float)
	TWO_INPUT_NO_RETURN("SetModifyMPDelay", OCSetDataMpdMPDelay);

	// void SetModifyMPType(float, float)
	TWO_INPUT_NO_RETURN("SetModifyMPType", OCSetDataModMPType);

	// void SetNoPushBlocks(float, float)
	TWO_INPUT_NO_RETURN("SetNoPushBlocks", OCSetDataNoPush);

	// void SetOverhead(float, float)
	TWO_INPUT_NO_RETURN("SetOverhead", OCSetDataOverhead);

	// void SetPlaceEnemy(float, float)
	TWO_INPUT_NO_RETURN("SetPlaceEnemy", OCSetDataEnemyLoc);

	// void SetPushDirection(float, float)
	TWO_INPUT_NO_RETURN("SetPushDirection", OCSetDataPushDir);

	// void SetPushWeight(float, float)
	TWO_INPUT_NO_RETURN("SetPushWeight", OCSetDataPushWeight);

	// void SetPushWait(float, float)
	TWO_INPUT_NO_RETURN("SetPushWait", OCSetDataPushWait);

	// void SetPushed(float, float)
	TWO_INPUT_NO_RETURN("SetPushed", OCSetDataPushed);

	// void SetRaft(float, float)
	TWO_INPUT_NO_RETURN("SetRaft", OCSetDataRaft);

	// void SetResetRoom(float, float)
	TWO_INPUT_NO_RETURN("SetResetRoom", OCSetDataResetRoom);

	// void SetSavePoint(float, float)
	TWO_INPUT_NO_RETURN("SetSavePoint", OCSetDataSavePoint);

	// void SetScreenFreeze(float, float)
	TWO_INPUT_NO_RETURN("SetScreenFreeze", OCSetDataFreeezeScreen);

	// void SetSecretCombo(float, float)
	TWO_INPUT_NO_RETURN("SetSecretCombo", OCSetDataSecretCombo);

	// void SetSingular(float, float)
	TWO_INPUT_NO_RETURN("SetSingular", OCSetDataSingular);

	// void SetSlowMove(float, float)
	TWO_INPUT_NO_RETURN("SetSlowMove", OCSetDataSlowMove);

	// void SetStatue(float, float)
	TWO_INPUT_NO_RETURN("SetStatue", OCSetDataStatue);

	// void SetStepType(float, float)
	TWO_INPUT_NO_RETURN("SetStepType", OCSetDataStepType);

	// void SetStepChangeTo(float, float)
	TWO_INPUT_NO_RETURN("SetStepChangeTo", OCSetDataSteoChange);

	// void SetStrikeRemnants(float, float)
	TWO_INPUT_NO_RETURN("SetStrikeRemnants", OCSetDataStrikeRem);

	// void SetStrikeRemnantsType(float, float)
	TWO_INPUT_NO_RETURN("SetStrikeRemnantsType", OCSetDataStrikeRemType);

	// void SetStrikeChange(float, float)
	TWO_INPUT_NO_RETURN("SetStrikeChange", OCSetDataStrikeChange);

	// void SetStrikeItem(float, float)
	TWO_INPUT_NO_RETURN("SetStrikeItem", OCSetDataStrikeChangeItem);

	// void SetTouchItem(float, float)
	TWO_INPUT_NO_RETURN("SetTouchItem", OCSetDataTouchItem);

	// void SetTouchStairs(float, float)
	TWO_INPUT_NO_RETURN("SetTouchStairs", OCSetDataTouchStairs);

	// void SetTriggerType(float, float)
	TWO_INPUT_NO_RETURN("SetTriggerType", OCSetDataTriggerType);

	// void SetTriggerSens(float, float)
	TWO_INPUT_NO_RETURN("SetTriggerSens", OCSetDataTriggerSens);

	// void SetWarpType(float, float)
	TWO_INPUT_NO_RETURN("SetWarpType", OCSetDataWarpType);

	// void SetWarpSens(float, float)
	TWO_INPUT_NO_RETURN("SetWarpSens", OCSetDataWarpSens);

	// void SetWarpDirect(float, float)
	TWO_INPUT_NO_RETURN("SetWarpDirect", OCSetDataWarpDirect);

	// void SetWarpLocation(float, float)
	TWO_INPUT_NO_RETURN("SetWarpLocation", OCSetDataWarpLoc);

	// void SetWater(float, float)
	TWO_INPUT_NO_RETURN("SetWater", OCSetDataWater);

	// void SetWhistle(float, float)
	TWO_INPUT_NO_RETURN("SetWhistle", OCSetDataWhistle);

	// void SetWinGame(float, float)
	TWO_INPUT_NO_RETURN("SetWinGame", OCSetDataWinGame);

	// void SetBlockWeaponLevel(float, float)
	TWO_INPUT_NO_RETURN("SetBlockWeaponLevel", OCSetDataWeapBlockLevel);

	// void SetTile(float, float)
	TWO_INPUT_NO_RETURN("SetTile", OCSetDataTile);

	// void SetFlip(float, float)
	TWO_INPUT_NO_RETURN("SetFlip", OCSetDataFlip);

	// void SetWalkability(float, float)
	TWO_INPUT_NO_RETURN("SetWalkability", OCSetDataWalkability);

	// void SetType(float, float)
	TWO_INPUT_NO_RETURN("SetType", OCSetDataType);

	// void SetCSets(float, float)
	TWO_INPUT_NO_RETURN("SetCSets", OCSetDataCSets);

	// void SetFoo(float, float)
	TWO_INPUT_NO_RETURN("SetFoo", OCSetDataFoo);

	// void SetFrames(float, float)
	TWO_INPUT_NO_RETURN("SetFrames", OCSetDataFrames);

	// void SetSpeed(float, float)
	TWO_INPUT_NO_RETURN("SetSpeed", OCSetDataSpeed);

	// void SetNextCombo(float, float)
	TWO_INPUT_NO_RETURN("SetNextCombo", OCSetDataNext);

	// void SetNextCSet(float, float)
	TWO_INPUT_NO_RETURN("SetNextCSet", OCSetDataNextCSet);

	// void SetFlag(float, float)
	TWO_INPUT_NO_RETURN("SetFlag", OCSetDataFlag);

	// void SetSkipAnim(float, float)
	TWO_INPUT_NO_RETURN("SetSkipAnim", OCSetDataSkipAnim);

	// void SetNextTimer(float, float)
	TWO_INPUT_NO_RETURN("SetNextTimer", OCSetDataTimer);

	// void SetSkipAnimY(float, float)
	TWO_INPUT_NO_RETURN("SetSkipAnimY", OCSetDataAnimY);

	// void SetAnimFlags(float, float)
	TWO_INPUT_NO_RETURN("SetAnimFlags", OCSetDataAnimFlags);

	// void GetBlockWeapon(float, float)
	TWO_INPUT_ONE_RETURN("GetBlockWeapon", OCDataBlockWeapon);

	// void GetExpansion(float, float)
	TWO_INPUT_ONE_RETURN("GetExpansion", OCDataExpansion);

	// void GetStrikeWeapons(float, float)
	TWO_INPUT_ONE_RETURN("GetStrikeWeapons", OCDataStrikeWeapon);

	// void SetBlockWeapon(float, float, float)
	THREE_INPUT_NO_RETURN("SetBlockWeapon",  SCDBLOCKWEAPON);

	// void SetExpansion(float, float, float)
	THREE_INPUT_NO_RETURN("SetExpansion",  SCDEXPANSION);

	// void SetStrikeWeapons(float, float, float)
	THREE_INPUT_NO_RETURN("SetStrikeWeapons",  SCDSTRIKEWEAPONS);
}

#undef ONE_INPUT_ONE_RETURN
#undef TWO_INPUT_NO_RETURN
#undef TWO_INPUT_ONE_RETURN
#undef THREE_INPUT_NO_RETURN

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
