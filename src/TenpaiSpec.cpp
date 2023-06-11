#include "TenpaiSpec.h"
#include "LuaDataHolder.h"
#include "CandidateExtractor.h"
#include "Enumerator.h"
#include <queue>
#include <stack>

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
    std::vector<std::tuple<BodyCandidate, int>> bodies;

    std::vector<std::vector<std::tuple<BodyCandidate, int>>> totalCandidates;

    std::unordered_map<HaiSpec, int, HaiSpec::Hash> leftHaiCount;

    std::unordered_map<std::string, int> componentLeftCount;
};

struct HaiSpecVectorHash
{
    std::size_t operator()(const std::vector<HaiSpec>& key) const
    {
        HaiSpec::Hash hasher;
        size_t seed = 0;

        for (auto h : key)
        {
            seed ^= hasher(h) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        return seed;
    }
};

std::unique_ptr<ShangtenInfoHolder> TenpaiSpec::GetShangten(const std::vector<const Hai*>& hais)
{
    auto& lua = LuaDataHolder::GetInstance();
    auto result = std::make_unique<ShangtenInfoHolder>();
    auto holder = result.get();

    std::stack<ShangtenProcessor> stack;

    stack.push(ShangtenProcessor());
    auto& initValue = stack.top();

    auto& map = initValue.leftHaiCount;

    for (auto h : hais)
    {
        auto haiSpec = h->GetHaiSpec();
        map[haiSpec] = map.contains(haiSpec) ? map[haiSpec] + 1 : 1;
    }

    std::unordered_map<const BodySpec*, std::unordered_map<std::vector<HaiSpec>, std::vector<HaiSpec>, HaiSpecVectorHash>> candidatesHolder;

    for (auto& componentsKv : components)
    {
        auto& bodyType = componentsKv.first;

        auto& bodySpecs = lua.GetBodySpecs(bodyType);

        for (auto& bodySpec : bodySpecs)
        {
            auto& candidateMap = candidatesHolder[&bodySpec];

            for (const auto& haiCountKv : map)
            {
                auto extractor = FinalFormExtractor(haiCountKv.first);
                auto&& finalForms = extractor.GetFinalForms(map);
            }
        }
    }

    initValue.componentLeftCount = components;

    while (!stack.empty())
    {

    }

    return result;
}
