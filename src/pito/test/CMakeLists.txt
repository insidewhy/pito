add_executable(break_jail break_jail.c)

add_custom_target(
    test
    COMMAND LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/interceptor/log pito log ${CMAKE_CURRENT_BINARY_DIR}/break_jail
    DEPENDS break_jail)
