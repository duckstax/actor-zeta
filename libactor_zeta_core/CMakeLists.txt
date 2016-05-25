cmake_minimum_required(VERSION 2.8.12)

set(PROJECT actor-zeta-libactor_zeta_core)

project(${PROJECT} CXX)

include_directories(.)

set(HEADER_FILES
        actor-zeta/actor/standard_handlers/sync_contacts.hpp
        actor-zeta/actor/abstract_actor.hpp
        actor-zeta/actor/actor.hpp
        actor-zeta/actor/actor_address.hpp
        actor-zeta/actor/behavior.hpp
        actor-zeta/actor/blocking_actor.hpp
        actor-zeta/actor/book_contacts.hpp
        actor-zeta/actor/local_actor.hpp

        actor-zeta/environment/cooperation.hpp
        actor-zeta/environment/group.hpp

        actor-zeta/executor/policy/work_sharing.hpp
        actor-zeta/executor/abstract_coordinator.hpp
        actor-zeta/executor/coordinator.hpp
        actor-zeta/executor/executable.hpp
        actor-zeta/executor/executor_service.hpp
        actor-zeta/executor/time_unit.hpp
        actor-zeta/executor/worker.hpp

        actor-zeta/messaging/blocking_mail_queue.hpp
        actor-zeta/messaging/mail_box.hpp
        actor-zeta/messaging/message.hpp
        actor-zeta/messaging/message_priorities.hpp

        actor-zeta/await_all_actors_done.hpp
        actor-zeta/environment.hpp
        actor-zeta/forwards.hpp
        actor-zeta/intrusive_ptr.hpp
        actor-zeta/log.hpp
        actor-zeta/ref_counted.hpp
        actor-zeta/shutdown.hpp
        actor-zeta/command.hpp
)

set(SOURCE_FILES
        source/actor/abstract_actor.cpp
        source/actor/actor.cpp
        source/actor/actor_address.cpp
        source/actor/behavior.cpp
        source/actor/book_contacts.cpp
        source/actor/local_actor.cpp

        source/environment/cooperation.cpp
        source/environment/group.cpp

        source/await_all_actors_done.cpp
        source/log.cpp
        source/ref_counted.cpp
        source/shutdown.cpp
)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES})