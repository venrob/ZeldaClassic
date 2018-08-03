#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_GAME
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
		//	  name,				rettype,	setorget,     var,			num,	params
		{ "GetCurScreen",		tFlt,		GETTER,	      CURSCR,			1,	P0					  },
		{ "GetCurDMapScreen",		tFlt,		GETTER,	      CURDSCR,			1,	P0					  },
		{ "GetCurMap",			tFlt,		GETTER,	      CURMAP,			1,	P0					  },
		{ "GetCurDMap",			tFlt,		GETTER,	      CURDMAP,			1,	P0					  },
		{ "GetCurLevel",		tFlt,		GETTER,	      CURLEVEL,			1,	P0					  },
		{ "getNumDeaths",		tFlt,		GETTER,	      GAMEDEATHS,		1,	P0					  },
		{ "setNumDeaths",		tVoid,		SETTER,	      GAMEDEATHS,		1,	P1(	tFlt				) },
		{ "getCheat",			tFlt,		GETTER,	      GAMECHEAT,		1,	P0					  },
		{ "setCheat",			tVoid,		SETTER,	      GAMECHEAT,		1,	P1(	tFlt				) },
		{ "getTime",			tFlt,		GETTER,	      GAMETIME,			1,	P0					  },
		{ "setTime",			tVoid,		SETTER,	      GAMETIME,			1,	P1(	tFlt				) },
		{ "getHasPlayed",		tBool,		GETTER,	      GAMEHASPLAYED,		1,	P0					  },
		{ "setHasPlayed",		tVoid,		SETTER,	      GAMEHASPLAYED,		1,	P1(	tBool				) },
		{ "getTypingMode",		tBool,		GETTER,	      TYPINGMODE,		1,	P0					  },
		{ "setTypingMode",		tVoid,		SETTER,	      TYPINGMODE,		1,	P1(	tBool				) },
		{ "getTimeValid",		tBool,		GETTER,	      GAMETIMEVALID,		1,	P0					  },
		{ "setTimeValid",		tVoid,		SETTER,	      GAMETIMEVALID,		1,	P1(	tBool				) },
		{ "getGuyCount[]",		tFlt,		GETTER,	      GAMEGUYCOUNT,		2,	P1(	tFlt				) },
		{ "setGuyCount[]",		tVoid,		SETTER,	      GAMEGUYCOUNT,		2,	P2(	tFlt,	tFlt			) },
		{ "getContinueScreen",		tFlt,		GETTER,	      GAMECONTSCR,		1,	P0					  },
		{ "setContinueScreen",		tVoid,		SETTER,	      GAMECONTSCR,		1,	P1(	tFlt				) },
		{ "getContinueDMap",		tFlt,		GETTER,	      GAMECONTDMAP,		1,	P0					  },
		{ "setContinueDMap",		tVoid,		SETTER,	      GAMECONTDMAP,		1,	P1(	tFlt				) },
		{ "getCounter[]",		tFlt,		GETTER,	      GAMECOUNTERD,		32,	P1(	tFlt				) },
		{ "setCounter[]",		tVoid,		SETTER,	      GAMECOUNTERD,		32,	P2(	tFlt,	tFlt			) },
		{ "getMCounter[]",		tFlt,		GETTER,	      GAMEMCOUNTERD,		32,	P1(	tFlt				) },
		{ "setMCounter[]",		tVoid,		SETTER,	      GAMEMCOUNTERD,		32,	P2(	tFlt,	tFlt			) },
		{ "getDCounter[]",		tFlt,		GETTER,	      GAMEDCOUNTERD,		32,	P1(	tFlt				) },
		{ "setDCounter[]",		tVoid,		SETTER,	      GAMEDCOUNTERD,		32,	P2(	tFlt,	tFlt			) },
		{ "getGeneric[]",		tFlt,		GETTER,	      GAMEGENERICD,		256,	P1(	tFlt				) },
		{ "setGeneric[]",		tVoid,		SETTER,	      GAMEGENERICD,		256,	P2(	tFlt,	tFlt			) },
		{ "getMisc[]",			tFlt,		GETTER,	      GAMEMISC,			32,	P1(	tFlt				) },
		{ "setMisc[]",			tVoid,		SETTER,	      GAMEMISC,			32,	P2(	tFlt,	tFlt			) },
		{ "getLItems[]",		tFlt,		GETTER,	      GAMELITEMSD,		512,	P1(	tFlt				) },
		{ "setLItems[]",		tVoid,		SETTER,	      GAMELITEMSD,		512,	P2(	tFlt,	tFlt			) },
		{ "getLKeys[]",			tFlt,		GETTER,	      GAMELKEYSD,		512,	P1(	tFlt				) },
		{ "setLKeys[]",			tVoid,		SETTER,	      GAMELKEYSD,		512,	P2(	tFlt,	tFlt			) },
		{ "GetScreenState",		tBool,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenState",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tBool	) },
		{ "GetScreenD",			tAny,		FUNCTION,     0,			1,	P2(	tFlt,	tAny			) },
		{ "SetScreenD",			tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetDMapScreenD",		tAny,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetDMapScreenD",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tAny	) },
		{ "LoadItemData",		tItmC,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "PlaySound",			tVoid,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "PlayMIDI",			tVoid,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "PlayEnhancedMusic",		tBool,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetDMapMusicFilename",	tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetDMapMusicTrack",		tFlt,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "SetDMapEnhancedMusic",	tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetComboData",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboData",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetComboCSet",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboCSet",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetComboFlag",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboFlag",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetComboType",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboType",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetComboInherentFlag",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboInherentFlag",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetComboSolid",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetComboSolid",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetMIDI",			tFlt,		GETTER,	      GETMIDI,			1,	P0					  },
		{ "GetScreenFlags",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenEFlags",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "getDMapFlags[]",		tFlt,		GETTER,	      DMAPFLAGSD,		512,	P1(	tFlt				) },
		{ "setDMapFlags[]",		tVoid,		SETTER,	      DMAPFLAGSD,		512,	P2(	tFlt,	tFlt			) },
		{ "getDMapLevel[]",		tFlt,		GETTER,	      DMAPLEVELD,		512,	P1(	tFlt				) },
		{ "setDMapLevel[]",		tVoid,		SETTER,	      DMAPLEVELD,		512,	P2(	tFlt,	tFlt			) },
		{ "getDMapCompass[]",		tFlt,		GETTER,	      DMAPCOMPASSD,		512,	P1(	tFlt				) },
		{ "setDMapCompass[]",		tVoid,		SETTER,	      DMAPCOMPASSD,		512,	P2(	tFlt,	tFlt			) },
		{ "getDMapContinue[]",		tFlt,		GETTER,	      DMAPCONTINUED,		512,	P1(	tFlt				) },
		{ "setDMapContinue[]",		tVoid,		SETTER,	      DMAPCONTINUED,		512,	P2(	tFlt,	tFlt			) },
		{ "getDMapMIDI[]",		tFlt,		GETTER,	      DMAPMIDID,		512,	P1(	tFlt				) },
		{ "setDMapMIDI[]",		tVoid,		SETTER,	      DMAPMIDID,		512,	P2(	tFlt,	tFlt			) },
		{ "Save",			tVoid,		FUNCTION,     0,			1,	P0					  },
		{ "End",			tVoid,		FUNCTION,     0,			1,	P0					  },
		{ "ComboTile",			tFlt,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "GetSaveName",		tVoid,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "SetSaveName",		tVoid,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "GetMessage",			tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetDMapName",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetDMapTitle",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetDMapIntro",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "getStandalone",		tBool,		GETTER,	      GAMESTANDALONE,		1,	P0					  },
		{ "setStandalone",		tVoid,		SETTER,	      GAMESTANDALONE,		1,	P1(	tBool				) },
		{ "ShowSaveScreen",		tBool,		FUNCTION,     0,			1,	P0					  },
		{ "ShowSaveQuitScreen",		tVoid,		FUNCTION,     0,			1,	P0					  },
		{ "getLastEntranceScreen",	tFlt,		GETTER,	      GAMEENTRSCR,		1,	P0					  },
		{ "setLastEntranceScreen",	tVoid,		SETTER,	      GAMEENTRSCR,		1,	P1(	tFlt				) },
		{ "getLastEntranceDMap",	tFlt,		GETTER,	      GAMEENTRDMAP,		1,	P0					  },
		{ "setLastEntranceDMap",	tVoid,		SETTER,	      GAMEENTRDMAP,		1,	P1(	tFlt				) },
		{ "getClickToFreezeEnabled",	tBool,		GETTER,	      GAMECLICKFREEZE,		1,	P0					  },
		{ "setClickToFreezeEnabled",	tVoid,		SETTER,	      GAMECLICKFREEZE,		1,	P1(	tBool				) },
		{ "getDMapOffset[]",		tFlt,		GETTER,	      DMAPOFFSET,		512,	P1(	tFlt				) },
		{ "setDMapOffset[]",		tVoid,		SETTER,	      DMAPOFFSET,		512,	P2(	tFlt,	tFlt			) },
		{ "getDMapMap[]",		tFlt,		GETTER,	      DMAPMAP,			512,	P1(	tFlt				) },
		{ "setDMapMap[]",		tVoid,		SETTER,	      DMAPMAP,			512,	P2(	tFlt,	tFlt			) },
		{ "GetFFCScript",		tFlt,		FUNCTION,     0,			1,	P1(	tFlt				) },
		// Get an item script ID, similar to GetFFCScript()
		{ "GetItemScript",		tFlt,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "GreyscaleOn",		tVoid,		FUNCTION,     0,			1,	P0					  },
		{ "GreyscaleOff",		tVoid,		FUNCTION,     0,			1,	P0					  },
		// Joypad and Keyboard. -Z
		{ "getButtonPress[]",		tBool,		GETTER,	      BUTTONPRESS,		18,	P1(	tFlt				) },
		{ "setButtonPress[]",		tVoid,		SETTER,	      BUTTONPRESS,		18,	P2(	tFlt,	tBool			) },
		{ "getButtonInput[]",		tBool,		GETTER,	      BUTTONINPUT,		18,	P1(	tFlt				) },
		{ "setButtonInput[]",		tVoid,		SETTER,	      BUTTONINPUT,		18,	P2(	tFlt,	tBool			) },
		{ "getButtonHeld[]",		tBool,		GETTER,	      BUTTONHELD,		18,	P1(	tFlt				) },
		{ "setButtonHeld[]",		tVoid,		SETTER,	      BUTTONHELD,		18,	P2(	tFlt,	tBool			) },
		{ "getReadKey[]",		tBool,		GETTER,	      READKEY,			127,	P1(	tFlt				) },
		{ "getKeyPress[]",		tBool,		GETTER,	      KEYPRESS,			127,	P1(	tFlt				) },
		{ "setKeyPress[]",		tVoid,		SETTER,	      KEYPRESS,			127,	P2(	tFlt,	tBool			) },
		{ "getDisableItem[]",		tBool,		GETTER,	      DISABLEDITEM,		256,	P1(	tFlt				) },
		{ "setDisableItem[]",		tVoid,		SETTER,	      DISABLEDITEM,		256,	P2(	tFlt,	tBool			) },
		{ "getJoypadPress[]",		tFlt,		GETTER,	      JOYPADPRESS,		18,	P1(	tFlt				) },
		{ "getDMapPalette[]",		tFlt,		GETTER,	      DMAPLEVELPAL,		512,	P1(	tFlt				) },
		{ "setDMapPalette[]",		tVoid,		SETTER,	      DMAPLEVELPAL,		512,	P2(	tFlt,	tFlt			) },
		{ "MapCount",			tFlt,		GETTER,	      GAMEMAXMAPS,		1,	P0					  },
		// Versioning
		{ "getVersion",			tFlt,		GETTER,	      ZELDAVERSION,		1,	P0					  },
		{ "getBuild",			tFlt,		GETTER,	      ZELDABUILD,		1,	P0					  },
		{ "getBeta",			tFlt,		GETTER,	      ZELDABETA,		1,	P0					  },
		{ "getDisableActiveSubscreen",	tBool,		GETTER,	      NOACTIVESUBSC,		1,	P0					  },
		{ "setDisableActiveSubscreen",	tVoid,		SETTER,	      NOACTIVESUBSC,		1,	P1(	tBool				) },
		{ "SetMessage",			tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetDMapName",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetDMapTitle",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetDMapIntro",		tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "GetScreenEnemy",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenEnemy",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenDoor",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenDoor",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "SetScreenWidth",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenWidth",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenHeight",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenHeight",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenViewX",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenViewX",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenViewY",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenViewY",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenGuy",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenGuy",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenString",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenString",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenRoomType",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenRoomType",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenEntryX",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenEntryX",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenEntryY",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenEntryY",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenItem",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenItem",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenUndercombo",	tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenUndercombo",	tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenUnderCSet",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenUnderCSet",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenCatchall",		tVoid,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "GetScreenCatchall",		tFlt,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "SetScreenLayerOpacity",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenLayerOpacity",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenSecretCombo",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenSecretCombo",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenSecretCSet",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenSecretCSet",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenSecretFlag",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenSecretFlag",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenLayerMap",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenLayerMap",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenLayerScreen",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenLayerScreen",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenPath",		tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenPath",		tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenWarpReturnX",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenWarpReturnX",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "SetScreenWarpReturnY",	tVoid,		FUNCTION,     0,			1,	P4(	tFlt,	tFlt,	tFlt,	tFlt	) },
		{ "GetScreenWarpReturnY",	tFlt,		FUNCTION,     0,			1,	P3(	tFlt,	tFlt,	tFlt		) },
		{ "getHighestStringID",		tFlt,		GETTER,	      GAMENUMMESSAGES,		1,	P0					  },
		{ "getNumMessages",		tFlt,		GETTER,	      GAMENUMMESSAGES,		1,	P0					  },
		{ "setGameOverScreen[]",	tVoid,		SETTER,	      SETGAMEOVERELEMENT,	12,	P2(	tFlt,	tFlt			) },
		{ "setGameOverStrings[]",	tVoid,		SETTER,	      SETGAMEOVERSTRING,	3,	P2(	tFlt,	tFlt			) },
	//	{ "SetContinueScreen[]",	tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
	//	{ "SetContinueString[]",	tVoid,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "getJoypad[]",		tFlt,		GETTER,	      JOYPADPRESS,		18,	P1(	tFlt				) },
		{ "getPress[]",			tBool,		GETTER,	      BUTTONPRESS,		18,	P1(	tFlt				) },
		{ "setPress[]",			tVoid,		SETTER,	      BUTTONPRESS,		18,	P2(	tFlt,	tBool			) },
		{ "getButton[]",		tBool,		GETTER,	      BUTTONINPUT,		18,	P1(	tFlt				) },
		{ "setButton[]",		tVoid,		SETTER,	      BUTTONINPUT,		18,	P2(	tFlt,	tBool			) },
		{ "getHold[]",			tBool,		GETTER,	      BUTTONHELD,		18,	P1(	tFlt				) },
		{ "setHold[]",			tVoid,		SETTER,	      BUTTONHELD,		18,	P2(	tFlt,	tBool			) },
		{ "getReadKey[]",		tBool,		GETTER,	      READKEY,			127,	P1(	tFlt				) },
		{ "getKey[]",			tBool,		GETTER,	      KEYPRESS,			127,	P1(	tFlt				) },
		{ "setKey[]",			tVoid,		SETTER,	      KEYPRESS,			127,	P2(	tFlt,	tBool			) },
		{ "getMouse[]",			tFlt,		GETTER,	      MOUSEARR,			6,	P1(	tFlt				) },
		{ "setMouse[]",			tVoid,		SETTER,	      MOUSEARR,			6,	P2(	tFlt,	tFlt			) },
		{ "LoadNPCData",		tNpcC,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadComboData",		tCmb,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadMapData",		tMap,		FUNCTION,     0,			1,	P2(	tFlt,	tFlt			) },
		{ "LoadSpriteData",		tSpr,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadShopData",		tShp,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadInfoShopData",		tShp,		FUNCTION,     0,			1,	P1(	tFlt				) },
	//	{ "LoadScreenData",		tAny,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadBitmapID",		tGfx,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadMessageData",		tMsg,		FUNCTION,     0,			1,	P1(	tFlt				) },
		{ "LoadDMapData",		tDMap,		FUNCTION,     0,			1,	P1(	tFlt				) },
		ENTRY_END
	};
	
#	include "EntryHelperUnload.h"
}

Library::Game& Library::Game::instance()
{
	static Library::Game instance(NUL, table);
	return instance;
}

// void function(int, int)
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
	
#define LOAD_REFDATA(flabel, ffins, ref_var) \
{ \
	int id = memberids["flabel"]; \
	int label = lt.functionToLabel(id); \
	vector<Opcode *> code; \
	Opcode *first = new OPopRegister(new VarArgument(EXP1)); \
	first->setLabel(label); \
	code.push_back(first); \
	code.push_back(new OPopRegister(new VarArgument(NUL))); \
	code.push_back(new ffins(new VarArgument(EXP1))); \
	code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(ref_var))); \
	code.push_back(new OPopRegister(new VarArgument(EXP2))); \
	code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
	rval[label] = code; \
}
    
void Library::Game::generateFunctionCode(
		LinkTable* linktable, std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
	
	// bool GetScreenState(float, float, float)
	{
		int id = memberids["GetScreenState"];
		int label = lt.functionToLabel(id);
		int done = ScriptParser::getUniqueLabelID();
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OMultImmediate(new VarArgument(EXP1), new LiteralArgument(1360000)));
		code.push_back(new OAddRegister(new VarArgument(INDEX), new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENSTATEDD)));
		code.push_back(new OCompareImmediate(new VarArgument(EXP1), new LiteralArgument(0)));
		code.push_back(new OGotoTrueImmediate(new LabelArgument(done)));
		code.push_back(new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OGotoImmediate(new LabelArgument(done)));
		Opcode *next = new OPopRegister(new VarArgument(EXP2));
		next->setLabel(done);
		code.push_back(next);
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenState(float, float, float,bool)
	{
		int id = memberids["SetScreenState"];
		int label = lt.functionToLabel(id);
		int done = ScriptParser::getUniqueLabelID();
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OSubImmediate(new VarArgument(EXP1), new LiteralArgument(10000)));
		code.push_back(new OMultImmediate(new VarArgument(EXP1), new LiteralArgument(1360000)));
		code.push_back(new OAddRegister(new VarArgument(INDEX), new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OCompareImmediate(new VarArgument(SFTEMP), new LiteralArgument(0)));
		code.push_back(new OGotoTrueImmediate(new LabelArgument(done)));
		code.push_back(new OSetImmediate(new VarArgument(SFTEMP), new LiteralArgument(10000)));
		Opcode *next = new OSetRegister(new VarArgument(SCREENSTATEDD), new VarArgument(SFTEMP));
		next->setLabel(done);
		code.push_back(next);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenD(float, float,int)
	{
		int id = memberids["GetScreenD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SDDD)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenD(float, float, float)
	{
		int id = memberids["SetScreenD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SDDD), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetDMapScreenD(float, float, float)
	{
		int id = memberids["GetDMapScreenD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SDDDD)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDMapScreenD(float, float, float, float)
	{
		int id = memberids["SetDMapScreenD"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SDDDD), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// itemclass LoadItemData(float)
	{
		int id = memberids["LoadItemData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadItemDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFITEMCLASS)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void PlaySound(float)
	{
		int id = memberids["PlaySound"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPlaySoundRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void PlayMIDI(float)
	{
		int id = memberids["PlayMIDI"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPlayMIDIRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void PlayEnhancedMusic(float, float)
	{
		int id = memberids["PlayEnhancedMusic"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPlayEnhancedMusic(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetDMapMusicFilename(float, float)
	{
		int id = memberids["GetDMapMusicFilename"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetDMapMusicFilename(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetDMapMusicTrack(float)
	{
		int id = memberids["GetDMapMusicTrack"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetDMapMusicTrack(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void SetDMapEnhancedMusic(float, float, float)
	{
		int id = memberids["SetDMapEnhancedMusic"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetDMapEnhancedMusic();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
        
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float GetComboData(float, float, float)
	{
		int id = memberids["GetComboData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBODDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboData(float, float, float, float)
	{
		int id = memberids["SetComboData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBODDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetComboCSet(float, float, float)
	{
		int id = memberids["GetComboCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOCDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboCSet(float, float, float, float)
	{
		int id = memberids["SetComboCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBOCDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetComboFlag(float, float, float)
	{
		int id = memberids["GetComboFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOFDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboFlag(float, float, float, float)
	{
		int id = memberids["SetComboFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBOFDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetComboType(float, float, float)
	{
		int id = memberids["GetComboType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOTDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboType(float, float, float, float)
	{
		int id = memberids["SetComboType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBOTDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetComboInherentFlag(float, float, float)
	{
		int id = memberids["GetComboInherentFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOIDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboInherentFlag(float, float, float, float)
	{
		int id = memberids["SetComboInherentFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBOIDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetComboCollision(float, float, float)
	{
		int id = memberids["GetComboSolid"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOSDM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetComboCollision(float, float, float, float)
	{
		int id = memberids["SetComboSolid"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(COMBOSDM), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenFlags(float, float, float)
	{
		int id = memberids["GetScreenFlags"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenFlags(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenEFlags(float, float, float)
	{
		int id = memberids["GetScreenEFlags"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenEFlags(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void Save()
	{
		int id = memberids["Save"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OSave());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void End()
	{
		int id = memberids["End"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OEnd());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// float ComboTile(float)
	{
		int id = memberids["ComboTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OComboTile(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	// void GetSaveName(float)
	{
		int id = memberids["GetSaveName"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetSaveName(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSaveName(float)
	{
		int id = memberids["SetSaveName"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetSaveName(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetMessage(float, float)
	{
		int id = memberids["GetMessage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OGetMessage(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetDMapName(float, float)
	{
		int id = memberids["GetDMapName"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OGetDMapName(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetDMapTitle(float, float)
	{
		int id = memberids["GetDMapTitle"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OGetDMapTitle(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetDMapIntro(float, float)
	{
		int id = memberids["GetDMapIntro"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OGetDMapIntro(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void GreyscaleOn()
	{
		int id = memberids["GreyscaleOn"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OGreyscaleOn());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
            
	// void GreyscaleOff()
	{
		int id = memberids["GreyscaleOff"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OGreyscaleOff());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// void SetMessage(float, float)
	{
		int id = memberids["SetMessage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSetMessage(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDMapName(float, float)
	{
		int id = memberids["SetDMapName"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSetDMapName(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDMapTitle(float, float)
	{
		int id = memberids["SetDMapTitle"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSetDMapTitle(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDMapIntro(float, float)
	{
		int id = memberids["SetDMapIntro"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new OSetDMapIntro(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// bool ShowSaveScreen()
	{
		int id = memberids["ShowSaveScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OShowSaveScreen(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// void ShowSaveQuitScreen()
	{
		int id = memberids["ShowSaveQuitScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop pointer, and ignore it
		Opcode *first = new OPopRegister(new VarArgument(NUL));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OShowSaveQuitScreen());
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// float GetFFCScript(float)
	{
		int id = memberids["GetFFCScript"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetFFCScript(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// float GetItemScript(float)
	{
		int id = memberids["GetItemScript"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetItemScript(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// float GetScreenEnemy(float, float, float)
	{
		int id = memberids["GetScreenEnemy"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenEnemy(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenDoor(float, float, float)
	{
		int id = memberids["GetScreenDoor"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenDoor(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenEnemy(float, float, float, float)
	{
		int id = memberids["SetScreenEnemy"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENENEMY), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenDoor(float, float, float, float)
	{
		int id = memberids["SetScreenDoor"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENDOOR), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetScreenWidth(float, float, float)
	{
		int id = memberids["SetScreenWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENWIDTH), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenWidth(float, float)
	{
		int id = memberids["GetScreenWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENWIDTH)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetScreenHeight(float, float, float)
	{
		int id = memberids["SetScreenHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENHEIGHT), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenHeight(float, float)
	{
		int id = memberids["GetScreenHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENHEIGHT)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenViewX(float, float, float)
	{
		int id = memberids["SetScreenViewX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENVIEWX), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenViewX(float, float)
	{
		int id = memberids["GetScreenViewX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENVIEWX)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenViewY(float, float, float)
	{
		int id = memberids["SetScreenViewY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENVIEWY), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenViewY(float, float)
	{
		int id = memberids["GetScreenViewY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENVIEWY)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenGuy(float, float, float)
	{
		int id = memberids["SetScreenGuy"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENGUY), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenGuy(float, float)
	{
		int id = memberids["GetScreenGuy"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENGUY)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenString(float, float, float)
	{
		int id = memberids["SetScreenString"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENSTRING), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenString(float, float)
	{
		int id = memberids["GetScreenString"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENSTRING)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenRoomType(float, float, float)
	{
		int id = memberids["SetScreenRoomType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENROOM), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenRoomType(float, float)
	{
		int id = memberids["GetScreenRoomType"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENROOM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenEntryX(float, float, float)
	{
		int id = memberids["SetScreenEntryX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENENTX), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenEntryX(float, float)
	{
		int id = memberids["GetScreenEntryX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENENTX)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenEntryY(float, float, float)
	{
		int id = memberids["SetScreenEntryY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENENTY), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenEntryY(float, float)
	{
		int id = memberids["GetScreenEntryY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENENTY)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenItem(float, float, float)
	{
		int id = memberids["SetScreenItem"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENITEM), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenItem(float, float)
	{
		int id = memberids["GetScreenItem"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENITEM)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenUndercombo(float, float, float)
	{
		int id = memberids["SetScreenUndercombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENUNDCMB), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenUndercombo(float, float)
	{
		int id = memberids["GetScreenUndercombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENUNDCMB)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenUnderCSet(float, float, float)
	{
		int id = memberids["SetScreenUnderCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENUNDCST), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenUnderCSet(float, float)
	{
		int id = memberids["GetScreenUnderCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENUNDCST)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenCatchall(float, float, float)
	{
		int id = memberids["SetScreenCatchall"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SCREENCATCH), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenCatchall(float, float)
	{
		int id = memberids["GetScreenCatchall"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SCREENCATCH)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetScreenLayerOpacity(float, float, float, float)
	{
		int id = memberids["SetScreenLayerOpacity"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENLAYOP), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenLayerOpacity(float, float, float)
	{
		int id = memberids["GetScreenLayerOpacity"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenLayerOpacity(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScreenSecretCombo(float, float, float, float)
	{
		int id = memberids["SetScreenSecretCombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENSECCMB), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenSecretCombo(float, float, float)
	{
		int id = memberids["GetScreenSecretCombo"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenSecretCombo(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScreenSecretCSet(float, float, float, float)
	{
		int id = memberids["SetScreenSecretCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENSECCST), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenSecretCSet(float, float, float)
	{
		int id = memberids["GetScreenSecretCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenSecretCSet(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenSecretFlag(float, float, float, float)
	{
		int id = memberids["SetScreenSecretFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENSECFLG), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenSecretFlag(float, float, float)
	{
		int id = memberids["GetScreenSecretFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenSecretFlag(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScreenLayerMap(float, float, float, float)
	{
		int id = memberids["SetScreenLayerMap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENLAYMAP), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenLayerMap(float, float, float)
	{
		int id = memberids["GetScreenLayerMap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenLayerMap(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScreenLayerScreen(float, float, float, float)
	{
		int id = memberids["SetScreenLayerScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENLAYSCR), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenLayerScreen(float, float, float)
	{
		int id = memberids["GetScreenLayerScreen"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenLayerScreen(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetScreenPath(float, float, float, float)
	{
		int id = memberids["SetScreenPath"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENPATH), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenPath(float, float, float)
	{
		int id = memberids["GetScreenPath"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenPath(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenWarpReturnX(float, float, float, float)
	{
		int id = memberids["SetScreenWarpReturnX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENWARPRX), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScreenWarpReturnX(float, float, float)
	{
		int id = memberids["GetScreenWarpReturnX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenWarpReturnX(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScreenWarpReturnY(float, float, float, float)
	{
		int id = memberids["SetScreenWarpReturnY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(SETSCREENWARPRY), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// void SetContinueScreen(float, float)
	//TWO_INPUT_NO_RETURN("SetContinueScreen", OSSetContinueScreen);

	// void SetContinueString(float, float)
	//TWO_INPUT_NO_RETURN("SetContinueString", OSSetContinueString);
	
	// float GetScreenWarpReturnY(float, float, float)
	{
		int id = memberids["GetScreenWarpReturnY"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetScreenWarpReturnY(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// NpcData LoadNPCData(float)
	{
	    
		int id = memberids["LoadNPCData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadNPCDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFNPCCLASS)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code; 
	}
    
	// DMap LoadDMapData(float)
	{
	    
		int id = memberids["LoadDMapData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadDMapDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFDMAPDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code; 
	}
	
	// Message LoadMessageData(float)
	{
	    
		int id = memberids["LoadMessageData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadMessageDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFMSGDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code; 
	}
	
	// Combo LoadComboData(float)
	{
		int id = memberids["LoadComboData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadComboDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFCOMBODATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code; 
	}

	// int LoadMapData(float map, float scr)
	{
		int id = memberids["LoadMapData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(LOADMAPDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// Sprite LoadSpriteData(float)
	{
	    
		int id = memberids["LoadSpriteData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadSpriteDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFSPRITEDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;    
	}
	
	// Shop LoadShopData(float)
	{
	    
		int id = memberids["LoadShopData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadShopDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFSHOPDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;    
	}
	
	// Shop LoadInfoShopData(float)
	{
		int id = memberids["LoadInfoShopData"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadInfoShopDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFSHOPDATA)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;    
	}
	
	// Screen LoadScreenData(float)
	//LOAD_REFDATA("LoadScreenData", OLoadScreenDataRegister, NUL);
	
	// graphics LoadBitmapId(float)
	{
		int id = memberids["LoadBitmapID"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OLoadBitmapDataRegister(new VarArgument(EXP1)));
		code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(REFGRAPHICS)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;   
	}
}

#undef TWO_INPUT_NO_RETURN
#undef LOAD_REFDATA

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
