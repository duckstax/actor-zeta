#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/string_view.hpp>

#include <new>
#include <unordered_map>
#include <utility>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an actor
    ///

    class actor_abstract : public communication_module {
    public:
        actor_abstract() = delete;
        ~actor_abstract() override;

        // allow placement new (only)
        void* operator new(std::size_t, void* ptr) {
            return ptr;
        }

        auto address() noexcept -> address_t;
    protected:
        actor_abstract(std::string);
        // prohibit copies, assignments, and heap allocations
        void* operator new(size_t);
        void* operator new[](size_t);
        actor_abstract(const actor_abstract&) = delete;
        actor_abstract& operator=(const actor_abstract&) = delete;

        auto address_book(detail::string_view) -> address_t;
        auto address_book(std::string&) -> address_t;
        /**
        * debug method
        */
        auto all_view_address() const -> std::set<std::string>;

    private:
        void add_link();
        void remove_link();
        void add_link_impl(address_t&);
        void remove_link_impl(const address_t&);
        std::unordered_map<detail::string_view, address_t> contacts_;
    };

}} // namespace actor_zeta::base
