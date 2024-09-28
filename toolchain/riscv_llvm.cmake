FIND_FILE(COMPILER "clang++" PATHS ENV INCLUDE)

if (NOT EXISTS ${COMPILER})
    message(ERROR "couldn't find clang++")
endif()

message("clang++ found: ${COMPILER}")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR rv64gc)

set(CMAKE_AR ${COMPILER})
set(CMAKE_ASM_COMPILER ${COMPILER})
set(CMAKE_CXX_COMPILER ${COMPILER})

set(COMMON_FLAGS "--target=riscv64 -mcmodel=medany -march=${CMAKE_SYSTEM_PROCESSOR} -nostdlib -ffreestanding -fno-exceptions -fno-inline -Wall -Wextra -Wpedantic")

if (CMAKE_BUILD_TYPE STREQUAL "debug")
    set(COMMON_FLAGS "${COMMON_FLAGS} -ggdb -g3 -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "release")
    set(COMMON_FLAGS "${COMMON_FLAGS} -O3")
endif()

set(CMAKE_CXX_STANDARD 20)
set(NOX_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/link/riscv_qemu.ld")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} -T ${NOX_LINKER_SCRIPT}")