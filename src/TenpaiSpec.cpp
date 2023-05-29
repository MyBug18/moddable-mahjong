#include "TenpaiSpec.h"
#include "LuaDataHolder.h"
#include "CandidateExtractor.h"
#include <queue>
#include <coroutine>

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

struct CombinationGenerator
{
    struct promise_type
    {
        std::vector<int> currentCombination;
        
        auto get_return_object()
        {
            return CombinationGenerator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }
        
        auto final_suspend() noexcept
        {
            return std::suspend_always{};
        }
        
        void return_void() noexcept {}
        
        auto yield_value(std::vector<int> combination) noexcept
        {
            currentCombination = std::move(combination);
            return std::suspend_always{};
        }
        
        void unhandled_exception() 
        {
            std::terminate();
        }
    };
    
    std::coroutine_handle<promise_type> coro_handle;
    
    explicit CombinationGenerator(std::coroutine_handle<promise_type> handle) : coro_handle(handle) {}
    
    ~CombinationGenerator() 
    {
        if (coro_handle) 
        {
            coro_handle.destroy();
        }
    }
    
    bool move_next() 
    {
        coro_handle.resume();
        return !coro_handle.done();
    }
    
    const std::vector<int>& current_combination() const 
    {
        return coro_handle.promise().currentCombination;
    }
};

struct ShangtenProcessor
{
    std::unordered_map<std::string, int> compLeftCount;

    std::vector<const Hai*> currentHais;


};

struct CombHelper
{
    std::vector<HaiSpec> curHaiSpecs;
    int loopStartIndex;
};

std::vector<std::vector<HaiSpec>> GetAllCombination(HaiSpec base, std::unordered_map<HaiSpec, int, HaiSpec::Hash> haisMap)
{
    std::vector<std::vector<HaiSpec>> result;
    std::queue<CombHelper> queue;
    std::vector<HaiSpec> hais;

    if (haisMap.contains(base))
    {
        auto& count = haisMap[base];
        for (int i = 0; i < count; i++)
        {
            hais.push_back(base);
        }

        haisMap.erase(base);
    }

    for (auto& kv : haisMap)
    {
        for (int i = 0; i < kv.second; i++)
        {
            hais.emplace_back(kv.first);
        }   
    }

    CombHelper initial;
    initial.loopStartIndex = 1;
    initial.curHaiSpecs = hais;

    queue.push(initial);

    while (!queue.empty())
    {
        auto& cur = queue.front();
        result.push_back(cur.curHaiSpecs);

        HaiSpec prev(0, 0);

        for (auto i = cur.loopStartIndex; i < hais.size(); i++)
        {
            if (prev == hais[i]) continue;
            prev = hais[i];

            auto newHelper = cur;

            newHelper.curHaiSpecs.erase(newHelper.curHaiSpecs.begin() + i);
            newHelper.loopStartIndex = i + 1;

            queue.push(newHelper);
        }

        queue.pop();
    }

    return result;
}

void GetAll(const std::vector<const Hai*>& hais, int index, TenpaiSpec* tenpai, ShangtenInfoHolder& output)
{
    auto curHai = hais[index];
}

std::unique_ptr<ShangtenInfoHolder> TenpaiSpec::GetShangten(const std::vector<const Hai*>& hais)
{
    auto& lua = LuaDataHolder::GetInstance();
    auto result = std::make_unique<ShangtenInfoHolder>();
    auto holder = result.get();

    for (int i = 0; i < hais.size(); i++)
    {
        auto curHai = hais[i];
    }


    return result;
}
