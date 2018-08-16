#include "actor-zeta/environment/group.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace environment {
        auto group::operator->() noexcept -> abstract_group * {
            return group_.get();
        }

        auto group::channel() -> channel::channel {
            return group_->channel();
        }

        group::operator bool() const noexcept {
            return static_cast<bool>(group_);
        }

        bool group::operator!() const noexcept {
            return !group_;
        }

        void group::swap(group &g) noexcept {
            using std::swap;
            group_.swap(g.group_);
        }
    }
}