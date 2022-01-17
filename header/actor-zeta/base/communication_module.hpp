#pragma once

#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;
    using actor_id_t = int64_t;
    constexpr static actor_id_t invalid_actor_id{-1};

    class communication_module {
    public:
        using key_type = detail::string_view;
        using handler_storage_t = std::unordered_map<key_type, std::unique_ptr<handler>>;

        communication_module(const communication_module&) = delete;
        communication_module& operator=(const communication_module&) = delete;

        class id_t {
        public:
            id_t() = default;

            explicit id_t(communication_module* impl) noexcept
                : impl_{impl} {
            }

            explicit id_t(actor_id_t id) noexcept
                : impl_{reinterpret_cast<communication_module*>(id)} {
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

        auto type() const -> detail::string_view;
        auto id() const -> id_t;
        auto enqueue(message_ptr) -> void;
        void enqueue(message_ptr, scheduler::execution_unit*);

    protected:
        virtual ~communication_module();
        /**
        * debug method
        */
        auto message_types() const -> std::set<std::string>;
        auto current_message() -> message*;

        communication_module(actor_id_t , std::string);
        explicit communication_module(actor_id_t);
        explicit communication_module(std::string);
        communication_module();

        virtual auto current_message_impl() -> message* = 0;
        virtual void enqueue_impl(message_ptr, scheduler::execution_unit*) = 0;

        template<class F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f)));
        }

        template<typename F>
        auto add_handler(detail::string_view name, F&& f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
            on(name, make_handler(std::forward<F>(f), static_cast<typename type_traits::get_callable_trait_t<F>::class_type*>(this)));
        }

        void execute();
        bool on(detail::string_view, handler*);

    private:
        handler_storage_t handlers_;
        const actor_id_t id_;
#ifdef DEBUG
             std::string type_;
#endif
    };

}} // namespace actor_zeta::base
