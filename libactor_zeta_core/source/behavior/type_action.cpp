#include "actor-zeta/behavior/type_action.hpp"

namespace actor_zeta {
    namespace behavior {

        bool type_action::operator==(const type_action &t) const noexcept {
            return (hash() == t.hash());
        }

        auto type_action::hash() const noexcept -> std::size_t {
            return hash_;
        }

        type_action::type_action(const char *str, std::size_t len) : body_(str, len) {
            hash_ = std::hash<std::string>{}(body_);
        }


        type_action::type_action(const std::string &token) : body_(token) {
            hash_ = std::hash<std::string>{}(body_);
        }

        auto type_action::to_string() const -> const std::string & {
            return body_;
        }
    }
}