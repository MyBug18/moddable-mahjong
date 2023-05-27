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

    struct Hash
    {
        size_t operator()(const HaiSpec& obj) const
        {
            size_t seed = 0;
            seed ^= std::hash<int>()(obj.haiType) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<int>()(obj.number) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
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
