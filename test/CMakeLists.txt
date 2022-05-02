#available tests

include_directories(.)
include_directories(../header/)

add_subdirectory(tooltestsuites)

add_subdirectory(handler)
add_subdirectory(actor-id)
add_subdirectory(intrusive_ptr)
add_subdirectory(memory_resource)
add_subdirectory(message)
add_subdirectory(message-id)
add_subdirectory(metaprogramming)
add_subdirectory(polymorphic_allocator)
add_subdirectory(spawn-actor)
add_subdirectory(rtt)
add_subdirectory(timer)
