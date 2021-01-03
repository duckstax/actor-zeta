#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace messaging {
///
/// @brief
///
        class message_header final {
        public:
            message_header() = default;

            message_header(const message_header &) = default;

            message_header &operator=(const message_header &) = default;

            message_header(message_header &&) = default;

            message_header &operator=(message_header &&) = default;

            ~message_header() = default;

            message_header(base::address_type sender_, detail::string_view name);

            auto command() const noexcept -> detail::string_view;

            auto sender() const -> base::address_type;

            operator bool();

        private:
            base::address_type sender_;
            detail::string_view command_;
        };
    }
}
