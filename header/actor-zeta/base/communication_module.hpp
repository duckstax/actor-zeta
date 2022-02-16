#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta {
    namespace mailbox {
        using message_ptr = std::unique_ptr<mailbox::message>;
    }

    namespace base {

        class communication_module {
        public:
            communication_module() = delete;
            communication_module(const communication_module&) = delete;
            communication_module& operator=(const communication_module&) = delete;

            auto type() const -> detail::string_view;
            auto id() const -> int64_t;
            auto enqueue(mailbox::message_ptr) -> void;
            void enqueue(mailbox::message_ptr, scheduler::execution_unit*);

        protected:
            virtual ~communication_module();

            communication_module(std::string, int64_t);
            virtual void enqueue_impl(mailbox::message_ptr, scheduler::execution_unit*) = 0;

        private:
            const std::string type_;
            const int64_t id_;
        };

    } // namespace base
} // namespace actor_zeta
