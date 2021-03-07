#pragma once

#include <set>
#include <unordered_map>
#include <memory>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/base/metadata.hpp>
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/detail/callable_trait.hpp>


namespace actor_zeta { namespace base {

        using message_ptr = std::unique_ptr<message>;

        class communication_module
                : public ref_counted
                , public context {
        public:

            using key_type  = detail::string_view;
            using storage   = std::unordered_map<key_type, std::unique_ptr<handler>>;

            communication_module() = delete;

            communication_module(const communication_module &) = delete;

            communication_module &operator=(const communication_module &) = delete;

            ~communication_module() override;

            actor_address address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto message_types() const -> std::set<std::string>;

            auto enqueue(message_ptr) -> void;

            virtual void enqueue(message_ptr, executor::execution_device *) = 0;

            auto broadcast(message_ptr) -> bool;

        protected:
            communication_module(detail::string_view, abstract);

            auto addresses(detail::string_view) -> actor_address & override;

            auto self() -> actor_address override ;

            template<class F>
            auto add_handler(detail::string_view name, F &&f) ->  typename std::enable_if<!std::is_member_function_pointer<F>::value>::type {
                on(name, make_handler(std::forward<F>(f)));
            }

            template<typename F>
            auto add_handler(detail::string_view name, F &&f) -> typename std::enable_if<std::is_member_function_pointer<F>::value>::type {
                on(name, make_handler(std::forward<F>(f),static_cast<typename type_traits::get_callable_trait_t<F>::class_type *>(this)));
            }

            void execute(context&);

            bool on(detail::string_view, handler*);

            /**
           * debug method
           */
            auto all_view_address() const -> void ;

        private:
            void add_link(actor_address);

            void remove_link(const actor_address&);

            void initialize();

            std::unique_ptr<std::unordered_map<detail::string_view, actor_address>> contacts_;
            storage handlers_;
            metadata type_;
        };
}}
