#include <pito/interceptor/SystemCall.hpp>

extern "C" {

using namespace pito::interceptor;

// #include "SystemCallsGenerated.hpp"

int open(const char *pathname, int flags, mode_t mode) {
    return system_call::instance<system_call::open>()(pathname, flags, mode);
}

int open64(const char *pathname, int flags, mode_t mode) {
    return system_call::instance<system_call::open>()(pathname, flags, mode);
}

}
