#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_set>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/scheduler/scheduler.hpp>
#include <actor-zeta/clock/clock_thread_safe.hpp>

constexpr static uint64_t command_alarm = 0;
static std::atomic<uint64_t> alarm_counter{0};

class advanced_scheduler_t final : public actor_zeta::scheduler::scheduler_t {
public:
    using super = actor_zeta::scheduler_t;

    advanced_scheduler_t(size_t num_worker_threads, size_t max_throughput_param)
        : super(num_worker_threads, max_throughput_param) {}

    void start() override {
        super::start();
        clock_.start_dispatch_loop();
    }

    void stop() override {
        super::stop();
        clock_.stop_dispatch_loop();
    }

    actor_zeta::clock::thread_safe_clock_t& clock() {
        return clock_;
    }

private:
    actor_zeta::clock::thread_safe_clock_t clock_;
};

using shared_work = advanced_scheduler_t<actor_zeta::work_sharing>;

auto thread_pool_deleter = [](shared_work* ptr) {
    ptr->stop();
    delete ptr;
};

/// non thread safe
class supervisor_lite final : public actor_zeta::actor_abstract {
public:
    supervisor_lite(actor_zeta::pmr::memory_resource* ptr)
        : actor_abstract(ptr)
        , alarm_( actor_zeta::make_behavior(resource(), command_alarm, this, &supervisor_lite::alarm))
        , e_(new shared_work(
                 1,
                 100),
             thread_pool_deleter) {
        e_->start();
    }

    ~supervisor_lite() = default;

    void alarm() {
        alarm_counter += 1;
    }

    actor_zeta::clock::thread_safe_clock_t& clock() {
        return e_->clock();
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_t* { return e_.get(); }

protected:
    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case command_alarm: {
                        alarm_(msg);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            });
    }

    void enqueue_impl(actor_zeta::message_ptr msg) {
        {
            auto tmp = std::move(msg);
            behavior()(tmp.get());
        }
    }

private:
    actor_zeta::behavior_t alarm_;
    std::unique_ptr<shared_work, decltype(thread_pool_deleter)> e_;
};

int main() {
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::make<supervisor_lite>(mr_ptr);

    supervisor->clock().schedule_message(supervisor->clock().now() + std::chrono::seconds(60), supervisor->address(), actor_zeta::make_message(actor_zeta::address_t::empty_address(), command_alarm));

    std::this_thread::sleep_for(std::chrono::seconds(180));

    std::cerr << " Finish " << std::endl;
    std::cerr << " Finish Alarm Counter :" << alarm_counter << std::endl;
    assert(alarm_counter.load() == 1);
    return 0;
}
