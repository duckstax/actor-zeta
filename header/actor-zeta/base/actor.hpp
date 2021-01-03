#pragma once

#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/forwards.hpp>
#include <detail/control_block.hpp>

//smart actor
namespace actor_zeta { namespace base {
///
/// @brief An Actor's entity container
///
        class actor final {
        public:

            static constexpr bool has_weak_ptr_semantics = false;

            actor() = default;

            actor(const actor &a) = delete;

            actor(actor &&a) = default;

            actor &operator=(const actor &a) = delete;

            actor &operator=(actor &&a) = default;

            actor(std::nullptr_t);

            actor& operator=(std::nullptr_t);

            template <
                    class T,
                    class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>
            >
            actor(intrusive_ptr <T> ptr) : ptr_(std::move(ptr)) {}

            template <
                    class T,
                    class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>
            >
            actor(T *ptr) : ptr_(ptr) {}

            template <
                    class T,
                    class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>
            >
            actor &operator=(intrusive_ptr <T> ptr) {
                actor tmp{std::move(ptr)};
                swap(tmp);
                return *this;
            }

            template <
                    class T,
                    class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>
            >
            actor &operator=(T *ptr) {
                actor tmp{ptr};
                swap(tmp);
                return *this;
            }

            address_type address() const noexcept;

            ~actor();

            inline abstract_actor *operator->() const noexcept {
                return ptr_->get();
            }

            inline explicit operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

           auto name() const -> detail::string_view;

            inline bool operator!() const noexcept {
                return !ptr_;
            }

            actor(control_block<abstract_actor>* ptr, bool add_ref): ptr_(ptr, add_ref) {

            }

        private:

            actor(control_block<abstract_actor>*ptr): ptr_(ptr){}

            control_block<abstract_actor>* get() const noexcept {
                return ptr_.get();
            }

            control_block<abstract_actor>* release() noexcept {
                return ptr_.release();
            }

            void swap(actor &) noexcept;

            intrusive_ptr <control_block<abstract_actor>> ptr_;
        };
}}
