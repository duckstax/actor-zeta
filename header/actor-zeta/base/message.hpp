#pragma once

#include <cassert>

#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>
#include <string>

namespace actor_zeta { namespace base {

    ///
    /// @brief
    ///

    enum class priority : int {
        normal = 0x00,
        high = 0x01
    };

    class message final {
    public:
        message();
        message(const message&) = delete;
        message& operator=(const message&) = delete;
        message(message&& other) = default;
        message& operator=(message&&) = default;
        ~message() = default;
        message(address_t /*sender*/, std::string /*name*/);
        message(address_t /*sender*/, std::string /*name*/, detail::any /*body*/);
        message* next;
        message* prev;
        auto command() const noexcept -> detail::string_view;
        auto sender() & noexcept -> address_t&;
        auto sender() && noexcept -> address_t&&;
        auto sender() const& noexcept -> address_t const&;

        template<typename T>
        auto body() const -> const T& {
            assert(body_.has_value());
            return detail::any_cast<const T&>(body_);
        }

        template<typename T>
        auto body() -> T& {
            assert(body_.has_value());
            return detail::any_cast<T&>(body_);
        }

        auto body() -> detail::any&;
        auto clone() const -> message*;
        operator bool();
        void swap(message& other) noexcept;
        bool is_high_priority() const;

    private:
        address_t sender_;
        std::string command_;
        detail::any body_;
        priority priority_ = priority::normal;
    };

    static_assert(std::is_move_constructible<message>::value, "");
    static_assert(not std::is_copy_constructible<message>::value, "");

}} // namespace actor_zeta::base

inline void swap(actor_zeta::base::message& lhs, actor_zeta::base::message& rhs) noexcept {
    lhs.swap(rhs);
}
