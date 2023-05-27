#pragma once

#include "Body.h"
#include <unordered_map>
#include <memory>
#include <tuple>

class ShangtenInfo final
{
private:
    std::vector<const BodyCandidate*> bodyCandidates;

public:
    BodyCandidate* NewBodyCandidate();
    BodyCandidate* NewBodyCandidate(const BodyCandidate*);

    const std::vector<const BodyCandidate*>& GetBodyCandidates() const
    {
        return bodyCandidates;
    }
};

class ShangtenInfoHolder final
{
private:
    std::vector<std::unique_ptr<BodyCandidate>> allBodyCandidates;

    std::vector<std::unique_ptr<ShangtenInfo>> shangtenInfos;

    ShangtenInfoHolder(const ShangtenInfoHolder&) = delete;
    ShangtenInfoHolder& operator=(const ShangtenInfoHolder&) = delete;

public:
    BodyCandidate* NewBodyCandidate()
    {
        auto ptr = std::make_unique<BodyCandidate>();
        auto result = ptr.get();

        allBodyCandidates.push_back(std::move(ptr));
        return result;
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

    std::unique_ptr<ShangtenInfoHolder> GetShangten(const std::vector<const Hai*>&);
};
