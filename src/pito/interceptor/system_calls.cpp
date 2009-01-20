#include <pito/interceptor/SystemCall.hpp>
#include <iostream>

extern "C" {

using namespace pito::interceptor;

#define super(calltype)   system_call::instance<system_call:: calltype >()

int open(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open(" << pathname << ", " << flags << ", " << mode << ")\n";
    return super(open)(pathname, flags, mode);
}

int open64(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open64(" << pathname << ", " << flags << ", " << mode << ")\n";
    return super(open)(pathname, flags, mode);
}

#undef super

}
