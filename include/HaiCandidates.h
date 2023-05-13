#include "Hai.h"
#include <vector>

namespace sol
{
    class state;
}

class HaiCandidates
{
private:
    std::vector<HaiSpec> hais;
    int completeCount;

public:
    static void BindLua(sol::state &);

    void PushHai(HaiSpec);
    const std::vector<HaiSpec> &GetHais();

    int GetCompleteCount() const;
    void SetCompleteCount(int);

    int GetLength();
};