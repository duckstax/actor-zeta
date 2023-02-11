#pragma once

#include "forwards.hpp"
#include <actor-zeta/detail/intrusive_ptr.hpp>

#include <type_traits>

namespace actor_zeta { namespace base {


    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, T>::value>>
    intrusive_ptr<supervisor_abstract> make_supervisor(intrusive_ptr<T> ptr){

    }

    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, T>::value>>
    intrusive_ptr<supervisor_abstract> make_supervisor(T* ptr){

    }


}} // namespace actor_zeta::base
