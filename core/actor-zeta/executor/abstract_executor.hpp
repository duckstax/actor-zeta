#pragma once

#include <chrono>
#include <atomic>
#include <cstddef>
#include <array>

#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/executor/executable.hpp>

namespace actor_zeta { namespace executor {
///
/// @brief
///
        class abstract_executor {
        public:
            abstract_executor(std::size_t num_worker_threads, std::size_t max_throughput);

            virtual ~abstract_executor() = default;

            virtual void execute(executable *) = 0;

            inline size_t max_throughput() const {
                return max_throughput_;
            }

            inline size_t num_workers() const {
                return num_workers_;
            }

            virtual void start() = 0;

        protected:
            std::atomic<size_t> next_worker_;

            std::size_t max_throughput_;

            std::size_t num_workers_;

        };

}}
