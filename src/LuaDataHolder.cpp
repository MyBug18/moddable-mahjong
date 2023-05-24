#include "LuaDataHolder.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <functional>

#include "ROContainer/ROVector.h"

std::unique_ptr<LuaDataHolder> instance;

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

void BindROContainers(sol::state& lua)
{
    ROVector<const Hai*>::BindLua(lua);
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
    BodyCandidate::BindLua(lua);
    Hai::BindLua(lua);

    BindROContainers(lua);
}

LuaDataHolder::LuaDataHolder()
{
    lua.open_libraries(sol::lib::base);
    BindLua();

    LoadBodySpecs();
}

const LuaDataHolder& LuaDataHolder::GetInstance()
{
    if (instance.get() == nullptr)
    {
        instance = std::make_unique<LuaDataHolder>();
    }

    return *(instance.get());
}

void LuaDataHolder::LoadBodySpecs()
{
    DoFileRecursively("./Resource/Lua/BodySpec", [this](std::string path)
        {
            const auto& table = LoadLuaFile(path);
            const auto& bodySpec = BodySpec(table);

            auto& name = bodySpec.GetName();
            auto& bodyType = bodySpec.GetBodyType();

            bodySpecs[bodyType].emplace_back(bodySpec);
        });
}

const std::vector<BodySpec>& LuaDataHolder::GetBodySpecs(std::string bodyType) const
{
    return bodySpecs.at(bodyType);
}
