#pragma once

#include "Body.h"
#include <unordered_map>
#include <memory>

class ShangtenInfo
{
private:
    std::vector<const BodyCandidate*> bodyCandidates;

    ShangtenInfo& operator=(const ShangtenInfo&) = delete;
    ShangtenInfo& operator=(ShangtenInfo&&) = delete;

public:
    ~ShangtenInfo();

    BodyCandidate* NewBodyCandidate();

    const std::vector<const BodyCandidate*>& GetBodyCandidates() const
    {
        return bodyCandidates;
    }
};

class TenpaiSpec
{
private:
    std::string name;
    std::unordered_map<std::string, int> components;

public:
    TenpaiSpec(const sol::table&);

    std::unique_ptr<ShangtenInfo> GetShangten(const std::vector<const Hai*>&);
};
