#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "actor-zeta/intrusive_ptr.hpp"
#include "actor-zeta/channel/abstract_channel.hpp"

namespace actor_zeta { namespace channel {

///
/// @brief 
///
        class channel final {
        public:

            explicit channel(abstract_channel *ac);

            abstract_channel *operator->() const noexcept;

            explicit operator bool() const noexcept;

            bool operator!() const noexcept;

        private:

            void swap(channel &other) noexcept;

            intrusive_ptr<abstract_channel> channel_;
        };
    }
}
#endif //CHANNEL_HPP
