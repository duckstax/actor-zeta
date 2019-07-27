#pragma once

#include <set>

#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/actor/metadata.hpp>
#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief Abstract concept of an actor
///

        class abstract_actor : public ref_counted {
        public:
            abstract_actor()= default;
            abstract_actor(const abstract_actor &) = delete;
            abstract_actor &operator=(const abstract_actor &) = delete;
            ~abstract_actor() override;

            virtual bool send(messaging::message) = 0;

            virtual bool send(messaging::message, executor::execution_device *) = 0;

            actor_address address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto locating() const -> locations;

            virtual auto message_types() const -> std::set<std::string> ;

            metadata type_;
        };

}}
