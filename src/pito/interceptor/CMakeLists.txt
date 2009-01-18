set(INTERCEPTOR_NAME pito_interceptor)

add_library(${INTERCEPTOR_NAME} SHARED system_calls.cpp)

#target_link_libraries(${INTERCEPTOR_NAME} /usr/lib/gcc/i686-pc-linux-gnu/4.3.2/libstdc++.a)
# target_link_libraries(${INTERCEPTOR_NAME} gcc_s)

# TODO: check gcc
set_target_properties(${INTERCEPTOR_NAME} PROPERTIES LINK_FLAGS -nostdlib)

install_targets(/lib ${INTERCEPTOR_NAME})
