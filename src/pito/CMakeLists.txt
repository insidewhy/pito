cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

include(C++0x)
project(pito)

set(CONFIG_DIR_SUFFIX /pito)
set(SHARE_DIR_SUFFIX ${CONFIG_DIR_SUFFIX})
include(Installer)
configure_file(${CMAKE_SOURCE_DIR}/config.hpp.cmake ${CMAKE_BINARY_DIR}/config.hpp)

include_directories(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/..)

add_subdirectory(interceptor)

add_executable(pito pito.cpp)
install_targets(/bin pito)

