#pragma once
// clang-format off
#include <actor-zeta/link.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
// clang-format on
/// ------------------------------------------------
#include <actor-zeta/base/actor.hpp>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <iostream>

namespace actor_zeta { namespace base {

    static void error_sync_contacts_in_supervisor(detail::string_view name, detail::string_view error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    using detail::aligned_allocate;
    using detail::aligned_deallocate;
    using detail::DEFAULT_ALIGNMENT;
    using detail::is_supported_alignment;

    class new_delete_resource final : public detail::pmr::memory_resource {
    public:
    private:
        void* do_allocate(std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            alignment = (is_supported_alignment(alignment)) ? alignment : DEFAULT_ALIGNMENT;
            return aligned_allocate(bytes, alignment, [](std::size_t size) { return ::operator new(size); });
        }

        void do_deallocate(void* p, std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            aligned_deallocate(p, bytes, alignment, [](void* p) { ::operator delete(p); });
        }

        bool do_is_equal(const memory_resource& other) const noexcept override { return &other == this; }
    };

    supervisor_abstract::supervisor_abstract(detail::pmr::memory_resource* mr, std::string name)
        : communication_module(std::move(name))
        , memory_resource_(mr) {
        add_handler("delegate", &supervisor_abstract::redirect);
        add_handler("add_link", &supervisor_abstract::add_link);
        add_handler("remove_link", &supervisor_abstract::remove_link);
    }

    supervisor_abstract::supervisor_abstract(std::string name)
        : communication_module(std::move(name))
        , memory_resource_(new new_delete_resource) {
        add_handler("delegate", &supervisor_abstract::redirect);
        add_handler("add_link", &supervisor_abstract::add_link);
        add_handler("remove_link", &supervisor_abstract::remove_link);
    }

    supervisor_abstract::supervisor_abstract(supervisor_abstract* ptr, std::string name)
        : communication_module(std::move(name))
        , memory_resource_(ptr->resource()) {
        add_handler("delegate", &supervisor_abstract::redirect);
        add_handler("add_link", &supervisor_abstract::add_link);
        add_handler("remove_link", &supervisor_abstract::remove_link);
    }
    supervisor_abstract::~supervisor_abstract() {}

    auto supervisor_abstract::current_message_impl() -> message* {
        return current_message_;
    }

    auto supervisor_abstract::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

    auto supervisor_abstract::resource() const -> detail::pmr::memory_resource* {
        return memory_resource_;
    }

    auto supervisor_abstract::executor() noexcept -> executor::abstract_executor* {
        return executor_impl();
    }

    auto supervisor_abstract::redirect(std::string& type, message* msg) -> void {
        message_ptr tmp(std::move(msg));
        auto type_t = std::move(type);
        tmp->sender() = std::move(address());
        send(address_book(type_t), std::move(tmp));
    }

    auto supervisor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

    auto supervisor_abstract::all_view_address() const -> std::set<std::string> {
        std::set<std::string> tmp;
        for (const auto& i : contacts_) {
            tmp.emplace(std::string(i.first.begin(), i.first.end()));
        }
        return tmp;
    }

    auto supervisor_abstract::address_book(detail::string_view type) -> address_t {
        auto tmp = address_t::empty_address();
        auto result = contacts_.find(type);
        if (result != contacts_.end()) {
            tmp = *(result->second.begin());
        }
        return tmp;
    }

    auto supervisor_abstract::address_book(std::string& type) -> address_t {
        detail::string_view tmp(type.data(), type.size());
        return address_book(tmp);
    }

    auto supervisor_abstract::address_book() -> address_range_t {
        return std::make_pair(contacts_.cbegin(), contacts_.cend());
    }

    void supervisor_abstract::add_link() {
        add_link_impl(std::move(current_message()->sender()));
    }

    void supervisor_abstract::remove_link() {
        remove_link_impl(current_message()->sender());
    }

    void supervisor_abstract::add_link_impl(address_t address) {
        if (address && this != address.get()) {
            auto name = address.type();
            auto it = contacts_.find(name);
            if (it == contacts_.end()) {
                auto result = contacts_.emplace(name, storage_contact_t());
                result.first->second.emplace_back(std::move(address));
                return;
            } else {
                it->second.emplace_back(std::move(address));
                return;
            }
        } else {
            error_sync_contacts_in_supervisor(type(), address.type());
        }
    }

    void supervisor_abstract::remove_link_impl(const address_t& address) {
        auto name = address.type();
        auto it = contacts_.find(name);
        if (it == contacts_.end()) {
            // not find
        } else {
            auto end = it->second.end();
            for (auto i = it->second.begin(); i != end; ++i) {
                if (address.get() == i->get()) {
                    it->second.erase(i);
                }
            }
        }
    }

    auto supervisor_abstract::broadcast(message_ptr msg) -> void {
        auto tmp = std::move(msg);

        for (auto& i : contacts_) {
            for (auto& j : i.second) {
                j.enqueue(message_ptr(tmp->clone()));
            }
        }
    }

    auto supervisor_abstract::broadcast(detail::string_view type, message_ptr msg) -> void {
        auto tmp = std::move(msg);
        auto range = contacts_.find(type);
        for (auto& i : range->second) {
            i.enqueue(message_ptr(tmp->clone()));
        }
    }

    void supervisor_abstract::sync(const base::address_t& address) {
        auto address_tmp(address);
        add_link_impl(address_t(address));
        send(address_tmp, supervisor_abstract::address(), "add_link");
        auto& sender = current_message()->sender();
        if (sender && this != sender.get()) {
            link(sender, address_tmp);
        }
    }

}} // namespace actor_zeta::base
