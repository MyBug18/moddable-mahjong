#include <vector>
#include <memory>

class Hai;

namespace sol
{
    class state;
}

class Player
{
private:
    std::vector<Hai *> freeHais;

public:
    const static void
    BindLua(sol::state &);
};