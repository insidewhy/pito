cmake_minimum_required(VERSION 2.6)

set(project_root ../..)
find_path(CHILON_DIR chilon/cmake ${project_root}/.. ..)
set(CMAKE_MODULE_PATH ${CHILON_DIR}/chilon/cmake/modules)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
project(pito)
include(C++0x)

################################################################################
# configuration
set(CONFIG_DIR_SUFFIX /pito)
set(SHARE_DIR_SUFFIX ${CONFIG_DIR_SUFFIX})
include(Installer)

include(CheckTypeSize)
check_type_size(__off64_t OFF64_SIZE)
if(OFF64_SIZE)
    set(OFF64_TYPE __off64_t)
else()
    set(OFF64_TYPE off_t)
endif()

if(APPLE)
    set(PITO_APPLE 1)
else()
    exec_program(uname ARGS -s OUTPUT_VARIABLE arch_s)
    if (arch_s MATCHES BSD)
        set(PITO_BSD 1)
    endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/config.hpp.cmake ${CMAKE_SOURCE_DIR}/config.hpp)
# end configuration
################################################################################

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/..)

add_subdirectory(interceptor)

if(TESTING)
    add_subdirectory(test)
endif()

add_executable(pito pito.cpp config.hpp)
install_targets(/bin pito)
installDirectory(${CMAKE_SOURCE_DIR}/.. ${INCLUDE_DIR} .hpp$)
