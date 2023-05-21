#pragma once

#include "sol/sol.hpp"
#include <string>

class HaiSpec
{
private:
    int haiType;
    int number;

public:
    static void BindLua(sol::state&);

    bool operator==(const HaiSpec&) const;

    HaiSpec(int, int);

    int GetNumber() const;
    int GetHaiType() const;
};

class Hai
{
private:
    int id;

    HaiSpec haiSpec;

    // bitmask
    int properties;

public:
    static void BindLua(sol::state&);

    Hai(int, HaiSpec);

    int GetId() const;
    HaiSpec GetHaiSpec() const;

    void Print() const;

    void AddProperty(int);

    bool IsIdentical(const Hai&) const;
};
