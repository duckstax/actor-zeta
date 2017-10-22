#ifndef ABSTRACT_BEHAVIOR_HPP
#define ABSTRACT_BEHAVIOR_HPP
namespace actor_zeta {
    namespace behavior {
        struct abstract_behavior {
            abstract_behavior() = default;

            abstract_behavior(const abstract_behavior &) = delete;

            abstract_behavior &operator=(const abstract_behavior &) = delete;

            abstract_behavior(abstract_behavior &&) = delete;

            abstract_behavior &operator=(abstract_behavior &&) = delete;

            virtual ~abstract_behavior() = default;

            virtual bool insert(abstract_action *aa) = 0;

            virtual response run(request &&)         = 0;
        };
    }
}
#endif //
