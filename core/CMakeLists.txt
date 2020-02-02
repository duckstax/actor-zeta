cmake_minimum_required(VERSION 2.8)

set(project actor-zeta-core)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

include_directories(SYSTEM .)

set(HEADER_FILES
        actor-zeta/base/abstract_actor.hpp
        actor-zeta/base/actor.hpp
        actor-zeta/base/actor_address.hpp
        actor-zeta/base/cooperative_actor.hpp
        actor-zeta/base/basic_actor.hpp
        actor-zeta/base/blocking_actor.hpp
        actor-zeta/base/communication_module.hpp
        actor-zeta/base/context.hpp
        actor-zeta/base/dispatcher.hpp
        actor-zeta/base/handler.hpp
        actor-zeta/base/metadata.hpp
        actor-zeta/base/supervisor.hpp

        actor-zeta/detail/any.hpp
        actor-zeta/detail/callable_trait.hpp
        actor-zeta/detail/intrusive_ptr.hpp
        actor-zeta/detail/ref_counted.hpp
        actor-zeta/detail/string_view.hpp
        actor-zeta/detail/type_list.hpp
        actor-zeta/detail/type_traits.hpp

        actor-zeta/executor/policy/profiled.hpp
        actor-zeta/executor/policy/unprofiled.hpp
        actor-zeta/executor/policy/work_sharing.hpp
        actor-zeta/executor/abstract_executor.hpp
        actor-zeta/executor/executor.hpp
        actor-zeta/executor/executable.hpp
        actor-zeta/executor/profiled_executor.hpp
        actor-zeta/executor/execution_device.hpp
        actor-zeta/executor/worker.hpp

        actor-zeta/messaging/blocking_mail_queue.hpp
        actor-zeta/messaging/mail_box.hpp
        actor-zeta/messaging/message.hpp
        actor-zeta/messaging/message_header.hpp

        actor-zeta/forwards.hpp
)

set(SOURCE_FILES

        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/cooperative_actor.cpp
        source/actor/blocking_actor.cpp
        source/actor/dispatcher.cpp
        source/actor/supervisor.cpp
        source/actor/communication_module.cpp

        source/detail/string_view.cpp
        source/detail/ref_counted.cpp

        source/executor/abstract_executor.cpp
        source/executor/executable.cpp
        source/executor/execution_device.cpp

        source/messaging/message.cpp
        source/messaging/message_header.cpp
        source/messaging/blocking_mail_queue.cpp
)

add_library(
        ${PROJECT_NAME} OBJECT
        ${SOURCE_FILES}
        ${HEADER_FILES}
)


target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

if (ALLOW_TESTS)
    add_subdirectory(test)
endif ()
