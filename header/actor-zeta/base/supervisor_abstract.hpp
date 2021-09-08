#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    using default_spawn_actor = std::function<actor(supervisor_abstract*)>;
    using default_spawn_supervisor = std::function<supervisor(supervisor_abstract*)>;

    class supervisor_abstract : public communication_module {
    public:
        supervisor_abstract(detail::pmr::memory_resource*,std::string);
        supervisor_abstract(std::string);
        supervisor_abstract(supervisor_abstract*, std::string);
        ~supervisor_abstract() override;
        auto executor() noexcept -> executor::abstract_executor*;
        auto resource() const -> detail::pmr::memory_resource*;
        auto address() noexcept -> address_t;
        auto broadcast(message_ptr) -> void;
        auto broadcast(detail::string_view, message_ptr) -> void;

    protected:
        using storage_contact_t = std::list<address_t>;
        using contacts_t = std::unordered_map<key_type, storage_contact_t>;
        using contacts_iterator_t = storage_contact_t::iterator;
        using address_range_t = std::pair<contacts_t::const_iterator, contacts_t::const_iterator>;

        using communication_module::add_handler;
        virtual auto executor_impl() noexcept -> executor::abstract_executor* = 0;
        virtual auto add_actor_impl(actor) -> void = 0;
        virtual auto add_supervisor_impl(supervisor) -> void = 0;
        auto set_current_message(message_ptr) -> void;
        auto current_message_impl() -> message* final;
        auto address_book(detail::string_view) -> address_t;
        auto address_book() -> address_range_t;
        /**
        * debug method
        */
        auto all_view_address() const -> std::set<std::string>;

    private:
        auto redirect(std::string& type, message* msg) -> void;
        auto spawn_actor(default_spawn_actor&) -> void;
        auto spawn_supervisor(default_spawn_supervisor&) -> void;

        void add_link(address_t&);
        void remove_link(const address_t&);

        contacts_t contacts_;
        message* current_message_;
        detail::pmr::memory_resource* memory_resource_;
    };

}} // namespace actor_zeta::base
