cmake_minimum_required(VERSION 3.0)

PROJECT(actor-zeta LANGUAGES C CXX)

message(STATUS "CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_C_COMPILER_ID = ${CMAKE_C_COMPILER_ID}")
message(STATUS "STANDARD CPP = ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") #------------------------------------- Clang
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    list(APPEND CMAKE_MODULE_PATH "${LLVM_DIR}")
endif() #--------------------------------------------------------------------------- Clang

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard whose features are requested.")
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

option(ALLOW_EXAMPLES               "ALLOW EXAMPLES"            OFF)
option(ALLOW_TESTS                  "ALLOW TESTS"               OFF)
option(ENABLE_TESTS_MEASUREMENTS    "ENABLE TESTS MEASUREMENTS" OFF)
option(ALLOW_BENCHMARK              "ALLOW BENCHMARK"           OFF)
option(RTTI_DISABLE                 "RTTI DISABLE"              ON)
option(EXCEPTIONS_DISABLE           "EXCEPTIONS DISABLE"        ON)

message(STATUS "ALLOW_EXAMPLES = ${ALLOW_EXAMPLES}")
message(STATUS "ALLOW_TESTS = ${ALLOW_TESTS}")
message(STATUS "ENABLE_TESTS_MEASUREMENTS = ${ENABLE_TESTS_MEASUREMENTS}")
message(STATUS "ALLOW_BENCHMARK = ${ALLOW_BENCHMARK}")
message(STATUS "RTTI_DISABLE = ${RTTI_DISABLE}")
message(STATUS "EXCEPTIONS_DISABLE = ${EXCEPTIONS_DISABLE}")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE
      STRING "Build type (default Debug):" FORCE)
endif()

add_compile_options(
  "$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:DEBUG>>:-fno-rtti;-Wall>"
  "$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:RELEASE>>:-fno-rtti;-Wall>"
)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") #------------------------------------- Clang
    ############## LLVM CONFIGURATION #################
    # https://github.com/nsumner/llvm-demo Example LLVM Build

    # LLVM_DIR must be set to the prefix of /share/llvm/cmake via commandline
    find_package(LLVM REQUIRED CONFIG)
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

    # We incorporate the CMake features provided by LLVM:
    list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
    include(AddLLVM)

    message("LLVM STATUS:
        Definitions ${LLVM_DEFINITIONS}
        Includes    ${LLVM_INCLUDE_DIRS}
        Libraries   ${LLVM_LIBRARY_DIRS}
        Targets     ${LLVM_TARGETS_TO_BUILD}
        CXX         ${CMAKE_CXX_COMPILER}
        C           ${CMAKE_C_COMPILER}"
    )

    # Now set the LLVM header and library paths:
    include_directories(
        ${LLVM_INCLUDE_DIRS}
        ${LLVM_INCLUDE_DIRS}/c++/v1
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/header)

    link_directories(${LLVM_LIBRARY_DIRS})
    add_definitions(${LLVM_DEFINITIONS})

else() #---------------------------------------------------------------------------- GNU
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/header)
endif() #--------------------------------------------------------------------------- Clang

############## FINAL PROJECT CONFIG #################

file(GLOB ${PROJECT_NAME}_HEADERS
    header/actor-zeta/base/*.hpp
    header/actor-zeta/base/*.h

    header/actor-zeta/detail/queue/*.hpp
    header/actor-zeta/detail/queue/*.h

    header/actor-zeta/detail/pmr/*.hpp
    header/actor-zeta/detail/pmr/*.h

    header/actor-zeta/detail/*.hpp
    header/actor-zeta/detail/*.h

    header/actor-zeta/scheduler/policy/*.hpp
    header/actor-zeta/scheduler/policy/*.h

    header/actor-zeta/scheduler/*.hpp
    header/actor-zeta/scheduler/*.h

    header/actor-zeta/mailbox/*.hpp
    header/actor-zeta/mailbox/*.h

    header/actor-zeta/*.hpp
    header/actor-zeta/*.h

    header/*.hpp
    header/*.h
)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") #------------------------------------- Clang
    find_library(CLANG_LIBCPP
        NAMES libc++ c++
        HINTS ${LLVM_LIBRARY_DIRS})

    find_library(CLANG_LIBCPP_ABI
        NAMES libc++abi c++abi
        HINTS ${LLVM_LIBRARY_DIRS})

    message(STATUS "Find CLANG_LIBCPP=${CLANG_LIBCPP}")
    message(STATUS "Find CLANG_LIBCPP_ABI=${CLANG_LIBCPP_ABI}")
    ### https://stackoverflow.com/questions/43662736/cmake-switch-between-clang-g-and-libc-libstdc
    if (${CLANG_LIBCPP} MATCHES "CLANG_LIBCPP-NOTFOUND")
        set(LIBCXX "libstdc++11")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
        set(LIBCXX "libc++")
    endif()

    if (${CLANG_LIBCPP_ABI} MATCHES "CLANG_LIBCPP_ABI-NOTFOUND")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++abi")
    endif()

else() #---------------------------------------------------------------------------- GNU
    set(LIBCXX "libstdc++11")
endif() #--------------------------------------------------------------------------- Clang

add_library(
    ${PROJECT_NAME} SHARED
    source/src.cpp
    ${${PROJECT_NAME}_HEADERS}
)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") #------------------------------------- Clang
    ### https://stackoverflow.com/questions/62926242/how-to-link-all-llvm-libraries-in-cmake
    execute_process(COMMAND llvm-config --libs all
                    OUTPUT_VARIABLE REQ_LLVM_LIBRARIES)

    #llvm_map_components_to_libnames(REQ_LLVM_LIBRARIES
    #  ${LLVM_TARGETS_TO_BUILD}
    #  core asmparser linker bitreader bitwriter irreader
    #  target mc support native
    #  all #all-targets amdgpu amdgpuasmparser amdgpucodegen amdgpudesc amdgpudisassembler amdgpuinfo amdgpuutils analysis arm armasmparser armcodegen armdesc armdisassembler arminfo armutils asmparser asmprinter avr avrasmparser avrcodegen avrdesc avrdisassembler avrinfo binaryformat bitreader bitstreamreader bitwriter bpf bpfasmparser bpfcodegen bpfdesc bpfdisassembler bpfinfo cfguard codegen core coroutines coverage debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb demangle dlltooldriver dwarflinker engine executionengine frontendopenmp fuzzmutate globalisel hexagon hexagonasmparser hexagoncodegen hexagondesc hexagondisassembler hexagoninfo instcombine instrumentation interpreter ipo irreader jitlink lanai lanaiasmparser lanaicodegen lanaidesc lanaidisassembler lanaiinfo libdriver lineeditor linker lto mc mca mcdisassembler mcjit mcparser mips mipsasmparser mipscodegen mipsdesc mipsdisassembler mipsinfo mirparser msp430 msp430asmparser msp430codegen msp430desc msp430disassembler msp430info native nativecodegen nvptx nvptxcodegen nvptxdesc nvptxinfo objcarcopts object objectyaml option orcerror orcjit passes perfjitevents powerpc powerpcasmparser powerpccodegen powerpcdesc powerpcdisassembler powerpcinfo profiledata remarks riscv riscvasmparser riscvcodegen riscvdesc riscvdisassembler riscvinfo riscvutils runtimedyld scalaropts selectiondag sparc sparcasmparser sparccodegen sparcdesc sparcdisassembler sparcinfo support symbolize systemz systemzasmparser systemzcodegen systemzdesc systemzdisassembler systemzinfo tablegen target textapi transformutils vectorize webassembly webassemblyasmparser webassemblycodegen webassemblydesc webassemblydisassembler webassemblyinfo windowsmanifest x86 x86asmparser x86codegen x86desc x86disassembler x86info x86utils xcore xcorecodegen xcoredesc xcoredisassembler xcoreinfo xray
    #)

    target_link_libraries(${PROJECT_NAME}
        INTERFACE ${REQ_LLVM_LIBRARIES}
    )
endif() #--------------------------------------------------------------------------- Clang

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)

#################################################################

# configuration
#############################################################################################
#conan

if (CONAN_EXPERIMENTAL_INCLUDE)
    set(CONAN_SYSTEM_INCLUDES "On")
endif ()
include(conan.cmake)

# https://docs.conan.io/1/reference/config_files/settings.yml.html#c-standard-libraries-aka-compiler-libcxx
#conan_cmake_autodetect(CONAN_SETTINGS)
set(CONAN_SETTINGS "build_type=${CMAKE_BUILD_TYPE};compiler.libcxx=${LIBCXX};compiler.cppstd=${CMAKE_CXX_STANDARD}")

message(STATUS "CONAN_SETTINGS: ${CONAN_SETTINGS}")

conan_cmake_run(REQUIRES
    catch2/2.13.6
#    benchmark/1.6.2
    BASIC_SETUP CMAKE_TARGETS
    SETTINGS ${CONAN_SETTINGS}
    ENV CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER}
    BUILD missing
)

# configuration
#############################################################################################
#conan

if (ALLOW_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
