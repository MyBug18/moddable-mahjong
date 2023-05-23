#pragma once

#include "Body.h"
#include <unordered_map>
#include <memory>

class ShangtenInfo final
{
private:
    std::vector<const BodyCandidate*> bodyCandidates;

    ShangtenInfo(const ShangtenInfo&) = delete;
    ShangtenInfo& operator=(const ShangtenInfo&) = delete;

public:
    ~ShangtenInfo();
    ShangtenInfo() = default;

    BodyCandidate* NewBodyCandidate();
    BodyCandidate* NewBodyCandidate(const BodyCandidate*);

    const std::vector<const BodyCandidate*>& GetBodyCandidates() const
    {
        return bodyCandidates;
    }
};

class TenpaiSpec final
{
private:
    std::string name;
    std::unordered_map<std::string, int> components;

    TenpaiSpec(const TenpaiSpec&) = delete;
    TenpaiSpec& operator=(const TenpaiSpec&) = delete;

public:
    TenpaiSpec(const sol::table&);

    std::unique_ptr<ShangtenInfo> GetShangten(const std::vector<const Hai*>&);
};
