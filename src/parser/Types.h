#ifndef ZSCRIPT_TYPES_H
#define ZSCRIPT_TYPES_H

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "CompilerUtils.h"

namespace ZScript
{
	////////////////////////////////////////////////////////////////
	// Forward Declarations
	class Function;
	class Scope;
	class ZClass;
	class DataType;

	typedef int DataTypeId;

	////////////////////////////////////////////////////////////////
	// Stores and lookup types and classes.
	class TypeStore
	{
	public:
		TypeStore();
		~TypeStore();

		// Types
		DataType const* getType(DataTypeId typeId) const;
		optional<DataTypeId> getTypeId(DataType const& type) const;
		optional<DataTypeId> assignTypeId(DataType const& type);
		optional<DataTypeId> getOrAssignTypeId(DataType const& type);

		template <typename Type>
		Type const* getCanonicalType(Type const& type)
		{
			return static_cast<Type const*>(
					ownedTypes[*getOrAssignTypeId(type)]);
		}
	
		// Classes
		std::vector<ZScript::ZClass*> getClasses() const {
			return ownedClasses;}
		ZScript::ZClass* getClass(int classId) const;
		ZScript::ZClass* createClass(std::string const& name);

	private:
		// Comparator for pointers to types.
		struct TypeIdMapComparator {
			bool operator() (
					DataType const* const& lhs, DataType const* const& rhs)
					const;
		};

		std::vector<DataType const*> ownedTypes;
		std::map<DataType const*, DataTypeId, TypeIdMapComparator> typeIdMap;
		std::vector<ZClass*> ownedClasses;
	};

	std::vector<Function*> getClassFunctions(TypeStore const&);

	////////////////////////////////////////////////////////////////
	// Data Types

	enum DataTypeIdBuiltin
	{
		ZVARTYPEID_START = 0,

		ZVARTYPEID_PRIMITIVE_START = 0,
		ZVARTYPEID_UNTYPED = 0,
		ZVARTYPEID_VOID,
		ZVARTYPEID_FLOAT,
		ZVARTYPEID_BOOL,
		ZVARTYPEID_PRIMITIVE_END,

		ZVARTYPEID_CLASS_START = ZVARTYPEID_PRIMITIVE_END,
		ZVARTYPEID_GAME = ZVARTYPEID_CLASS_START,
		ZVARTYPEID_LINK,
		ZVARTYPEID_SCREEN,
		ZVARTYPEID_FFC,
		ZVARTYPEID_ITEM,
		ZVARTYPEID_ITEMCLASS,
		ZVARTYPEID_NPC,
		ZVARTYPEID_LWPN,
		ZVARTYPEID_EWPN,
		ZVARTYPEID_NPCDATA,
		ZVARTYPEID_DEBUG,
		ZVARTYPEID_AUDIO,
		ZVARTYPEID_COMBOS,
		ZVARTYPEID_SPRITEDATA,
		ZVARTYPEID_GRAPHICS,
		ZVARTYPEID_BITMAP,
		ZVARTYPEID_TEXT,
		ZVARTYPEID_INPUT,
		ZVARTYPEID_MAPDATA,
		ZVARTYPEID_DMAPDATA,
		ZVARTYPEID_ZMESSAGE,
		ZVARTYPEID_SHOPDATA,
		ZVARTYPEID_DROPSET,
		ZVARTYPEID_PONDS,
		ZVARTYPEID_WARPRING,
		ZVARTYPEID_DOORSET,
		ZVARTYPEID_ZUICOLOURS,
		ZVARTYPEID_RGBDATA,
		ZVARTYPEID_PALETTE,
		ZVARTYPEID_TUNES,
		ZVARTYPEID_PALCYCLE,
		ZVARTYPEID_GAMEDATA,
		ZVARTYPEID_CHEATS,
		ZVARTYPEID_CLASS_END,

		ZVARTYPEID_END = ZVARTYPEID_CLASS_END
	};

	class DataTypeSimple;
	class DataTypeSimpleConst;
	class DataTypeClass;
	class DataTypeClassConst;
	class DataTypeArray;
	class DataTypeCustom;
	class DataTypeCustomConst;

	class DataType
	{
	public:
		DataType(DataType* constType)
			: constType(constType ? constType->clone() : NULL)
		{}
		
		// Call derived class's copy constructor.
		virtual DataType* clone() const = 0;

		// Resolution.
		virtual bool isResolved() const {return true;}
		virtual DataType* resolve(ZScript::Scope& scope) {return this;}

		// Basics
		virtual std::string getName() const = 0;
		virtual bool canCastTo(DataType const& target) const = 0;
		virtual bool canBeGlobal() const {return false;}
		virtual DataType* getConstType() const {return constType;}

		// Derived class info.
		virtual bool isArray() const {return false;}
		virtual bool isClass() const {return false;}
		virtual bool isConstant() const {return false;}
		virtual bool isUntyped() const {return false;}
		virtual bool isCustom() const {return false;}

		// Returns <0 if <rhs, 0, if ==rhs, and >0 if >rhs.
		int compare(DataType const& rhs) const;
		
		//Static functions
		static DataType const* get(DataTypeId id);
		static DataTypeClass const* getClass(int classId);
		static DataTypeCustom const* getCustom(int customId) {return find<DataTypeCustom*>(customTypes, customId).value_or(NULL);};
		static void addCustom(DataTypeCustom* custom);
		static int getUniqueCustomId() {return nextCustomId_++;}
		
	private:
		// Returns <0 if <rhs, 0, if ==rhs, and >0 if >rhs.
		// rhs is guaranteed to be the same class as the derived type.
		virtual int selfCompare(DataType const& rhs) const = 0;

		//Static variables
		static int nextCustomId_;
		static std::map<int, DataTypeCustom*> customTypes;
		
		DataType* constType;
		// Standard Types.
	public:
		static DataTypeSimpleConst CUNTYPED;
		static DataTypeSimpleConst CFLOAT;
		static DataTypeSimpleConst CBOOL;
		static DataTypeSimple UNTYPED;
		static DataTypeSimple ZVOID;
		static DataTypeSimple FLOAT;
		static DataTypeSimple BOOL;
		static DataTypeArray STRING;
		//Classes: Global Pointer
		static DataTypeClassConst GAME;
		static DataTypeClassConst LINK;
		static DataTypeClassConst SCREEN;
		static DataTypeClassConst AUDIO;
		static DataTypeClassConst DEBUG;
		static DataTypeClassConst GRAPHICS;
		static DataTypeClassConst INPUT;
		static DataTypeClassConst TEXT;
		//Class: Types
		static DataTypeClassConst CBITMAP;
		static DataTypeClassConst CCHEATS;
		static DataTypeClassConst CCOMBOS;
		static DataTypeClassConst CDOORSET;
		static DataTypeClassConst CDROPSET;
		static DataTypeClassConst CDMAPDATA;
		static DataTypeClassConst CEWPN;
		static DataTypeClassConst CFFC;
		static DataTypeClassConst CGAMEDATA;
		static DataTypeClassConst CITEM;
		static DataTypeClassConst CITEMCLASS;
		static DataTypeClassConst CLWPN;
		static DataTypeClassConst CMAPDATA;
		static DataTypeClassConst CZMESSAGE;
		static DataTypeClassConst CZUICOLOURS;
		static DataTypeClassConst CNPC;
		static DataTypeClassConst CNPCDATA;
		static DataTypeClassConst CPALCYCLE;
		static DataTypeClassConst CPALETTE;
		static DataTypeClassConst CPONDS;
		static DataTypeClassConst CRGBDATA;
		static DataTypeClassConst CSHOPDATA;
		static DataTypeClassConst CSPRITEDATA;
		static DataTypeClassConst CTUNES;
		static DataTypeClassConst CWARPRING;
		//Class: Var Types
		static DataTypeClass BITMAP;
		static DataTypeClass CHEATS;
		static DataTypeClass COMBOS;
		static DataTypeClass DOORSET;
		static DataTypeClass DROPSET;
		static DataTypeClass DMAPDATA;
		static DataTypeClass EWPN;
		static DataTypeClass FFC;
		static DataTypeClass GAMEDATA;
		static DataTypeClass ITEM;
		static DataTypeClass ITEMCLASS;
		static DataTypeClass LWPN;
		static DataTypeClass MAPDATA;
		static DataTypeClass ZMESSAGE;
		static DataTypeClass ZUICOLOURS;
		static DataTypeClass NPC;
		static DataTypeClass NPCDATA;
		static DataTypeClass PALCYCLE;
		static DataTypeClass PALETTE;
		static DataTypeClass PONDS;
		static DataTypeClass RGBDATA;
		static DataTypeClass SHOPDATA;
		static DataTypeClass SPRITEDATA;
		static DataTypeClass TUNES;
		static DataTypeClass WARPRING;
	};

	bool operator==(DataType const&, DataType const&);
	bool operator!=(DataType const&, DataType const&);
	bool operator<(DataType const&, DataType const&);
	bool operator<=(DataType const&, DataType const&);
	bool operator>(DataType const&, DataType const&);
	bool operator>=(DataType const&, DataType const&);

	// Get the data type stripped of consts and arrays.
	DataType const& getNaiveType(DataType const& type, Scope* scope);
	
	// Get the number of nested arrays at top level.
	int getArrayDepth(DataType const&);

	class DataTypeUnresolved : public DataType
	{
	public:
		DataTypeUnresolved(ASTExprIdentifier* iden) : DataType(NULL), iden(iden) {}
		DataTypeUnresolved* clone() const {
			return new DataTypeUnresolved(*this);}
		
		virtual bool isResolved() const {return false;}
		virtual DataType* resolve(ZScript::Scope& scope);

		virtual std::string getName() const {return iden->asString();}
		virtual bool canCastTo(DataType const& target) const {return false;}

	private:
		ASTExprIdentifier* iden;

		int selfCompare(DataType const& rhs) const;
	};

	class DataTypeSimple : public DataType
	{
	public:
		DataTypeSimple(int simpleId, std::string const& name, DataType* constType);
		DataTypeSimple* clone() const {return new DataTypeSimple(*this);}

		virtual DataTypeSimple* resolve(ZScript::Scope&) {return this;}
		
		virtual std::string getName() const {return name;}
		virtual bool canCastTo(DataType const& target) const;
		virtual bool canBeGlobal() const;
		virtual bool isConstant() const {return false;}
		virtual bool isUntyped() const {return simpleId == ZVARTYPEID_UNTYPED;}

		int getId() const {return simpleId;}

	protected:
		int simpleId;
		std::string name;

		int selfCompare(DataType const& rhs) const;
	};
	
	class DataTypeSimpleConst : public DataTypeSimple
	{
	public:
		DataTypeSimpleConst(int simpleId, std::string const& name);
		DataTypeSimpleConst* clone() const {return new DataTypeSimpleConst(*this);}
		
		virtual DataTypeSimpleConst* resolve(ZScript::Scope&) {return this;}
		
		virtual bool isConstant() const {return true;}
	};

	class DataTypeClass : public DataType
	{
	public:
		DataTypeClass(int classId, DataType* constType);
		DataTypeClass(int classId, std::string const& className, DataType* constType);
		DataTypeClass* clone() const {return new DataTypeClass(*this);}

		virtual DataTypeClass* resolve(ZScript::Scope& scope);

		virtual std::string getName() const;
		virtual bool canCastTo(DataType const& target) const;
		virtual bool canBeGlobal() const {return true;}
		virtual bool isClass() const {return true;}
		virtual bool isConstant() const {return false;}

		std::string getClassName() const {return className;}
		int getClassId() const {return classId;}
		
	protected:
		int classId;
		std::string className;

		int selfCompare(DataType const& other) const;
	};
	
	class DataTypeClassConst : public DataTypeClass
	{
	public:
		DataTypeClassConst(int classId, std::string const& name);
		DataTypeClassConst* clone() const {return new DataTypeClassConst(*this);}
		
		virtual DataTypeClassConst* resolve(ZScript::Scope&) {return this;}
		
		virtual bool isConstant() const {return true;}
	};

	class DataTypeArray : public DataType
	{
	public:
		DataTypeArray(DataType const& elementType)
			: DataType(NULL), elementType(elementType) {}
		DataTypeArray* clone() const {return new DataTypeArray(*this);}

		virtual DataTypeArray* resolve(ZScript::Scope& scope) {return this;}

		virtual std::string getName() const {
			return elementType.getName() + "[]";}
		virtual bool canCastTo(DataType const& target) const;
		virtual bool canBeGlobal() const {return true;}
		virtual bool isArray() const {return true;}

		DataType const& getElementType() const {return elementType;}

	private:
		DataType const& elementType;

		int selfCompare(DataType const& other) const;
	};
	
	class DataTypeCustom : public DataType
	{
	public:
		DataTypeCustom(std::string name, DataType* constType, int id = getUniqueCustomId())
			: DataType(constType), name(name), id(id)
		{}
		DataTypeCustom* clone() const {return new DataTypeCustom(*this);}
		
		virtual DataTypeCustom* resolve(ZScript::Scope& scope) {return this;}
		
		virtual bool isConstant() const {return false;}
		virtual bool isCustom() const {return false;}
		virtual bool canBeGlobal() const {return true;}
		virtual std::string getName() const {return name;}
		virtual bool canCastTo(DataType const& target) const;
		int getCustomId() const {return id;}
		
	protected:
		int id;
		std::string name;

		int selfCompare(DataType const& other) const;
	};
	
	class DataTypeCustomConst : public DataTypeCustom
	{
	public:
		DataTypeCustomConst(std::string name)
			: DataTypeCustom(name, NULL)
		{}
		DataTypeCustomConst* clone() const {return new DataTypeCustomConst(*this);}
		
		virtual DataTypeCustomConst* resolve(ZScript::Scope& scope) {return this;}
		
		virtual bool isConstant() const {return true;}
	};

	DataType const& getBaseType(DataType const&);

	////////////////////////////////////////////////////////////////
	// Script Types

	// Basically an enum.
	class ScriptType
	{
		friend bool operator==(ScriptType const& lhs, ScriptType const& rhs);
		friend bool operator!=(ScriptType const& lhs, ScriptType const& rhs);

	public:
		enum Id
		{
			idInvalid,
			idStart,
			idGlobal = idStart,
			idFfc,
			idItem,
			idNPC,
			idEWeapon,
			idLWeapon,
			idLink,
			idScreen,
			idDMap,
			idItemSprite,
			idUntyped,
			
			idEnd
		};
	
		ScriptType() : id_(idInvalid) {}
		
		std::string const& getName() const;
		DataTypeId getThisTypeId() const;
		bool isValid() const {return id_ >= idStart && id_ < idEnd;}

		static ScriptType const invalid;
		static ScriptType const global;
		static ScriptType const ffc;
		static ScriptType const item;
		static ScriptType const npc;
		static ScriptType const eweapon;
		static ScriptType const lweapon;
		static ScriptType const link;
		static ScriptType const dmapdata;
		static ScriptType const screendata;
		static ScriptType const ScriptType::itemsprite;
		static ScriptType const ScriptType::untyped;

	private:
		ScriptType(Id id) : id_(id) {}
		
		Id id_;
	};

	// All invalid values are equal to each other.
	bool operator==(ScriptType const& lhs, ScriptType const& rhs);
	bool operator!=(ScriptType const& lhs, ScriptType const& rhs);
}

#endif
