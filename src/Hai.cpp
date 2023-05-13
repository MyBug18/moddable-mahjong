#include "Hai.h"
#include <iostream>

HaiSpec::HaiSpec(HaiType haiType, int number) : haiType(haiType), number(number)
{
}

void HaiSpec::BindLua(sol::state &lua)
{
    lua["HaiType"] = lua.create_table_with(
        "Wan", HaiType::Wan,
        "Sou", HaiType::Sou,
        "Pin", HaiType::Pin,
        "Kaze", HaiType::Kaze,
        "Sangen", HaiType::Sangen);

    auto haiType = lua.new_usertype<HaiSpec>("HaiSpec", sol::constructors<HaiSpec(HaiType, int)>());

    haiType["HaiType"] = sol::property(&HaiSpec::GetHaiType);
    haiType["Number"] = sol::property(&HaiSpec::GetNumber);
}
int HaiSpec::GetNumber() const
{
    return number;
}

HaiType HaiSpec::GetHaiType() const
{
    return haiType;
}

void Hai::BindLua(sol::state &lua)
{
    auto haiType = lua.new_usertype<Hai>("Hai", sol::constructors<Hai(int, HaiSpec)>());

    haiType["Id"] = sol::property(&Hai::GetId);
    haiType["HaiSpec"] = sol::property(&Hai::GetHaiSpec);
    haiType["AddProperty"] = &Hai::AddProperty;
}

Hai::Hai(int id, HaiSpec haiSpec) : id{id}, haiSpec{haiSpec}
{
}

int Hai::GetId() const
{
    return id;
}

HaiSpec Hai::GetHaiSpec() const
{
    return haiSpec;
}

void Hai::Print() const
{
    std::cout << id << " " << std::endl;
}

const std::unordered_set<std::string> &Hai::GetProperties()
{
    return properties;
}

void Hai::AddProperty(const std::string &p)
{
    properties.insert(p);
}
