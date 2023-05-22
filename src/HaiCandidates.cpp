#include "HaiCandidates.h"

void HaiCandidates::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<HaiCandidates>("HaiCandidates", sol::constructors<HaiCandidates()>());

    haiType["Name"] = sol::property(&HaiCandidates::GetName, &HaiCandidates::SetName);
    haiType["PushHai"] = &HaiCandidates::PushHai;
}

void HaiCandidates::PushHai(HaiSpec spec)
{
    hais.push_back(spec);
}

const std::vector<HaiSpec>& HaiCandidates::GetHais()
{
    return hais;
}
