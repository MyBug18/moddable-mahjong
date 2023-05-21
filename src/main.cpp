#include <iostream>
#include "LuaDataHolder.h"
#include "Body.h"

int main(int, char**)
{
    auto specs = LuaDataHolder::GetInstance().GetBodySpecs("triplet");
    auto spec = specs[0];

    auto hai = Hai(4, HaiSpec(1, 5));
    auto vec = std::vector<Hai*>{ &hai };
}
