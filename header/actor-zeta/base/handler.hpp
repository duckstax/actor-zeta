#pragma once

#include <functional>

#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief Abstract concept of an action
    ///
    class handler {
    public:
        virtual ~handler() = default;

        virtual void invoke(communication_module&) = 0;
    };

    class helper final : public handler {
    public:
        ~helper() override = default;

        template<typename F>
        helper(F&& f);

        template<typename F, typename ClassPtr>
        helper(F&& f, ClassPtr* self);

        void invoke(communication_module& ctx) final {
            helper_(ctx);
        }

    private:
        std::function<void(communication_module&)> helper_;
    };

    template<typename F>
    inline auto make_handler(F&& f) -> handler* {
        return new helper(std::forward<F>(f));
    }

    template<typename F, typename ClassPtr>
    inline auto make_handler(F&& f, ClassPtr* self) -> handler* {
        return new helper(std::forward<F>(f), self);
    }

}} // namespace actor_zeta::base
