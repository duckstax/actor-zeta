cmake_minimum_required(VERSION 2.8)

include_directories(.)

set(PREFIX "${CMAKE_CURRENT_SOURCE_DIR}")

set(HEADERS ${HEADERS}
        ${PREFIX}/actor-zeta/actor/abstract_actor.hpp
        ${PREFIX}/actor-zeta/actor/actor.hpp
        ${PREFIX}/actor-zeta/actor/actor_address.hpp
        ${PREFIX}/actor-zeta/actor/basic_actor.hpp
        ${PREFIX}/actor-zeta/actor/blocking_actor.hpp
        ${PREFIX}/actor-zeta/actor/local_actor.hpp
        ${PREFIX}/actor-zeta/actor/async_actor.hpp

        ${PREFIX}/actor-zeta/behavior/abstract_action.hpp
        ${PREFIX}/actor-zeta/behavior/reactions.hpp
        ${PREFIX}/actor-zeta/behavior/context.hpp
        ${PREFIX}/actor-zeta/behavior/type_action.hpp

        ${PREFIX}/actor-zeta/channel/abstract_channel.hpp
        ${PREFIX}/actor-zeta/channel/channel.hpp

        ${PREFIX}/actor-zeta/environment/abstract_environment.hpp
        ${PREFIX}/actor-zeta/environment/abstract_group.hpp
        ${PREFIX}/actor-zeta/environment/adjacency_list.hpp
        ${PREFIX}/actor-zeta/environment/cooperation.hpp
        ${PREFIX}/actor-zeta/environment/environment.hpp
        ${PREFIX}/actor-zeta/environment/group.hpp
        ${PREFIX}/actor-zeta/environment/storage_space.hpp

        ${PREFIX}/actor-zeta/executor/policy/work_sharing.hpp
        ${PREFIX}/actor-zeta/executor/abstract_coordinator.hpp
        ${PREFIX}/actor-zeta/executor/coordinator.hpp
        ${PREFIX}/actor-zeta/executor/executable.hpp
        ${PREFIX}/actor-zeta/executor/execution_device.hpp
        ${PREFIX}/actor-zeta/executor/time_unit.hpp
        ${PREFIX}/actor-zeta/executor/worker.hpp

        ${PREFIX}/actor-zeta/messaging/blocking_mail_queue.hpp
        ${PREFIX}/actor-zeta/messaging/mail_box.hpp
        ${PREFIX}/actor-zeta/messaging/message.hpp
        ${PREFIX}/actor-zeta/messaging/any.hpp
        ${PREFIX}/actor-zeta/messaging/message_header.hpp

        ${PREFIX}/actor-zeta/standard_handlers/add_channel.hpp
        ${PREFIX}/actor-zeta/standard_handlers/sync_contacts.hpp
        ${PREFIX}/actor-zeta/standard_handlers/skip.hpp

        ${PREFIX}/actor-zeta/forwards.hpp
        ${PREFIX}/actor-zeta/intrusive_ptr.hpp
        ${PREFIX}/actor-zeta/metadata.hpp
        ${PREFIX}/actor-zeta/ref_counted.hpp

        PARENT_SCOPE
)

set(SOURCES "${SOURCES}"
        ${PREFIX}/source/actor/abstract_actor.cpp
        ${PREFIX}/source/actor/actor.cpp
        ${PREFIX}/source/actor/actor_address.cpp
        ${PREFIX}/source/actor/blocking_actor.cpp
        ${PREFIX}/source/actor/local_actor.cpp
        ${PREFIX}/source/actor/async_actor.cpp

        ${PREFIX}/source/behavior/reactions.cpp
        ${PREFIX}/source/behavior/context.cpp
        ${PREFIX}/source/behavior/type_action.cpp
        ${PREFIX}/source/behavior/abstract_action.cpp

        ${PREFIX}/source/channel/abstract_channel.cpp
        ${PREFIX}/source/channel/channel.cpp

        ${PREFIX}/source/environment/abstract_environment.cpp
        ${PREFIX}/source/environment/storage_space.cpp
        ${PREFIX}/source/environment/abstract_group.cpp
        ${PREFIX}/source/environment/cooperation.cpp
        ${PREFIX}/source/environment/environment.cpp
        ${PREFIX}/source/environment/group.cpp
        ${PREFIX}/source/environment/storage_space.cpp

        ${PREFIX}/source/messaging/message.cpp
        ${PREFIX}/source/messaging/message_header.cpp
        ${PREFIX}/source/messaging/blocking_mail_queue.cpp

        ${PREFIX}/source/standard_handlers/add_channel.cpp
        ${PREFIX}/source/standard_handlers/skip.cpp
        ${PREFIX}/source/standard_handlers/sync_contacts.cpp
        ${PREFIX}/source/ref_counted.cpp

        PARENT_SCOPE
)

set(IMPORT_LOCATIONS "${IMPORT_LOCATIONS}" ${CMAKE_CURRENT_SOURCE_DIR}/io PARENT_SCOPE)
