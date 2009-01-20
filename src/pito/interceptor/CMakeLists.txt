set(INTERCEPTOR_NAME pito_interceptor)

add_library(${INTERCEPTOR_NAME} SHARED system_calls.cpp)
target_link_libraries(${INTERCEPTOR_NAME} dl)
install_targets(/lib ${INTERCEPTOR_NAME})
