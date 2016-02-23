#ifndef ABSTRACT_ACTOR_HPP
#define ABSTRACT_ACTOR_HPP


#include <mutex>
#include <condition_variable>
#include <string>
#include "ref_counted.hpp"
#include "actor.hpp"
#include "forwards.hpp"

namespace actor_zeta {

    class abstract_actor : public ref_counted {
    public:
        abstract_actor() = delete;

        abstract_actor(const abstract_actor &) = delete;

        abstract_actor &operator=(const abstract_actor &) = delete;

        std::string type() const;

        abstract_actor(const std::string& type, abstract_coordinator_ptr e);

        virtual bool async_send(messaging::message &&) = 0;

        virtual bool async_send(messaging::message &&, executor_ptr) = 0;

        inline void attach(abstract_coordinator_ptr e) {
            abstract_actor::_executor = e;
        }

        inline abstract_coordinator_ptr attach() const {
            return abstract_actor::_executor;
        }

        virtual ~abstract_actor();

        actor_address adddres() const noexcept;

        bool is_remote() const noexcept;

        void is_remote(bool r) noexcept;

        bool is_blocked() const noexcept;

        void is_blocked(bool blocked)noexcept;

        bool is_master() const noexcept;

        void is_master(bool master)noexcept;

    protected:
        const std::string actor_type;
        bool remote;
        bool blocked;
        bool master;
        abstract_coordinator_ptr _executor;
        mutable std::mutex mtx_;
        mutable std::condition_variable cv_;

    };
}
#endif //ABSTRACT_ACTOR_HPP
