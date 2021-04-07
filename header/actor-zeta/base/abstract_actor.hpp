#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an actor
    ///

    class abstract_actor : public communication_module {
    public:
        abstract_actor() = delete;

        abstract_actor(const abstract_actor&) = delete;

        abstract_actor& operator=(const abstract_actor&) = delete;

        ~abstract_actor() override;

    protected:
        abstract_actor(std::string);
    };

}} // namespace actor_zeta::base
