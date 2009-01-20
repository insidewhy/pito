#include <pito/interceptor/SystemCall.hpp>
#include <iostream>

namespace pito { namespace interceptor {

template <>
struct SystemCall<system_call::open> 
  : SystemCallHelper<library::c, int, const char *, int, mode_t> 
{
    SystemCall() : SystemCallHelper<library::c, int, const char *, int, mode_t>("open") {}
};

} }

extern "C" {

using namespace pito::interceptor;

int open(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open(" << pathname << ", " << flags << ", " << mode << ")\n";
    return PITO_SUPER(open)(pathname, flags, mode);
}

int open64(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open64(" << pathname << ", " << flags << ", " << mode << ")\n";
    return PITO_SUPER(open)(pathname, flags, mode);
}

}
