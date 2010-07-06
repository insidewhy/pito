#define PITO_SYSTEM_CALL_BASE  log::system_call
#define PITO_INTERCEPTOR_LOG_PID
#include <pito/interceptor/sandbox/helper.hpp>
#include <pito/interceptor/jail/libc.hpp>
#include <pito/interceptor/lib/c.hpp>
