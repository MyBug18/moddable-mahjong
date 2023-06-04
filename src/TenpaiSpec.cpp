#include "TenpaiSpec.h"
#include "LuaDataHolder.h"
#include "CandidateExtractor.h"
#include "Enumerator.h"
#include <queue>
#include <stack>

BodyCandidate* ShangtenInfo::NewBodyCandidate()
{
    auto result = new BodyCandidate();

    bodyCandidates.push_back(result);

    return result;
}

BodyCandidate* ShangtenInfo::NewBodyCandidate(const BodyCandidate* from)
{
    auto result = new BodyCandidate(*from);

    bodyCandidates.push_back(result);

    return result;
}

TenpaiSpec::TenpaiSpec(const sol::table& table) : name{ table["Name"] }
{
    sol::table componentsRaw = table["Properties"];

    for (auto& pair : componentsRaw)
    {
        components[pair.first.as<std::string>()] = pair.second.as<int>();
    }
}

struct CombHelper
{
    // nth element is removed from combination if the value is false.
    std::vector<bool> remains;

    int loopStartIndex;
};

Enumerator<std::vector<HaiSpec>> GetAllCombination(HaiSpec base, const std::unordered_map<HaiSpec, int, HaiSpec::Hash>& bodyHaiSpecMap)
{
    std::queue<CombHelper> queue;
    std::vector<HaiSpec> hais;

    for (auto& kv : bodyHaiSpecMap)
    {
        if (kv.first < base) continue;

        for (int i = 0; i < kv.second; i++)
        {
            hais.push_back(kv.first);
        }
    }

    std::sort(hais.begin(), hais.end(), [](HaiSpec a, HaiSpec b) { return a < b; });

    CombHelper initial;
    initial.loopStartIndex = 1;

    for (int i = 0; i < hais.size(); i++)
    {
        initial.remains.push_back(true);
    }

    queue.push(initial);

    while (!queue.empty())
    {
        auto cur = queue.front();
        queue.pop();

        std::vector<HaiSpec> result;

        for (int i = 0; i < hais.size(); i++)
        {
            if (!cur.remains[i]) continue;

            result.push_back(hais[i]);
        }

        co_yield result;

        HaiSpec prev(0, 0);

        for (auto i = cur.loopStartIndex; i < hais.size(); i++)
        {
            if (prev == hais[i]) continue;
            prev = hais[i];

            auto newHelper = cur;

            newHelper.remains[i] = false;
            newHelper.loopStartIndex = i + 1;

            queue.push(newHelper);
        }
    }
}

struct CandidateHolder
{
    BodySpec* bodySpec;

    Enumerator<std::vector<HaiSpec>>* enumerator;
};

struct CandidateHolderComparator
{
    bool operator()(CandidateHolder* a, CandidateHolder* b)
    {
        auto& vec1 = a->enumerator->current();
        auto& vec2 = b->enumerator->current();

        auto l1 = vec1.size();
        auto l2 = vec2.size();

        auto to1 = l1 - a->bodySpec->GetCompleteCount();
        auto to2 = l2 - b->bodySpec->GetCompleteCount();

        if (to1 == to2)
        {
            return l1 < l2;
        }

        return to1 < to2;
    }
};

class CombinationMerger
{
private:
    std::priority_queue<CandidateHolder*, std::vector<CandidateHolder*>, CandidateHolderComparator> holders;
    CandidateHolder* currentHolder;

public:
    void PushHolder(CandidateHolder* holder)
    {
        if (!holder->enumerator->move_next()) return;

        holders.push(holder);
        currentHolder = holders.top();
    }

    CandidateHolder* Current() const
    {
        return currentHolder;
    }

    bool MoveNext()
    {
        if (holders.size() == 0)
        {
            return false;
        }

        auto* cur = holders.top();
        holders.pop();

        if (cur->enumerator->move_next())
        {
            holders.push(cur);
        }

        currentHolder = holders.top();
        return true;
    }
};

struct ShangtenProcessor
{
    CombinationMerger* enumerator;

    int loopStartIndex;

    BodySpec* bodySpec;

    std::vector<std::vector<HaiSpec>> bodies;

    std::unordered_map<std::string, int> componentLeftCount;
};

std::unique_ptr<ShangtenInfoHolder> TenpaiSpec::GetShangten(const std::vector<const Hai*>& hais)
{
    auto& lua = LuaDataHolder::GetInstance();
    auto result = std::make_unique<ShangtenInfoHolder>();
    auto holder = result.get();

    std::stack<std::unique_ptr<ShangtenProcessor>> stack;

    while (!stack.empty())
    {
        auto lastProcessor = stack.top().get();



    }

    return result;
}
