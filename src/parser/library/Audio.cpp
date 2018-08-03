#include "../../precompiled.h" // always first
#include "../Library.h"
#include "../ByteCode.h"
#include "../Compiler.h"

namespace // file local
{
#	define tSelf ScriptParser::TYPE_AUDIO 
#	include "EntryHelper.h"

	using Library::GETTER;
	using Library::SETTER;
	using Library::FUNCTION;

	Library::Entry table[] =
	{
	//	  name,			rettype,type,		var,		num,    params
		{ "PlaySound",		tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "EndSound",		tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "PauseSound",		tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "ResumeSound",	tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "ContinueSound",	tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "AdjustMusicVolume",	tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "AdjustSFXVolume",	tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "AdjustSound",	tVoid,	FUNCTION,	0,		1,	P3(	tBool,	tFlt,	tFlt	) },
		{ "PauseCurMIDI",	tVoid,	FUNCTION,	0,		1,	P0				  },
		{ "ResumeCurMIDI",	tVoid,	FUNCTION,	0,		1,	P0				  },
		{ "PlayMIDI",		tVoid,	FUNCTION,	0,		1,	P1(	tFlt			) },
		{ "PlayEnhancedMusic",	tBool,	FUNCTION,	0,		1,	P2(	tFlt,	tFlt		) },
		{ "getVolume[]",	tFlt,	GETTER,		AUDIOVOLUME,	4,	P1(	tFlt			) },
		{ "setVolume[]",	tVoid,	SETTER,		AUDIOVOLUME,	4,	P2(	tFlt,	tFlt		) },
		{ "getPanStyle",	tFlt,	GETTER,		AUDIOPAN,	1,	P0				  },
		{ "setPanStyle",	tVoid,	SETTER,		AUDIOPAN,	1,	P1(	tFlt			) },
		ENTRY_END
	};
	
#	include "EntryHelperUnload.h"
}

Library::Audio& Library::Audio::instance()
{
	static Library::Audio instance(NUL, table);
	return instance;
}

void Library::Audio::generateFunctionCode(
		LinkTable* linktable,
		std::map<int, std::vector<Opcode*> >& rval)
{
	LinkTable& lt = *linktable;
	    
	// void PlaySound(float)
	{
		int id = memberids["PlaySound"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPlaySoundRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void EndSound(float)
	{
		int id = memberids["EndSound"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OEndSoundRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void PauseSound(float)
	{
		int id = memberids["PauseSound"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
                code.push_back(new OPauseSoundRegister(new VarArgument(EXP1)));
                code.push_back(new OPopRegister(new VarArgument(EXP2)));
                code.push_back(new OGotoRegister(new VarArgument(EXP2)));
                rval[label] = code;
        }
    
        // void ResumeSound(float)
        {
                int id = memberids["ResumeSound"];
                int label = lt.functionToLabel(id);
                vector<Opcode *> code;
                // pop off the param
                Opcode *first = new OPopRegister(new VarArgument(EXP1));
                first->setLabel(label);
                code.push_back(first);
                // pop pointer, and ignore it
                code.push_back(new OPopRegister(new VarArgument(NUL)));
                code.push_back(new OResumeSoundRegister(new VarArgument(EXP1)));
                code.push_back(new OPopRegister(new VarArgument(EXP2)));
                code.push_back(new OGotoRegister(new VarArgument(EXP2)));
                rval[label] = code;
        }
    
        // void ContinueSound(float)
        {
                int id = memberids["ContinueSound"];
                int label = lt.functionToLabel(id);
                vector<Opcode *> code;
                // pop off the param
                Opcode *first = new OPopRegister(new VarArgument(EXP1));
                first->setLabel(label);
                code.push_back(first);
                // pop pointer, and ignore it
                code.push_back(new OPopRegister(new VarArgument(NUL)));
                code.push_back(new OContinueSFX(new VarArgument(EXP1)));
                code.push_back(new OPopRegister(new VarArgument(EXP2)));
                code.push_back(new OGotoRegister(new VarArgument(EXP2)));
                rval[label] = code;
        }
    
	// void AdjustMusicVolume(float)
	{
		int id = memberids["AdjustMusicVolume"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OAdjustVolumeRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
	// void AdjustSFXVolume(float)
	{
		int id = memberids["AdjustSFXVolume"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the param
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OAdjustSFXVolumeRegister(new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
    
	// void AdjustSound(float, float, bool)
	{
		int id = memberids["AdjustSound"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(INDEX2)));
		code.push_back(new OPopRegister(new VarArgument(INDEX)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OSetRegister(new VarArgument(ADJUSTSFX), new VarArgument(SFTEMP)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
	
        // void PauseCurMIDI()
        {
                int id = memberids["PauseCurMIDI"];
                int label = lt.functionToLabel(id);
                vector<Opcode *> code;
                // pop pointer, and ignore it
                Opcode *first = new OPopRegister(new VarArgument(NUL));
                first->setLabel(label);
                code.push_back(first);
                code.push_back(new OPauseMusic());
                code.push_back(new OPopRegister(new VarArgument(EXP2)));
                code.push_back(new OGotoRegister(new VarArgument(EXP2)));
                rval[label]=code;
        }
    
        // void ResumeCurMIDI()
        {
                int id = memberids["ResumeCurMIDI"];
                int label = lt.functionToLabel(id);
                vector<Opcode *> code;
                // pop pointer, and ignore it
                Opcode *first = new OPopRegister(new VarArgument(NUL));
                first->setLabel(label);
                code.push_back(first);
                code.push_back(new OResumeMusic());
                code.push_back(new OPopRegister(new VarArgument(EXP2)));
                code.push_back(new OGotoRegister(new VarArgument(EXP2)));
                rval[label]=code;
        }

        // void PlayMIDI(float)
        {
                int id = memberids["PlayMIDI"];
                int label = lt.functionToLabel(id);
                vector<Opcode *> code;
                // pop off the param
                Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// pop pointer, and ignore it
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
		// pop off the params
		Opcode *first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		// pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));
		code.push_back(new OPlayEnhancedMusic(new VarArgument(EXP2), new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label] = code;
	}
}

// Emacs Config:
// Local Variables:
// tab-width: 8
// End:
