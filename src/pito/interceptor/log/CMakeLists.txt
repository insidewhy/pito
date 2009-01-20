set(INTERCEPTOR_NAME pito_log)

add_library(${INTERCEPTOR_NAME} SHARED libc.cpp)
target_link_libraries(${INTERCEPTOR_NAME} dl)
install_targets(/lib ${INTERCEPTOR_NAME})
