#pragma once

#include <actor-zeta/environment.hpp>
#include <actor-zeta/network/multiplexer.hpp>
#include <memory>

namespace actor_zeta { namespace environment {

        using actor_zeta::network::multiplexer;
        using actor_zeta::executor::abstract_executor;

        class network_environment : public abstract_environment {
        public:
            network_environment() = delete;

            network_environment(const network_environment &) = delete;

            network_environment &operator=(const network_environment &) = delete;

            ~network_environment() override = default;

            network_environment(abstract_executor *executor_, multiplexer *ptr);

            std::size_t start() final;

            executor::abstract_executor &get_executor() final;

        private:
            intrusive_ptr<multiplexer> multiplexer_;
            std::unique_ptr<abstract_executor> executor_;
        };

    }
}
