#include "TenpaiSpec.h"
#include "LuaDataHolder.h"
#include "CandidateExtractor.h"
#include <queue>
#include <tuple>
#include <coroutine>

BodyCandidate* ShangtenInfo::NewBodyCandidate()
{
    auto result = new BodyCandidate();

    bodyCandidates.push_back(result);

    return result;
}

BodyCandidate* ShangtenInfo::NewBodyCandidate(const BodyCandidate* from)
{
    auto result = new BodyCandidate(*from);

    bodyCandidates.push_back(result);

    return result;
}

TenpaiSpec::TenpaiSpec(const sol::table& table) : name{ table["Name"] }
{
    sol::table componentsRaw = table["Properties"];

    for (auto& pair : componentsRaw)
    {
        components[pair.first.as<std::string>()] = pair.second.as<int>();
    }
}

struct ShangtenProcessor
{
    std::unordered_map<std::string, int> compLeftCount;
};

void GetAll(const std::vector<const Hai*>& hais, ShangtenInfoHolder& output)
{

}

std::unique_ptr<ShangtenInfoHolder> TenpaiSpec::GetShangten(const std::vector<const Hai*>& hais)
{
    auto& lua = LuaDataHolder::GetInstance();
    auto result = std::make_unique<ShangtenInfoHolder>();
    auto holder = result.get();

    for (int i = 0; i < hais.size(); i++)
    {
        auto curHai = hais[i];
    }


    return result;
}
