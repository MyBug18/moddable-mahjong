


#include <iostream>
#include "LuaDataHolder.h"
#include "Body.h"
#include "TenpaiSpec.h"
#include "ROContainer/ROVector.h"
#include "ROContainer/ROSet.h"
#include "CandidateExtractor.h"
#include <unordered_map>
#include "FinalFormExtractor.h"

std::vector<int> n()
{
    std::vector<int> a;
    a.push_back(2);
    a.push_back(3);

    return a;
}

int main(int, char**)
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    HaiSpec::BindLua(lua);

    sol::table res = lua.script_file("./Resource/Lua/test.lua");

    sol::table specs = res["a"];
    for (auto a : specs)
    {
        auto df = a.first.as<HaiSpec>();
        std::cout << df.GetNumber() << std::endl;
    }
}
