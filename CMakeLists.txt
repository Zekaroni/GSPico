cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
project(major C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
pico_sdk_init()

add_executable(major ./src/major.cpp)
target_link_libraries(major pico_stdlib pico_multicore)
pico_add_extra_outputs(major)