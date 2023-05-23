#pragma once

#include "Hai.h"
#include <string>
#include <vector>

class HaiCandidates
{
private:
    const std::vector<const Hai*>& components;

    std::vector<HaiSpec> candidates;
    std::string formName;

public:
    static void BindLua(sol::state&)
    {
        auto haiType = lua.new_usertype<HaiCandidates>("HaiCandidates", sol::no_constructor);

        haiType["Name"] = sol::property(&HaiCandidates::GetName, &HaiCandidates::SetName);
        haiType["PushHai"] = &HaiCandidates::PushHai;
    }

    HaiCandidates(const std::vector<const Hai*>& components) : components{ components }
    {

    }

    void PushHai(HaiSpec spec)
    {
        candidates.push_back(spec);
    }

    const std::vector<HaiSpec>& GetSpecs() const
    {
        return candidates;
    }

    void SetName(std::string formName)
    {
        this->formName = formName;
    }

    const std::string& GetName() const
    {
        return formName;
    }
};
