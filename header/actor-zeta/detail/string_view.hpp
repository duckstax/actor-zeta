#pragma once

#include <actor-zeta/config.hpp>

#if CPP17_OR_GREATER

#include <string_view>

namespace actor_zeta { namespace detail {

    using std::basic_string_view;
    using std::string_view;
    using std::u16string_view;
    using std::u32string_view;
    using std::wstring_view;

    using std::operator==;
    using std::operator!=;
    using std::operator<;
    using std::operator<=;
    using std::operator>;
    using std::operator>=;

    using std::operator<<;

}} // namespace actor_zeta::detail

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <type_traits>

namespace actor_zeta { namespace detail {
    /// Drop-in replacement for C++17 std::string_view.
    namespace implementation {
        template<typename CharT>
        inline constexpr std::size_t length(const CharT* s, std::size_t result = 0) {
            return *s == '\0' ? result : length(s + 1, result + 1);
        }
    } // namespace implementation

    class string_view final {
    public:
        using value_type = char;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using const_iterator = const_pointer;
        using iterator = const_iterator;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = const_reverse_iterator;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        static_assert((!std::is_array<value_type>::value), "Character type of basic_string_view must not be an array");
        static_assert((std::is_standard_layout<value_type>::value), "Character type of basic_string_view must be standard-layout");
        static_assert((std::is_trivial<value_type>::value), "Character type of basic_string_view must be trivial");

        constexpr string_view() noexcept
            : data_(nullptr)
            , size_(0) {}

        constexpr string_view(const string_view& other) noexcept = default;

        string_view& operator=(const string_view&) = default;

        constexpr string_view(const char* cstr, size_t length) noexcept
            : data_(cstr)
            , size_(length) {}

#if defined(__GNUC__)
        constexpr string_view(const char* cstr) noexcept
            : data_(cstr)
            , size_(implementation::length<char>(cstr)) {
        }
#else
        template<size_t N>
        constexpr string_view(const char (&cstr)[N]) noexcept
            : data_(cstr)
            , size_(N - 1) {
        }
#endif

        constexpr size_type size() const noexcept {
            return size_;
        }

        constexpr size_type length() const noexcept {
            return size_;
        }

        constexpr size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }

        constexpr bool empty() const noexcept {
            return size_ == 0;
        }

        constexpr const_pointer data() const noexcept {
            return data_;
        }

        constexpr const_iterator begin() const noexcept {
            return data_;
        }

        constexpr const_iterator end() const noexcept {
            return data_ + size_;
        }

        constexpr const_iterator cbegin() const noexcept {
            return begin();
        }

        constexpr const_iterator cend() const noexcept {
            return end();
        }

        int compare(string_view str) const noexcept;

    private:
        const char* data_;
        size_t size_;
    };

    inline constexpr bool operator==(string_view lhs, string_view rhs) {
        return (lhs.size() == rhs.size()) && (lhs.compare(rhs) == 0);
    }

    inline constexpr bool operator!=(string_view lhs, string_view rhs) {
        return !(lhs == rhs);
    }

}} // namespace actor_zeta::detail

#include <string>

namespace std {

    string to_string(actor_zeta::detail::string_view v);

    std::ostream& operator<<(std::ostream& out, actor_zeta::detail::string_view);

    template<>
    struct hash<actor_zeta::detail::string_view> final {
        size_t operator()(const actor_zeta::detail::string_view& x) const noexcept {
            auto p = x.cbegin();
            auto end = x.cend();
            uint32_t result = 2166136261U; // We implement an FNV-like string hash.
            while (p != end)
                result = (result * 16777619) ^ (uint8_t) *p++;
            return static_cast<size_t>(result);
        }
    };
} // namespace std

#endif
