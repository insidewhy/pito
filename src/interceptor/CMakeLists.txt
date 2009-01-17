set(INTERCEPTOR_NAME pito_interceptor)
add_library(${INTERCEPTOR_NAME} SHARED system_calls.c)
install_targets(/lib ${INTERCEPTOR_NAME})
