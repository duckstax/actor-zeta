#ifndef ABSTRACT_CHANNEL_HPP
#define ABSTRACT_CHANNEL_HPP

#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/ref_counted.hpp"

namespace actor_zeta {
    namespace channel {
///
/// @brief
///
        struct abstract_channel : public ref_counted {
            virtual bool send(messaging::message *) = 0;
            virtual const std::string& type() const =0;
        };
    }
}
#endif //ABSTRACT_CHANNEL_HPP
