#pragma once

#include <type_traits>
#include <cassert>

namespace actor_zeta { namespace base {

    class actor_abstract;

    template<typename actor_traits>
    class supervisor_abstract;

    /**
     * @class address_t
     * @brief A compact location expressor
     */
    class address_t final {
    public:
        using actor_ptr = actor_abstract*;
        template<typename actor_traits>
        using supervisor_ptr = supervisor_abstract<actor_traits>*;

        address_t(address_t&& other) noexcept;
        address_t(const address_t& other);

        address_t& operator=(address_t&& other) noexcept;
        address_t& operator=(const address_t& other);
        bool operator==(const address_t& rhs) noexcept;

        ~address_t() noexcept;

        /**
         * @brief Construct a new address t object
         *
         */
        explicit address_t(actor_ptr);

        /**
         * @brief Construct a new address t object
         *
         * @tparam actor_traits
         * @param ptr
         */
        template<typename actor_traits>
        explicit address_t(supervisor_ptr<actor_traits> ptr)
            : ptr_(ptr) {
            assert(ptr != nullptr);
        }

        static auto empty_address() -> address_t;

        /**
         * @brief
         *
         * @return actor_ptr
         */
        inline actor_ptr operator->() const noexcept {
            return ptr_;
        }

        operator bool() const noexcept;
        auto operator!() const noexcept -> bool;

        void swap(address_t& other);
        actor_ptr get() const;

    private:
        address_t() noexcept;
        actor_ptr ptr_;
    };

    static_assert(!std::is_default_constructible<address_t>::value, "");
    static_assert(std::is_move_constructible<address_t>::value, "");
    static_assert(std::is_move_assignable<address_t>::value, "");
    static_assert(std::is_copy_constructible<address_t>::value, "");
    static_assert(std::is_copy_assignable<address_t>::value, "");

}} // namespace actor_zeta::base
