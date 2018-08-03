#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_LINK
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,			rettype,	type,		var,			num,	params
		{ "getX",		tFlt,		GETTER,		LINKX,			1,	P0				  },
		{ "setX",		tVoid,		SETTER,		LINKX,			1,	P1(	tFlt			) },
		{ "getY",		tFlt,		GETTER,		LINKY,			1,	P0				  },
		{ "setY",		tVoid,		SETTER,		LINKY,			1,	P1(	tFlt			) },
		{ "getZ",		tFlt,		GETTER,		LINKZ,			1,	P0				  },
		{ "setZ",		tVoid,		SETTER,		LINKZ,			1,	P1(	tFlt			) },
		{ "getJump",		tFlt,		GETTER,		LINKJUMP,		1,	P0				  },
		{ "setJump",		tVoid,		SETTER,		LINKJUMP,		1,	P1(	tFlt			) },
		{ "getDir",		tFlt,		GETTER,		LINKDIR,		1,	P0				  },
		{ "setDir",		tVoid,		SETTER,		LINKDIR,		1,	P1(	tFlt			) },
		{ "getHitDir",		tFlt,		GETTER,		LINKHITDIR,		1,	P0				  },
		{ "setHitDir",		tVoid,		SETTER,		LINKHITDIR,		1,	P1(	tFlt			) },
		{ "getSwordJinx",	tFlt,		GETTER,		LINKSWORDJINX,		1,	P0				  },
		{ "setSwordJinx",	tVoid,		SETTER,		LINKSWORDJINX,		1,	P1(	tFlt			) },
		{ "getItemJinx",	tFlt,		GETTER,		LINKITEMJINX,		1,	P0				  },
		{ "setItemJinx",	tVoid,		SETTER,		LINKITEMJINX,		1,	P1(	tFlt			) },
		{ "getHP",		tFlt,		GETTER,		LINKHP,			1,	P0				  },
		{ "setHP",		tVoid,		SETTER,		LINKHP,			1,	P1(	tFlt			) },
		{ "getMP",		tFlt,		GETTER,		LINKMP,			1,	P0				  },
		{ "setMP",		tVoid,		SETTER,		LINKMP,			1,	P1(	tFlt			) },
		{ "getMaxHP",		tFlt,		GETTER,		LINKMAXHP,		1,	P0				  },
		{ "setMaxHP",		tVoid,		SETTER,		LINKMAXHP,		1,	P1(	tFlt			) },
		{ "getMaxMP",		tFlt,		GETTER,		LINKMAXMP,		1,	P0				  },
		{ "setMaxMP",		tVoid,		SETTER,		LINKMAXMP,		1,	P1(	tFlt			) },
		{ "getAction",		tFlt,		GETTER,		LINKACTION,		1,	P0				  },
		{ "setAction",		tVoid,		SETTER,		LINKACTION,		1,	P1(	tFlt			) },
		{ "getHeldItem",	tFlt,		GETTER,		LINKHELD,		1,	P0				  },
		{ "setHeldItem",	tVoid,		SETTER,		LINKHELD,		1,	P1(	tFlt			) },
		{ "Warp",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "PitWarp",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "getInputStart",	tBool,		GETTER,		INPUTSTART,		1,	P0				  },
		{ "setInputStart",	tVoid,		SETTER,		INPUTSTART,		1,	P1(	tBool			) },
		{ "getInputMap",	tBool,		GETTER,		INPUTMAP,		1,	P0				  },
		{ "setInputMap",	tVoid,		SETTER,		INPUTMAP,		1,	P1(	tBool			) },
		{ "getInputUp",		tBool,		GETTER,		INPUTUP,		1,	P0				  },
		{ "setInputUp",		tVoid,		SETTER,		INPUTUP,		1,	P1(	tBool			) },
		{ "getInputDown",	tBool,		GETTER,		INPUTDOWN,		1,	P0				  },
		{ "setInputDown",	tVoid,		SETTER,		INPUTDOWN,		1,	P1(	tBool			) },
		{ "getInputLeft",	tBool,		GETTER,		INPUTLEFT,		1,	P0				  },
		{ "setInputLeft",	tVoid,		SETTER,		INPUTLEFT,		1,	P1(	tBool			) },
		{ "getInputRight",	tBool,		GETTER,		INPUTRIGHT,		1,	P0				  },
		{ "setInputRight",	tVoid,		SETTER,		INPUTRIGHT,		1,	P1(	tBool			) },
		{ "getInputA",		tBool,		GETTER,		INPUTA,			1,	P0				  },
		{ "setInputA",		tVoid,		SETTER,		INPUTA,			1,	P1(	tBool			) },
		{ "getInputB",		tBool,		GETTER,		INPUTB,			1,	P0				  },
		{ "setInputB",		tVoid,		SETTER,		INPUTB,			1,	P1(	tBool			) },
		{ "getInputL",		tBool,		GETTER,		INPUTL,			1,	P0				  },
		{ "setInputL",		tVoid,		SETTER,		INPUTL,			1,	P1(	tBool			) },
		{ "getInputR",		tBool,		GETTER,		INPUTR,			1,	P0				  },
		{ "setInputR",		tVoid,		SETTER,		INPUTR,			1,	P1(	tBool			) },
		{ "getInputEx1",	tBool,		GETTER,		INPUTEX1,		1,	P0				  },
		{ "setInputEx1",	tVoid,		SETTER,		INPUTEX1,		1,	P1(	tBool			) },
		{ "getInputEx2",	tBool,		GETTER,		INPUTEX2,		1,	P0				  },
		{ "setInputEx2",	tVoid,		SETTER,		INPUTEX2,		1,	P1(	tBool			) },
		{ "getInputEx3",	tBool,		GETTER,		INPUTEX3,		1,	P0				  },
		{ "setInputEx3",	tVoid,		SETTER,		INPUTEX3,		1,	P1(	tBool			) },
		{ "getInputEx4",	tBool,		GETTER,		INPUTEX4,		1,	P0				  },
		{ "setInputEx4",	tVoid,		SETTER,		INPUTEX4,		1,	P1(	tBool			) },
		{ "getPressStart",	tBool,		GETTER,		INPUTPRESSSTART,	1,	P0				  },
		{ "setPressStart",	tVoid,		SETTER,		INPUTPRESSSTART,	1,	P1(	tBool			) },
		{ "getPressUp",		tBool,		GETTER,		INPUTPRESSUP,		1,	P0				  },
		{ "setPressUp",		tVoid,		SETTER,		INPUTPRESSUP,		1,	P1(	tBool			) },
		{ "getPressDown",	tBool,		GETTER,		INPUTPRESSDOWN,		1,	P0				  },
		{ "setPressDown",	tVoid,		SETTER,		INPUTPRESSDOWN,		1,	P1(	tBool			) },
		{ "getPressLeft",	tBool,		GETTER,		INPUTPRESSLEFT,		1,	P0				  },
		{ "setPressLeft",	tVoid,		SETTER,		INPUTPRESSLEFT,		1,	P1(	tBool			) },
		{ "getPressRight",	tBool,		GETTER,		INPUTPRESSRIGHT,	1,	P0				  },
		{ "setPressRight",	tVoid,		SETTER,		INPUTPRESSRIGHT,	1,	P1(	tBool			) },
		{ "getPressA",		tBool,		GETTER,		INPUTPRESSA,		1,	P0				  },
		{ "setPressA",		tVoid,		SETTER,		INPUTPRESSA,		1,	P1(	tBool			) },
		{ "getPressB",		tBool,		GETTER,		INPUTPRESSB,		1,	P0				  },
		{ "setPressB",		tVoid,		SETTER,		INPUTPRESSB,		1,	P1(	tBool			) },
		{ "getPressL",		tBool,		GETTER,		INPUTPRESSL,		1,	P0				  },
		{ "setPressL",		tVoid,		SETTER,		INPUTPRESSL,		1,	P1(	tBool			) },
		{ "getPressR",		tBool,		GETTER,		INPUTPRESSR,		1,	P0				  },
		{ "setPressR",		tVoid,		SETTER,		INPUTPRESSR,		1,	P1(	tBool			) },
		{ "getPressEx1",	tBool,		GETTER,		INPUTPRESSEX1,		1,	P0				  },
		{ "setPressEx1",	tVoid,		SETTER,		INPUTPRESSEX1,		1,	P1(	tBool			) },
		{ "getPressEx2",	tBool,		GETTER,		INPUTPRESSEX2,		1,	P0				  },
		{ "setPressEx2",	tVoid,		SETTER,		INPUTPRESSEX2,		1,	P1(	tBool			) },
		{ "getPressEx3",	tBool,		GETTER,		INPUTPRESSEX3,		1,	P0				  },
		{ "setPressEx3",	tVoid,		SETTER,		INPUTPRESSEX3,		1,	P1(	tBool			) },
		{ "getPressEx4",	tBool,		GETTER,		INPUTPRESSEX4,		1,	P0				  },
		{ "setPressEx4",	tVoid,		SETTER,		INPUTPRESSEX4,		1,	P1(	tBool			) },
		{ "getInputMouseX",	tFlt,		GETTER,		INPUTMOUSEX,		1,	P0				  },
		{ "setInputMouseX",	tVoid,		SETTER,		INPUTMOUSEX,		1,	P1(	tFlt			) },
		{ "getInputMouseY",	tFlt,		GETTER,		INPUTMOUSEY,		1,	P0				  },
		{ "setInputMouseY",	tVoid,		SETTER,		INPUTMOUSEY,		1,	P1(	tFlt			) },
		{ "getInputMouseZ",	tFlt,		GETTER,		INPUTMOUSEZ,		1,	P0				  },
		{ "setInputMouseZ",	tVoid,		SETTER,		INPUTMOUSEZ,		1,	P1(	tFlt			) },
		{ "getInputMouseB",	tFlt,		GETTER,		INPUTMOUSEB,		1,	P0				  },
		{ "setInputMouseB",	tVoid,		SETTER,		INPUTMOUSEB,		1,	P1(	tFlt			) },
		{ "getItem[]",		tBool,		GETTER,		LINKITEMD,		256,	P1(	tFlt			) },
		{ "setItem[]",		tVoid,		SETTER,		LINKITEMD,		256,	P2(	tFlt,	tBool		) },
		{ "getHitWidth",	tFlt,		GETTER,		LINKHXSZ,		1,	P0				  },
		{ "setHitWidth",	tVoid,		SETTER,		LINKHXSZ,		1,	P1(	tFlt			) },
		{ "getHitHeight",	tFlt,		GETTER,		LINKHYSZ,		1,	P0				  },
		{ "setHitHeight",	tVoid,		SETTER,		LINKHYSZ,		1,	P1(	tFlt			) },
		{ "getHitZHeight",	tFlt,		GETTER,		LINKHZSZ,		1,	P0				  },
		{ "setHitZHeight",	tVoid,		SETTER,		LINKHZSZ,		1,	P1(	tFlt			) },
		{ "getTileWidth",	tFlt,		GETTER,		LINKTXSZ,		1,	P0				  },
		{ "setTileWidth",	tVoid,		SETTER,		LINKTXSZ,		1,	P1(	tFlt			) },
		{ "getTileHeight",	tFlt,		GETTER,		LINKTYSZ,		1,	P0				  },
		{ "setTileHeight",	tVoid,		SETTER,		LINKTYSZ,		1,	P1(	tFlt			) },
		{ "getDrawXOffset",	tFlt,		GETTER,		LINKXOFS,		1,	P0				  },
		{ "setDrawXOffset",	tVoid,		SETTER,		LINKXOFS,		1,	P1(	tFlt			) },
		{ "getDrawYOffset",	tFlt,		GETTER,		LINKYOFS,		1,	P0				  },
		{ "setDrawYOffset",	tVoid,		SETTER,		LINKYOFS,		1,	P1(	tFlt			) },
		{ "getDrawZOffset",	tFlt,		GETTER,		LINKZOFS,		1,	P0				  },
		{ "setDrawZOffset",	tVoid,		SETTER,		LINKZOFS,		1,	P1(	tFlt			) },
		{ "getHitXOffset",	tFlt,		GETTER,		LINKHXOFS,		1,	P0				  },
		{ "setHitXOffset",	tVoid,		SETTER,		LINKHXOFS,		1,	P1(	tFlt			) },
		{ "getHitYOffset",	tFlt,		GETTER,		LINKHYOFS,		1,	P0				  },
		{ "setHitYOffset",	tVoid,		SETTER,		LINKHYOFS,		1,	P1(	tFlt			) },
		{ "getDrunk",		tFlt,		GETTER,		LINKDRUNK,		1,	P0				  },
		{ "setDrunk",		tVoid,		SETTER,		LINKDRUNK,		1,	P1(	tFlt			) },
		{ "getEquipment",	tFlt,		GETTER,		LINKEQUIP,		1,	P0				  },
		{ "setEquipment",	tVoid,		SETTER,		LINKEQUIP,		1,	P1(	tFlt			) },
		{ "getInputAxisUp",	tBool,		GETTER,		INPUTAXISUP,		1,	P0				  },
		{ "setInputAxisUp",	tVoid,		SETTER,		INPUTAXISUP,		1,	P1(	tBool			) },
		{ "getInputAxisDown",	tBool,		GETTER,		INPUTAXISDOWN,		1,	P0				  },
		{ "setInputAxisDown",	tVoid,		SETTER,		INPUTAXISDOWN,		1,	P1(	tBool			) },
		{ "getInputAxisLeft",	tBool,		GETTER,		INPUTAXISLEFT,		1,	P0				  },
		{ "setInputAxisLeft",	tVoid,		SETTER,		INPUTAXISLEFT,		1,	P1(	tBool			) },
		{ "getInputAxisRight",	tBool,		GETTER,		INPUTAXISRIGHT,		1,	P0				  },
		{ "setInputAxisRight",	tVoid,		SETTER,		INPUTAXISRIGHT,		1,	P1(	tBool			) },
		{ "getPressAxisUp",	tBool,		GETTER,		INPUTPRESSAXISUP,	1,	P0				  },
		{ "setPressAxisUp",	tVoid,		SETTER,		INPUTPRESSAXISUP,	1,	P1(	tBool			) },
		{ "getPressAxisDown",	tBool,		GETTER,		INPUTPRESSAXISDOWN,	1,	P0				  },
		{ "setPressAxisDown",	tVoid,		SETTER,		INPUTPRESSAXISDOWN,	1,	P1(	tBool			) },
		{ "getPressAxisLeft",	tBool,		GETTER,		INPUTPRESSAXISLEFT,	1,	P0				  },
		{ "setPressAxisLeft",	tVoid,		SETTER,		INPUTPRESSAXISLEFT,	1,	P1(	tBool			) },
		{ "getPressAxisRight",	tBool,		GETTER,		INPUTPRESSAXISRIGHT,	1,	P0				  },
		{ "setPressAxisRight",	tVoid,		SETTER,		INPUTPRESSAXISRIGHT,	1,	P1(	tBool			) },
		{ "getInvisible",	tFlt,		GETTER,		LINKINVIS,		1,	P0				  },
		{ "setInvisible",	tVoid,		SETTER,		LINKINVIS,		1,	P1(	tBool			) },
		{ "getCollDetection",	tFlt,		GETTER,		LINKINVINC,		1,	P0				  },
		{ "setCollDetection",	tVoid,		SETTER,		LINKINVINC,		1,	P1(	tBool			) },
		{ "getMisc[]",		tAny,		GETTER,		LINKMISCD,		32,	P1(	tFlt			) },
		{ "setMisc[]",		tVoid,		SETTER,		LINKMISCD,		32,	P2(	tFlt,	tAny		) },
		{ "getDefense[]",	tFlt,		GETTER,		LINKDEFENCE,		256,	P1(	tFlt			) },
		{ "setDefense[]",	tVoid,		SETTER,		LINKDEFENCE,		256,	P2(	tFlt,	tFlt		) },
		{ "getHitBy[]",		tAny,		GETTER,		LINKHITBY,		4,	P1(	tFlt			) },
		{ "setHitBy[]",		tVoid,		SETTER,		LINKHITBY,		4,	P2(	tFlt,	tAny		) },
		{ "getLadderX",		tFlt,		GETTER,		LINKLADDERX,		1,	P0				  },
		{ "getLadderY",		tFlt,		GETTER,		LINKLADDERY,		1,	P0				  },
		{ "getTile",		tFlt,		GETTER,		LINKTILE,		1,	P0				  },
		{ "setTile",		tVoid,		SETTER,		LINKTILE,		1,	P1(	tFlt			) },
		{ "getFlip",		tFlt,		GETTER,		LINKFLIP,		1,	P0				  },
		{ "setFlip",		tVoid,		SETTER,		LINKFLIP,		1,	P1(	tFlt			) },
		{ "getPressMap",	tBool,		GETTER,		INPUTPRESSMAP,		1,	P0				  },
		{ "setPressMap",	tVoid,		SETTER,		INPUTPRESSMAP,		1,	P1(	tBool			) },
		{ "SelectAWeapon",	tVoid,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "SelectBWeapon",	tVoid,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "setInvFrames",	tVoid,		SETTER,		LINKINVFRAME,		1,	P1(	tFlt			) },
		{ "getInvFrames",	tFlt,		GETTER,		LINKINVFRAME,		1,	P0				  },
		{ "setInvFlicker",	tVoid,		SETTER,		LINKCANFLICKER,		1,	P1(	tBool			) },
		{ "getInvFlicker",	tBool,		GETTER,		LINKCANFLICKER,		1,	P0				  },
		{ "setHurtSound",	tVoid,		SETTER,		LINKHURTSFX,		1,	P1(	tFlt			) },
		{ "getHurtSound",	tFlt,		GETTER,		LINKHURTSFX,		1,	P0				  },
		{ "getUsingItem",	tFlt,		GETTER,		LINKUSINGITEM,		1,	P0				  },
		{ "setUsingItem",	tVoid,		SETTER,		LINKUSINGITEM,		1,	P1(	tFlt			) },
		// Not sure what the 'attack' var is used for at present, but that is what etItemA returned, so I'm renaming these to ->Attack
		{ "getAttack",		tFlt,		GETTER,		LINKUSINGITEMA,		1,	P0				  },
		{ "setAttack",		tVoid,		SETTER,		LINKUSINGITEMA,		1,	P1(	tFlt			) },
		{ "SetItemA",		tVoid,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "SetItemB",		tVoid,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "SetItemSlot",	tVoid,		FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt	) },
		{ "setItemB",		tVoid,		SETTER,		LINKITEMB,		1,	P1(	tFlt			) },
		{ "setItemA",		tVoid,		SETTER,		LINKITEMA,		1,	P1(	tFlt			) },
		{ "getItemB",		tFlt,		GETTER,		LINKITEMB,		1,	P0				  },
		{ "getItemA",		tFlt,		GETTER,		LINKITEMA,		1,	P0				  },
		{ "getEaten",		tFlt,		GETTER,		LINKEATEN,		1,	P0				  },
		{ "setEaten",		tVoid,		SETTER,		LINKEATEN,		1,	P1(	tFlt			) },
		{ "getStun",		tFlt,		GETTER,		LINKSTUN,		1,	P0				  },
		{ "setStun",		tVoid,		SETTER,		LINKSTUN,		1,	P1(	tFlt			) },
		{ "getPushing",		tFlt,		GETTER,		LINKPUSH,		1,	P0				  },
	//	{ "setPushing",		tVoid,		SETTER,		LINKEATEN,		1,	P1(	tFlt			) },
		{ "getScriptTile",	tFlt,		GETTER,		LINKSCRIPTTILE,		1,	P0				  },
		{ "setScriptTile",	tVoid,		SETTER,		LINKSCRIPTTILE,		1,	P1(	tFlt			) },
		{ "getScriptFlip",	tFlt,		GETTER,		LINKSCRIPFLIP,		1,	P0				  },
		{ "setScriptFlip",	tVoid,		SETTER,		LINKSCRIPFLIP,		1,	P1(	tFlt			) },
		{ "getDiagonal",	tBool,		GETTER,		LINKDIAG,		1,	P0				  },
		{ "setDiagonal",	tVoid,		SETTER,		LINKDIAG,		1,	P1(	tBool			) },
		{ "getBigHitbox",	tBool,		GETTER,		LINKBIGHITBOX,		1,	P0				  },
		{ "setBigHitbox",	tVoid,		SETTER,		LINKBIGHITBOX,		1,	P1(	tBool			) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Link& Library::Link::instance()
{
	static Library::Link instance(NUL, table);
	return instance;
}

void Library::Link::generateFunctionCode(
		LinkTable* linktable, std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// Warp(float, float)
	{
		int id = memberids["Warp"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop ffc, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		//ffc must be this (link is not a user-accessible type)
		code.push_back(new OWarp(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetItemSlot(float item, float slot, float force)
	{
		int id = memberids["SetItemSlot"];
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
		code.push_back(new OSetRegister(new VarArgument(SETITEMSLOT), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetItemA(float)
	{
		int id = memberids["SetItemA"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OSetRegister(new VarArgument(GAMESETA), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetItemB(float)
	{
		int id = memberids["SetItemB"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//code.push_back(new OPopRegister(new VarArgument(INDEX)));
		code.push_back(new OSetRegister(new VarArgument(GAMESETB), new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void PitWarp(float, float)
	{
		int id = memberids["PitWarp"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop ffc, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		//ffc must be this (link is not a user-accessible type)
		code.push_back(new OPitWarp(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SelectAWeapon(float)
	{
		int id = memberids["SelectAWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSelectAWeaponRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// SelectBWeapon(float)
	{
		int id = memberids["SelectBWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSelectBWeaponRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
