#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "forwards.hpp"
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    class communication_module
        : public ref_counted {
    public:
        communication_module() = delete;
        communication_module(const communication_module&) = delete;
        communication_module& operator=(const communication_module&) = delete;
        ~communication_module() override;

        auto type() const -> detail::string_view;
        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, scheduler::execution_unit*);
        auto current_message() -> message*;

    protected:
        communication_module(std::string);
        virtual auto current_message_impl() -> message* = 0;
        virtual void enqueue_base(message_ptr, scheduler::execution_unit*) = 0;

    private:
        const std::string type_;
    };

}} // namespace actor_zeta::base
