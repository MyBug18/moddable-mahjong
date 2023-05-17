#include "TenpaiSpec.h"
#include "LuaDataHolder.h"

TenpaiSpec::TenpaiSpec(const sol::table& table) : name{ table["Name"] }
{
    sol::table componentsRaw = table["Properties"];

    for (auto& pair : componentsRaw)
    {
        components[pair.first.as<std::string>()] = pair.second.as<int>();
    }
}

ShangtenInfo TenpaiSpec::GetShangten(const std::vector<Hai*>& hais)
{
    LuaDataHolder lua;
    ShangtenInfo result;

    for (auto& bodyType : components)
    {
        if (!components.contains(bodyType.first)) continue;

        for (auto& bodySpec : lua.GetBodySpecs(bodyType.first))
        {
            // bodyspecs: shuntsu, toitsu

        }
    }

    return result;
}
