#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "forwards.hpp"
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    class communication_module {
    public:
        communication_module() = delete;
        communication_module(const communication_module&) = delete;
        communication_module& operator=(const communication_module&) = delete;
        virtual ~communication_module();

        auto type() const -> detail::string_view;
        auto id() const -> int64_t ;

        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, scheduler::execution_unit*);

    protected:
        communication_module(std::string,int64_t);
        virtual void enqueue_impl(message_ptr, scheduler::execution_unit*) = 0;

    private:
        const std::string type_;
        const int64_t id_;
    };

}} // namespace actor_zeta::base
