macro(interceptor_lib _name _version)
    add_library(${_name} SHARED libc.cpp)

    # at least for netbsd.. this won't work
    if(NOT PITO_BSD)
        target_link_libraries(${_name} dl)
    endif()
    set_target_properties(${_name} PROPERTIES VERSION ${_version})
    install_targets(/lib ${_name})
endmacro()

add_subdirectory(log)
