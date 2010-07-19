add_custom_target(test)
macro(pito_test _testType _testName _testArgs)
    add_executable(${_testName} ${_testName}.c)
    add_custom_command(
        SOURCE test
        TARGET test
        COMMAND
        rm -rf .tmp && mkdir .tmp && cd .tmp && touch existing &&
        LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugin
                ${CMAKE_BINARY_DIR}/pito ${_testType}
                ${_testArgs} ${CMAKE_CURRENT_BINARY_DIR}/${_testName}
        DEPENDS ${_testName})
endmacro()

pito_test(sandbox break_sandbox "-b/")
