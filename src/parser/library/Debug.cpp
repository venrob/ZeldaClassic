#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_DEBUG
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	   name,                rettype,        type,		var,			num,	 params
                // All of these return a function label error when used:
	//	{ "getRefFFC",          tFlt,		GETTER,		DEBUGREFFFC,            1,      P0			  },
	//	{ "getRefItem",         tFlt,		GETTER,		DEBUGREFITEM,           1,      P0			  },
	//	{ "getRefItemdata",     tFlt,		GETTER,		DEBUGREFITEMDATA,       1,      P0			  },
	//	{ "getRefNPC",          tFlt,		GETTER,		DEBUGREFNPC,            1,      P0			  },
	//	{ "getRefLWeapon",      tFlt,		GETTER,		DEBUGREFLWEAPON,        1,      P0			  },
	//	{ "getRefEWeapon",      tFlt,		GETTER,		DEBUGREFEWEAPON,        1,      P0			  },
	//	{ "getSP",              tFlt,		GETTER,		DEBUGSP,		1,      P0			  },
	//	{ "setRefFFC",          tFlt,		SETTER,		DEBUGREFFFC,            1,      P0			  },
	//	{ "setRefItem",         tFlt,		SETTER,		DEBUGREFITEM,           1,      P0			  },
	//	{ "setRefItemdata",     tFlt,		SETTER,		DEBUGREFITEMDATA,       1,      P0			  },
	//	{ "setRefNPC",          tFlt,		SETTER,		DEBUGREFNPC,            1,      P0			  },
	//	{ "setRefLWeapon",      tFlt,		SETTER,		DEBUGREFLWEAPON,        1,      P0			  },
	//	{ "setRefEWeapon",      tFlt,		SETTER,		DEBUGREFEWEAPON,        1,      P0			  },
	//	{ "setSP",              tFlt,		SETTER,		DEBUGSP,		1,      P0			  },
	//	{ "getGDR[]",           tFlt,		GETTER,		DEBUGGDR,		256,    P1(	tFlt		) },
	//	{ "setGDR[]",           tVoid,          SETTER,		DEBUGGDR,		256,    P2(	tFlt,	tFlt	) },
													                            
		// These all work, but may not be permitted by the rest of the dev team. 		                            
		// At least they are now in a pointer class that denotes that they can be dangerous. 	                            
		{ "GetBoolPointer",     tFlt,		FUNCTION,	0,			1,      P1(	tBool		) },
		{ "SetBoolPointer",     tBool,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetNPCPointer",      tFlt,		FUNCTION,	0,			1,      P1(	tNpc		) },
		{ "SetNPCPointer",      tNpc,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetLWeaponPointer",  tFlt,		FUNCTION,	0,			1,      P1(	tLW		) },
		{ "SetLWeaponPointer",  tLW,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetEWeaponPointer",  tFlt,		FUNCTION,	0,			1,      P1(	tEW		) },
		{ "SetEWeaponPointer",  tEW,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetFFCPointer",      tFlt,		FUNCTION,	0,			1,      P1(	tFfc		) },
		{ "SetFFCPointer",      tFfc,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetItemPointer",     tFlt,		FUNCTION,	0,			1,      P1(	tItm		) },
		{ "SetItemPointer",     tItm,		FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "GetItemdataPointer", tFlt,		FUNCTION,	0,			1,      P1(	tItmC		) },
		{ "SetItemdataPointer", tItmC,		FUNCTION,	0,			1,      P1(	tFlt		) },
													                            
                // Changing the subscreen and screen offsets seems to do nothing. 			                            
		{ "getSubscreenOffset", tFlt,		GETTER,		PASSSUBOFS,		1,      P0			  },
		{ "setSubscreenOffset", tVoid,          SETTER,		PASSSUBOFS,		1,      P1(	tFlt		) },
		{ "getSubscreenHeight", tFlt,		GETTER,		GAMESUBSCHEIGHT,        1,      P0			  },
		{ "setSubscreenHeight", tVoid,          SETTER,		GAMESUBSCHEIGHT,        1,      P1(	tFlt		) },
		{ "getPlayfieldOffset", tFlt,		GETTER,		GAMEPLAYFIELDOFS,       1,      P0			  },
		{ "setPlayfieldOffset", tVoid,          SETTER,		GAMEPLAYFIELDOFS,       1,      P1(	tFlt		) },
		{ "TriggerSecret",      tVoid,          FUNCTION,	0,			1,      P1(	tFlt		) },
		{ "ChangeFFCScript",    tVoid,          FUNCTION,       0,                      1,      P1(	tFlt		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::Debug& Library::Debug::instance()
{
	static Library::Debug instance(NUL, table);
	return instance;
}

void Library::Debug::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
	
	//int GetPointer(itemclass, itemclass)
	{
		int id = memberids["GetItemdataPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetItemDataPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(itemclass, float)
	{
		int id = memberids["SetItemdataPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetItemDataPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(item, item)
	{
		int id = memberids["GetItemPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetItemPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(item, float)
	{
		int id = memberids["SetItemPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetItemPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(ffc, ffc)
	{
		int id = memberids["GetFFCPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetFFCPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(ffc, float)
	{
		int id = memberids["SetFFCPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetFFCPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(eweapon, eweapon)
	{
		int id = memberids["GetEWeaponPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetEWeaponPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(eweapon, float)
	{
		int id = memberids["SetEWeaponPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetEWeaponPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(lweapon, lweapon)
	{
		int id = memberids["GetLWeaponPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetLWeaponPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(lweapon, float)
	{
		int id = memberids["SetLWeaponPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetLWeaponPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(npc, ffc)
	{
		int id = memberids["GetNPCPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetNPCPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(npc, float)
	{
		int id = memberids["SetNPCPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetNPCPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//int GetPointer(game, bool)
	{
		int id = memberids["GetBoolPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OGetBoolPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	//int SetPointer(game, float)
	{
		int id = memberids["SetBoolPointer"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetBoolPointer(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
    
	// void TriggerSecret(float)
	{
		int id = memberids["TriggerSecret"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OTriggerSecretRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void ChangeFFCScript(float)
	{
		int id = memberids["ChangeFFCScript"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		//pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OChangeFFCScriptRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
