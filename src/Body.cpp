#include "Body.h"

BodySpec::BodySpec(const sol::table &table)
{
    name = table["Name"];
    bodyType = table["BodyType"];

    sol::table propertiesRaw = table["Properties"];

    for (auto &pair : propertiesRaw)
    {
        properties.insert(pair.second.as<std::string>());
    }

    shouldFuro = table["ShouldFuro"];
    getCandidates = table["GetCandidates"];
}

const HaiCandidates &BodySpec::GetCandidates(const std::vector<Hai *> &hais)
{
    return getCandidates(hais);
}

Body::Body(const BodySpec &spec) : bodySpec(spec)
{
}