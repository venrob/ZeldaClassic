#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_EWPN
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	  name,                 rettype,        setorget,	var,			num     params
		{ "getX",               tFlt,		GETTER,		EWPNX,			1,    	P0			  },
		{ "setX",               tVoid,          SETTER,		EWPNX,			1,      P1(	tFlt		) },
		{ "getY",               tFlt,		GETTER,		EWPNY,			1,      P0			  },
		{ "setY",               tVoid,          SETTER,		EWPNY,			1,      P1(	tFlt		) },
		{ "getZ",               tFlt,		GETTER,		EWPNZ,			1,      P0			  },
		{ "setZ",               tVoid,          SETTER,		EWPNZ,			1,      P1(	tFlt		) },
		{ "getJump",            tFlt,		GETTER,		EWPNJUMP,		1,      P0			  },
		{ "setJump",            tVoid,          SETTER,		EWPNJUMP,		1,      P1(	tFlt		) },
		{ "getDir",             tFlt,		GETTER,		EWPNDIR,		1,      P0			  },
		{ "setDir",             tVoid,          SETTER,		EWPNDIR,		1,      P1(	tFlt		) },
		{ "getAngle",           tFlt,		GETTER,		EWPNANGLE,		1,      P0			  },
		{ "setAngle",           tVoid,          SETTER,		EWPNANGLE,		1,      P1(	tFlt		) },
		{ "getStep",		tFlt,		GETTER,		EWPNSTEP,		1,      P0			  },
		{ "setStep",		tVoid,		SETTER,		EWPNSTEP,		1,      P1(	tFlt		) },
		{ "getNumFrames",       tFlt,		GETTER,		EWPNFRAMES,		1,      P0			  },
		{ "setNumFrames",       tVoid,          SETTER,		EWPNFRAMES,		1,      P1(	tFlt		) },
		{ "getFrame",           tFlt,		GETTER,		EWPNFRAME,		1,      P0			  },
		{ "setFrame",           tVoid,          SETTER,		EWPNFRAME,		1,      P1(	tFlt		) },
		{ "getDrawStyle",       tFlt,		GETTER,		EWPNDRAWTYPE,		1,      P0			  },
		{ "setDrawStyle",       tVoid,          SETTER,		EWPNDRAWTYPE,		1,      P1(	tFlt		) },
		{ "getDamage",          tFlt,		GETTER,		EWPNPOWER,		1,      P0			  },
		{ "setDamage",          tVoid,          SETTER,		EWPNPOWER,		1,      P1(	tFlt		) },
		{ "getID",              tFlt,		GETTER,		EWPNID,			1,      P0			  },
		{ "setID",              tVoid,          SETTER,		EWPNID,			1,      P1(	tFlt		) },
		{ "getAngular",         tBool,          GETTER,		EWPNANGULAR,		1,      P0			  },
		{ "setAngular",         tVoid,          SETTER,		EWPNANGULAR,		1,      P1(	tBool		) },
		{ "getBehind",          tBool,          GETTER,		EWPNBEHIND,		1,      P0			  },
		{ "setBehind",          tVoid,          SETTER,		EWPNBEHIND,		1,      P1(	tBool		) },
		{ "getASpeed",          tFlt,		GETTER,		EWPNASPEED,		1,      P0			  },
		{ "setASpeed",          tVoid,          SETTER,		EWPNASPEED,		1,      P1(	tFlt		) },
		{ "getTile",            tFlt,		GETTER,		EWPNTILE,		1,      P0			  },
		{ "setTile",            tVoid,          SETTER,		EWPNTILE,		1,      P1(	tFlt		) },
		{ "getFlashCSet",       tFlt,		GETTER,		EWPNFLASHCSET,		1,      P0			  },
		{ "setFlashCSet",       tVoid,          SETTER,		EWPNFLASHCSET,		1,      P1(	tFlt		) },
		{ "getDeadState",       tFlt,		GETTER,		EWPNDEAD,		1,      P0			  },
		{ "setDeadState",       tVoid,          SETTER,		EWPNDEAD,		1,      P1(	tFlt		) },
		{ "getCSet",            tFlt,		GETTER,		EWPNCSET,		1,      P0			  },
		{ "setCSet",            tVoid,          SETTER,		EWPNCSET,		1,      P1(	tFlt		) },
		{ "getFlash",           tBool,          GETTER,		EWPNFLASH,		1,      P0			  },
		{ "setFlash",           tVoid,          SETTER,		EWPNFLASH,		1,      P1(	tBool		) },
		{ "getFlip",            tFlt,		GETTER,		EWPNFLIP,		1,      P0			  },
		{ "setFlip",            tVoid,          SETTER,		EWPNFLIP,		1,      P1(	tFlt		) },
		{ "getOriginalTile",    tFlt,		GETTER,		EWPNOTILE,		1,      P0			  },
		{ "setOriginalTile",    tVoid,          SETTER,		EWPNOTILE,		1,      P1(	tFlt		) },
		{ "getOriginalCSet",    tFlt,		GETTER,		EWPNOCSET,		1,      P0			  },
		{ "setOriginalCSet",	tVoid,          SETTER,		EWPNOCSET,		1,      P1(	tFlt		) },
		{ "getExtend",          tFlt,		GETTER,		EWPNEXTEND,		1,      P0			  },
		{ "setExtend",          tVoid,          SETTER,		EWPNEXTEND,		1,      P1(	tFlt		) },
		{ "getHitWidth",        tFlt,		GETTER,		EWPNHXSZ,		1,      P0			  },
		{ "setHitWidth",        tVoid,          SETTER,		EWPNHXSZ,		1,      P1(	tFlt		) },
		{ "getHitHeight",       tFlt,		GETTER,		EWPNHYSZ,		1,      P0			  },
		{ "setHitHeight",       tVoid,          SETTER,		EWPNHYSZ,		1,      P1(	tFlt		) },
		{ "getHitZHeight",      tFlt,		GETTER,		EWPNHZSZ,		1,      P0			  },
		{ "setHitZHeight",      tVoid,          SETTER,		EWPNHZSZ,		1,      P1(	tFlt		) },
		{ "getTileWidth",       tFlt,		GETTER,		EWPNTXSZ,		1,      P0			  },
		{ "setTileWidth",       tVoid,          SETTER,		EWPNTXSZ,		1,      P1(	tFlt		) },
		{ "getTileHeight",      tFlt,		GETTER,		EWPNTYSZ,		1,      P0			  },
		{ "setTileHeight",      tVoid,          SETTER,		EWPNTYSZ,		1,      P1(	tFlt		) },
		{ "getDrawXOffset",     tFlt,		GETTER,		EWPNXOFS,		1,      P0			  },
		{ "setDrawXOffset",     tVoid,          SETTER,		EWPNXOFS,		1,      P1(	tFlt		) },
		{ "getDrawYOffset",     tFlt,		GETTER,		EWPNYOFS,		1,      P0			  },
		{ "setDrawYOffset",     tVoid,          SETTER,		EWPNYOFS,		1,      P1(	tFlt		) },
		{ "getDrawZOffset",     tFlt,		GETTER,		EWPNZOFS,		1,      P0			  },
		{ "setDrawZOffset",     tVoid,          SETTER,		EWPNZOFS,		1,      P1(	tFlt		) },
		{ "getHitXOffset",      tFlt,		GETTER,		EWPNHXOFS,		1,      P0			  },
		{ "setHitXOffset",      tVoid,          SETTER,		EWPNHXOFS,		1,      P1(	tFlt		) },
		{ "getHitYOffset",      tFlt,		GETTER,		EWPNHYOFS,		1,      P0			  },
		{ "setHitYOffset",      tVoid,          SETTER,		EWPNHYOFS,		1,      P1(	tFlt		) },
		{ "getParent",          tFlt,		GETTER,		EWPNPARENT,		1,      P0			  },
		{ "setParent",          tVoid,          SETTER,		EWPNPARENT,		1,      P1(	tFlt		) },
		{ "isValid",		tBool,          FUNCTION,	0,			1,      P0			  },
		{ "UseSprite",          tVoid,          FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "getMisc[]",          tAny,		GETTER,		EWPNMISCD,		32,     P1(	tFlt		) },
		{ "setMisc[]",          tVoid,          SETTER,		EWPNMISCD,		32,     P2(	tFlt,	tAny	) },
		{ "getCollDetection", 	tFlt,		GETTER,		EWPNCOLLDET,		1,      P0			  },
		{ "setCollDetection", 	tVoid,          SETTER,		EWPNCOLLDET,		1,      P1(	tBool		) },
		{ "getUID",		tFlt,		GETTER,		EWEAPONSCRIPTUID,       1,      P0			  },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::EnemyWeapon& Library::EnemyWeapon::instance()
{
	static Library::EnemyWeapon instance(REFEWPN, table);
	return instance;
}

void Library::EnemyWeapon::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
	int id = -1;
	
	// bool isValid()
	{
		id = memberids["isValid"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the pointer
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//Check validity
		code.push_back(new OIsValidEWpn(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void UseSprite(float)
	{
		id = memberids["UseSprite"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the val
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop off the pointer
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(refVar), new VarArgument(EXP2)));
		code.push_back(new OUseSpriteEWpn(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
