#include "LuaDataHolder.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

void DoFileRecursively(std::string directory, std::function<void(std::string)> cb)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (fs::is_directory(entry))
        {
            // Recursively load files from subdirectory
            DoFileRecursively(entry.path(), cb);
            return;
        }

        cb(entry.path());
    }
}

sol::table LuaDataHolder::LoadLuaFile(const std::string& dir)
{
    const sol::table& table = lua.script_file(dir);

    container[dir] = table;
    return table;
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

    LoadBodySpecs();
}

void LuaDataHolder::LoadBodySpecs()
{
    DoFileRecursively("./Resource/Lua/BodySpec", [this](std::string path)
        {
            const auto& table = LoadLuaFile(path);
            const auto& bodySpec = BodySpec(table);

            auto& name = bodySpec.GetName();
            auto& bodyType = bodySpec.GetBodyType();

            bodySpecs[bodyType].emplace(name, bodySpec);
        });
}

const std::unordered_map<std::string, BodySpec>& LuaDataHolder::GetBodySpecs(std::string bodyType)
{
    return bodySpecs[bodyType];
}
