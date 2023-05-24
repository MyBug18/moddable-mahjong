#include "Body.h"
#include <algorithm>

BodySpec::BodySpec(const sol::table& table) : name{ table["Name"] }, bodyType{ table["BodyType"] }
{
    sol::table propertiesRaw = table["Properties"];

    for (auto& pair : propertiesRaw)
    {
        properties.insert(pair.second.as<std::string>());
    }

    auto val = table.get<sol::optional<sol::object>>("CompleteCount");
    if (val)
    {
        completeCount = val.value().as<int>();
    }

    val = table.get<sol::optional<sol::object>>("GetCandidates");
    if (val)
    {
        getCandidates = val.value().as<std::function<bool(CandidateExtractor&)>>();
        shouldFuro = false;
    }
    else
    {
        shouldFuro = true;
    }
}

std::vector<Hai*> ReverseCopy(std::vector<Hai*> input)
{
    auto output = input;
    std::reverse(output.begin(), output.end());

    return output;
}

void BodyCandidate::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<BodyCandidate>("BodyCandidate");

    haiType["Name"] = sol::property(&BodyCandidate::GetName, &BodyCandidate::SetName);
    haiType["ComponentHais"] = sol::property(&BodyCandidate::GetComponentHaisLua);
    haiType["PushCandidate"] = &BodyCandidate::PushCandidate;
}
