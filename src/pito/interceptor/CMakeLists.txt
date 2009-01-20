set(INTERCEPTOR_NAME pito_interceptor)

add_library(${INTERCEPTOR_NAME} SHARED system_calls.cpp)
target_link_libraries(${INTERCEPTOR_NAME} dl)
set_target_properties(${INTERCEPTOR_NAME} PROPERTIES LINK_FLAGS -nostdlib)
install_targets(/lib ${INTERCEPTOR_NAME})
