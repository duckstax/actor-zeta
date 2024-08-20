#pragma once

#include <new>
#include <utility>
#include <string>

#include "forwards.hpp"
#include <actor-zeta/scheduler/forwards.hpp>
#include "actor-zeta/detail/intrusive_ptr.hpp"
#include "actor-zeta/detail/ref_counted.hpp"

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an actor
    ///

    class actor_abstract : public ref_counted {
    public:
        // allow placement new (only)
        void* operator new(std::size_t, void* ptr) {
            return ptr;
        }

        auto address() noexcept -> address_t;

        class id_t final {
        public:
            id_t() = delete;

            explicit id_t(actor_abstract* impl) noexcept
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
            actor_abstract* impl_{nullptr};
        };

        auto type() const noexcept -> const char*;
        auto id() const -> id_t;
        auto enqueue(mailbox::message_ptr) -> void;
        void enqueue(mailbox::message_ptr, scheduler::execution_unit*);

    protected:
        // prohibit copies, assignments, and heap allocations
        void* operator new(size_t);
        void* operator new[](size_t);
        actor_abstract() = delete;
        actor_abstract(const actor_abstract&) = delete;
        actor_abstract& operator=(const actor_abstract&) = delete;
        ~actor_abstract() override;

        virtual void enqueue_impl(mailbox::message_ptr, scheduler::execution_unit*) = 0;
        virtual auto type_impl()  const noexcept -> const char* = 0;

    private:

    };

    using actor_t = intrusive_ptr<actor_abstract>;

}} // namespace actor_zeta::base
