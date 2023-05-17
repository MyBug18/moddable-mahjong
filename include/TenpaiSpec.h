#pragma once

#include "Body.h"
#include <unordered_map>

class ShangtenInfo
{

};

class TenpaiSpec
{
private:
    std::string name;
    std::unordered_map<std::string, int> components;

public:
    TenpaiSpec(const sol::table&);

    ShangtenInfo GetShangten(const std::vector<Hai*>&);
};
