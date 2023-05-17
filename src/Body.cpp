#include "Body.h"
#include <algorithm>

BodySpec::BodySpec(const sol::table& table) : name{ table["Name"] }
{
    bodyType = table["BodyType"];

    auto val = table.get<sol::optional<sol::object>>("CompleteCount");
    if (val)
    {
        completeCount = val.value().as<int>();
    }

    sol::table propertiesRaw = table["Properties"];

    for (auto& pair : propertiesRaw)
    {
        properties.insert(pair.second.as<std::string>());
    }

    val = table.get<sol::optional<sol::object>>("GetCandidates");
    if (val)
    {
        getCandidates = val.value().as<std::function<void(Hai*, BodyCandidate&)>>();
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

void BodySpec::GetCandidates(Hai* hai, BodyCandidate& hais) const
{
    return getCandidates(hai, hais);
}

std::vector<Hai*> ReverseCopy(std::vector<Hai*> input)
{
    auto output = input;
    std::reverse(output.begin(), output.end());

    return output;
}

void BodyCandidate::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<BodyCandidate>("HaiCandidates", sol::constructors<BodyCandidate()>());

    haiType["Name"] = sol::property(&BodyCandidate::GetName, &BodyCandidate::SetName);
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

void BodyCandidate::PushCandidate(Hai* h)
{
    candidatesHais.insert(h);
}


Body::Body(const BodySpec& spec) : bodySpec(spec)
{
}
