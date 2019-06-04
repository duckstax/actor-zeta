#include <actor-zeta/detail/string_view.hpp>
#include <ostream>

namespace std {

    std::ostream &operator<<(std::ostream &out, actor_zeta::detail::string_view str) {
        for (auto ch : str)
            out.put(ch);
        return out;
    }

    string to_string(actor_zeta::detail::string_view v) {
        return string(v.begin(), v.end()); /// TODO:
    }

}