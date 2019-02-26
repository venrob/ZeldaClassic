#include "../precompiled.h"
#include "Scope.h"

#include <set>
#include "CompileError.h"
#include "GlobalSymbols.h"
#include "Types.h"
#include "ZScript.h"

using namespace std;
using namespace ZScript;

////////////////////////////////////////////////////////////////
// Scope

Scope::Scope(TypeStore& typeStore)
	: typeStore_(typeStore), name_(nullopt)
{}

Scope::Scope(TypeStore& typeStore, string const& name)
	: typeStore_(typeStore), name_(name)
{}

void Scope::invalidateStackSize()
{
	if (Scope* parent = getParent())
		parent->invalidateStackSize();
}

// Inheritance

Scope* ZScript::getDescendant(Scope const& scope, vector<string> const& names)
{
	Scope* child = const_cast<Scope*>(&scope);
	for (vector<string>::const_iterator it = names.begin();
	     child && it != names.end(); ++it)
		child = child->getChild(*it);
	return child;
}

Scope* ZScript::lookupScope(Scope const& scope, string const& name)
{
	Scope* current = const_cast<Scope*>(&scope);
	while (current)
	{
		if (Scope* child = current->getChild(name))
	return child;

		if (optional<string> const& currentName = current->getName())
			if (*currentName == name)
				return current;

		current = current->getParent();
	}

	return NULL;
}

Scope* ZScript::lookupScope(Scope const& scope, vector<string> const& names)
{
	// Travel as far up the tree as needed for the first scope.
	Scope* current = lookupScope(scope, names.front());
	if (!current) return NULL;
	if (names.size() == 1) return current;

	// Descend with the rest of the names from the first found scope.
	vector<string> restOfNames(++names.begin(), names.end());
	return getDescendant(*current, restOfNames);
}

vector<Scope*> ZScript::lookupScopes(Scope const& scope, vector<string> const& names)
{
	vector<Scope*> scopes;
	for (Scope* current = const_cast<Scope*>(&scope);
	     current; current = current->getParent())
	{
		if(current == getRoot(*current) && scopes.size() != 0)
			break;
		if (Scope* descendant = getDescendant(*current, names))
			scopes.push_back(descendant);
	}
	return scopes;
}

RootScope* ZScript::getRoot(Scope const& scope)
{
	Scope* current = const_cast<Scope*>(&scope);
	while (Scope* parent = current->getParent())
		current = parent;
	return dynamic_cast<RootScope*>(current);
}

// Lookup

DataType const* ZScript::lookupDataType(
	Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (DataType const* type = current->getLocalDataType(name))
			return type;
	return NULL;
}

ScriptType ZScript::lookupScriptType(Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (optional<ScriptType> type = current->getLocalScriptType(name))
			return *type;
	return ScriptType::invalid;
}

ZClass* ZScript::lookupClass(Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (ZClass* klass = current->getLocalClass(name))
			return klass;
	return NULL;
}

Datum* ZScript::lookupDatum(Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (Datum* datum = current->getLocalDatum(name))
			return datum;
	return NULL;
}

Datum* ZScript::lookupDatum(Scope const& scope, vector<string> const& names)
{
	if (names.size() == 0)
		return NULL;
	else if (names.size() == 1)
		return lookupDatum(scope, names[0]);

	vector<string> childNames(names.begin(), --names.end());
	if (Scope* child = lookupScope(scope, childNames))
		return lookupDatum(*child, names.back());

	return NULL;
}

Function* ZScript::lookupGetter(Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (Function* getter = current->getLocalGetter(name))
			return getter;
	return NULL;
}

Function* ZScript::lookupSetter(Scope const& scope, string const& name)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (Function* setter = current->getLocalSetter(name))
			return setter;
	return NULL;
}

Function* ZScript::lookupFunction(Scope const& scope,
                         FunctionSignature const& signature)
{
	for (Scope const* current = &scope;
	     current; current = current->getParent())
		if (Function* function = current->getLocalFunction(signature))
			return function;
	return NULL;
}

vector<Function*> ZScript::lookupFunctions(Scope const& scope, string const& name)
{
	set<Function*> functions;
	for (Scope const* current = &scope;
	     current; current = current->getParent())
	{
		vector<Function*> currentFunctions = current->getLocalFunctions(name);
		functions.insert(currentFunctions.begin(), currentFunctions.end());
	}
	return vector<Function*>(functions.begin(), functions.end());
}

vector<Function*> ZScript::lookupFunctions(
		Scope const& scope, vector<string> const& names)
{
	if (names.size() == 0)
		return vector<Function*>();
	else if (names.size() == 1)
		return lookupFunctions(scope, names[0]);

	vector<Function*> functions;
	string const& name = names.back();

	vector<string> ancestry(names.begin(), --names.end());
	vector<Scope*> scopes = lookupScopes(scope, ancestry);
	for (vector<Scope*>::const_iterator it = scopes.begin();
	     it != scopes.end(); ++it)
	{
		Scope& current = **it;
		vector<Function*> currentFunctions = current.getLocalFunctions(name);
		functions.insert(functions.end(),
		                 currentFunctions.begin(), currentFunctions.end());
	}

	return functions;
}

optional<long> ZScript::lookupOption(Scope const& scope, CompileOption option)
{
	if (!option.isValid()) return nullopt;
	for (Scope const* current = &scope;
	     current; current = current->getParent())
	{
		CompileOptionSetting setting = current->getLocalOption(option);
		if (setting == CompileOptionSetting::Inherit) continue;
		if (setting == CompileOptionSetting::Default)
			return *option.getDefault();
		return *setting.getValue();
	}
	return *option.getDefault();
}

// Stack

bool ZScript::isStackRoot(Scope const& scope)
{
	return scope.getRootStackSize();
}

optional<int> ZScript::lookupStackOffset(
		Scope const& scope, Datum const& datum)
{
	Scope* s = const_cast<Scope*>(&scope);
	while (s)
	{
		if (optional<int> offset = s->getLocalStackOffset(datum))
			return offset;

		if (isStackRoot(*s)) return nullopt;

		s = s->getParent();
	}
	return nullopt;
}

optional<int> ZScript::lookupStackSize(Scope const& scope)
{
	Scope* s = const_cast<Scope*>(&scope);
	while (s)
	{
		if (optional<int> size = s->getRootStackSize())
			return size;

		s = s->getParent();
	}
	return nullopt;
}

optional<int> ZScript::lookupStackPosition(
		Scope const& scope, Datum const& datum)
{
	optional<int> offset = lookupStackOffset(scope, datum);
	optional<int> size = lookupStackSize(scope);
	if (offset && size)
		return *size - 1 - *offset;
	return nullopt;
}

// Get all in branch

vector<Function*> ZScript::getFunctionsInBranch(Scope const& scope)
{
	typedef vector<Function*> (Scope::*Call)() const;
	Call call = static_cast<Call>(&Scope::getLocalFunctions);
	return getInBranch<Function*>(scope, call);
}

////////////////////////////////////////////////////////////////
// Basic Scope

BasicScope::BasicScope(Scope* parent)
	: Scope(parent->getTypeStore()), parent_(parent),
	  stackDepth_(parent->getLocalStackDepth()),
	  defaultOption_(CompileOptionSetting::Inherit)
{}

BasicScope::BasicScope(Scope* parent, string const& name)
	: Scope(parent->getTypeStore(), name), parent_(parent),
	  stackDepth_(parent->getLocalStackDepth()),
	  defaultOption_(CompileOptionSetting::Inherit)
{}

BasicScope::BasicScope(TypeStore& typeStore)
	: Scope(typeStore), parent_(NULL), stackDepth_(0),
	  defaultOption_(CompileOptionSetting::Inherit)
{}

BasicScope::BasicScope(TypeStore& typeStore, string const& name)
	: Scope(typeStore, name), parent_(NULL), stackDepth_(0),
	  defaultOption_(CompileOptionSetting::Inherit)
{}

BasicScope::~BasicScope()
{
	deleteSeconds(children_);
	deleteElements(anonymousChildren_);
	deleteElements(anonymousData_);
	deleteSeconds(namedData_);
	deleteSeconds(getters_);
	deleteSeconds(setters_);
	deleteSeconds(functionsBySignature_);
}

// Inheritance

Scope* BasicScope::getChild(string const& name) const
{
	return find<Scope*>(children_, name).value_or(NULL);
}

vector<Scope*> BasicScope::getChildren() const
{
	vector<Scope*> results = anonymousChildren_;
	appendElements(results, getSeconds<Scope*>(children_));
	return results;
}

// Lookup Local

DataType const* BasicScope::getLocalDataType(string const& name) const
{
	return find<DataType const*>(dataTypes_, name).value_or(NULL);
}

optional<ScriptType> BasicScope::getLocalScriptType(string const& name) const
{
	return find<ScriptType>(scriptTypes_, name);
}

ZClass* BasicScope::getLocalClass(string const& name) const
{
	return find<ZClass*>(classes_, name).value_or(NULL);
}

Datum* BasicScope::getLocalDatum(string const& name) const
{
	return find<Datum*>(namedData_, name).value_or(NULL);
}

Function* BasicScope::getLocalGetter(string const& name) const
{
	return find<Function*>(getters_, name).value_or(NULL);
}

Function* BasicScope::getLocalSetter(string const& name) const
{
	return find<Function*>(setters_, name).value_or(NULL);
}

Function* BasicScope::getLocalFunction(
		FunctionSignature const& signature) const
{
	return find<Function*>(functionsBySignature_, signature).value_or(NULL);
}

vector<Function*> BasicScope::getLocalFunctions(string const& name) const
{
	return find<vector<Function*> >(functionsByName_, name)
		.value_or(vector<Function*>());
}

CompileOptionSetting BasicScope::getLocalOption(CompileOption option) const
{
	if (optional<CompileOptionSetting> setting =
	    	find<CompileOptionSetting>(options_, option))
		return *setting;
	return defaultOption_;
}

// Get All Local

vector<Datum*> BasicScope::getLocalData() const
{
	vector<Datum*> results = getSeconds<Datum*>(namedData_);
	appendElements(results, anonymousData_);
	return results;
}

vector<Function*> BasicScope::getLocalFunctions() const
{
	return getSeconds<Function*>(functionsBySignature_);
}

vector<Function*> BasicScope::getLocalGetters() const
{
	return getSeconds<Function*>(getters_);
}

vector<Function*> BasicScope::getLocalSetters() const
{
	return getSeconds<Function*>(setters_);
}

map<CompileOption, CompileOptionSetting> BasicScope::getLocalOptions() const
{
	return options_;
}

// Add

Scope* BasicScope::makeChild()
{
	Scope* child = new BasicScope(this);
	anonymousChildren_.push_back(child);
	return child;
}

Scope* BasicScope::makeChild(string const& name)
{
	if (find<Scope*>(children_, name)) return NULL;
	Scope* child = new BasicScope(this, name);
	children_[name] = child;
	return child;
}

FileScope* BasicScope::makeFileChild(string const& filename)
{
	FileScope* child = new FileScope(this, filename);
	anonymousChildren_.push_back(child);
	return child;
}

ScriptScope* BasicScope::makeScriptChild(Script& script)
{
	string name = script.getName();
	if (find<Scope*>(children_, name)) return NULL;
	ScriptScope* child = new ScriptScope(this, script);
	children_[name] = child;
	return child;
}

FunctionScope* BasicScope::makeFunctionChild(Function& function)
{
	FunctionScope* child = new FunctionScope(this, function);
	anonymousChildren_.push_back(child);
	return child;
}

DataType const* BasicScope::addDataType(
		string const& name, DataType const* type, AST* node)
{
	if (find<DataType const*>(dataTypes_, name)) return NULL;
	type = typeStore_.getCanonicalType(*type);
	dataTypes_[name] = type;
	return type;
}

bool BasicScope::addScriptType(
	string const& name, ScriptType type, AST* node)
{
	if (find<ScriptType>(scriptTypes_, name)) return false;
	scriptTypes_[name] = type;
	return true;
}

Function* BasicScope::addGetter(
		DataType const* returnType, string const& name,
		vector<DataType const*> const& paramTypes, AST* node)
{
	if (find<Function*>(getters_, name)) return NULL;

	Function* fun = new Function(
			returnType, name, paramTypes, ScriptParser::getUniqueFuncID());
	getters_[name] = fun;
	return fun;
}

Function* BasicScope::addSetter(
		DataType const* returnType, string const& name,
		vector<DataType const*> const& paramTypes, AST* node)
{
	if (find<Function*>(setters_, name)) return NULL;

	Function* fun = new Function(
			returnType, name, paramTypes, ScriptParser::getUniqueFuncID());
	setters_[name] = fun;
	return fun;
}

Function* BasicScope::addFunction(
		DataType const* returnType, string const& name,
		vector<DataType const*> const& paramTypes, AST* node)
{
	FunctionSignature signature(name, paramTypes);
	if (find<Function*>(functionsBySignature_, signature))
		return NULL;

	Function* fun = new Function(
			returnType, name, paramTypes, ScriptParser::getUniqueFuncID());
	fun->internalScope = makeFunctionChild(*fun);
	
	functionsByName_[name].push_back(fun);
	functionsBySignature_[signature] = fun;
	return fun;
}

void BasicScope::setDefaultOption(CompileOptionSetting value)
{
	defaultOption_ = value;
}
		
void BasicScope::setOption(CompileOption option, CompileOptionSetting value)
{
	assert(option.isValid());
	options_[option] = value;
}

bool BasicScope::add(Datum& datum, CompileErrorHandler* errorHandler)
{
	if (optional<string> name = datum.getName())
	{
		if (find<Datum*>(namedData_, *name))
		{
			if (errorHandler)
				errorHandler->handleError(
						CompileError::VarRedef(datum.getNode(),
						                       name->c_str()));
			return false;
		}
		namedData_[*name] = &datum;
	}
	else anonymousData_.push_back(&datum);

	if (!ZScript::isGlobal(datum))
	{
		stackOffsets_[&datum] = stackDepth_++;
		invalidateStackSize();
	}

	return true;
}

// Stack

optional<int> BasicScope::getLocalStackOffset(Datum const& datum) const
{
	Datum* key = const_cast<Datum*>(&datum);
	return find<int>(stackOffsets_, key);
}

////////////////////////////////////////////////////////////////
// FileScope

FileScope::FileScope(Scope* parent, string const& filename)
	: BasicScope(parent), filename_(filename)
{
	defaultOption_ = CompileOptionSetting::Default;
}

Scope* FileScope::makeChild(std::string const& name)
{
	Scope* result = BasicScope::makeChild(name);
	if (!result) return NULL;
	if (!getRoot(*this)->registerChild(name, result))
		result = NULL;
	return result;
}

ScriptScope* FileScope::makeScriptChild(Script& script)
{
	ScriptScope* result = BasicScope::makeScriptChild(script);
	if (!result) return NULL;
	if (!getRoot(*this)->registerChild(script.getName(), result))
		result = NULL;
	return result;
}

DataType const* FileScope::addDataType(
		std::string const& name, DataType const* type, AST* node)
{
	DataType const* result = BasicScope::addDataType(name, type, node);
	if (!result) return NULL;
	if (!getRoot(*this)->registerDataType(name, result)) result = NULL;
	return result;
}

bool FileScope::addScriptType(string const& name, ScriptType type, AST* node)
{
	if (!BasicScope::addScriptType(name, type, node)) return false;
	if (!getRoot(*this)->registerScriptType(name, type)) return false;
	return true;
}

Function* FileScope::addGetter(
		DataType const* returnType, std::string const& name,
		std::vector<DataType const*> const& paramTypes, AST* node)
{
	Function* result = BasicScope::addGetter(
			returnType, name, paramTypes, node);
	if (!result) return NULL;
	if (!getRoot(*this)->registerGetter(name, result))
		result = NULL;
	return result;
}

Function* FileScope::addSetter(
		DataType const* returnType, std::string const& name,
		std::vector<DataType const*> const& paramTypes, AST* node)
{
	Function* result = BasicScope::addSetter(
			returnType, name, paramTypes, node);
	if (!result) return NULL;
	if (!getRoot(*this)->registerSetter(name, result))
		result = NULL;
	return result;
}

Function* FileScope::addFunction(
		DataType const* returnType, std::string const& name,
		std::vector<DataType const*> const& paramTypes, AST* node)
{
	Function* result = BasicScope::addFunction(
			returnType, name, paramTypes, node);
	if (!result) return NULL;
	if (!getRoot(*this)->registerFunction(result))
		result = NULL;
	return result;
}

bool FileScope::add(Datum& datum, CompileErrorHandler* errorHandler)
{
	if (!BasicScope::add(datum, errorHandler))
		return false;

	// Register in root scope if it's named.
	if (optional<string> name = datum.getName())
	{
		if (!getRoot(*this)->registerDatum(*name, &datum))
		{
			if (errorHandler)
				errorHandler->handleError(
						CompileError::VarRedef(datum.getNode(),
						                       name->c_str()));
			return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// RootScope

namespace // file local
{
	int calculateStackSize(Scope* scope)
	{
		int greatestSize = scope->getLocalStackDepth();
		vector<Scope*> children = scope->getChildren();
		for (vector<Scope*>::const_iterator it = children.begin();
		     it != children.end(); ++it)
		{
			int size = calculateStackSize(*it);
			if (greatestSize < size) greatestSize = size;
		}
		return greatestSize;
	}
};

RootScope::RootScope(TypeStore& typeStore)
	: BasicScope(typeStore, "root")
{
	// Add global library functions.
    GlobalSymbols::getInst().addSymbolsToScope(*this);

	// Create builtin classes (not primitives like void, float, and bool).
	for (DataTypeId typeId = ZVARTYPEID_CLASS_START;
	     typeId < ZVARTYPEID_CLASS_END; ++typeId)
	{
		DataTypeClass const& type =
			*static_cast<DataTypeClass const*>(DataType::get(typeId));
		ZClass& klass = *typeStore.getClass(type.getClassId());
		LibrarySymbols& library = *LibrarySymbols::getTypeInstance(typeId);
		library.addSymbolsToScope(klass);
	}

	// Add builtin pointers.
	BuiltinConstant::create(*this, DataType::LINK, "Link", 0);
	BuiltinConstant::create(*this, DataType::SCREEN, "Screen", 0);
	BuiltinConstant::create(*this, DataType::GAME, "Game", 0);
	BuiltinConstant::create(*this, DataType::AUDIO, "Audio", 0);
	BuiltinConstant::create(*this, DataType::DEBUG, "Debug", 0);
	BuiltinConstant::create(*this, DataType::NPCDATA, "NPCData", 0);
	BuiltinConstant::create(*this, DataType::TEXT, "Text", 0);
	BuiltinConstant::create(*this, DataType::COMBOS, "ComboData", 0);
	BuiltinConstant::create(*this, DataType::SPRITEDATA, "SpriteData", 0);
	BuiltinConstant::create(*this, DataType::INPUT, "Input", 0);
	BuiltinConstant::create(*this, DataType::GRAPHICS, "Graphics", 0);
	BuiltinConstant::create(*this, DataType::MAPDATA, "MapData", 0);
	BuiltinConstant::create(*this, DataType::DMAPDATA, "DMapData", 0);
	BuiltinConstant::create(*this, DataType::ZMESSAGE, "MessageData", 0);
	BuiltinConstant::create(*this, DataType::SHOPDATA, "ShopData", 0);
	BuiltinConstant::create(*this, DataType::DROPSET, "DropData", 0);
	BuiltinConstant::create(*this, DataType::PONDS, "PondData", 0);
	BuiltinConstant::create(*this, DataType::WARPRING, "WarpRing", 0);
	BuiltinConstant::create(*this, DataType::DOORSET, "DoorSet", 0);
	BuiltinConstant::create(*this, DataType::ZUICOLOURS, "MiscColors", 0);
	BuiltinConstant::create(*this, DataType::RGBDATA, "RGBData", 0);
	BuiltinConstant::create(*this, DataType::PALETTE, "Palette", 0);
	BuiltinConstant::create(*this, DataType::TUNES, "MusicTrack", 0);
	BuiltinConstant::create(*this, DataType::PALCYCLE, "PalCycle", 0);
	BuiltinConstant::create(*this, DataType::GAMEDATA, "GameData", 0);
	BuiltinConstant::create(*this, DataType::CHEATS, "Cheats", 0);
}

optional<int> RootScope::getRootStackSize() const
{
	if (!stackSize_)
	{
		RootScope* mutableThis = const_cast<RootScope*>(this);
		stackSize_ = calculateStackSize(mutableThis);
	}
	return stackSize_;
}

// Single

Scope* RootScope::getChild(std::string const& name) const
{
	Scope* result = BasicScope::getChild(name);
	if (!result)
		result = find<Scope*>(descChildren_, name).value_or(NULL);
	return result;
}

DataType const* RootScope::getLocalDataType(string const& name) const
{
	DataType const* result = BasicScope::getLocalDataType(name);
	if (!result)
		result = find<DataType const*>(descDataTypes_, name).value_or(NULL);
	return result;
}

optional<ScriptType> RootScope::getLocalScriptType(string const& name) const
{
	if (optional<ScriptType> result = BasicScope::getLocalScriptType(name))
		return result;
	return find<ScriptType>(descScriptTypes_, name);
}

ZClass* RootScope::getLocalClass(string const& name) const
{
	ZClass* result = BasicScope::getLocalClass(name);
	if (!result)
		result = find<ZClass*>(descClasses_, name).value_or(NULL);
	return result;
}

Datum* RootScope::getLocalDatum(string const& name) const
{
	Datum* result = BasicScope::getLocalDatum(name);
	if (!result)
		result = find<Datum*>(descData_, name).value_or(NULL);
	return result;
}

Function* RootScope::getLocalGetter(string const& name) const
{
	Function* result = BasicScope::getLocalGetter(name);
	if (!result)
		result = find<Function*>(descGetters_, name).value_or(NULL);
	return result;
}

Function* RootScope::getLocalSetter(string const& name) const
{
	Function* result = BasicScope::getLocalSetter(name);
	if (!result)
		result = find<Function*>(descSetters_, name).value_or(NULL);
	return result;
}

Function* RootScope::getLocalFunction(
		FunctionSignature const& signature) const
{
	Function* result = BasicScope::getLocalFunction(signature);
	if (!result)
		result = find<Function*>(descFunctionsBySignature_, signature)
			.value_or(NULL);
	return result;
}

vector<Function*> RootScope::getLocalFunctions(string const& name) const
{
	vector<Function*> results(BasicScope::getLocalFunctions(name));
	if (optional<vector<Function*> > desc =
	    	find<vector<Function*> >(descFunctionsByName_, name))
		appendElements(results, *desc);
	return results;
}

// All

vector<Datum*> RootScope::getLocalData() const
{
	vector<Datum*> results(BasicScope::getLocalData());
	appendElements(results, getSeconds<Datum*>(descData_));
	return results;
}

vector<Function*> RootScope::getLocalFunctions() const
{
	vector<Function*> results(BasicScope::getLocalFunctions());
	appendElements(results, getSeconds<Function*>(descFunctionsBySignature_));
	return results;
}

vector<Function*> RootScope::getLocalGetters() const
{
	vector<Function*> results(BasicScope::getLocalGetters());
	appendElements(results, getSeconds<Function*>(descGetters_));
	return results;
}

vector<Function*> RootScope::getLocalSetters() const
{
	vector<Function*> results(BasicScope::getLocalSetters());
	appendElements(results, getSeconds<Function*>(descSetters_));
	return results;
}

// Register

bool RootScope::registerChild(string const& name, Scope* child)
{
	if (getChild(name)) return false;
	descChildren_[name] = child;
	return true;
}

bool RootScope::registerDataType(string const& name, DataType const* type)
{
	if (getLocalDataType(name)) return false;
	descDataTypes_[name] = type;
	return true;
}

bool RootScope::registerScriptType(std::string const& name, ScriptType type)
{
	if (getLocalScriptType(name)) return false;
	descScriptTypes_[name] = type;
	return true;
}

bool RootScope::registerClass(string const& name, ZClass* klass)
{
	if (getLocalClass(name)) return false;
	descClasses_[name] = klass;
	return true;
}

bool RootScope::registerDatum(string const& name, Datum* datum)
{
	if (getLocalDatum(name)) return false;
	descData_[name] = datum;
	return true;
}

bool RootScope::registerGetter(string const& name, Function* getter)
{
	if (getLocalGetter(name)) return false;
	descGetters_[name] = getter;
	return true;
}

bool RootScope::registerSetter(string const& name, Function* setter)
{
	if (getLocalSetter(name)) return false;
	descSetters_[name] = setter;
	return true;
}

bool RootScope::registerFunction(Function* function)
{
	FunctionSignature signature(*function);
	if (getLocalFunction(signature)) return false;
	descFunctionsByName_[signature.name].push_back(function);
	descFunctionsBySignature_[signature] = function;
	return true;
}

////////////////////////////////////////////////////////////////
// ScriptScope

ScriptScope::ScriptScope(Scope* parent, Script& script)
	: BasicScope(parent, script.getName()), script(script)
{}

////////////////////////////////////////////////////////////////
// FunctionScope

FunctionScope::FunctionScope(Scope* parent, Function& function)
	: BasicScope(parent, function.name), function(function)
{
	// Functions have their own stack.
	stackDepth_ = 0;
}

optional<int> FunctionScope::getRootStackSize() const
{
	if (!stackSize)
	{
		FunctionScope* mutableThis = const_cast<FunctionScope*>(this);
		stackSize = calculateStackSize(mutableThis);
	}
	return stackSize;
}

////////////////////////////////////////////////////////////////
// ZClass

ZClass::ZClass(TypeStore& typeStore, string const& name, int id)
	: BasicScope(typeStore), name(name), id(id)
{}


