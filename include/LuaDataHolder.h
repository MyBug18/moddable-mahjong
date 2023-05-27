#include "Body.h"
#include "TenpaiSpec.h"

class LuaDataHolder
{
private:
    sol::state lua;
    std::unordered_map<std::string, sol::table> container;

    void BindLua();
    sol::table LoadLuaFile(const std::string&);

    std::unordered_map<std::string, std::vector<BodySpec>> bodySpecs;
    void LoadBodySpecs();

    std::vector<TenpaiSpec> tenpaiSpecs;
    void LoadTenpaiSpecs();

    LuaDataHolder& operator=(const LuaDataHolder&) = delete;
public:
    LuaDataHolder();

    static const LuaDataHolder& GetInstance();

    const std::vector<BodySpec>& GetBodySpecs(std::string) const;
    const std::vector<TenpaiSpec>& GetTenpaiSpecs() const
    {
        return tenpaiSpecs;
    }
};
