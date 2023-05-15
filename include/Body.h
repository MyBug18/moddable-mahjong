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

    std::function<const HaiCandidates& (Hai*, const std::vector<Hai*>&)> getCandidates;

public:
    BodySpec(const sol::table&);

    const std::string& GetName() const;
    const std::string& GetBodyType() const;

    const HaiCandidates& GetCandidates(Hai*, const std::vector<Hai*>&) const;
};

class BodyCandidate
{
private:
    std::string formName;
    std::unordered_set<Hai*> componentshais;
    std::unordered_set<Hai*> candidatesHais;
    int completeCount;

public:
    static void BindLua(sol::state&);

    void SetName(std::string);
    const std::string& GetName() const;

    void SetCompleteCount(int);
    int GetCompleteCount() const;

    void PushComponent(Hai*);
    void PushCandidate(Hai*);
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
