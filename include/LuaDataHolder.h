#include "Body.h"

class LuaDataHolder
{
private:
    sol::state lua;
    std::unordered_map<std::string, sol::table> container;

    void BindLua();
    sol::table LoadLuaFile(const std::string&);

    std::unordered_map<std::string, std::vector<BodySpec>> bodySpecs;
    void LoadBodySpecs();

    LuaDataHolder& operator=(const LuaDataHolder&) = delete;
    LuaDataHolder& operator=(LuaDataHolder&&) = delete;
public:
    LuaDataHolder();

    static const LuaDataHolder& GetInstance();

    const std::vector<BodySpec>& GetBodySpecs(std::string) const;
};
