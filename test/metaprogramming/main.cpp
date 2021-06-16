#include <actor-zeta/detail/type_list.hpp>
#include <cassert>
#include <cstdint>
#include <string>
#include <type_traits>

int main() {
    using std::is_same;
    using namespace actor_zeta::type_traits;
    using l1 = type_list<int, float, std::string>;
    using r1 = type_list<std::string, float, int>;

    static_assert((is_same<int, type_list_at<l1, 0>::type>::value), "");
    static_assert((is_same<float, type_list_at<l1, 1>::type>::value), "");
    static_assert((is_same<std::string, type_list_at<l1, 2>::type>::value), "");
    static_assert(3u == type_list_size<l1>::value, "");
    static_assert(type_list_size<r1>::value == type_list_size<l1>::value, "");
    static_assert((is_same<type_list_at<l1, 0>::type, type_list_at<r1, 2>::type>::value), "");
    static_assert((is_same<type_list_at<l1, 1>::type, type_list_at<r1, 1>::type>::value), "");
    static_assert((is_same<type_list_at<l1, 2>::type, type_list_at<r1, 0>::type>::value), "");
}
