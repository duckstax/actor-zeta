#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>
#include <iostream>

namespace actor_zeta { namespace base {

    inline void error_duplicate_handler(detail::string_view _error_) {
        std::cerr << "Duplicate" << std::endl;
        std::cerr << "Handler: " << _error_ << std::endl;
        std::cerr << "Duplicate" << std::endl;
    }

    inline void error_add_handler(detail::string_view _error_) {
        std::cerr << "error add handler" << std::endl;
        std::cerr << "Handler: " << _error_ << std::endl;
        std::cerr << "error add handler" << std::endl;
    }

    inline void error_skip(detail::string_view __error__) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << "Skip : " << __error__ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    using handler = std::function<void()>;
    ///
    /// @brief
    ///

    class dispatcher_t final {
    public:
        using key_type = detail::string_view;
        using storage = std::unordered_map<key_type,std::unique_ptr<handler>>;
        using iterator = storage::iterator;
        using const_iterator = storage::const_iterator;

        dispatcher_t() = default;

        dispatcher_t(const dispatcher_t&) = delete;

        dispatcher_t& operator=(const dispatcher_t&) = delete;

        dispatcher_t(dispatcher_t&&) = delete;

        dispatcher_t& operator=(dispatcher_t&&) = delete;

        ~dispatcher_t() = default;

        template<typename Actor>
        void execute(Actor& ctx) {
            auto it = handlers_.find(ctx.current_message().command());
            if (it != handlers_.end()) {
                it->second->operator()(ctx);
            } else {
                error_skip(ctx.current_message().command());
            }
        }

        void on(detail::string_view name, handler* aa) {
            auto it = handlers_.find(name);
            bool status = false;
            if (it == handlers_.end()) {
                auto it1 = handlers_.emplace(name, std::unique_ptr<handler>(aa));
                status = it1.second;
                if (status == false) {
                    error_add_handler(name);
                }
            } else {
                error_duplicate_handler(name);
            }
        }

        auto end() -> iterator {
            return handlers_.end();
        }

        auto begin() -> iterator {
            return handlers_.begin();
        }

        auto cend() -> const_iterator {
            return handlers_.cend();
        }

        auto cbegin() -> const_iterator {
            return handlers_.cbegin();
        }

        auto begin() const -> const_iterator {
            return handlers_.begin();
        }

        auto end() const -> const_iterator {
            return handlers_.end();
        }

    private:
        storage handlers_;
    };

}} // namespace actor_zeta::base
