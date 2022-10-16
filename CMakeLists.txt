# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

#include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ Standards
project(rpico-home C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

#
add_subdirectory(lamp)

include_directories(lamp)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

# create map/bin/hex/uf2 files.
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})

# Pull in our pico_stdlib which pulls in commonly used features (gpio, timer-delay etc)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    pico_stdlib
    Lamp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "${PROJECT_SOURCE_DIR}/lamp"
)
