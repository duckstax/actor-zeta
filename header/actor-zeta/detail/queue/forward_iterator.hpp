#pragma once

namespace actor_zeta { namespace detail {

    template<class T>
    class forward_iterator {
    public:
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using node_type = typename std::conditional<std::is_const<T>::value,
                                                    const typename T::node_type,
                                                    typename T::node_type>::type;
        using node_pointer = node_type*;

        static auto promote(node_pointer ptr) noexcept -> pointer {
            return static_cast<pointer>(ptr);
        }

        constexpr forward_iterator(node_pointer init = nullptr)
            : ptr(init) {}

        forward_iterator(const forward_iterator&) = default;

        auto operator=(const forward_iterator&) -> forward_iterator& = default;

        auto next() -> forward_iterator {
            return ptr->next;
        }

        auto operator++() -> forward_iterator& {
            ptr = ptr->next;
            return *this;
        }

        auto operator++(int) -> forward_iterator {
            forward_iterator res = *this;
            ptr = ptr->next;
            return res;
        }

        auto operator*() -> reference {
            return *promote(ptr);
        }

        auto operator*() const -> const_reference {
            return *promote(ptr);
        }

        auto operator->() -> pointer {
            return promote(ptr);
        }

        auto operator->() const -> const_pointer {
            return promote(ptr);
        }

        node_pointer ptr;
    };


    template<class T>
    constexpr auto operator==(const forward_iterator<T>& x, const forward_iterator<T>& y) -> bool {
        return x.ptr == y.ptr;
    }

    template<class T>
    constexpr auto operator!=(const forward_iterator<T>& x, const forward_iterator<T>& y) -> bool {
        return !(x == y);
    }

}} // namespace actor_zeta::detail
