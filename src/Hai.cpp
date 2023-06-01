#include "Hai.h"
#include "fmt/core.h"

HaiSpec::HaiSpec(int haiType, int number) : haiType(haiType), number(number)
{
}

void HaiSpec::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<HaiSpec>("HaiSpec", sol::constructors<HaiSpec(int, int)>());

    haiType["HaiType"] = sol::property(&HaiSpec::GetHaiType);
    haiType["Number"] = sol::property(&HaiSpec::GetNumber);
}
int HaiSpec::GetNumber() const
{
    return number;
}

int HaiSpec::GetHaiType() const
{
    return haiType;
}

std::string HaiSpec::ToString() const
{
    return fmt::format("HaiSpec({}, {})", haiType, number);
}

void Hai::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<Hai>("Hai", sol::constructors<Hai(int, HaiSpec)>());

    haiType["Id"] = sol::property(&Hai::GetId);
    haiType["HaiSpec"] = sol::property(&Hai::GetHaiSpec);
    haiType["AddProperty"] = &Hai::AddProperty;
}

Hai::Hai(int id, HaiSpec haiSpec) : id{ id }, haiSpec{ haiSpec }
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

void Hai::AddProperty(int p)
{
    if (properties & p > 0) return;

    properties |= p;
}

bool Hai::IsIdentical(const Hai& hai) const
{
    return haiSpec == hai.haiSpec && properties == hai.properties;
}
