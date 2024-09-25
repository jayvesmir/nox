cmake_minimum_required(VERSION 3.30)
project(
    nox 
    VERSION 0.0.0
    LANGUAGES CXX ASM
)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory(src main)