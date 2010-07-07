macro(interceptor_lib __name _version _sources)
    set(_name pito_${__name})
    add_library(${_name} SHARED ${_sources})

    # at least for netbsd.. this won't work
    if(NOT PITO_BSD)
        target_link_libraries(${_name} dl)
    endif()
    set_target_properties(${_name} PROPERTIES VERSION ${_version})
    install_targets(/lib ${_name})

    set(_libname lib${_name}.so)
    exec_program(ln ARGS -sf
        ${__name}/${_libname} ${CMAKE_CURRENT_BINARY_DIR}/../${_libname})
endmacro()

add_subdirectory(log)
add_subdirectory(sandbox)
