#include "actor-zeta/channel/channel.hpp"
namespace actor_zeta {
    namespace channel {

        channel::channel(abstract_channel *ac) : channel_(ac) {}

        abstract_channel *channel::operator->() const noexcept {
            return channel_.get();
        }

        channel::operator bool() const noexcept {
            return static_cast<bool>(channel_);
        }

        bool channel::operator!() const noexcept {
            return !channel_;
        }

        void channel::swap(channel &other) noexcept {
            using std::swap;
            channel_.swap(other.channel_);
        }
    }
}