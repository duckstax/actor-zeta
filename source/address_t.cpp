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
        return type_ != abstract::non and (ptr_.supervisor != nullptr || ptr_.supervisor != nullptr);
    }

    address_t::address_t(abstract_actor* ptr)
        : type_(abstract::actor)
        , ptr_(ptr) {
    }

    address_t::address_t(abstract_supervisor* ptr)
        : type_(abstract::supervisor)
        , ptr_(ptr) {
    }


    auto address_t::enqueue( message msg) -> void {
        switch (type_) {
            case abstract::actor:
                ptr_.actor->enqueue(std::move(msg));
                break;
            case abstract::supervisor:
                ptr_.supervisor->enqueue(std::move(msg));
                break;
            case abstract::non:
                break;
        }
    }

    auto address_t::name() const -> detail::string_view {
        switch (type_) {
            case abstract::actor:
                ptr_.actor->name();
                break;
            case abstract::supervisor:
                ptr_.supervisor->name();
                break;
            case abstract::non:
                break;
        }
    }

} // namespace actor_zeta
