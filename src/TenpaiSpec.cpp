#include "TenpaiSpec.h"
#include "LuaDataHolder.h"

BodyCandidate* ShangtenInfo::NewBodyCandidate()
{
    auto result = new BodyCandidate();

    bodyCandidates.push_back(result);

    return result;
}

ShangtenInfo::~ShangtenInfo()
{
    for (auto& ptr : bodyCandidates)
    {
        delete ptr;
    }
}

TenpaiSpec::TenpaiSpec(const sol::table& table) : name{ table["Name"] }
{
    sol::table componentsRaw = table["Properties"];

    for (auto& pair : componentsRaw)
    {
        components[pair.first.as<std::string>()] = pair.second.as<int>();
    }
}

void ExtractFromHai(const BodySpec& bodySpec, const std::vector<const Hai*>& hais, ShangtenInfo* output, int index)
{
    auto bodyCandidate = output->NewBodyCandidate();
}

void GetAllCandidates(const BodySpec& bodySpec, const std::vector<const Hai*>& hais, ShangtenInfo* output)
{
    for (auto i = 0; i < hais.size(); i++)
    {
        auto curHai = hais[i];


    }
}

std::unique_ptr<ShangtenInfo> TenpaiSpec::GetShangten(const std::vector<const Hai*>& hais)
{
    auto& lua = LuaDataHolder::GetInstance();
    auto result = std::make_unique<ShangtenInfo>();

    for (auto& bodyType : components)
    {
        if (!components.contains(bodyType.first)) continue;

        for (auto& bodySpec : lua.GetBodySpecs(bodyType.first))
        {
            // bodyspecs: shuntsu, toitsu
            GetAllCandidates(bodySpec, hais, result.get());

        }
    }

    return result;
}
