#include "Hai.h"

#include <vector>
#include <unordered_map>

class FinalFormExtractor final
{
private:
    HaiSpec initialHaiSpec;

    std::vector<std::unordered_map<HaiSpec, int, HaiSpec::Hash>> finalForms;

    void PushForm(sol::table raw)
    {
        std::unordered_map<HaiSpec, int, HaiSpec::Hash> form;

        for (auto& kv : raw)
        {
            form[kv.first.as<HaiSpec>()] = kv.second.as<int>();
        }

        finalForms.push_back(std::move(form));
    }

public:
    static void BindLua(sol::state& lua)
    {
        auto haiType = lua.new_usertype<FinalFormExtractor>("FinalFormExtractor", sol::no_constructor);

        haiType["PushForm"] = &FinalFormExtractor::PushForm;
        haiType["HaiSpec"] = &FinalFormExtractor::GetHaiSpec;
    }

    FinalFormExtractor(HaiSpec spec) : initialHaiSpec{ spec }
    {

    }

    const std::vector<std::unordered_map<HaiSpec, int, HaiSpec::Hash>>& GetFinalForms()
    {
        return finalForms;
    }

    HaiSpec GetHaiSpec()
    {
        return initialHaiSpec;
    }
};
