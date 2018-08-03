#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_LWPN
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;
	
	Library::Entry table[] =
	{
	//	name,                   rettype,        type,		var,			num,    params
		{ "getX",               tFlt,		GETTER,		LWPNX,			1,      P0			  },
		{ "setX",               tVoid,          SETTER,		LWPNX,			1,      P1(	tFlt		) },
		{ "getY",               tFlt,		GETTER,		LWPNY,			1,      P0			  },
		{ "setY",               tVoid,          SETTER,		LWPNY,			1,      P1(	tFlt		) },
		{ "getZ",               tFlt,		GETTER,		LWPNZ,			1,      P0			  },
		{ "setZ",               tVoid,          SETTER,		LWPNZ,			1,      P1(	tFlt		) },
		{ "getJump",            tFlt,		GETTER,		LWPNJUMP,		1,      P0			  },
		{ "setJump",            tVoid,          SETTER,		LWPNJUMP,		1,      P1(	tFlt		) },
		{ "getDir",             tFlt,		GETTER,		LWPNDIR,		1,      P0			  },
		{ "setDir",             tVoid,          SETTER,		LWPNDIR,		1,      P1(	tFlt		) },
		{ "getAngle",           tFlt,		GETTER,		LWPNANGLE,		1,      P0			  },
		{ "setAngle",           tVoid,          SETTER,		LWPNANGLE,		1,      P1(	tFlt		) },
		{ "getStep",		tFlt,	        GETTER,		LWPNSTEP,		1,	P0			  },
		{ "setStep",		tVoid,		SETTER,		LWPNSTEP,		1,	P1(	tFlt		) },
		{ "getNumFrames",       tFlt,		GETTER,		LWPNFRAMES,		1,      P0			  },
		{ "setNumFrames",       tVoid,          SETTER,		LWPNFRAMES,		1,      P1(	tFlt		) },
		{ "getFrame",           tFlt,		GETTER,		LWPNFRAME,		1,      P0			  },
		{ "setFrame",           tVoid,          SETTER,		LWPNFRAME,		1,      P1(	tFlt		) },
		{ "getDrawStyle",       tFlt,		GETTER,		LWPNDRAWTYPE,		1,      P0			  },
		{ "setDrawStyle",       tVoid,          SETTER,		LWPNDRAWTYPE,		1,      P1(	tFlt		) },
		{ "getDamage",          tFlt,		GETTER,		LWPNPOWER,		1,      P0			  },
		{ "setDamage",          tVoid,          SETTER,		LWPNPOWER,		1,      P1(	tFlt		) },
		{ "getID",              tFlt,		GETTER,		LWPNID,			1,      P0			  },
		{ "setID",              tVoid,          SETTER,		LWPNID,			1,      P1(	tFlt		) },
		{ "getAngular",         tBool,          GETTER,		LWPNANGULAR,		1,      P0			  },
		{ "setAngular",         tVoid,          SETTER,		LWPNANGULAR,		1,      P1(	tBool		) },
		{ "getBehind",          tBool,          GETTER,		LWPNBEHIND,		1,      P0			  },
		{ "setBehind",          tVoid,          SETTER,		LWPNBEHIND,		1,      P1(	tBool		) },
		{ "getASpeed",          tFlt,		GETTER,		LWPNASPEED,		1,      P0			  },
		{ "setASpeed",          tVoid,          SETTER,		LWPNASPEED,		1,      P1(	tFlt		) },
		{ "getTile",            tFlt,		GETTER,		LWPNTILE,		1,      P0			  },
		{ "setTile",            tVoid,          SETTER,		LWPNTILE,		1,      P1(	tFlt		) },
		{ "getFlashCSet",       tFlt,		GETTER,		LWPNFLASHCSET,		1,      P0			  },
		{ "setFlashCSet",       tVoid,          SETTER,		LWPNFLASHCSET,		1,      P1(	tFlt		) },
		{ "getDeadState",       tFlt,		GETTER,		LWPNDEAD,		1,      P0			  },
		{ "setDeadState",       tVoid,          SETTER,		LWPNDEAD,		1,      P1(	tFlt		) },
		{ "getCSet",            tFlt,		GETTER,		LWPNCSET,		1,      P0			  },
		{ "setCSet",            tVoid,          SETTER,		LWPNCSET,		1,      P1(	tFlt		) },
		{ "getFlash",           tBool,          GETTER,		LWPNFLASH,		1,      P0			  },
		{ "setFlash",           tVoid,          SETTER,		LWPNFLASH,		1,      P1(	tBool		) },
		{ "getFlip",            tFlt,		GETTER,		LWPNFLIP,		1,      P0			  },
		{ "setFlip",            tVoid,          SETTER,		LWPNFLIP,		1,      P1(	tFlt		) },
		{ "getOriginalTile",    tFlt,		GETTER,		LWPNOTILE,		1,      P0			  },
		{ "setOriginalTile",    tVoid,          SETTER,		LWPNOTILE,		1,      P1(	tFlt		) },
		{ "getOriginalCSet",    tFlt,		GETTER,		LWPNOCSET,		1,      P0			  },
		{ "setOriginalCSet",	tVoid,          SETTER,		LWPNOCSET,		1,      P1(	tFlt		) },
		{ "getExtend",          tFlt,		GETTER,		LWPNEXTEND,		1,      P0			  },
		{ "setExtend",          tVoid,          SETTER,		LWPNEXTEND,		1,      P1(	tFlt		) },
		{ "getHitWidth",        tFlt,		GETTER,		LWPNHXSZ,		1,      P0			  },
		{ "setHitWidth",        tVoid,          SETTER,		LWPNHXSZ,		1,      P1(	tFlt		) },
		{ "getHitHeight",       tFlt,		GETTER,		LWPNHYSZ,		1,      P0			  },
		{ "setHitHeight",       tVoid,          SETTER,		LWPNHYSZ,		1,      P1(	tFlt		) },
		{ "getHitZHeight",      tFlt,		GETTER,		LWPNHZSZ,		1,      P0			  },
		{ "setHitZHeight",      tVoid,          SETTER,		LWPNHZSZ,		1,      P1(	tFlt		) },
		{ "getTileWidth",       tFlt,		GETTER,		LWPNTXSZ,		1,      P0			  },
		{ "setTileWidth",       tVoid,          SETTER,		LWPNTXSZ,		1,      P1(	tFlt		) },
		{ "getTileHeight",      tFlt,		GETTER,		LWPNTYSZ,		1,      P0			  },
		{ "setTileHeight",      tVoid,          SETTER,		LWPNTYSZ,		1,      P1(	tFlt		) },
		{ "getDrawXOffset",     tFlt,		GETTER,		LWPNXOFS,		1,      P0			  },
		{ "setDrawXOffset",     tVoid,          SETTER,		LWPNXOFS,		1,      P1(	tFlt		) },
		{ "getDrawYOffset",     tFlt,		GETTER,		LWPNYOFS,		1,      P0			  },
		{ "setDrawYOffset",     tVoid,          SETTER,		LWPNYOFS,		1,      P1(	tFlt		) },
		{ "getDrawZOffset",     tFlt,		GETTER,		LWPNZOFS,		1,      P0			  },
		{ "setDrawZOffset",     tVoid,          SETTER,		LWPNZOFS,		1,      P1(	tFlt		) },
		{ "getHitXOffset",      tFlt,		GETTER,		LWPNHXOFS,		1,      P0			  },
		{ "setHitXOffset",      tVoid,          SETTER,		LWPNHXOFS,		1,      P1(	tFlt		) },
		{ "getHitYOffset",      tFlt,		GETTER,		LWPNHYOFS,		1,      P0			  },
		{ "setHitYOffset",      tVoid,          SETTER,		LWPNHYOFS,		1,      P1(	tFlt		) },
		{ "isValid",		tBool,          FUNCTION,	0,			1,      P0			  },
		{ "UseSprite",          tVoid,          FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "getMisc[]",          tAny,		GETTER,		LWPNMISCD,		32,     P1(	tFlt		) },
		{ "setMisc[]",          tVoid,          SETTER,		LWPNMISCD,		32,     P2(	tFlt,	tAny	) },
		{ "getCollDetection", 	tBool,		GETTER,		LWPNCOLLDET,		1,      P0			  },
		{ "setCollDetection", 	tVoid,          SETTER,		LWPNCOLLDET,		1,      P1(	tBool		) },
	//	{ "getRange",		tFlt,		GETTER,		LWPNRANGE,		1,      P0			  },
	//	{ "setRange",		tVoid,          SETTER,		LWPNRANGE,		1,      P1(	tFlt		) },
		{ "getParent",          tFlt,		GETTER,		LWPNPARENT,		1,      P0			  },
		{ "setParent",          tVoid,          SETTER,		LWPNPARENT,		1,      P1(	tFlt		) },
		{ "getLevel",		tFlt,		GETTER,		LWPNLEVEL,		1,      P0			  },
		{ "setLevel",		tVoid,          SETTER,		LWPNLEVEL,		1,      P1(	tFlt		) },
		{ "getUID",		tFlt,		GETTER,		LWEAPONSCRIPTUID,       1,      P0			  },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::LinkWeapon& Library::LinkWeapon::instance()
{
	static Library::LinkWeapon instance(REFLWPN, table);
	return instance;
}

void Library::LinkWeapon::generateFunctionCode(
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
		code.push_back(new OIsValidLWpn(new VarArgument(EXP1)));
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
		code.push_back(new OUseSpriteLWpn(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
