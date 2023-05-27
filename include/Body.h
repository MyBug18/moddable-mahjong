#pragma once

#include <string>
#include <unordered_set>
#include <functional>
#include "FinalFormExtractor.h"

class BodyCandidate final
{
private:
    std::string formName;

    std::vector<const Hai*> componentHais;
    std::unordered_set<const Hai*> candidateHais;

    ROVector<const Hai*> GetComponentHaisLua()
    {
        return ROVector<const Hai*>(componentHais);
    }

public:
    BodyCandidate() = default;

    BodyCandidate(const BodyCandidate& obj)
    {
        // only copy existing components
        this->componentHais = obj.componentHais;
    }

    static void BindLua(sol::state&);

    void PushCandidate(const Hai* h)
    {
        candidateHais.insert(h);
    }

    const std::vector<const Hai*>& GetComponentHais() const
    {
        return componentHais;
    }

    const std::unordered_set<const Hai*>& GetCandidateHais() const
    {
        return candidateHais;
    }

    const std::string& GetName() const
    {
        return formName;
    }

    void SetName(std::string name)
    {
        formName = name;
    }
};

class BodySpec final
{
private:
    std::string name;

    // menstu or toitsu
    std::string bodyType;

    // shunstu or koutsu
    std::unordered_set<std::string> properties;

    bool shouldFuro;

    std::function<void(FinalFormExtractor&)> getCandidates;

    int completeCount;

public:
    BodySpec(const sol::table&);

    const std::string& GetName() const
    {
        return name;
    }

    const std::string& GetBodyType() const
    {
        return bodyType;
    }

    void GetCandidates(FinalFormExtractor& extractor) const
    {
        getCandidates(extractor);
    }
};

class Body
{
private:
    std::vector<Hai*> hais;
    const BodySpec& bodySpec;
    bool isMenzen;

public:
    Body(const BodySpec& spec) : bodySpec(spec)
    {

    }

    const BodySpec& GetBodySpec() const
    {
        return bodySpec;
    }
};
