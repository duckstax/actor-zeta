#pragma once

#include <cassert>

#include <actor-zeta/base/priority.hpp>
#include <actor-zeta/detail/rtt.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>
#include <string>

namespace actor_zeta { namespace base {

    ///
    /// @brief
    ///

    class rtt_message final {
    public:
        rtt_message();
        rtt_message(const rtt_message&) = delete;
        rtt_message& operator=(const rtt_message&) = delete;
        rtt_message(rtt_message&& other) = default;
        rtt_message& operator=(rtt_message&&) = default;
        ~rtt_message() = default;
        rtt_message(address_t /*sender*/, std::string /*name*/);
        rtt_message(address_t /*sender*/, std::string /*name*/, detail::rtt /*body*/);
        rtt_message* next;
        rtt_message* prev;
        auto command() const noexcept -> detail::string_view;
        auto sender() & noexcept -> address_t&;
        auto sender() && noexcept -> address_t&&;
        auto sender() const& noexcept -> address_t const&;

        /*template<typename T>
        auto body() const -> const T& {
            assert(body_.has_value());
            return detail::any_cast<const T&>(body_);
        }

        template<typename T>
        auto body() -> T& {
            assert(body_.has_value());
            return detail::any_cast<T&>(body_);
        }*/

        auto body() -> detail::rtt&;
        auto clone() const -> rtt_message*;
        operator bool();
        void swap(rtt_message& other) noexcept;
        bool is_high_priority() const;

    private:
        address_t sender_;
        std::string command_;
        detail::rtt body_;
        priority priority_ = priority::normal;
    };

    static_assert(std::is_move_constructible<rtt_message>::value, "");
    static_assert(not std::is_copy_constructible<rtt_message>::value, "");

}} // namespace actor_zeta::base

inline void swap(actor_zeta::base::rtt_message& lhs, actor_zeta::base::rtt_message& rhs) noexcept {
    lhs.swap(rhs);
}
