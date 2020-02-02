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

            message_header(base::actor_address sender_, std::string name);

            auto command() const noexcept -> detail::string_view;

            auto sender() const -> base::actor_address ;

            operator bool();

        private:
            base::actor_address sender_;
            std::string command_;
        };
    }
}
