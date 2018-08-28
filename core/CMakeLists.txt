cmake_minimum_required(VERSION 2.8)
project(actor-zeta CXX)

set(HEADERS
  include/actor-zeta/actor/abstract_actor.hpp
  include/actor-zeta/actor/actor.hpp
  include/actor-zeta/actor/actor_address.hpp
  include/actor-zeta/actor/basic_actor.hpp
  include/actor-zeta/actor/blocking_actor.hpp
  include/actor-zeta/actor/local_actor.hpp
  include/actor-zeta/actor/async_actor.hpp
  include/actor-zeta/behavior/abstract_action.hpp
  include/actor-zeta/behavior/reactions.hpp
  include/actor-zeta/behavior/context.hpp
  include/actor-zeta/behavior/type_action.hpp
  include/actor-zeta/channel/abstract_channel.hpp
  include/actor-zeta/channel/channel.hpp 
  include/actor-zeta/environment/abstract_environment.hpp
  include/actor-zeta/environment/abstract_group.hpp
  include/actor-zeta/environment/adjacency_list.hpp
  include/actor-zeta/environment/cooperation.hpp
  include/actor-zeta/environment/environment.hpp
  include/actor-zeta/environment/group.hpp
  include/actor-zeta/environment/storage_space.hpp
  include/actor-zeta/executor/policy/work_sharing.hpp
  include/actor-zeta/executor/abstract_coordinator.hpp
  include/actor-zeta/executor/coordinator.hpp
  include/actor-zeta/executor/executable.hpp
  include/actor-zeta/executor/execution_device.hpp
  include/actor-zeta/executor/time_unit.hpp
  include/actor-zeta/executor/worker.hpp
  include/actor-zeta/messaging/blocking_mail_queue.hpp
  include/actor-zeta/messaging/mail_box.hpp
  include/actor-zeta/messaging/message.hpp
  include/actor-zeta/messaging/any.hpp
  include/actor-zeta/messaging/message_header.hpp
  include/actor-zeta/standard_handlers/add_channel.hpp
  include/actor-zeta/standard_handlers/sync_contacts.hpp
  include/actor-zeta/standard_handlers/skip.hpp
  include/actor-zeta/forwards.hpp
  include/actor-zeta/intrusive_ptr.hpp
  include/actor-zeta/metadata.hpp
  include/actor-zeta/ref_counted.hpp)

set(SOURCES
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
  source/messaging/message.cpp
  source/messaging/message_header.cpp
  source/messaging/blocking_mail_queue.cpp
  source/standard_handlers/add_channel.cpp
  source/standard_handlers/skip.cpp
  source/standard_handlers/sync_contacts.cpp
  source/ref_counted.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include)
set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ./)
