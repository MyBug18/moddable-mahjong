#pragma once

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

    std::vector<std::unordered_map<HaiSpec, int, HaiSpec::Hash>> GetFinalForms(std::unordered_map<HaiSpec, int, HaiSpec::Hash> haiCounts)
    {
        std::vector<std::unordered_map<HaiSpec, int, HaiSpec::Hash>> result;

        for (auto& finalForm : finalForms)
        {
            for (auto& haiCountKv : haiCounts)
            {

            }
        }
    }

    HaiSpec GetHaiSpec()
    {
        return initialHaiSpec;
    }
};
