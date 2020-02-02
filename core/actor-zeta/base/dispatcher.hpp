#pragma once

#include <memory>
#include <unordered_map>
#include <string>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta { namespace base {
///
/// @brief
///
        class dispatcher_t final {
        public:
            using key_type       = detail::string_view;
            using storage        = std::unordered_map<key_type, std::unique_ptr<handler>>;
            using iterator       = storage::iterator;
            using const_iterator = storage::const_iterator;

            dispatcher_t()  = default;

            dispatcher_t(const dispatcher_t &) = delete;

            dispatcher_t &operator=(const dispatcher_t &) = delete;

            dispatcher_t(dispatcher_t &&) = delete;

            dispatcher_t &operator=(dispatcher_t &&) = delete;

            ~dispatcher_t() = default;

            void execute(context&);

            bool on(detail::string_view, handler*);

            auto begin() -> iterator;

            auto end() -> iterator;

            auto begin() const -> const_iterator;

            auto end() const -> const_iterator;

            auto cbegin() -> const_iterator;

            auto cend() -> const_iterator;

        private:
            storage handlers_;
        };

}} /// namespace actor_zeta { namespace base {}}
