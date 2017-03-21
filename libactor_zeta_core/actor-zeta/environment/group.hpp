#ifndef GROUP_HPP
#define GROUP_HPP

#include "actor-zeta/intrusive_ptr.hpp"
#include "abstract_group.hpp"

namespace actor_zeta {
    namespace environment {
        class group final {
        public:
            group() = delete;

            group(const group &) = default;

            group &operator=(const group &)= default;

            group(group &&) = default;

            group &operator=(group &&)= default;

            ~group() = default;

            template<class T>
            explicit group(intrusive_ptr<T> ptr) : group_(std::move(ptr)) {}

            template<class T>
            explicit group(T *ptr) : group_(ptr) {}

            template<class T>
            group &operator=(intrusive_ptr<T> ptr) {
                group tmp{std::move(ptr)};
                swap(tmp);
                return *this;
            }

            template<class T>
            group &operator=(T *ptr) {
                group tmp{ptr};
                swap(tmp);
                return *this;
            }

            auto operator->() noexcept -> abstract_group *;

            auto channel() -> channel::channel;

            explicit operator bool() const noexcept;

            bool operator!() const noexcept;

        private:

            void swap(group &g) noexcept;

            intrusive_ptr<abstract_group> group_;
        };
    }
}
#endif //GROUP_HPP
