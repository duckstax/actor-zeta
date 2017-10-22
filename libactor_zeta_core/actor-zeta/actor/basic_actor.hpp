#ifndef BASIC_ACTOR_HPP
#define BASIC_ACTOR_HPP
namespace actor_zeta {
    namespace actor {

        template<
                typename Actor,
                typename MailBox,
                typename Behavior
        >
        class basic_actor : public Actor {
        public:
           virtual ~basic_actor() = default;
        protected:
            basic_actor(environment::environment *ptr, const std::string &name)
                    : Actor(ptr, new MailBox,new Behavior, name) {}

        };
    }
}
#endif
