#pragma once

#include <string>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>

//smart actor
namespace actor_zeta { namespace actor {
///
/// @brief An actor's entity container
///
        class actor final {
        public:
            actor() = default;

            actor(const actor &a) = delete;

            actor(actor &&a) = default;

            actor &operator=(const actor &a) = delete;

            actor &operator=(actor &&a) = default;

            template<class T>
            explicit  actor(intrusive_ptr <T> ptr) : ptr_(std::move(ptr)) {}

            template<class T>
            explicit actor(T *ptr) : ptr_(ptr) {}

            template<class T>
            actor &operator=(intrusive_ptr <T> ptr) {
                actor tmp{std::move(ptr)};
                swap(tmp);
                return *this;
            }

            template<class T>
            actor &operator=(T *ptr) {
                actor tmp{ptr};
                swap(tmp);
                return *this;
            }

            actor_address address() const noexcept;

            ~actor();

            inline abstract_actor *operator->() const noexcept {
                return ptr_.get();
            }

            inline explicit operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

           auto name() const -> detail::string_view;

            inline bool operator!() const noexcept {
                return !ptr_;
            }

        private:

            void swap(actor &) noexcept;

            intrusive_ptr <abstract_actor> ptr_;
        };
}}
