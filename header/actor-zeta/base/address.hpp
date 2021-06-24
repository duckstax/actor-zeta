#pragma once

#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief A compact location expressor
    ///
    class address_t final {
    public:
        address_t() noexcept;

        address_t(address_t&& other) noexcept;

        address_t(const address_t& other);

        address_t& operator=(address_t&& other) noexcept ;

        address_t& operator=(const address_t& other);

        ~address_t();

        explicit address_t(actor_abstract*);

        explicit address_t(supervisor_abstract*);

        address_t(std::nullptr_t) noexcept;

        auto enqueue(message_ptr) noexcept -> void;

        auto type() const -> detail::string_view;

        operator bool() const noexcept;

        auto operator!() const noexcept -> bool;

        void swap(address_t& other);
    private:
        enum class sub_type_t : char {
            none = 0x0,
            actor,
            supervisor
        };

        sub_type_t sub_type_;

        union pointer_t {
            actor_abstract* actor_;
            supervisor_abstract* supervisor_;

            pointer_t() {
            }

            pointer_t(actor_abstract* ptr)
                : actor_(ptr) {}

            pointer_t(supervisor_abstract* ptr)
                : supervisor_(ptr) {}

            void destroy(sub_type_t sub_type) noexcept {
                switch (sub_type) {
                    case sub_type_t::actor: {
                        actor_ = nullptr;
                        break;
                    }

                    case sub_type_t::supervisor: {
                        supervisor_ = nullptr;
                        break;
                    }

                    case sub_type_t::none: {
                        break;
                    }

                    default:
                        break;
                }
                actor_ = nullptr;
                supervisor_ = nullptr;
            }
        };
        pointer_t ptr_;
    };

    static_assert(std::is_default_constructible<address_t>::value, "");
    static_assert(std::is_move_constructible<address_t>::value, "");
    static_assert(std::is_move_assignable<address_t>::value, "");
    static_assert(std::is_copy_constructible<address_t>::value, "");
    static_assert(std::is_copy_assignable<address_t>::value, "");

}} // namespace actor_zeta::base
