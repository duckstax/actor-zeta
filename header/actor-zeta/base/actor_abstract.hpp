#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an actor
    ///

    class actor_abstract : public communication_module {
    public:
        actor_abstract() = delete;

        actor_abstract(const actor_abstract&) = delete;

        actor_abstract& operator=(const actor_abstract&) = delete;

        ~actor_abstract() override;

    protected:
        actor_abstract(std::string);
    };

}} // namespace actor_zeta::base
