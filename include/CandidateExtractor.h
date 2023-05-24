#pragma once

#include <string>
#include "Hai.h"
#include "ROContainer/ROVector.h"

class CandidateExtractor
{
private:
    ROVector<const Hai*> components;

    std::vector<HaiSpec> candidates;
    std::string formName;

    ROVector<const Hai*> GetComponents()
    {
        return components;
    }

public:
    static void BindLua(sol::state& lua)
    {
        auto haiType = lua.new_usertype<CandidateExtractor>("CandidateExtractor", sol::no_constructor);

        haiType["Hais"] = sol::property(&CandidateExtractor::GetComponents);
        haiType["Name"] = sol::property(&CandidateExtractor::GetName, &CandidateExtractor::SetName);
        haiType["PushHai"] = &CandidateExtractor::PushHai;
    }

    CandidateExtractor(const std::vector<const Hai*>& components) :components{ ROVector<const Hai*>(components) }
    {

    }

    void PushHai(HaiSpec spec)
    {
        candidates.push_back(spec);
    }

    void Sort()
    {
        std::sort(candidates.begin(), candidates.end(), [](HaiSpec a, HaiSpec b)
            {
                return a < b;
            });
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
