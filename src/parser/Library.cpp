#include "../precompiled.h" // always first
#include "Library.h"

#include "ByteCode.h"
#include "DataStructs.h"

using std::string;
using std::map;
using std::vector;
using std::pair;

void Library::Base::writeSymbols(Scope* scope, SymbolTable* t)
{
    // waste an ID, OH WELL
    memberids.clear();
    firstid = ScriptParser::getUniqueFuncID()+1;
    int id = firstid;
    
    for (int i = 0; entries[i].name != ""; ++i, ++id)
    {
        vector<int> param;
        
        for (int k = 0; entries[i].params[k] != -1 && k < 20; ++k)
            param.push_back(entries[i].params[k]);
            
        string name = entries[i].name;
        scope->getFuncSymbols().addFunction(name, entries[i].rettype, param);
        t->putFunc(id, entries[i].rettype);
        t->putFuncDecl(id, param);
        memberids[name] = id;
    }
}

namespace // file local
{
	vector<Opcode*> getVariable(
			LinkTable& lt, int id, int var, int refVar)
	{
		int label = lt.functionToLabel(id);
		vector<Opcode*> code;
		// Pop object pointer
		Opcode* first = new OPopRegister(new VarArgument(EXP2));
		first->setLabel(label);
		code.push_back(first);
		// Load object pointer into ref register
		if (refVar != NUL)
			code.push_back(new OSetRegister(new VarArgument(refVar),
			                                new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(EXP1),
		                                new VarArgument(var)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		return code;
	}

	vector<Opcode*> getIndexedVariable(
			LinkTable& lt, int id, int var, int refVar)
	{
		int label = lt.functionToLabel(id);
		vector<Opcode*> code;
		// Pop index
		Opcode* first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		// Pop object pointer
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		// Load object pointer into ref register
		if (refVar != NUL)
			code.push_back(new OSetRegister(new VarArgument(refVar),
			                                new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(EXP1),
		                                new VarArgument(var)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		return code;
	}

	vector<Opcode*> setVariable(
			LinkTable& lt, int id, int var, int refVar)
	{
		int label = lt.functionToLabel(id);
		vector<Opcode*> code;
		// Pop off the value to set to
		Opcode* first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// Pop object pointer
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		// Load object pointer into ref register
		if (refVar != NUL)
			code.push_back(new OSetRegister(new VarArgument(refVar),
			                                new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(var),
		                                new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		return code;
	}

	vector<Opcode *> setBoolVariable(
			LinkTable& lt, int id, int var, int refVar)
	{
		int label = lt.functionToLabel(id);
		vector<Opcode*> code;
		// Pop off the value to set to
		Opcode* first = new OPopRegister(new VarArgument(EXP1));
		first->setLabel(label);
		code.push_back(first);
		// Renormalize true to 1
		int donerenorm = ScriptParser::getUniqueLabelID();
		code.push_back(new OCompareImmediate(new VarArgument(EXP1),
		                                     new LiteralArgument(0)));
		code.push_back(new OGotoTrueImmediate(new LabelArgument(donerenorm)));
		code.push_back(new OSetImmediate(new VarArgument(EXP1),
		                                 new LiteralArgument(10000)));
    
		// Pop object pointer
		Opcode* next = new OPopRegister(new VarArgument(EXP2));
		next->setLabel(donerenorm);
		code.push_back(next);
		// Load object pointer into ref register
		if (refVar != NUL)
			code.push_back(new OSetRegister(new VarArgument(refVar),
			                                new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(var),
		                                new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		return code;
	}

	vector<Opcode*> setIndexedVariable(
			LinkTable& lt, int id, int var, int refVar)
	{
		int label = lt.functionToLabel(id);
		vector<Opcode*> code;
		// Pop off index
		Opcode* first = new OPopRegister(new VarArgument(INDEX));
		first->setLabel(label);
		code.push_back(first);
		// Pop off the value to set to
		code.push_back(new OPopRegister(new VarArgument(EXP1)));
		// Pop object pointer
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		// Load object pointer into ref register
		if (refVar != NUL)
			code.push_back(new OSetRegister(new VarArgument(refVar),
			                                new VarArgument(EXP2)));
		code.push_back(new OSetRegister(new VarArgument(var),
		                                new VarArgument(EXP1)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		return code;
	}
}

void Library::Base::writeCode(LinkTable* lt, map<int, vector<Opcode*> >& target)
{
    for (int i = 0; entries[i].name != ""; ++i)
    {
	    int var = entries[i].var;
        int id = memberids[entries[i].name];
        bool isIndexed = entries[i].numindex > 1;
        int label = lt->functionToLabel(id);
        
        switch (entries[i].type)
        {
        case Library::GETTER:
	        if (isIndexed)
		        target[label] = getIndexedVariable(*lt, id, var, refVar);
            else
	            target[label] = getVariable(*lt, id, var, refVar);
            break;
            
        case Library::SETTER:
            if (isIndexed)
	            target[label] = setIndexedVariable(*lt, id, var, refVar);
            else
            {
                if (entries[i].params[1] == ScriptParser::TYPE_BOOL)
	                target[label] = setBoolVariable(*lt, id, var, refVar);
                else
	                target[label] = setVariable(*lt, id, var, refVar);
            }
            break;
        }
    }

    generateFunctionCode(lt, target);
}

pair<int, vector<int> > Library::Base::matchFunction(
		string const& name, SymbolTable *t)
{
    pair<int,vector<int> > rval;
    int id = -1;

    map<string, int>::iterator it = memberids.find(name);
    if (it != memberids.end())
        id = it->second;
        
    if (id == -1)
    {
        rval.first = -1;
        return rval;
    }
    
    // Else we're good
    rval.first = id;
    rval.second = t->getFuncParams(id);
    return rval;
}

namespace // file local
{
	map<int, Library::Base*>& typeMap()
	{
		static bool initialized = false;
		static map<int, Library::Base*> types;
		if (!initialized)
		{
			types[ScriptParser::TYPE_AUDIO] = &Library::Audio::instance();
			types[ScriptParser::TYPE_CHEATS] = &Library::Cheat::instance();
			types[ScriptParser::TYPE_COMBOS] = &Library::Combo::instance();
			types[ScriptParser::TYPE_DEBUG] = &Library::Debug::instance();
			types[ScriptParser::TYPE_DOORSET] = &Library::DoorSet::instance();
			types[ScriptParser::TYPE_DROPSET] = &Library::DropSet::instance();
			types[ScriptParser::TYPE_DMAPDATA] = &Library::DMap::instance();
			types[ScriptParser::TYPE_EWPN] = &Library::EnemyWeapon::instance();
			types[ScriptParser::TYPE_FFC] = &Library::Ffc::instance();
			types[ScriptParser::TYPE_GAME] = &Library::Game::instance();
			types[ScriptParser::TYPE_GAMEDATA] = &Library::GameData::instance();
			types[ScriptParser::TYPE_GRAPHICS] = &Library::Graphics::instance();
			types[ScriptParser::TYPE_INPUT] = &Library::Input::instance();
			types[ScriptParser::TYPE_ITEM] = &Library::Item::instance();
			types[ScriptParser::TYPE_ITEMCLASS] = &Library::ItemClass::instance();
			types[ScriptParser::TYPE_LINK] = &Library::Link::instance();
			types[ScriptParser::TYPE_LWPN] = &Library::LinkWeapon::instance();
			types[ScriptParser::TYPE_MAPDATA] = &Library::Map::instance();
			types[ScriptParser::TYPE_ZMESSAGE] = &Library::Message::instance();
			types[ScriptParser::TYPE_ZUICOLOURS] = &Library::MiscColor::instance();
			types[ScriptParser::TYPE_NPC] = &Library::Npc::instance();
			types[ScriptParser::TYPE_NPCDATA] = &Library::NpcClass::instance();
			types[ScriptParser::TYPE_PALCYCLE] = &Library::PalCycle::instance();
			types[ScriptParser::TYPE_PALETTE] = &Library::Palette::instance();
			types[ScriptParser::TYPE_PONDS] = &Library::Pond::instance();
			types[ScriptParser::TYPE_RGBDATA] = &Library::Rgb::instance();
			types[ScriptParser::TYPE_SCREEN] = &Library::Screen::instance();
			types[ScriptParser::TYPE_SHOPDATA] = &Library::Shop::instance();
			types[ScriptParser::TYPE_SPRITEDATA] = &Library::Sprite::instance();
			types[ScriptParser::TYPE_TEXT] = &Library::Text::instance();
			types[ScriptParser::TYPE_TUNES] = &Library::Tune::instance();
			types[ScriptParser::TYPE_WARPRING] = &Library::WarpRing::instance();
			initialized = true;
		}
		return types;
	}
}

Library::Base* Library::getLibraryForType(int type)
{
	map<int, Base*>& map = typeMap();
	std::map<int, Base*>::iterator it = map.find(type);
	if (it == map.end()) return NULL;
	return it->second;
}
