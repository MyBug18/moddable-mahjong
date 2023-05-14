#include "Body.h"

typedef std::function<const HaiCandidates& (const std::vector<Hai*>&)> GetCandidateFunc;

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

const HaiCandidates& BodySpec::GetCandidates(const std::vector<Hai*>& hais) const
{
    return getCandidates(hais);
}

Body::Body(const BodySpec& spec) : bodySpec(spec)
{
}
