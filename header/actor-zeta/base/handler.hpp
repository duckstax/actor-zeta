#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/unique_function.hpp>

namespace actor_zeta { namespace base {

    enum class status : uint8_t {
        await = 0x00,
        yield = 0x01,
        finish = 0x02,
    };

    template<class Target,class Status>
    class handler {
    public:
        handler() = delete;
        handler(const handler&) = delete;
        handler& operator=(const handler&) = delete;
        handler(handler&&) = default;
        handler& operator=(handler&&) = default;
        handler(Target out, status ){

        }
    private:
        Target out_;
        Status status_;
    };
    ///handler<mailbox::message*,status>
    using action = detail::unique_function<void(mailbox::message*)>;

    template<typename F>
    auto make_handler(F&& f)-> action ;

    template<typename ClassPtr,typename F>
    auto make_handler(ClassPtr*self,F&& f ) -> action ;

}} // namespace actor_zeta::base
