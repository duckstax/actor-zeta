#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "forwards.hpp"
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/scheduler/execution_unit.hpp>

namespace actor_zeta {

    namespace mailbox {
        using message_ptr = std::unique_ptr<message>;
    }

    namespace base {

        class communication_module {
        public:
            communication_module() = delete;
            communication_module(const communication_module&) = delete;
            communication_module& operator=(const communication_module&) = delete;

            class id_t final {
            public:
                id_t() = default;

                explicit id_t(communication_module* impl) noexcept
                    : impl_{impl} {
                }

                bool operator==(id_t const& other) const noexcept {
                    return impl_ == other.impl_;
                }

                bool operator!=(id_t const& other) const noexcept {
                    return impl_ != other.impl_;
                }

                bool operator<(id_t const& other) const noexcept {
                    return impl_ < other.impl_;
                }

                bool operator>(id_t const& other) const noexcept {
                    return other.impl_ < impl_;
                }

                bool operator<=(id_t const& other) const noexcept {
                    return !(*this > other);
                }

                bool operator>=(id_t const& other) const noexcept {
                    return !(*this < other);
                }

                template<typename charT, class traitsT>
                friend std::basic_ostream<charT, traitsT>&
                operator<<(std::basic_ostream<charT, traitsT>& os, id_t const& other) {
                    if (nullptr != other.impl_) {
                        return os << other.impl_;
                    }
                    return os << "{not-valid}";
                }

                explicit operator bool() const noexcept {
                    return nullptr != impl_;
                }

                bool operator!() const noexcept {
                    return nullptr == impl_;
                }

            private:
                communication_module* impl_{nullptr};
            };

            auto type() const -> const char* const;
            auto id() const -> id_t;
            auto enqueue(mailbox::message_ptr) -> void;
            void enqueue(mailbox::message_ptr, scheduler::execution_unit*);

        protected:
            virtual ~communication_module();
            communication_module(std::string);

            virtual void enqueue_impl(mailbox::message_ptr, scheduler::execution_unit*) = 0;

        private:
#ifdef DEBUG
            std::string type_;
#endif
        };

    } // namespace base
} // namespace actor_zeta
