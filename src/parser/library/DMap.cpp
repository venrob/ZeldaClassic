#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_DMAPDATA
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	name,				rettype,	type,		var,			num,	params
		{ "GetName",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "SetName",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "GetTitle",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "SetTitle",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "GetIntro",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "SetIntro",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "GetMusic",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "SetMusic",			tVoid,		FUNCTION,	0,			1,	P1(	tFlt		) },
		{ "getMap",			tFlt,		GETTER,		DMAPDATAMAP,		1,	P0			  },
		{ "setMap",			tVoid,		SETTER,		DMAPDATAMAP,		1,	P1(	tFlt		) },
		{ "getLevel",			tFlt,		GETTER,		DMAPDATALEVEL,		1,	P0			  },
		{ "setLevel",			tVoid,		SETTER,		DMAPDATALEVEL,		1,	P1(	tFlt		) },
		{ "getOffset",			tFlt,		GETTER,		DMAPDATAOFFSET,		1,	P0			  },
		{ "setOffset",			tVoid,		SETTER,		DMAPDATAOFFSET,		1,	P1(	tFlt		) },
		{ "getCompass",			tFlt,		GETTER,		DMAPDATACOMPASS,	1,	P0			  },
		{ "setCompass",			tVoid,		SETTER,		DMAPDATACOMPASS,	1,	P1(	tFlt		) },
		{ "getPalette",			tFlt,		GETTER,		DMAPDATAPALETTE,	1,	P0			  },
		{ "setPalette",			tVoid,		SETTER,		DMAPDATAPALETTE,	1,	P1(	tFlt		) },
		{ "getMIDI",			tFlt,		GETTER,		DMAPDATAMIDI,		1,	P0			  },
		{ "setMIDI",			tVoid,		SETTER,		DMAPDATAMIDI,		1,	P1(	tFlt		) },
		{ "getContinue",		tFlt,		GETTER,		DMAPDATACONTINUE,	1,	P0			  },
		{ "setContinue",		tVoid,		SETTER,		DMAPDATACONTINUE,	1,	P1(	tFlt		) },
		{ "getType",			tFlt,		GETTER,		DMAPDATATYPE,		1,	P0			  },
		{ "setType",			tVoid,		SETTER,		DMAPDATATYPE,		1,	P1(	tFlt		) },
		{ "getMusicTrack",		tFlt,		GETTER,		DMAPDATAMUISCTRACK,	1,	P0			  },
		{ "setMusicTrack",		tVoid,		SETTER,		DMAPDATAMUISCTRACK,	1,	P1(	tFlt		) },
		{ "getActiveSubscreen",		tFlt,		GETTER,		DMAPDATASUBSCRA,	1,	P0			  },
		{ "setActiveSubscreen",		tVoid,		SETTER,		DMAPDATASUBSCRA,	1,	P1(	tFlt		) },
		{ "getPassiveSubscreen",	tFlt,		GETTER,		DMAPDATASUBSCRP,	1,	P0			  },
		{ "setPassiveSubscreen",	tVoid,		SETTER,		DMAPDATASUBSCRP,	1,	P1(	tFlt		) },
	//	{ "getGravity[]",		tFlt,		GETTER,		DMAPDATASUBSCRP,	1,	P0			  },
	//	{ "setGravity[]",		tVoid,		SETTER,		DMAPDATASUBSCRP,	1,	P1(	tFlt		) },
	//	{ "getJumpThreshold",		tFlt,		GETTER,		DMAPDATASUBSCRP,	1,	P0			  },
	//	{ "setJumpThreshold",		tVoid,		SETTER,		DMAPDATASUBSCRP,	1,	P1(	tFlt		) },
		{ "getGrid[]",			tFlt,		GETTER,		DMAPDATAGRID,		8,	P1(	tFlt		) },
		{ "setGrid[]",			tVoid,		SETTER,		DMAPDATAGRID,		8,	P2(	tFlt,	tFlt	) },
		{ "getMiniMapTile[]",		tFlt,		GETTER,		DMAPDATAMINIMAPTILE,	2,	P1(	tFlt		) },
		{ "setMiniMapTile[]",		tVoid,		SETTER,		DMAPDATAMINIMAPTILE,	2,	P2(	tFlt,	tFlt	) },
		{ "getMiniMapCSet[]",		tFlt,		GETTER,		DMAPDATAMINIMAPCSET,	2,	P1(	tFlt		) },
		{ "setMiniMapCSet[]",		tVoid,		SETTER,		DMAPDATAMINIMAPCSET,	2,	P2(	tFlt,	tFlt	) },
		{ "getMapTile[]",		tFlt,		GETTER,		DMAPDATALARGEMAPTILE,	2,	P1(	tFlt		) },
		{ "setMapTile[]",		tVoid,		SETTER,		DMAPDATALARGEMAPTILE,	2,	P2(	tFlt,	tFlt	) },
		{ "getMapCSet[]",		tFlt,		GETTER,		DMAPDATALARGEMAPCSET,	2,	P1(	tFlt		) },
		{ "setMapCSet[]",		tVoid,		SETTER,		DMAPDATALARGEMAPCSET,	2,	P2(	tFlt,	tFlt	) },
		{ "getDisabledItems[]",		tFlt,		GETTER,		DMAPDATADISABLEDITEMS,	256,	P1(	tFlt		) },
		{ "setDisabledItems[]",		tVoid,		SETTER,		DMAPDATADISABLEDITEMS,	256,	P2(	tFlt,	tFlt	) },
		{ "getFlags",			tFlt,		GETTER,		DMAPDATAFLAGS,		1,	P0			  },
		{ "setFlags",			tVoid,		SETTER,		DMAPDATAFLAGS,		1,	P1(	tFlt		) },
		{ "getSideview",		tBool,		GETTER,		DMAPDATAFLAGS,		1,	P0			  },
		{ "setSideview",		tVoid,		SETTER,		DMAPDATAFLAGS,		1,	P1(	tBool		) },
		ENTRY_END
	};

#	include "EntryHelperUnload.h"
}

Library::DMap& Library::DMap::instance()
{
	static Library::DMap instance(REFDMAPDATA, table);
	return instance;
}

void Library::DMap::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;

	// void GetName(float output_string)
	{
		int id = memberids["GetName"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataGetNameRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void SetName(float string)	
	{
		int id = memberids["SetName"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataSetNameRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void GetTitle(float output_string)
	{	
		int id = memberids["GetTitle"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataGetTitleRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void SetTitle(float string)
	{	
		int id = memberids["SetTitle"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataSetTitleRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void GetIntro(float output_string)
	{	
		int id = memberids["GetIntro"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataGetIntroRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void SetIntro(float string)
	{	
		int id = memberids["SetIntro"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataSetIntroRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void GetMusic(float output_string)
	{	
		int id = memberids["GetMusic"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataGetMusicRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}

	// void SetMusic(float string)
	{	
		int id = memberids["SetMusic"]; 
		int label = lt.functionToLabel(id); 
		vector<Opcode *> code; 
		Opcode *first = new OPopRegister(new VarArgument(EXP2)); 
		first->setLabel(label); 
		code.push_back(first); 
		code.push_back(new ODMapDataSetMusicRegister(new VarArgument(EXP2))); 
		code.push_back(new OPopRegister(new VarArgument(EXP2))); 
		code.push_back(new OGotoRegister(new VarArgument(EXP2))); 
		rval[label]=code; 
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
