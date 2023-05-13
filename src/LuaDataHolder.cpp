#include "LuaDataHolder.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void LuaDataHolder::LoadLuaFiles(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (fs::is_directory(entry))
        {
            // Recursively load files from subdirectory
            LuaDataHolder::LoadLuaFiles(entry.path());
            return;
        }

        const sol::table& table = lua.script_file(entry.path());
        container[table["Name"]] = table;
    }
}

void LuaDataHolder::BindLua()
{
    HaiSpec::BindLua(lua);
    Hai::BindLua(lua);
    HaiCandidates::BindLua(lua);
}

LuaDataHolder::LuaDataHolder()
{
    lua.open_libraries(sol::lib::base);
    BindLua();
    LoadLuaFiles("./Resources/lua");
}

const sol::table& LuaDataHolder::GetLua(const std::string& name)
{
    return container[name];
}
