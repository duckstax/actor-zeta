#pragma once
// clang-format off
#include <actor-zeta/link.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
// clang-format on
/// ------------------------------------------------
#include <actor-zeta/base/actor.hpp>

#include <iostream>

namespace actor_zeta { namespace base {

    static void error_sync_contacts_in_supervisor(detail::string_view name, detail::string_view error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    static constexpr std::size_t DEFAULT_ALIGNMENT{alignof(std::max_align_t)};

    constexpr bool is_pow2(std::size_t n) { return (0 == (n & (n - 1))); }

    constexpr bool is_supported_alignment(std::size_t alignment) { return is_pow2(alignment); }

    template<typename Alloc>
    void* aligned_allocate(std::size_t bytes, std::size_t alignment, Alloc alloc) {
        assert(is_pow2(alignment));

        std::size_t padded_allocation_size{bytes + alignment + sizeof(std::ptrdiff_t)};

        char* const original = static_cast<char*>(alloc(padded_allocation_size));

        void* aligned{original + sizeof(std::ptrdiff_t)};

        std::align(alignment, bytes, aligned, padded_allocation_size);

        std::ptrdiff_t offset = static_cast<char*>(aligned) - original;

        *(static_cast<std::ptrdiff_t*>(aligned) - 1) = offset;

        return aligned;
    }

    template<typename Dealloc>
    void aligned_deallocate(void* p, std::size_t bytes, std::size_t alignment, Dealloc dealloc) {
        (void) alignment;
        (void) bytes;

        std::ptrdiff_t const offset = *(reinterpret_cast<std::ptrdiff_t*>(p) - 1);

        void* const original = static_cast<char*>(p) - offset;

        dealloc(original);
    }

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

    supervisor_abstract::supervisor_abstract(detail::pmr::memory_resource* memory_resource, std::string name)
        : communication_module(std::move(name))
        , memory_resource_(memory_resource) {
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
        send(address_book(type_t.c_str()), std::move(tmp));
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
        auto result = contacts_.find(type);
        if (result != contacts_.end()) {
            return *(result->second.begin());
        }
    }

    auto supervisor_abstract::address_book() -> address_range_t {
        return std::make_pair(contacts_.cbegin(), contacts_.cend());
    }

    void supervisor_abstract::add_link(address_t& address) {
        std::cerr << "supervisor_abstract::add_link address: " << address.get() << " " << address.type() << std::endl;
        std::cerr << "supervisor_abstract::add_link this: " << this << " " << type() << std::endl;
        if (address && this != address.get()) {
            auto name = address.type();
            auto it = contacts_.find(name);
            if (it == contacts_.end()) {
                auto result = contacts_.emplace(name, storage_contact_t());
                result.first->second.emplace_back(std::move(address));
            } else {
                it->second.emplace_back(std::move(address));
            }
        } else {
            std::cerr << "supervisor_abstract::add_link : ";
            error_sync_contacts_in_supervisor(type(), address.type());
        }
    }

    void supervisor_abstract::remove_link(const address_t& address) {
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

    void supervisor_abstract::sync(base::address_t&address){
        link(*this, address);
        auto sender = current_message()->sender();
        if (this != sender.get()) {
            link(sender, address);
        }
    }

}} // namespace actor_zeta::base
