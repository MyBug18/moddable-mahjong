#include <iostream>
#include "LuaDataHolder.h"
#include "Body.h"

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

    int* a = new int(5);
    lua.set("a", a);
    sol::table res = lua.script_file("./Resource/Lua/test.lua");

    int d = res["res"];

    std::cout << d << " " << *a << std::endl;
}
