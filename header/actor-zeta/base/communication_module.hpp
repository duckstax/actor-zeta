#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <actor-zeta/detail/callable_trait.hpp>
#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using message_ptr = std::unique_ptr<message>;

    using actor_id = std::size_t;

    enum class sub_type_t : uint8_t {
        non = 0x00,
        actor,
        supervisor
    };

    class communication_module
        : public ref_counted {
    public:
        using key_type = detail::string_view;
        using storage = std::unordered_map<key_type, std::unique_ptr<handler>>;

        communication_module() = delete;

        communication_module(const communication_module&) = delete;

        communication_module& operator=(const communication_module&) = delete;

        ~communication_module() override;

        actor_address address() const noexcept;

        auto sub_type() const -> sub_type_t;

        auto type() const -> detail::string_view;

        auto message_types() const -> std::set<std::string>;

        auto enqueue(message_ptr) -> void;

        void enqueue(message_ptr, executor::execution_device*);

        auto broadcast(message_ptr) -> bool;

        virtual auto current_message() -> message* = 0;

    protected:
        communication_module(std::string, sub_type_t);

        virtual void enqueue_base(message_ptr, executor::execution_device*) = 0;

        virtual auto addresses(detail::string_view) -> actor_address&;

        virtual auto self() -> actor_address;

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

        /**
           * debug method
           */
        auto all_view_address() const -> std::vector<std::string>;

    private:
        void add_link(actor_address);

        void remove_link(const actor_address&);

        std::unique_ptr<std::unordered_map<detail::string_view, actor_address>> contacts_;
        storage handlers_;
        actor_id id_;
        sub_type_t sub_type_;
        std::string type_;
    };
}} // namespace actor_zeta::base
