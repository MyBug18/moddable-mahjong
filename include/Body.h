#pragma once

#include <string>
#include <unordered_set>
#include <functional>
#include "FinalFormExtractor.h"

class BodyCandidate final
{
private:
    std::vector<HaiSpec> componentHais;
    std::vector<HaiSpec> candidateHais;

public:
    BodyCandidate() = default;

    BodyCandidate(const BodyCandidate& obj)
    {
        // only copy existing components
        this->componentHais = obj.componentHais;
    }

    void PushCandidate(HaiSpec h)
    {
        candidateHais.push_back(h);
    }

    const std::vector<HaiSpec>& GetComponentHais() const
    {
        return componentHais;
    }

    const std::vector<HaiSpec>& GetCandidateHais() const
    {
        return candidateHais;
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

    int GetCompleteCount() const
    {
        return completeCount;
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
