cmake_minimum_required(VERSION 2.8)

set(project actor-zeta-core)

if (CMAKE_VERSION VERSION_LESS 3.0)
    PROJECT(${project} CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    PROJECT(${project} VERSION "${CMAKE_PROJECT_VERSION}" LANGUAGES CXX)
endif()

include_directories(.)

set(HEADER_FILES
        actor-zeta/actor/abstract_action.hpp
        actor-zeta/actor/abstract_actor.hpp
        actor-zeta/actor/actor.hpp
        actor-zeta/actor/actor_address.hpp
        actor-zeta/actor/async_actor.hpp
        actor-zeta/actor/basic_actor.hpp
        actor-zeta/actor/blocking_actor.hpp
        actor-zeta/actor/context.hpp
        actor-zeta/actor/local_actor.hpp
        actor-zeta/actor/reactions.hpp
        actor-zeta/actor/type_action.hpp

        actor-zeta/channel/abstract_channel.hpp
        actor-zeta/channel/channel.hpp

        actor-zeta/detail/type_traits/callable_trait.hpp
        actor-zeta/detail/type_traits/type_list.hpp

        actor-zeta/environment/abstract_environment.hpp
        actor-zeta/environment/abstract_group.hpp
        actor-zeta/detail/adjacency_list.hpp
        actor-zeta/environment/cooperation.hpp
        actor-zeta/environment/environment.hpp
        actor-zeta/environment/group.hpp
        actor-zeta/environment/storage_space.hpp

        actor-zeta/executor/policy/unprofiled.hpp
        actor-zeta/executor/policy/work_sharing.hpp
        actor-zeta/executor/abstract_executor.hpp
        actor-zeta/executor/executor.hpp
        actor-zeta/executor/executable.hpp
        actor-zeta/executor/execution_device.hpp
        actor-zeta/executor/worker.hpp

        actor-zeta/messaging/blocking_mail_queue.hpp
        actor-zeta/messaging/mail_box.hpp
        actor-zeta/messaging/message.hpp
        actor-zeta/detail/any.hpp
        actor-zeta/messaging/message_header.hpp

        actor-zeta/forwards.hpp
        actor-zeta/intrusive_ptr.hpp
        actor-zeta/metadata.hpp
        actor-zeta/ref_counted.hpp
)

set(SOURCE_FILES

        source/actor/abstract_action.cpp
        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/async_actor.cpp
        source/actor/blocking_actor.cpp
        source/actor/context.cpp
        source/actor/local_actor.cpp
        source/actor/reactions.cpp
        source/actor/type_action.cpp

        source/channel/abstract_channel.cpp
        source/channel/channel.cpp

        source/environment/abstract_environment.cpp
        source/environment/storage_space.cpp
        source/environment/abstract_group.cpp
        source/environment/cooperation.cpp
        source/environment/environment.cpp
        source/environment/group.cpp
        source/environment/storage_space.cpp

        source/executor/abstract_executor.cpp
        source/executor/executable.cpp
        source/executor/execution_device.cpp

        source/messaging/message.cpp
        source/messaging/message_header.cpp
        source/messaging/blocking_mail_queue.cpp

        source/ref_counted.cpp
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
