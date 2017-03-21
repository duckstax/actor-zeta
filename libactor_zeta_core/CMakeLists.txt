cmake_minimum_required(VERSION 2.8)

set(PROJECT actor-zeta-libactor_zeta_core)

project(${PROJECT} CXX)

include_directories(.)

set(HEADER_FILES
        actor-zeta/actor/abstract_actor.hpp
        actor-zeta/actor/actor.hpp
        actor-zeta/actor/actor_address.hpp
        actor-zeta/actor/blocking_actor.hpp
        actor-zeta/actor/local_actor.hpp
        actor-zeta/actor/scheduled_actor.hpp

        actor-zeta/behavior/abstract_action.hpp
        actor-zeta/behavior/action.hpp
        actor-zeta/behavior/behavior.hpp
        actor-zeta/behavior/request.hpp
        actor-zeta/behavior/response.hpp
        actor-zeta/behavior/type_action.hpp

        actor-zeta/channel/abstract_channel.hpp
        actor-zeta/channel/channel.hpp

        actor-zeta/contacts/book_contacts.hpp

        actor-zeta/environment/abstract_group.hpp
        actor-zeta/environment/adjacency_list.hpp
        actor-zeta/environment/cooperation.hpp
        actor-zeta/environment/group.hpp
        actor-zeta/environment/storage_space.hpp
        source/environment/storage_space.cpp

        actor-zeta/executor/policy/work_sharing.hpp
        actor-zeta/executor/abstract_coordinator.hpp
        actor-zeta/executor/coordinator.hpp
        actor-zeta/executor/executable.hpp
        actor-zeta/executor/execution_device.hpp
        actor-zeta/executor/time_unit.hpp
        actor-zeta/executor/worker.hpp

        actor-zeta/messaging/blocking_mail_queue.hpp
        actor-zeta/messaging/message.hpp
        actor-zeta/messaging/message_body.hpp
        actor-zeta/messaging/message_header.hpp
        actor-zeta/messaging/message_priority.hpp

        actor-zeta/standard_handlers/add_channel.hpp
        actor-zeta/standard_handlers/sync_contacts.hpp
        actor-zeta/standard_handlers/skip.hpp

        actor-zeta/environment.hpp
        actor-zeta/forwards.hpp
        actor-zeta/intrusive_ptr.hpp
        actor-zeta/ref_counted.hpp
)

set(SOURCE_FILES
        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/blocking_actor.cpp
        source/actor/local_actor.cpp
        source/actor/scheduled_actor.cpp

        source/behavior/behavior.cpp
        source/behavior/action.cpp
        source/behavior/type_action.cpp
        source/channel/channel.cpp

        source/contacts/book_contacts.cpp

        source/environment/abstract_group.cpp
        source/environment/cooperation.cpp
        source/environment/group.cpp
        source/environment/storage_space.cpp

        source/messaging/message.cpp
        source/messaging/message_header.cpp

        source/standard_handlers/add_channel.cpp
        source/standard_handlers/skip.cpp
        source/standard_handlers/sync_contacts.cpp

        source/environment.cpp
        source/ref_counted.cpp
)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES})