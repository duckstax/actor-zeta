#ifndef ABSTRACT_ACTOR_HPP
#define ABSTRACT_ACTOR_HPP


#include <mutex>
#include <condition_variable>
#include <string>
#include "actor-zeta/ref_counted.hpp"
#include "actor.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {

    class abstract_actor : public ref_counted {
    public:
        abstract_actor() = delete;

        abstract_actor(const abstract_actor &) = delete;

        abstract_actor &operator=(const abstract_actor &) = delete;

        std::string type() const;

        abstract_actor(const std::string& type, abstract_coordinator* e);

        virtual bool async_send(messaging::message &&) = 0;

        virtual bool async_send(messaging::message &&, executor_service *) = 0;

        inline void attach(abstract_coordinator* e) {
            abstract_actor::_executor = e;
        }

        inline abstract_coordinator* attach() const {
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
        abstract_coordinator* _executor;
        mutable std::mutex mtx_;
        mutable std::condition_variable cv_;

    };
}
#endif //ABSTRACT_ACTOR_HPP
