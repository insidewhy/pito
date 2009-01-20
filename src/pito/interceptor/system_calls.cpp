#include <pito/interceptor/SystemCall.hpp>

extern "C" {

using namespace pito::interceptor;

// #include "SystemCallsGenerated.hpp"

int open(const char *pathname, int flags, mode_t mode) {
    return -1;
}

int open64(const char *pathname, int flags, mode_t mode) {
    return -1;
}

}
