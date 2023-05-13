#include "HaiCandidates.h"

void HaiCandidates::BindLua(sol::state& lua)
{
    auto haiType = lua.new_usertype<HaiCandidates>("HaiCandidates", sol::constructors<HaiCandidates()>());

    haiType["CompleteCount"] = sol::property(&HaiCandidates::GetCompleteCount, &HaiCandidates::SetCompleteCount);
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

int HaiCandidates::GetCompleteCount() const
{
    return completeCount;
}

void HaiCandidates::SetCompleteCount(int n)
{
    completeCount = n;
}

int HaiCandidates::GetLength()
{
    return hais.size();
}
