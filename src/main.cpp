#define SOL_ALL_SAFETIES_ON 1

#include <iostream>
#include "sol/sol.hpp"
#include "Body.h"

int main(int, char **)
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    Hai::BindLua(lua);
    HaiSpec::BindLua(lua);
    HaiCandidates::BindLua(lua);

    sol::table m1 = lua.script_file("./lua/test.lua");

    sol::table bodySpecTest = lua.script_file("./lua/BodySpec/Shuntsu.lua");
    auto spec = BodySpec(bodySpecTest);

    auto hai = Hai(4, HaiSpec(HaiType::Wan, 5));
    auto vec = std::vector<Hai *>{&hai};

    auto candidate = spec.GetCandidates(vec);

    for (auto &v : candidate.GetHais())
    {
        std::cout << v.GetNumber();
    }
}
