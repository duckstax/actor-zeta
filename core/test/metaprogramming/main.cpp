#include <string>
#include <cstdint>
#include <typeinfo>
#include <type_traits>
#include <cassert>
#include <actor-zeta/detail/type_traits/type_list.hpp>

using namespace actor_zeta::type_traits;

int main() {
    using std::is_same;
    using l1 = type_list<int, float, std::string>;
    using r1 = type_list<std::string, float,int>;
    assert((is_same<int, type_list_at<l1, 0>::type>::value));
    assert((is_same<float, type_list_at<l1, 1>::type>::value));
    assert((is_same<std::string, type_list_at<l1, 2>::type>::value));
    assert(3u == type_list_size<l1>::value);
    assert(type_list_size<r1>::value == type_list_size<l1>::value);
    assert((is_same<type_list_at<l1, 0>::type, type_list_at<r1, 2>::type>::value));
    assert((is_same<type_list_at<l1, 1>::type, type_list_at<r1, 1>::type>::value));
    assert((is_same<type_list_at<l1, 2>::type, type_list_at<r1, 0>::type>::value));
}
