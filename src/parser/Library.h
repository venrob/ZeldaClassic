#ifndef ZSCRIPT_LIBRARY_H
#define ZSCRIPT_LIBRARY_H

#include <map>
#include <string>
#include <utility>
#include <vector>

class Scope;
class SymbolTable;
class Opcode;
class LinkTable;

namespace Library
{
	enum EntryType {SETTER, GETTER, FUNCTION};
	struct Entry
	{
		std::string name;
		int rettype;
		int type;
		int var;
		int numindex;
		int params[20];
	};
	
	class Base
	{
	public:
		void writeSymbols(Scope* scope, SymbolTable* t);
		void writeCode(LinkTable* lt,
		               std::map<int, std::vector<Opcode*> >& target);
		std::pair<int, std::vector<int> > matchFunction(
				std::string const& name, SymbolTable* t);

	protected:
		Entry* entries;
		int firstid;
		int refVar;
		std::map<std::string, int> memberids;

		Base(int refVar, Entry* entries)
			: refVar(refVar), entries(entries)
		{}
	
		virtual void generateFunctionCode(
				LinkTable* lt,
				std::map<int, std::vector<Opcode*> >& target)
				= 0;
	};

	Base* getLibraryForType(int type);
	
	////////////////
	// Library Definitions
#	define LIBDEF(NAME) \
	class NAME : public Base \
	{ \
	public: \
		static NAME& instance(); \
	protected: \
		virtual void generateFunctionCode( \
				LinkTable* lt, std::map<int, std::vector<Opcode*> >& target); \
	private: \
		NAME(int refVar, Entry* entries) : Base(refVar, entries) {} \
	} \
	
	LIBDEF(Global);

	LIBDEF(Audio);
	LIBDEF(Cheat);
	LIBDEF(Combo);
	LIBDEF(Debug);
	LIBDEF(DoorSet);
	LIBDEF(DropSet);
	LIBDEF(DMap);
	LIBDEF(EnemyWeapon);
	LIBDEF(Ffc);
	LIBDEF(Game);
	LIBDEF(GameData);
	LIBDEF(Graphics);
	LIBDEF(Input);
	LIBDEF(Item);
	LIBDEF(ItemClass);
	LIBDEF(Link);
	LIBDEF(LinkWeapon);
	LIBDEF(Map);
	LIBDEF(Message);
	LIBDEF(MiscColor);
	LIBDEF(Npc);
	LIBDEF(NpcClass);
	LIBDEF(PalCycle);
	LIBDEF(Palette);
	LIBDEF(Pond);
	LIBDEF(Rgb);
	LIBDEF(Screen);
	LIBDEF(Shop);
	LIBDEF(Sprite);
	LIBDEF(Text);
	LIBDEF(Tune);
	LIBDEF(WarpRing);

#	undef LIBDEF
}

#endif
