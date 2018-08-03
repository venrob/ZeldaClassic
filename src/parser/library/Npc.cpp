#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_NPC
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	  name,			rettype,type,	        var,		num,	params
		{ "getX",               tFlt,   GETTER,         NPCX,           1,	P0			  },
		{ "setX",               tVoid,  SETTER,         NPCX,           1,      P1(	tFlt		) },
		{ "getY",               tFlt,   GETTER,         NPCY,           1,	P0			  },
		{ "setY",               tVoid,  SETTER,         NPCY,           1,      P1(	tFlt		) },
		{ "getZ",               tFlt,   GETTER,         NPCZ,           1,	P0			  },
		{ "setZ",               tVoid,  SETTER,         NPCZ,           1,      P1(	tFlt		) },
		{ "getJump",            tFlt,   GETTER,         NPCJUMP,        1,	P0			  },
		{ "setJump",            tVoid,  SETTER,         NPCJUMP,        1,      P1(	tFlt		) },
		{ "getDir",             tFlt,   GETTER,         NPCDIR,         1,	P0			  },
		{ "setDir",             tVoid,  SETTER,         NPCDIR,         1,      P1(	tFlt		) },
		{ "getRate",            tFlt,   GETTER,         NPCRATE,        1,	P0			  },
		{ "setRate",            tVoid,  SETTER,         NPCRATE,        1,      P1(	tFlt		) },
		{ "getHoming",          tFlt,   GETTER,         NPCHOMING,      1,	P0			  },
		{ "setHoming",          tVoid,  SETTER,         NPCHOMING,      1,      P1(	tFlt		) },
		{ "getStep",		tFlt,   GETTER,         NPCSTEP,        1,	P0			  },
		{ "setStep",		tVoid,  SETTER,         NPCSTEP,        1,      P1(	tFlt		) },
		{ "getASpeed",          tFlt,   GETTER,         NPCFRAMERATE,   1,	P0			  },
		{ "setASpeed",          tVoid,  SETTER,         NPCFRAMERATE,   1,      P1(	tFlt		) },
		{ "getHaltrate",        tFlt,   GETTER,         NPCHALTRATE,    1,	P0			  },
		{ "setHaltrate",        tVoid,  SETTER,         NPCHALTRATE,    1,      P1(	tFlt		) },
		{ "getDrawStyle",       tFlt,   GETTER,         NPCDRAWTYPE,    1,	P0			  },
		{ "setDrawStyle",       tVoid,  SETTER,         NPCDRAWTYPE,    1,      P1(	tFlt		) },
		{ "getHP",              tFlt,   GETTER,         NPCHP,          1,	P0			  },
		{ "setHP",              tVoid,  SETTER,         NPCHP,          1,      P1(	tFlt		) },
		{ "getID",              tFlt,   GETTER,         NPCID,          1,	P0			  },
		{ "setID",              tVoid,  SETTER,         NPCID,          1,      P1(	tFlt		) },
		{ "getType",            tFlt,   GETTER,         NPCTYPE,        1,	P0			  },
		{ "setType",            tVoid,  SETTER,         NPCTYPE,        1,      P1(	tFlt		) },
		{ "getDamage",          tFlt,   GETTER,         NPCDP,          1,	P0			  },
		{ "setDamage",          tVoid,  SETTER,         NPCDP,          1,      P1(	tFlt		) },
		{ "getWeaponDamage",    tFlt,   GETTER,         NPCWDP,         1,	P0			  },
		{ "setWeaponDamage",    tVoid,  SETTER,         NPCWDP,         1,      P1(	tFlt		) },
		{ "getTile",            tFlt,   GETTER,         NPCTILE,        1,	P0			  },
		{ "setTile",            tVoid,  SETTER,         NPCTILE,        1,      P1(	tFlt		) },
		{ "getOriginalTile",    tFlt,   GETTER,         NPCOTILE,       1,	P0			  },
		{ "setOriginalTile",    tVoid,  SETTER,         NPCOTILE,       1,      P1(	tFlt		) },
		{ "getWeapon",          tFlt,   GETTER,         NPCWEAPON,      1,	P0			  },
		{ "setWeapon",          tVoid,  SETTER,         NPCWEAPON,      1,      P1(	tFlt		) },
		{ "getItemSet",         tFlt,   GETTER,         NPCITEMSET,     1,	P0			  },
		{ "setItemSet",         tVoid,  SETTER,         NPCITEMSET,     1,      P1(	tFlt		) },
		{ "getCSet",            tFlt,   GETTER,         NPCCSET,        1,	P0			  },
		{ "setCSet",            tVoid,  SETTER,         NPCCSET,        1,      P1(	tFlt		) },
		{ "getBossPal",         tFlt,   GETTER,         NPCBOSSPAL,     1,	P0			  },
		{ "setBossPal",         tVoid,  SETTER,         NPCBOSSPAL,     1,      P1(	tFlt		) },
		{ "getSFX",             tFlt,   GETTER,         NPCBGSFX,       1,	P0			  },
		{ "setSFX",             tVoid,  SETTER,         NPCBGSFX,       1,      P1(	tFlt		) },
		{ "getExtend",          tFlt,   GETTER,         NPCEXTEND,      1,	P0			  },
		{ "setExtend",          tVoid,  SETTER,         NPCEXTEND,      1,      P1(	tFlt		) },
		{ "getHitWidth",        tFlt,   GETTER,         NPCHXSZ,        1,	P0			  },
		{ "setHitWidth",        tVoid,  SETTER,         NPCHXSZ,        1,      P1(	tFlt		) },
		{ "getHitHeight",       tFlt,   GETTER,         NPCHYSZ,        1,	P0			  },
		{ "setHitHeight",       tVoid,  SETTER,         NPCHYSZ,        1,      P1(	tFlt		) },
		{ "getHitZHeight",      tFlt,   GETTER,         NPCHZSZ,        1,	P0			  },
		{ "setHitZHeight",      tVoid,  SETTER,         NPCHZSZ,        1,      P1(	tFlt		) },
		{ "getTileWidth",       tFlt,   GETTER,         NPCTXSZ,        1,	P0			  },
		{ "setTileWidth",       tVoid,  SETTER,         NPCTXSZ,        1,      P1(	tFlt		) },
		{ "getTileHeight",      tFlt,   GETTER,         NPCTYSZ,        1,	P0			  },
		{ "setTileHeight",      tVoid,  SETTER,         NPCTYSZ,        1,      P1(	tFlt		) },
		{ "getDrawXOffset",     tFlt,   GETTER,         NPCXOFS,        1,	P0			  },
		{ "setDrawXOffset",     tVoid,  SETTER,         NPCXOFS,        1,      P1(	tFlt		) },
		{ "getDrawYOffset",     tFlt,   GETTER,         NPCYOFS,        1,	P0			  },
		{ "setDrawYOffset",     tVoid,  SETTER,         NPCYOFS,        1,      P1(	tFlt		) },
		{ "getDrawZOffset",     tFlt,   GETTER,         NPCZOFS,        1,	P0			  },
		{ "setDrawZOffset",     tVoid,  SETTER,         NPCZOFS,        1,      P1(	tFlt		) },
		{ "getHitXOffset",      tFlt,   GETTER,         NPCHXOFS,       1,	P0			  },
		{ "setHitXOffset",      tVoid,  SETTER,         NPCHXOFS,       1,      P1(	tFlt		) },
		{ "getHitYOffset",      tFlt,   GETTER,         NPCHYOFS,       1,	P0			  },
		{ "setHitYOffset",      tVoid,  SETTER,         NPCHYOFS,       1,      P1(	tFlt		) },
		{ "isValid",		tBool,  FUNCTION,       0,              1,	P0			  },
		{ "getMisc[]",          tAny,   GETTER,         NPCMISCD,       32,     P1(	tFlt		) },
		{ "setMisc[]",          tVoid,  SETTER,         NPCMISCD,       32,     P2(	tFlt,	tAny	) },
		{ "getAttributes[]",    tFlt,   GETTER,         NPCDD,          14,     P1(	tFlt		) },
		{ "setAttributes[]",    tVoid,  SETTER,         NPCDD,          14,     P2(	tFlt,	tFlt	) },
		{ "getMiscFlags",       tFlt,   GETTER,         NPCMFLAGS,      1,	P0			  },
		{ "setMiscFlags",       tVoid,  SETTER,         NPCMFLAGS,      1,      P1(	tFlt		) },
		{ "getCollDetection", 	tBool,  GETTER,         NPCCOLLDET,     1,	P0			  },
		{ "setCollDetection",   tVoid,  SETTER,         NPCCOLLDET,     1,      P1(	tBool		) },
		{ "getStun",            tFlt,   GETTER,         NPCSTUN,        1,	P0			  },
		{ "setStun",            tVoid,  SETTER,         NPCSTUN,        1,      P1(	tFlt		) },
		{ "getCore",            tBool,  GETTER,         NPCISCORE,      1,	P0			  },
		{ "setCore",            tVoid,  SETTER,         NPCISCORE,      1,      P1(	tBool		) },
		{ "getDefense[]",       tFlt,   GETTER,         NPCDEFENSED,    42,     P1(	tFlt		) },
		{ "setDefense[]",       tVoid,  SETTER,         NPCDEFENSED,    42,     P2(	tFlt,	tFlt	) },
		{ "getHitBy[]",         tFlt,   GETTER,         NPCHITBY,       4,      P1(	tFlt		) },
		{ "setHitBy[]",         tVoid,  SETTER,         NPCHITBY,       4,      P2(	tFlt,	tFlt	) },
		{ "GetName",            tVoid,  FUNCTION,       0,              1,      P1(	tFlt		) },
		{ "getHunger",          tFlt,   GETTER,         NPCHUNGER,      1,	P0			  },
		{ "setHunger",          tVoid,  SETTER,         NPCHUNGER,      1,      P1(	tFlt		) },
		{ "BreakShield",        tVoid,  FUNCTION,       0,              1,	P0			  },
		{ "getWeaponSprite",    tFlt,   GETTER,         NPCWEAPSPRITE,  1,	P0			  },
		{ "setWeaponSprite",    tVoid,  SETTER,         NPCWEAPSPRITE,  1,      P1(	tFlt		) },
		{ "getScriptDefense[]", tFlt,   GETTER,         NPCSCRDEFENSED, 10,     P1(	tFlt		) },
		{ "setScriptDefense[]", tVoid,  SETTER,         NPCSCRDEFENSED, 10,     P2(	tFlt,	tFlt	) },
		{ "getInvFrames",       tFlt,   GETTER,         NPCINVINC,      1,	P0			  },
		{ "setInvFrames",       tVoid,  SETTER,         NPCINVINC,      1,      P1(	tFlt		) },
		{ "getInvincible",      tFlt,   GETTER,         NPCSUPERMAN,    1,	P0			  },
		{ "setInvincible",      tVoid,  SETTER,         NPCSUPERMAN,    1,      P1(	tFlt		) },
		{ "getRingleader",      tBool,  GETTER,         NPCRINGLEAD,    1,	P0			  },
		{ "setRingleader",      tVoid,  SETTER,         NPCRINGLEAD,    1,      P1(	tBool		) },
		{ "getHasItem",         tBool,  GETTER,         NPCHASITEM,     1,	P0			  },
		{ "setHasItem",         tVoid,  SETTER,         NPCHASITEM,     1,      P1(	tBool		) },
		{ "getShield[]",        tBool,  GETTER,         NPCSHIELD,      5,      P1(	tFlt		) },
		{ "setShield[]",        tVoid,  SETTER,         NPCSHIELD,      5,      P2(	tFlt,	tBool	) },
		{ "getFrozen",          tFlt,   GETTER,         NPCFROZEN,      1,	P0			  },
		{ "setFrozen",          tVoid,  SETTER,         NPCFROZEN,      1,      P1(	tFlt		) },
		{ "getUID",             tFlt,   GETTER,         NPCSCRIPTUID,   1,	P0			  },
	//	{ "setUID",             tVoid,  SETTER,         NPCSCRIPTUID,   1,      P1(	tFlt		) },
		{ "getFrozenTile",      tFlt,   GETTER,         NPCFROZENTILE,  1,	P0			  },
		{ "setFrozenTile",      tVoid,  SETTER,         NPCFROZENTILE,  1,      P1(	tFlt		) },
		{ "getFrozenCSet",      tFlt,   GETTER,         NPCFROZENCSET,  1,	P0			  },
		{ "setFrozenCSet",      tVoid,  SETTER,         NPCFROZENCSET,  1,      P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Npc& Library::Npc::instance()
{
	static Library::Npc instance(REFNPC, table);
	return instance;
}

void Library::Npc::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
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
		code.push_back(new OIsValidNPC(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void GetName(float)
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
		code.push_back(new OGetNPCName(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void BreakShield()
	{
		int id = memberids["BreakShield"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the pointer
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//Break shield
		code.push_back(new OBreakShield(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
