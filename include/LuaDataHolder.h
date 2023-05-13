#include "Body.h"

class LuaDataHolder
{
private:
    sol::state lua;
    std::unordered_map<std::string, sol::table> container;

    void BindLua();
    void LoadLuaFiles(std::string);

    LuaDataHolder& operator=(const LuaDataHolder&) = delete;
    LuaDataHolder& operator=(LuaDataHolder&&) = delete;
public:
    LuaDataHolder();
    const sol::table& GetLua(const std::string&);
};