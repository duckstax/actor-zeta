#pragma once

#include <cassert>

#include <chrono>
#include <memory>
#include <vector>

#include "tooltestsuites/clock_test.hpp"
#include "tooltestsuites/scheduler_test.hpp"
#include <actor-zeta.hpp>

static std::atomic<uint64_t> alarm_counter{0};

using actor_zeta::detail::pmr::memory_resource;
/// non thread safe
constexpr static auto alarm_id = actor_zeta::make_message_id(0);

class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    explicit supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor(ptr)
        , alarm_(resource())
        , executor_(new actor_zeta::test::scheduler_test_t(1, 1)) {
        actor_zeta::behavior(alarm_,alarm_id,this, &supervisor_lite::alarm);
        scheduler()->start();
    }

    auto clock() noexcept -> actor_zeta::test::clock_test& {
        return executor_->clock();
    }

    ~supervisor_lite() override = default;


    auto make_type() /*const*/ noexcept -> const char* const {
        return "supervisor_lite";
    }

protected:

    void alarm() {
        alarm_counter += 1;
    }


    actor_zeta::behavior_t make_behavior() {
        return actor_zeta::behavior(
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

    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final { return executor_.get(); }
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            make_behavior()(current_message());
        }
    }

private:
    actor_zeta::behavior_t alarm_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::vector<actor_zeta::actor_t> actors_;
};