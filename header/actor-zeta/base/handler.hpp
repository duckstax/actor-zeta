#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/unique_function.hpp>

namespace actor_zeta { namespace base {

    /**
     * @brief Abstract concept of an action
     *
     */
    using action = detail::unique_function<void(mailbox::message*)>;

    /**
     * @brief
     *
     * @tparam F
     * @param memory_resource
     * @param f
     * @return action
     */
    template<typename F>
    auto make_handler(actor_zeta::detail::pmr::memory_resource* memory_resource, F&& f)-> action;

    /**
     * @brief
     *
     * @tparam F
     * @tparam ClassPtr
     * @param memory_resource
     * @param f
     * @param self
     * @return action
     */
    template<typename F, typename ClassPtr>
    auto make_handler(actor_zeta::detail::pmr::memory_resource* memory_resource, F&& f, ClassPtr* self) -> action;

}} // namespace actor_zeta::base
