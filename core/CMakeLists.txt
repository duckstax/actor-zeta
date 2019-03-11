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
        actor-zeta/actor/abstract_actor.hpp
        actor-zeta/actor/actor.hpp
        actor-zeta/actor/actor_address.hpp
        actor-zeta/actor/basic_actor.hpp
        actor-zeta/actor/blocking_actor.hpp
        actor-zeta/actor/local_actor.hpp
        actor-zeta/actor/async_actor.hpp

        actor-zeta/behavior/abstract_action.hpp
        actor-zeta/behavior/reactions.hpp
        actor-zeta/behavior/context.hpp
        actor-zeta/behavior/type_action.hpp

        actor-zeta/channel/abstract_channel.hpp
        actor-zeta/channel/channel.hpp

        actor-zeta/detail/contaner/hashmap.h

        actor-zeta/detail/type_traits/callable_trait.hpp
        actor-zeta/detail/type_traits/type_list.hpp

        actor-zeta/environment/abstract_environment.hpp
        actor-zeta/environment/abstract_group.hpp
        actor-zeta/environment/adjacency_list.hpp
        actor-zeta/environment/cooperation.hpp
        actor-zeta/environment/environment.hpp
        actor-zeta/environment/group.hpp
        actor-zeta/environment/storage_space.hpp

        actor-zeta/executor/policy/unprofiled.hpp
        actor-zeta/executor/policy/work_sharing.hpp
        actor-zeta/executor/abstract_coordinator.hpp
        actor-zeta/executor/coordinator.hpp
        actor-zeta/executor/executable.hpp
        actor-zeta/executor/execution_device.hpp
        actor-zeta/executor/worker.hpp

        actor-zeta/messaging/blocking_mail_queue.hpp
        actor-zeta/messaging/mail_box.hpp
        actor-zeta/messaging/message.hpp
        actor-zeta/messaging/any.hpp
        actor-zeta/messaging/message_header.hpp

        actor-zeta/standard_handlers/add_channel.hpp
        actor-zeta/standard_handlers/sync_contacts.hpp
        actor-zeta/standard_handlers/skip.hpp

        actor-zeta/forwards.hpp
        actor-zeta/intrusive_ptr.hpp
        actor-zeta/metadata.hpp
        actor-zeta/ref_counted.hpp
)

set(SOURCE_FILES
        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/blocking_actor.cpp
        source/actor/local_actor.cpp
        source/actor/async_actor.cpp

        source/behavior/reactions.cpp
        source/behavior/context.cpp
        source/behavior/type_action.cpp
        source/behavior/abstract_action.cpp

        source/channel/abstract_channel.cpp
        source/channel/channel.cpp

        source/environment/abstract_environment.cpp
        source/environment/storage_space.cpp
        source/environment/abstract_group.cpp
        source/environment/cooperation.cpp
        source/environment/environment.cpp
        source/environment/group.cpp
        source/environment/storage_space.cpp

        source/executor/abstract_coordinator.cpp
        source/executor/executable.cpp
        source/executor/execution_device.cpp

        source/messaging/message.cpp
        source/messaging/message_header.cpp
        source/messaging/blocking_mail_queue.cpp

        source/standard_handlers/add_channel.cpp
        source/standard_handlers/skip.cpp
        source/standard_handlers/sync_contacts.cpp
        source/ref_counted.cpp
)

find_package( Threads )

add_library(
        ${PROJECT_NAME} ${BUILD_TYPE}
        ${SOURCE_FILES}
        ${HEADER_FILES}
)


set_target_properties( ${PROJECT} PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/core)

target_link_libraries (
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

if (ALLOW_TESTS)
    add_subdirectory(test)
endif ()
