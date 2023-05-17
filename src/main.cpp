#include <iostream>
#include "LuaDataHolder.h"
#include "sol/sol.hpp"
#include "Body.h"

int main(int, char**)
{
    LuaDataHolder lua;

    auto specs = lua.GetBodySpecs("triplet");
    auto spec = specs[0];

    auto hai = Hai(4, HaiSpec(HaiType::Wan, 5));
    auto vec = std::vector<Hai*>{ &hai };
}
