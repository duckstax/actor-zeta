#include <actor-zeta/detail/string_view.hpp>
#include <cassert>
#include <string>

using namespace actor_zeta::detail;

int main() {
    {
        string_view x;
        string_view y;
        assert(x.empty());
        assert(x.size() == 0u);
        assert(x.data() == nullptr);
        assert(y == y);
    }

    {
        string_view x("abc");
        assert(x.size() == 3u);
        assert(x == string_view("abc"));
    }
}