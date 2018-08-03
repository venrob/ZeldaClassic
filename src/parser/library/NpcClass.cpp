#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_NPCDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
		// name,                rettype,        type,		var,			num,	params
		{ "getTile",		tFlt,		GETTER,		NPCDATATILE,		1,	P0				  },
		{ "setTile",		tVoid,		SETTER,		NPCDATATILE,		1,	P1(	tFlt			) },
		{ "getFlags",		tFlt,		GETTER,		NPCDATAFLAGS,		1,	P0				  },
		{ "setFlags",		tVoid,		SETTER,		NPCDATAFLAGS,		1,	P1(	tFlt			) },
		{ "getFlags2",		tFlt,		GETTER,		NPCDATAFLAGS2,		1,	P0				  },
		{ "setFlags2",		tVoid,		SETTER,		NPCDATAFLAGS2,		1,	P1(	tFlt			) },
		{ "getWidth",		tFlt,		GETTER,		NPCDATAWIDTH,		1,	P0				  },
		{ "setWidth",		tVoid,		SETTER,		NPCDATAWIDTH,		1,	P1(	tFlt			) },
		{ "getHeight",		tFlt,		GETTER,		NPCDATAHEIGHT,		1,	P0				  },
		{ "setHeight",		tVoid,		SETTER,		NPCDATAHEIGHT,		1,	P1(	tFlt			) },
		{ "getSTile",		tFlt,		GETTER,		NPCDATASTILE,		1,	P0				  },
		{ "setSTile",		tVoid,		SETTER,		NPCDATASTILE,		1,	P1(	tFlt			) },
		{ "getSWidth",		tFlt,		GETTER,		NPCDATASWIDTH,		1,	P0				  },
		{ "setSWidth",		tVoid,		SETTER,		NPCDATASWIDTH,		1,	P1(	tFlt			) },
		{ "getSHeight",		tFlt,		GETTER,		NPCDATASHEIGHT,		1,	P0				  },
		{ "setSHeight",		tVoid,		SETTER,		NPCDATASHEIGHT,		1,	P1(	tFlt			) },
		{ "getExTile",		tFlt,		GETTER,		NPCDATAETILE,		1,	P0				  },
		{ "setExTile",		tVoid,		SETTER,		NPCDATAETILE,		1,	P1(	tFlt			) },
		{ "getExWidth",		tFlt,		GETTER,		NPCDATAEWIDTH,		1,	P0				  },
		{ "setExWidth",		tVoid,		SETTER,		NPCDATAEWIDTH,		1,	P1(	tFlt			) },
		{ "getExHeight",	tFlt,		GETTER,		NPCDATAEHEIGHT,		1,	P0				  },
		{ "setExHeight",	tVoid,		SETTER,		NPCDATAEHEIGHT,		1,	P1(	tFlt			) },
		{ "getHP",		tFlt,		GETTER,		NPCDATAHP,		1,	P0				  },
		{ "setHP",		tVoid,		SETTER,		NPCDATAHP,		1,	P1(	tFlt			) },
		{ "getFamily",		tFlt,		GETTER,		NPCDATAFAMILY,		1,	P0				  },
		{ "setFamily",		tVoid,		SETTER,		NPCDATAFAMILY,		1,	P1(	tFlt			) },
		{ "getCSet",		tFlt,		GETTER,		NPCDATACSET,		1,	P0				  },
		{ "setCSet",		tVoid,		SETTER,		NPCDATACSET,		1,	P1(	tFlt			) },
		{ "getAnim",		tFlt,		GETTER,		NPCDATAANIM,		1,	P0				  },
		{ "setAnim",		tVoid,		SETTER,		NPCDATAANIM,		1,	P1(	tFlt			) },
		{ "getExAnim",		tFlt,		GETTER,		NPCDATAEANIM,		1,	P0				  },
		{ "setExAnim",		tVoid,		SETTER,		NPCDATAEANIM,		1,	P1(	tFlt			) },
		{ "getFramerate",	tFlt,		GETTER,		NPCDATAFRAMERATE,	1,	P0				  },
		{ "setFramerate",	tVoid,		SETTER,		NPCDATAFRAMERATE,	1,	P1(	tFlt			) },
		{ "getExFramerate",	tFlt,		GETTER,		NPCDATAEFRAMERATE,	1,	P0				  },
		{ "setExFramerate",	tVoid,		SETTER,		NPCDATAEFRAMERATE,	1,	P1(	tFlt			) },
		{ "getTouchDamage",	tFlt,		GETTER,		NPCDATATOUCHDAMAGE,	1,	P0				  },
		{ "setTouchDamage",	tVoid,		SETTER,		NPCDATATOUCHDAMAGE,	1,	P1(	tFlt			) },
		{ "getWeaponDamage",	tFlt,		GETTER,		NPCDATAWEAPONDAMAGE,	1,	P0				  },
		{ "setWeaponDamage",	tVoid,		SETTER,		NPCDATAWEAPONDAMAGE,	1,	P1(	tFlt			) },
		{ "getWeapon",		tFlt,		GETTER,		NPCDATAWEAPON,		1,	P0				  },
		{ "setWeapon",		tVoid,		SETTER,		NPCDATAWEAPON,		1,	P1(	tFlt			) },
		{ "getRandom",		tFlt,		GETTER,		NPCDATARANDOM,		1,	P0				  },
		{ "setRandom",		tVoid,		SETTER,		NPCDATARANDOM,		1,	P1(	tFlt			) },
		{ "getHaltrate",	tFlt,		GETTER,		NPCDATAHALT,		1,	P0				  },
		{ "setHaltrate",	tVoid,		SETTER,		NPCDATAHALT,		1,	P1(	tFlt			) },
		{ "getStep",		tFlt,		GETTER,		NPCDATASTEP,		1,	P0				  },
		{ "setStep",		tVoid,		SETTER,		NPCDATASTEP,		1,	P1(	tFlt			) },
		{ "getHoming",		tFlt,		GETTER,		NPCDATAHOMING,		1,	P0				  },
		{ "setHoming",		tVoid,		SETTER,		NPCDATAHOMING,		1,	P1(	tFlt			) },
		{ "getHunger",		tFlt,		GETTER,		NPCDATAHUNGER,		1,	P0				  },
		{ "setHunger",		tVoid,		SETTER,		NPCDATAHUNGER,		1,	P1(	tFlt			) },
		{ "getDropset",		tFlt,		GETTER,		NPCDATADROPSET,		1,	P0				  },
		{ "setDropset",		tVoid,		SETTER,		NPCDATADROPSET,		1,	P1(	tFlt			) },
		{ "getBGSFX",		tFlt,		GETTER,		NPCDATABGSFX,		1,	P0				  },
		{ "setBGSFX",		tVoid,		SETTER,		NPCDATABGSFX,		1,	P1(	tFlt			) },
		{ "getDeathSFX",	tFlt,		GETTER,		NPCDATADEATHSFX,	1,	P0				  },
		{ "setDeathSFX",	tVoid,		SETTER,		NPCDATADEATHSFX,	1,	P1(	tFlt			) },
		{ "getHitSFX",		tFlt,		GETTER,		NPCDATAHITSFX,		1,	P0				  },
		{ "setHitSFX",		tVoid,		SETTER,		NPCDATAHITSFX,		1,	P1(	tFlt			) },
	//	{ "getFireSFX",		tFlt,		GETTER,		SPRITEDATATYPE,		1,	P0				  },
	//	{ "setFireSFX",		tVoid,		SETTER,		SPRITEDATATYPE,		1,	P1(	tFlt			) },
		{ "getDrawXOffset",	tFlt,		GETTER,		NPCDATAXOFS,		1,	P0				  },
		{ "setDrawXOffset",	tVoid,		SETTER,		NPCDATAXOFS,		1,	P1(	tFlt			) },
		{ "getDrawYOffset",	tFlt,		GETTER,		NPCDATAYOFS,		1,	P0				  },
		{ "setDrawYOffset",	tVoid,		SETTER,		NPCDATAYOFS,		1,	P1(	tFlt			) },
		{ "getDrawZOffset",	tFlt,		GETTER,		NPCDATAZOFS,		1,	P0				  },
		{ "setDrawZOffset",	tVoid,		SETTER,		NPCDATAZOFS,		1,	P1(	tFlt			) },
		{ "getHitXOffset",	tFlt,		GETTER,		NPCDATAHXOFS,		1,	P0				  },
		{ "setHitXOffset",	tVoid,		SETTER,		NPCDATAHXOFS,		1,	P1(	tFlt			) },
		{ "getHitYOffset",	tFlt,		GETTER,		NPCDATAHYOFS,		1,	P0				  },
		{ "setHitYOffset",	tVoid,		SETTER,		NPCDATAHYOFS,		1,	P1(	tFlt			) },
		{ "getHitWidth",	tFlt,		GETTER,		NPCDATAHITWIDTH,	1,	P0				  },
		{ "setHitWidth",	tVoid,		SETTER,		NPCDATAHITWIDTH,	1,	P1(	tFlt			) },
		{ "getHitHeight",	tFlt,		GETTER,		NPCDATAHITHEIGHT,	1,	P0				  },
		{ "setHitHeight",	tVoid,		SETTER,		NPCDATAHITHEIGHT,	1,	P1(	tFlt			) },
		{ "getHitZHeight",	tFlt,		GETTER,		NPCDATAHITZ,		1,	P0				  },
		{ "setHitZHeight",	tVoid,		SETTER,		NPCDATAHITZ,		1,	P1(	tFlt			) },
		{ "getTileWidth",	tFlt,		GETTER,		NPCDATATILEWIDTH,	1,	P0				  },
		{ "setTileWidth",	tVoid,		SETTER,		NPCDATATILEWIDTH,	1,	P1(	tFlt			) },
		{ "getTileHeight",	tFlt,		GETTER,		NPCDATATILEHEIGHT,	1,	P0				  },
		{ "setTileHeight",	tVoid,		SETTER,		NPCDATATILEHEIGHT,	1,	P1(	tFlt			) },
		{ "getWeaponSprite",	tFlt,		GETTER,		NPCDATAWPNSPRITE,	1,	P0				  },
		{ "setWeaponSprite",	tVoid,		SETTER,		NPCDATAWPNSPRITE,	1,	P1(	tFlt			) },
		{ "getDefense[]",	tFlt,		GETTER,		NPCDATADEFENSE,		42,	P1(	tFlt			) },
		{ "setDefense[]",	tVoid,		SETTER,		NPCDATADEFENSE,		42,	P2(	tFlt,	tFlt		) },
		{ "getSizeFlag[]",	tBool,		GETTER,		NPCDATASIZEFLAG,	2,	P2(	tFlt,	tFfc		) },
		{ "setSizeFlag[]",	tVoid,		SETTER,		NPCDATASIZEFLAG,	2,	P3(	tBool,	tFlt,	tFfc	) },
		{ "getAttributes[]",	tFlt,		GETTER,		NPCDATAATTRIBUTE,	15,	P1(	tFlt			) },
		{ "setAttributes[]",	tVoid,		SETTER,		NPCDATAATTRIBUTE,	15,	P2(	tFlt,	tFlt		) },
		{ "getShield[]",	tBool,		GETTER,		NPCDATASHIELD,		5,	P1(	tFlt			) },
		{ "setShield[]",	tVoid,		SETTER,		NPCDATASHIELD,		5,	P2(	tBool,	tFlt		) },
		{ "getFrozenTile",	tFlt,		GETTER,		NPCDATAFROZENTILE,	1,	P0				  },
		{ "setFrozenTile",	tVoid,		SETTER,		NPCDATAFROZENTILE,	1,	P1(	tFlt			) },
		{ "getFrozenCSet",	tFlt,		GETTER,		NPCDATAFROZENCSET,	1,	P0				  },
		{ "setFrozenCSet",	tVoid,		SETTER,		NPCDATAFROZENCSET,	1,	P1(	tFlt			) },
		{ "GetTile",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetEHeight",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetFlags",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetFlags2",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetWidth",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHeight",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetSTile",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetSWidth",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetSHeight",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetETile",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetEWidth",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHP",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetFamily",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetCSet",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetAnim",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetEAnim",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetFramerate",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetEFramerate",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetTouchDamage",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetWeaponDamage",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetWeapon",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetRandom",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHaltRate",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetStep",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHoming",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHunger",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetDropset",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetBGSFX",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitSFX",		tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetDeathSFX",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetDrawXOffset",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetDrawYOffset",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetDrawZOffset",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitXOffset",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitYOffset",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitWidth",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitHeight",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetHitZHeight",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetTileWidth",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetTileHeight",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetWeaponSprite",	tFlt,		FUNCTION,	0,			1,	P1(	tFlt			) },
		{ "GetScriptDefense",	tFlt,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "GetDefense",		tFlt,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "GetSizeFlag",	tBool,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "GetAttribute",	tFlt,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetTile",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetEHeight",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetFlags",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetFlags2",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetWidth",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHeight",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetSTile",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetSWidth",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetSHeight",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetETile",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetEWidth",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHP",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetFamily",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetCSet",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetAnim",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetEAnim",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetFramerate",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetEFramerate",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetTouchDamage",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetWeaponDamage",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetWeapon",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetRandom",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHaltRate",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetStep",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHoming",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHunger",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetDropset",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetBGSFX",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitSFX",		tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetDeathSFX",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetDrawXOffset",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetDrawYOffset",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetDrawZOffset",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitXOffset",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitYOffset",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitWidth",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitHeight",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetHitZHeight",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetTileWidth",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetTileHeight",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetWeaponSprite",	tVoid,		FUNCTION,	0,			1,	P2(	tFlt,	tFlt		) },
		{ "SetScriptDefense",	tVoid,		FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt	) },
		{ "SetDefense",		tVoid,		FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt	) },
		{ "SetSizeFlag",	tVoid,		FUNCTION,	0,			1,	P3(	tBool,	tFlt,	tFlt	) },
		{ "SetAttribute",	tVoid,		FUNCTION,	0,			1,	P3(	tFlt,	tFlt,	tFlt	) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::NpcClass& Library::NpcClass::instance()
{
	static Library::NpcClass instance(REFNPCCLASS, table);
	return instance;
}

//Guydata member with one input, one return
#define GET_GUYDATA_MEMBER(flabel, ffins) \
{ \
	int id = memberids[flabel];\
	int label = lt.functionToLabel(id); \
        vector<Opcode *> code; \
        Opcode *first = new OPopRegister(new VarArgument(EXP2)); \
        first->setLabel(label); \
        code.push_back(first); \
        code.push_back(new OPopRegister(new VarArgument(NUL))); \
        code.push_back(new ffins(new VarArgument(EXP1),new VarArgument(EXP2))); \
        code.push_back(new OPopRegister(new VarArgument(EXP2))); \
        code.push_back(new OGotoRegister(new VarArgument(EXP2))); \
        rval[label] = code; \
}

void Library::NpcClass::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// float GetTile(float)
	{
		int id = memberids["GetTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataBaseTile(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
		//GET_GUYDATA_MEMBER("Tile", ONDataBaseTile);
	}
	
	// float GetEHeight(float)
	GET_GUYDATA_MEMBER("GetEHeight", ONDataEHeight);
    
	// float GetFlags(float)
	GET_GUYDATA_MEMBER("GetFlags", ONDataFlags);

	// float GetFlags2(float)
	{
		int id = memberids["GetFlags2"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataFlags2(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetWidth(float)
	GET_GUYDATA_MEMBER("GetWidth", ONDataWidth);
	
	// float GetHeight(float)
	GET_GUYDATA_MEMBER("GetHeight", ONDataHeight);

	// float GetSTile(float)
	GET_GUYDATA_MEMBER("GetSTile", ONDataTile);

	// float GetSWidth(float)
	GET_GUYDATA_MEMBER("GetSWidth", ONDataTile);

	// float GetSHeight(float)
	{
		int id = memberids["GetSHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataSHeight(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetETile(float)
	{
		int id = memberids["GetETile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataETile(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetEWidth(float)
	{
		int id = memberids["GetEWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataEWidth(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHP(float)
	{
		int id = memberids["GetHP"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHP(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetFamily(float)
	{
		int id = memberids["GetFamily"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataFamily(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetCSet(float)
	{
		int id = memberids["GetCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataCSet(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetAnim(float)
	{
		int id = memberids["GetAnim"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataAnim(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetEAnim(float)
	{
		int id = memberids["GetEAnim"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataEAnim(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetFramerate(float)
	{
		int id = memberids["GetFramerate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataFramerate(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetEFramerate(float)
	{
		int id = memberids["GetEFramerate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataEFramerate(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetTouchDamage(float)
	{
		int id = memberids["GetTouchDamage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataTouchDamage(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetWeaponDamage(float)
	{
		int id = memberids["GetWeaponDamage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataWeaponDamage(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetWeapon(float)
	{
		int id = memberids["GetWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataWeapon(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetRandom(float)
	{
		int id = memberids["GetRandom"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataRandom(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHaltRate(float)
	{
		int id = memberids["GetHaltRate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHalt(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetStep(float)
	{
		int id = memberids["GetStep"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataStep(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHoming(float)
	{
		int id = memberids["GetHoming"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHoming(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHunger(float)
	{
		int id = memberids["GetHunger"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHunger(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetDropset(float)
	{
		int id = memberids["GetDropset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataropset(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetBGSFX(float)
	{
		int id = memberids["GetBGSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataBGSound(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetHitSFX(float)
	{
		int id = memberids["GetHitSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHitSound(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetDeathSFX(float)
	{
		int id = memberids["GetDeathSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL))); 
		code.push_back(new ONDataDeathSound(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}

	// float GetDrawXOffset(float)
	{
		int id = memberids["GetDrawXOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataXofs(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetDrawYOffset(float)
	{
		int id = memberids["GetDrawYOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataYofs(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetDrawZOffset(float)
	{
		int id = memberids["GetDrawZOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataZofs(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHitXOffset(float)
	{
		int id = memberids["GetHitXOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHitXOfs(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHitYOffset(float)
	{
		int id = memberids["GetHitYOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHYOfs(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHitWidth(float)
	{
		int id = memberids["GetHitWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHitWidth(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHitHeight(float)
	{
		int id = memberids["GetHitHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHitHeight(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetHitZHeight(float)
	{
		int id = memberids["GetHitZHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataHitZ(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetTileWidth(float)
	{
		int id = memberids["GetTileWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataTileWidth(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetTileHeight(float)
	{
		int id = memberids["GetTileHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataTileHeight(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetWeaponSprite(float)
	{
		int id = memberids["GetWeaponSprite"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataWeapSprite(new VarArgument(EXP1),new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetScriptDefense(float, float)
	{
		int id = memberids["GetScriptDefense"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataScriptDef(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetDefense(float, float)
	{
		int id = memberids["GetDefense"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataDefense(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetSizeFlag(float, float)
	{
		int id = memberids["GetSizeFlag"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDataSizeFlag(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// float GetAttribute(float, float)
	{
		int id = memberids["GetAttribute"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(INDEX2));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new ONDatattributes(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetTile(float, float)
	{
		int id = memberids["SetTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetBaseTile(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetEHeight(float, float)
	{
		int id = memberids["SetEHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetEHeight(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetFlags(float, float)
	{
		int id = memberids["SetFlags"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetFlags(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetFlags2(float, float)
	{
		int id = memberids["SetFlags2"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetFlags2(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetWidth(float, float)
	{
		int id = memberids["SetWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetWidth(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHeight(float, float)
	{
		int id = memberids["SetHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHeight(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSTile(float, float)
	{
		int id = memberids["SetSTile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetTile(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSWidth(float, float)
	{
		int id = memberids["SetSWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetSWidth(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetSHeight(float, float)
	{
		int id = memberids["SetSHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetSHeight(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetETile(float, float)
	{
		int id = memberids["SetETile"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetETile(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetEWidth(float, float)
	{
		int id = memberids["SetEWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetEWidth(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHP(float, float)
	{
		int id = memberids["SetHP"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHP(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetFamily(float, float)
	{
		int id = memberids["SetFamily"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetFamily(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetCSet(float, float)
	{
		int id = memberids["SetCSet"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetCSet(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetAnim(float, float)
	{
		int id = memberids["SetAnim"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetAnim(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetEAnim(float, float)
	{
		int id = memberids["SetEAnim"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetEAnim(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetFramerate(float, float)
	{
		int id = memberids["SetFramerate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetFramerate(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetEFramerate(float, float)
	{
		int id = memberids["SetEFramerate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetEFramerate(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetTouchDamage(float, float)
	{
		int id = memberids["SetTouchDamage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetTouchDamage(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetWeaponDamage(float, float)
	{
		int id = memberids["SetWeaponDamage"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetWeaponDamage(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetWeapon(float, float)
	{
		int id = memberids["SetWeapon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetWeapon(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetRandom(float, float)
	{
		int id = memberids["SetRandom"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetRandom(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHaltRate(float, float)
	{
		int id = memberids["SetHaltRate"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHalt(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetStep(float, float)
	{
		int id = memberids["SetStep"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetStep(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHoming(float, float)
	{
		int id = memberids["SetHoming"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHoming(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHunger(float, float)
	{
		int id = memberids["SetHunger"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHunger(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDropset(float, float)
	{
		int id = memberids["SetDropset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetropset(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetBGSFX(float, float)
	{
		int id = memberids["SetBGSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetBGSound(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitSFX(float, float)
	{
		int id = memberids["SetHitSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHitSound(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDeathSFX(float, float)
	{
		int id = memberids["SetDeathSFX"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetDeathSound(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDrawXOffset(float, float)
	{
		int id = memberids["SetDrawXOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetXofs(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDrawYOffset(float, float)
	{
		int id = memberids["SetDrawYOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetYofs(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetDrawZOffset(float, float)
	{
		int id = memberids["SetDrawZOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetZofs(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitXOffset(float, float)
	{
		int id = memberids["SetHitXOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHitXOfs(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitYOffset(float, float)
	{
		int id = memberids["SetHitYOffset"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHYOfs(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitWidth(float, float)
	{
		int id = memberids["SetHitWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHitWidth(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitHeight(float, float)
	{
		int id = memberids["SetHitHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHitHeight(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetHitZHeight(float, float)
	{
		int id = memberids["SetHitZHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetHitZ(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetTileWidth(float, float)
	{
		int id = memberids["SetTileWidth"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetTileWidth(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetTileHeight(float, float)
	{
		int id = memberids["SetTileHeight"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetTileHeight(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetWeaponSprite(float, float)
	{
		int id = memberids["SetWeaponSprite"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(SFTEMP)));
		code.push_back(new ONDataSetWeapSprite(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void SetScriptDefense(float, float, float)
	{
		int id = memberids["SetScriptDefense"];
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
		code.push_back(new OSetRegister(new VarArgument(SETNPCDATASCRIPTDEF), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetDefense(float, float, float)
	{
		int id = memberids["SetDefense"];
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
		code.push_back(new OSetRegister(new VarArgument(SETNPCDATADEFENSE), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetSizeFlag(bool, float, float)
	{
		int id = memberids["SetSizeFlag"];
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
		code.push_back(new OSetRegister(new VarArgument(SETNPCDATASIZEFLAG), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void SetAttribute(float, float, float)
	{
		int id = memberids["SetAttribute"];
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
		code.push_back(new OSetRegister(new VarArgument(SETNPCDATAATTRIBUTE), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

#undef GET_GUYDATA_MEMBER

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
