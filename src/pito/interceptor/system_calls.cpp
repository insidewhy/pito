#include <pito/interceptor/SystemCall.hpp>

#include <sys/types.h>

extern "C" {

using namespace pito::interceptor;

// #include "SystemCallsGenerated.hpp"

int open(const char *pathname, int flags, mode_t mode) {
}

int open64(const char *pathname, int flags, mode_t mode) {
}

}
