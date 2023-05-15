#include "Body.h"

typedef std::function<const HaiCandidates& (Hai*, const std::vector<Hai*>&)> GetCandidateFunc;

BodySpec::BodySpec(const sol::table& table)
{
    name = table["Name"];
    bodyType = table["BodyType"];

    sol::table propertiesRaw = table["Properties"];

    for (auto& pair : propertiesRaw)
    {
        properties.insert(pair.second.as<std::string>());
    }

    auto val = table.get<sol::optional<sol::object>>("GetCandidates");

    if (val)
    {
        getCandidates = val.value().as<GetCandidateFunc>();
        shouldFuro = false;
    }
    else
    {
        shouldFuro = true;
    }
}

const std::string& BodySpec::GetName() const
{
    return name;
}

const std::string& BodySpec::GetBodyType() const
{
    return bodyType;
}

const HaiCandidates& BodySpec::GetCandidates(Hai* hai, const std::vector<Hai*>& hais) const
{
    return getCandidates(hai, hais);
}

void BodyCandidate::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<BodyCandidate>("HaiCandidates", sol::constructors<BodyCandidate()>());

    haiType["Name"] = sol::property(&BodyCandidate::GetName, &BodyCandidate::SetName);
    haiType["CompleteCount"] = sol::property(&BodyCandidate::GetCompleteCount, &BodyCandidate::SetCompleteCount);
    haiType["PushComponent"] = &BodyCandidate::PushComponent;
    haiType["PushCandidate"] = &BodyCandidate::PushCandidate;
}

const std::string& BodyCandidate::GetName() const
{
    return formName;
}

void BodyCandidate::SetName(std::string name)
{
    formName = name;
}

int BodyCandidate::GetCompleteCount() const
{
    return completeCount;
}

void BodyCandidate::SetCompleteCount(int n)
{
    completeCount = n;
}

Body::Body(const BodySpec& spec) : bodySpec(spec)
{
}
