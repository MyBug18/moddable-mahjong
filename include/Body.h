#pragma once

#include "HaiCandidates.h"
#include <vector>
#include <functional>

class BodySpec
{
private:
    std::string name;

    // menstu or toitsu
    std::string bodyType;

    // shunstu or koutsu
    std::unordered_set<std::string> properties;

    bool shouldFuro;

    std::function<const HaiCandidates& (const std::vector<Hai*>&)> getCandidates;

public:
    BodySpec(const sol::table&);

    const HaiCandidates& GetCandidates(const std::vector<Hai*>&);
};

class Body
{
private:
    std::vector<Hai*> hais;
    const BodySpec& bodySpec;
    bool isMenzen;

public:
    Body(const BodySpec&);
    const BodySpec& GetBodySpec() const;
};
