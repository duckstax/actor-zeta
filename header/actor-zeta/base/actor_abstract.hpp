#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>
#include <new>

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
    };

}} // namespace actor_zeta::base
