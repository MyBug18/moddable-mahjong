#pragma once

#include <unordered_set>
#include <string>
#include "sol/sol.hpp"

enum HaiType
{
    Wan,
    Sou,
    Pin,
    Kaze,
    Sangen,
};

class HaiSpec
{
private:
    HaiType haiType;
    int number;

public:
    static void BindLua(sol::state &);

    HaiSpec(HaiType, int);

    int GetNumber() const;
    HaiType GetHaiType() const;
};

class Hai
{
private:
    int id;

    HaiSpec haiSpec;

    std::unordered_set<std::string> properties;

public:
    static void BindLua(sol::state &);

    Hai(int, HaiSpec);

    int GetId() const;
    HaiSpec GetHaiSpec() const;

    void Print() const;

    const std::unordered_set<std::string> &GetProperties();

    void AddProperty(const std::string &);
};
