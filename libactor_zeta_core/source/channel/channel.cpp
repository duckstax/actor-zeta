#include "actor-zeta/channel/channel.hpp"
namespace actor_zeta {
    namespace channel {

        channel::channel(abstract_channel *ac) : channel_(ac) {}

        abstract_channel *channel::operator->() const {
            return channel_.get();
        }

        channel::operator bool() const {
            return static_cast<bool>(channel_);
        }

        bool channel::operator!() const {
            return !channel_;
        }

        void channel::swap(channel &other) {
            using std::swap;
            channel_.swap(other.channel_);
        }
    }
}