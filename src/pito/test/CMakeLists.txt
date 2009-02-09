macro(log_test _testName)
    add_executable(${_testName} ${_testName}.c)
    add_custom_target(
        test
        COMMAND LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/interceptor/log pito log ${CMAKE_CURRENT_BINARY_DIR}/${_testName}
        DEPENDS ${_testName})
endmacro()

log_test(break_jail)
