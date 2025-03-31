#pragma once

#include <cassert>

#include <chrono>
#include <memory>
#include <vector>

#include "test/tooltestsuites/clock_test.hpp"
#include "test/tooltestsuites/scheduler_test.hpp"
#include <actor-zeta.hpp>

static std::atomic<uint64_t> alarm_counter{0};

/// non thread safe
constexpr static auto alarm_id = actor_zeta::make_message_id(0);

class supervisor_lite final : public actor_zeta::actor_abstract_t {
public:
    explicit supervisor_lite(actor_zeta::pmr::memory_resource* ptr)
        : actor_abstract_t(ptr)
        , alarm_(actor_zeta::make_behavior(resource(), alarm_id, this, &supervisor_lite::alarm))
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        scheduler()->start();
    }

    auto clock() noexcept -> actor_zeta::test::clock_test& {
        return executor_->clock();
    }

    ~supervisor_lite() override = default;

    auto make_scheduler() noexcept -> actor_zeta::scheduler_t* { return executor_.get(); }

protected:
    void alarm() {
        alarm_counter += 1;
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case alarm_id: {
                        alarm_(msg);
                        break;
                    }
                }
            });
    }

    auto enqueue_impl(actor_zeta::message_ptr msg) -> void final {
        {
            auto tmp = std::move(msg);
            behavior()(tmp.get());
        }
    }

private:
    actor_zeta::behavior_t alarm_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
};