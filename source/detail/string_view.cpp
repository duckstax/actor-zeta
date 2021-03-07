#include <actor-zeta/detail/string_view.hpp>

#if CPP17_OR_GREATER

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

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
namespace actor_zeta { namespace  detail {
        int string_view::compare(actor_zeta::detail::string_view str) const noexcept {
            auto s0 = size();
            auto s1 = str.size();
            auto fallback = [](int x, int y) {
                return x == 0 ? y : x;
            };
            if (s0 == s1)
                return strncmp(data(), str.data(), s0);
            else if (s0 < s1)
                return fallback(strncmp(data(), str.data(), s0), -1);
            return fallback(strncmp(data(), str.data(), s1), 1);
        }

    }}

#endif