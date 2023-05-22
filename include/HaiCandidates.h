#pragma once

#include "Hai.h"
#include <string>
#include <vector>

namespace sol
{
    class state;
}

class HaiCandidates
{
private:
    std::vector<HaiSpec> hais;
    std::string formName;

public:
    static void BindLua(sol::state&);

    void PushHai(HaiSpec);
    const std::vector<HaiSpec>& GetHais();

    void SetName(std::string formName)
    {
        this->formName = formName;
    }

    const std::string& GetName() const
    {
        return formName;
    }
};
