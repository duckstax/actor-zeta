#ifndef GROUP_CONTACTS_HPP
#define GROUP_CONTACTS_HPP

#include "actor-zeta/forwards.hpp"
#include <vector>

namespace actor_zeta {
    namespace contacts {
///
/// @brief Address container for groups
///
        class group_contacts {
        public:
            group_contacts();

            group_contacts(group_contacts &&) = default;

            group_contacts &operator=(group_contacts &&)= default;

            void put(const actor_zeta::actor::actor_address &vc);

            const actor_zeta::actor::actor_address &get();

            const std::vector<actor_zeta::actor::actor_address> &get_all() const;

        private:
            std::size_t cursor;
            std::vector<actor_zeta::actor::actor_address> set_contact;
        };
    }
}
#endif //GROUP_CONTACTS_HPP
