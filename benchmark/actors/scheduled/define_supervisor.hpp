#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <semaphore.h>

#include <actor-zeta.hpp>

#include "enums.hpp"
#include "define_actor.hpp"

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

struct sync_t {
    sem_t prodToRoutine;
};

struct base_single_t {
    sync_t sync_;

    base_single_t() {
        sem_init_();
    }
    virtual ~base_single_t() {
        sem_destroy_();
    }

    auto sem_init_() -> int {
        return sem_init(&sync_.prodToRoutine, 0, 0);
    }

    auto sem_post_() -> int {
        return sem_post(&sync_.prodToRoutine);
    }

    auto sem_wait_() -> int {
        return sem_wait(&sync_.prodToRoutine);
    }

    auto sem_destroy_() -> int {
        return sem_destroy(&sync_.prodToRoutine);
    }
};

class sup_iface {
public:
    virtual void done() = 0;
};

template<class... Args>
class supervisor_t final : public actor_zeta::cooperative_supervisor<supervisor_t<Args...>>, public sup_iface {
    using base_t = actor_zeta::cooperative_supervisor<supervisor_t<Args...>>;
    using Actor = actor_t;
    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::map<name_t, actor_zeta::address_t> address_book_;
    std::map<name_t, Actor*> actors_;
    base_single_t sync_;

public:
    supervisor_t(actor_zeta::detail::pmr::memory_resource* resource)
        : base_t(resource, "Supervisor")
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(1, 1), thread_pool_deleter)
        , sync_() {
        e_->start();
    }
    virtual ~supervisor_t() {
        e_->stop();
    }

    auto make_type() const noexcept -> const char* const {
        return "collection";
    }

    void prepare() {
        auto address_0 = base_t::spawn_actor([this](Actor* ptr) {
            actors_.emplace(name_t::actor_0, ptr);
        }, actor_zeta::type_traits::make_index_sequence<counter_args_t<Args...>::value>());
        auto address_1 = base_t::spawn_actor([this](Actor* ptr) {
            actors_.emplace(name_t::actor_1, ptr);
        }, actor_zeta::type_traits::make_index_sequence<counter_args_t<Args...>::value>());
        address_book_.emplace(name_t::actor_0, std::move(address_0));
        address_book_.emplace(name_t::actor_1, std::move(address_1));

        actor_zeta::send(address_book_.at(name_t::actor_0), base_t::address(), command_t::add_address, address_book_.at(name_t::actor_1), name_t::actor_1);
        actor_zeta::send(address_book_.at(name_t::actor_1), base_t::address(), command_t::add_address, address_book_.at(name_t::actor_0), name_t::actor_0);
    }

    void send() {
        assert(actors_.size() == 2);
        actor_zeta::send(actors_.at(name_t::actor_0), base_t::address(), command_t::start);
        sync_.sem_wait_();
#ifdef BM_TRACE
        std::cout << std::this_thread::get_id() << " :: sem_wait_ RETURNED " << reinterpret_cast<void*>(this) << std::endl;
#endif
        //actors_.at(name_t::actor_0)->start();
    }
    void done() final {
        sync_.sem_post_();
#ifdef BM_TRACE
        std::cout << std::this_thread::get_id() << " :: sem_post_ RETURNED " << reinterpret_cast<void*>(this) << std::endl;
#endif
    }

#if 0
    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            base_t::resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    /*case actor_zeta::make_message_id(command_t::prepare): {
                        prepare();

                        break;
                    }
                    case actor_zeta::make_message_id(command_t::send): {
                        send();

                        break;
                    }*/
                    default: {
                        std::cerr << "unknown command" << std::endl;
                    }
                }
            });
    }
#endif

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        return e_.get();
    }

    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* override {
        return e_.get();
    }

protected:
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        auto ptr = msg.get();
        actor_zeta::base::supervisor_abstract::set_current_message(std::move(msg));
        actor_zeta::base::intrusive_behavior_t::execute(this, actor_zeta::base::supervisor_abstract::current_message());
        delete ptr;
    }
};
