#include <iostream>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

    static void error_sync_contacts(detail::string_view name, detail::string_view error) {
        std::cerr << "WARNING" << '\n';
        std::cerr << "Actor name : " << name << '\n';
        std::cerr << "Not initialization address type:" << error << '\n';
        std::cerr << "WARNING" << std::endl;
    }

    actor_abstract::~actor_abstract() {
    }

    actor_abstract::actor_abstract(std::string type)
        : communication_module(std::move(type)) {
        add_handler("add_link",&actor_abstract::add_link);
        add_handler("remove_link",&actor_abstract::remove_link);
    }

    auto actor_abstract::address_book(detail::string_view name) -> address_t {
        return contacts_.at(name);
    }

    auto actor_abstract::address_book(std::string&name) -> address_t {
        return contacts_.at(detail::string_view(name.data(),name.size()));
    }

    auto actor_abstract::all_view_address() const  -> std::set<std::string> {
        std::set<std::string> tmp;
        for (auto &i: contacts_) {
            tmp.emplace(std::string(i.first.data(),i.first.size()));
        }
        return tmp;
    }

    void actor_abstract::add_link(address_t& address) {
        std::cerr<< "actor_abstract::add_link parrent : " << this << " " << type() << std::endl;
        std::cerr<< "actor_abstract::add_link children : " << address.get() << " " <<address.type() << std::endl;
        if (address && this!=address.get()) {
            auto name = address.type();
            std::cerr << "!_!." << std::endl;
            contacts_.emplace(name, std::move(address));
        } else {
            error_sync_contacts(type(), address.type());
        }

    }

    void actor_abstract::remove_link(const address_t& address) {
        auto it = contacts_.find(address.type());
        if(it != contacts_.end()){
            contacts_.erase(it);
        }
    }

    auto actor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }

}} // namespace actor_zeta::base
