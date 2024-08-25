#pragma once

#include <new>
#include <utility>
#include <string>

#include "forwards.hpp"
#include <actor-zeta/scheduler/forwards.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/memory.hpp>

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

        // prohibit copies, assignments, and heap allocations
        //void* operator new(size_t) = delete;
        //void* operator new[](size_t) = delete;
        //void operator delete(void*) = delete;
        //void operator delete[](void*) = delete;

        explicit actor_abstract(pmr::memory_resource*);

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
        actor_zeta::pmr::memory_resource* resource() const noexcept;

    protected:
        actor_abstract() = delete;
        actor_abstract(const actor_abstract&) = delete;
        actor_abstract& operator=(const actor_abstract&) = delete;

        virtual void enqueue_impl(mailbox::message_ptr) = 0;
        virtual auto type_impl()  const noexcept -> const char* = 0;
    private:
        actor_zeta::pmr::memory_resource * resource_;

    };

}} // namespace actor_zeta::base
