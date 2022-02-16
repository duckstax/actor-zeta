#pragma once

#include <cassert>

#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/mailbox/id.hpp>

namespace actor_zeta { namespace mailbox {

    ///
    /// @brief
    ///

    class message final {
    public:
        message();
        message(const message&) = delete;
        message& operator=(const message&) = delete;
        message(message&& other) = default;
        message& operator=(message&&) = default;
        ~message() = default;
        message(base::address_t /*sender*/, message_id /*name*/);
        message(base::address_t /*sender*/, message_id /*name*/, detail::any /*body*/);
        message* next;
        message* prev;
        auto command() const noexcept -> message_id;
        auto sender() & noexcept -> base::address_t&;
        auto sender() && noexcept -> base::address_t&&;
        auto sender() const& noexcept -> base::address_t const&;

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
        base::address_t sender_;
        message_id command_;
        detail::any body_;
    };

    static_assert(std::is_move_constructible<message>::value, "");
    static_assert(not std::is_copy_constructible<message>::value, "");

}} // namespace actor_zeta::mailbox

inline void swap(actor_zeta::mailbox::message& lhs, actor_zeta::mailbox::message& rhs) noexcept {
    lhs.swap(rhs);
}
