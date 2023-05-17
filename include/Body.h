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
    std::unordered_set<Hai*> componentshais;
    std::unordered_set<Hai*> candidatesHais;

public:
    static void BindLua(sol::state&);

    void SetName(std::string);
    const std::string& GetName() const;

    void PushCandidate(Hai*);
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

    std::function<void(Hai*, BodyCandidate&)> getCandidates;

    int completeCount;

public:
    BodySpec(const sol::table&);

    const std::string& GetName() const;
    const std::string& GetBodyType() const;

    void GetCandidates(Hai*, BodyCandidate&) const;
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
