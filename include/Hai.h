#pragma once

#include "sol/sol.hpp"

class HaiSpec
{
private:
    int haiType;
    int number;

public:
    static void BindLua(sol::state&);

    HaiSpec(int, int);

    int GetNumber() const;
    int GetHaiType() const;

    bool operator<(const HaiSpec& other) const
    {
        if (haiType == other.haiType)
        {
            return number < other.number;
        }

        return haiType < other.haiType;
    }

    bool operator==(const HaiSpec& other) const
    {
        return number == other.number && haiType == other.haiType;
    }

    bool operator!=(const HaiSpec& other) const
    {
        return !(*this == other);
    }

    bool operator<=(const HaiSpec& other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator>(const HaiSpec& other) const
    {
        return !(*this <= other);
    }

    bool operator>=(const HaiSpec& other) const
    {
        return !(*this < other);
    }
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
