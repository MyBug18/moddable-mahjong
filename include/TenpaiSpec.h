#pragma once

#include "HaiCandidates.h"
#include <unordered_map>

class TenpaiSpec
{
private:
    std::string name;
    std::unordered_map<std::string, int> components;

public:
    const HaiCandidates& GetShangten(const std::vector<Hai*>&, std::unordered_map<std::string, int>*);
};
