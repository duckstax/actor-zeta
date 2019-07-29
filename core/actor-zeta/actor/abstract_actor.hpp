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
            abstract_actor() = delete;

            abstract_actor(const abstract_actor &) = delete;

            abstract_actor &operator=(const abstract_actor &) = delete;

            ~abstract_actor() override;

            explicit abstract_actor(detail::string_view);

            bool send(messaging::message);

            virtual bool send(messaging::message, executor::execution_device *) = 0;

            virtual auto message_types() const -> std::set<std::string> ;

            actor_address address() const noexcept;

            auto type() const -> abstract;

            auto name() const -> detail::string_view;

            auto locating() const -> locations;

            metadata type_;
        };

}}
