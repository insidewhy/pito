add_custom_target(test)
macro(pito_test _testType _testName)
    add_executable(${_testName} ${_testName}.c)
    add_custom_command(
        SOURCE test
        TARGET test
        COMMAND LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/interceptor/${_testType}
                ${CMAKE_BINARY_DIR}/pito ${_testType}
                ${CMAKE_CURRENT_BINARY_DIR}/${_testName}
        DEPENDS ${_testName})
endmacro()

pito_test(log break_jail)
pito_test(log break_fs_jail)
