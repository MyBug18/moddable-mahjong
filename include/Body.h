#pragma once

#include "Hai.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <functional>

class BodyCandidate
{
private:
    std::string formName;
    std::unordered_set<const Hai*> componentsHais;
    std::unordered_set<const Hai*> candidatesHais;

    void SetName(std::string);

public:
    static void BindLua(sol::state&);

    void PushCandidate(const Hai*);

    const std::unordered_set<const Hai*>& GetComponentHais() const;
    const std::string& GetName() const;
};

class BodySpec
{
private:
    std::string name;

    // menstu or toitsu
    std::string bodyType;

    // shunstu or koutsu
    std::unordered_set<std::string> properties;

    bool shouldFuro;

    std::function<bool(BodyCandidate&)> getCandidates;

    int completeCount;

public:
    BodySpec(const sol::table&);

    const std::string& GetName() const;
    const std::string& GetBodyType() const;

    bool GetCandidates(BodyCandidate&) const;
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
