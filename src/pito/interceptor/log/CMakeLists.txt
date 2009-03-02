set(INTERCEPTOR_NAME pito_log)

add_library(${INTERCEPTOR_NAME} SHARED libc.cpp)

# at least for netbsd.. this won't work
if(NOT PITO_BSD)
    target_link_libraries(${INTERCEPTOR_NAME} dl)
endif()
set_target_properties(${INTERCEPTOR_NAME} PROPERTIES VERSION 0.9.1)
install_targets(/lib ${INTERCEPTOR_NAME})
