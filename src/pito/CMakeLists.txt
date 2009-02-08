cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
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
set(PITO_APPLE ${APPLE})

configure_file(${CMAKE_SOURCE_DIR}/config.hpp.cmake ${CMAKE_SOURCE_DIR}/config.hpp)
# end configuration
################################################################################

include_directories(${CMAKE_SOURCE_DIR}/..)

add_subdirectory(interceptor)
add_subdirectory(test)

add_executable(pito pito.cpp config.hpp)
install_targets(/bin pito)
installDirectory(${CMAKE_SOURCE_DIR} ${INCLUDE_DIR}/pito .hpp$)
