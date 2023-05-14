#include "Body.h"

typedef std::unordered_map<std::string, std::unordered_map<std::string, BodySpec>> BodySpecMap;

class LuaDataHolder
{
private:
    sol::state lua;
    std::unordered_map<std::string, sol::table> container;

    void BindLua();
    sol::table  LoadLuaFile(const std::string&);

    BodySpecMap bodySpecs;
    void LoadBodySpecs();

    LuaDataHolder& operator=(const LuaDataHolder&) = delete;
    LuaDataHolder& operator=(LuaDataHolder&&) = delete;
public:
    LuaDataHolder();

    const std::unordered_map<std::string, BodySpec>& GetBodySpecs(std::string);
};
