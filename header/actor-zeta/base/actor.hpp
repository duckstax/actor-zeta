#pragma once

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>
#include <actor-zeta/detail/type_list.hpp>

//smart actor
namespace actor_zeta { namespace base {
    ///
    /// @brief An Actor's entity container
    /// \brief


    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<actor_abstract, T>::value>>
    intrusive_ptr<actor_abstract> make_actor(intrusive_ptr<T> ptr){

    }

    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<actor_abstract, T>::value>>
    intrusive_ptr<actor_abstract> make_actor(T* ptr){

    }

}} // namespace actor_zeta::base
