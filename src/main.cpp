


#include <iostream>
#include "LuaDataHolder.h"
#include "Body.h"
#include "ROContainer/ROVector.h"
#include "ROContainer/ROSet.h"
#include "CandidateExtractor.h"

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
    ROVector<int>::BindLua(lua);

    std::unordered_set<int> set;
    ROSet df(set);

    set.insert(1);
    set.insert(4);
    set.insert(3);
    set.insert(1);
    set.insert(1);

    lua.set("a", df);
    sol::table res = lua.script_file("./Resource/Lua/test.lua");

    int d = res["res"];
    std::cout << d << std::endl;
}
