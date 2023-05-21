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
    auto& lua = LuaDataHolder::GetInstance();
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

void GetAllCandidates(const BodySpec& bodySpec, const std::vector<Hai*>& hais, std::vector<BodyCandidate>& output)
{
    for (auto i = 0; i < hais.size(); i++)
    {
        auto curHai = hais[i];
    }
}