#pragma once

#include <new>
#include <string>
#include <utility>

#include "forwards.hpp"
#include "actor-zeta/scheduler/execution_unit.hpp"
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an actor
    ///

    class actor_abstract {
    public:
        actor_abstract() = delete;

        // allow placement new (only)
        void* operator new(std::size_t, void* ptr) {
            return ptr;
        }

        auto address() noexcept -> address_t;
        auto type() const -> detail::string_view;
        auto id() const -> int64_t;
        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, scheduler::execution_unit*);

    protected:
        // prohibit copies, assignments, and heap allocations
        void* operator new(size_t);
        void* operator new[](size_t);
        actor_abstract(const actor_abstract&) = delete;
        actor_abstract& operator=(const actor_abstract&) = delete;
        virtual ~actor_abstract();

        actor_abstract(std::string, int64_t);
        virtual void enqueue_impl(message_ptr, scheduler::execution_unit*) = 0;

    private:
        const std::string type_;
        const int64_t id_;
    };

}} // namespace actor_zeta::base
