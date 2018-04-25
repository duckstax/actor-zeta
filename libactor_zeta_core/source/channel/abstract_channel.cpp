#include <actor-zeta/channel/abstract_channel.hpp>

namespace actor_zeta { namespace channel {

        abstract_channel::~abstract_channel() {

        }

        abstract abstract_channel::type() const {
            return type_.type;
        }

        const std::string &abstract_channel::name() const {
            return type_.name;
        }

        locations abstract_channel::locating() const {
            return type_.location;
        }
    }
}

