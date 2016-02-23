cmake_minimum_required(VERSION 2.8.12)

set(PROJECT actor-zeta-core)

project(${PROJECT} CXX)

include_directories(BEFORE
        header
)

set(HEADER_FILES
        header/actor/standard_handlers/sync_contacts.hpp
        header/actor/abstract_actor.hpp
        header/actor/actor.hpp
        header/actor/actor_address.hpp
        header/actor/behavior.hpp
        header/actor/blocking_actor.hpp
        header/actor/book_contacts.hpp
        header/actor/local_actor.hpp

        header/environment/cooperation.hpp
        header/environment/group.hpp

        header/executor/policy/work_sharing.hpp
        header/executor/abstract_coordinator.hpp
        header/executor/coordinator.hpp
        header/executor/executable.hpp
        header/executor/executor_service.hpp
        header/executor/time_unit.hpp
        header/executor/worker.hpp

        header/messaging/blocking_mail_queue.hpp
        header/messaging/mail_box.hpp
        header/messaging/message.hpp
        header/messaging/message_priorities.hpp

        header/await_all_actors_done.hpp
        header/environment.hpp
        header/forwards.hpp
        header/intrusive_ptr.hpp
        header/log.hpp
        header/ref_counted.hpp
        header/shutdown.hpp)

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
        source/shutdown.cpp)

add_library(${PROJECT} OBJECT ${SOURCE_FILES} ${HEADER_FILES})