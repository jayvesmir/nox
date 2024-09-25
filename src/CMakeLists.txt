cmake_minimum_required(VERSION 3.30)

file(GLOB_RECURSE NOX_ASM ${CMAKE_CURRENT_SOURCE_DIR} *.asm)
file(GLOB_RECURSE NOX_CXX ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
set(NOX_SOURCES ${NOX_ASM} ${NOX_CXX})

add_executable(${PROJECT_NAME} ${NOX_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE std)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    LINK_DEPENDS ${NOX_LINKER_SCRIPT}
)