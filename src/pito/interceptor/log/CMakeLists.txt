set(INTERCEPTOR_NAME pito_log)

add_library(${INTERCEPTOR_NAME} SHARED libc.cpp)
target_link_libraries(${INTERCEPTOR_NAME} dl)
set_target_properties(${INTERCEPTOR_NAME} PROPERTIES VERSION 0.9.0)
install_targets(/lib ${INTERCEPTOR_NAME})
