#include "TenpaiSpec.h"
#include "LuaDataHolder.h"
#include <queue>
#include <tuple>

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

void GetAllCandidates(const BodySpec& bodySpec, const std::vector<const Hai*>& hais, ShangtenInfo* output)
{
    std::queue<std::tuple<BodyCandidate*, int>> queue;

    for (auto i = 0; i < hais.size(); i++)
    {
        auto curHai = hais[i];
        auto bodyCandidate = output->NewBodyCandidate();
        bodyCandidate->PushCandidate(curHai);
        queue.push(std::tuple(bodyCandidate, i));
    }

    while (!queue.empty())
    {
        auto cur = queue.front();
        queue.pop();

        auto curBodyCandidate = std::get<0>(cur);
        auto index = std::get<1>(cur);

        auto canProceed = bodySpec.GetCandidates(curBodyCandidate);

        if (!canProceed) continue;
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
