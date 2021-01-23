#include <address_t.hpp>

#include <abstract_actor.hpp>
#include <actor-zeta/abstract_supervisor.hpp>
#include <message.hpp>

namespace actor_zeta {

    void address_t::swap(address_t& other) noexcept {
        using std::swap;
        assert(type_ != other.type_);
        swap(ptr_, other.ptr_);
    }

    address_t::operator bool() const {
        return static_cast<bool>(ptr_);
    }

    address_t::address_t(abstract_actor* ptr)
        : type_(abstract::actor)
        , ptr_(ptr) {
    }

    address_t::address_t(abstract_supervisor* ptr)
        : type_(abstract::supervisor)
        , ptr_(ptr) {
    }
    auto address_t::ptr() -> void* {
        return ptr_;
    }
    auto address_t::type() const -> abstract {
        return type_;
    }

    auto enqueue_(address_t& address, message msg) -> void {
        switch (address.type()) {
            case abstract::actor:
                static_cast<abstract_actor*>(address.ptr())->enqueue(std::move(msg));
                break;
            case abstract::supervisor:
                static_cast<abstract_supervisor*>(address.ptr())->enqueue(std::move(msg));
                break;
            case abstract::non:
                break;
        }
    }
    auto name_(address_t& address) -> detail::string_view {
        switch (address.type()) {
            case abstract::actor:
                static_cast<abstract_actor*>(address.ptr())->name();
                break;
            case abstract::supervisor:
                static_cast<abstract_supervisor*>(address.ptr())->name();
                break;
            case abstract::non:
                break;
        }
    }

} // namespace actor_zeta
