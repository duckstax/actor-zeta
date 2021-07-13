#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace executor {
    ///
    /// @brief
    ///

    ///
    /// @enum
    /// @brief
    ///
    enum class executable_result : uint8_t {
        resume,
        awaiting,
        done,
        shutdown
    };

    struct executable {
        executable() = default;

        virtual ~executable();

        virtual void intrusive_ptr_add_ref_impl() = 0;

        virtual void intrusive_ptr_release_impl() = 0;

        virtual auto run(execution_device*, size_t max_throughput) -> executable_result = 0;
    };

    template<class T>
    auto intrusive_ptr_add_ref(T* ptr) -> typename std::enable_if<std::is_same<T*, executable*>::value>::type {
        ptr->intrusive_ptr_add_ref_impl();
    }

    template<class T>
    auto intrusive_ptr_release(T* ptr) -> typename std::enable_if<std::is_same<T*, executable*>::value>::type {
        ptr->intrusive_ptr_release_impl();
    }

}} // namespace actor_zeta::executor
