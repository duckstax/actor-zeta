#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/control_block.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/detail/weak_intrusive_ptr.hpp>

namespace actor_zeta { namespace base {
///
/// @brief A compact location expressor
///
        class address_type final {
        public:

            static constexpr bool has_weak_ptr_semantics = true;

            address_type() = default;

            address_type(address_type&&) = default;

            address_type(const address_type&) = default;

            address_type&operator=(address_type&&) = default;

            address_type&operator=(const address_type&) = default;

            explicit address_type(communication_module *);

            ~address_type();

            inline communication_module *operator->() const noexcept {
                return ptr_->get()
            }

            inline  operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

            inline  bool operator!() const noexcept {
                return !ptr_;
            }

        private:
            weak_intrusive_ptr<control_block<communication_module>> ptr_;
        };

}}
