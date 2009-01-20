#include <pito/interceptor/SystemCall.hpp>
#include <pito/interceptor/log/helper.hpp>
#include <iostream>

namespace pito { namespace interceptor {

namespace system_call {
    struct open {};
};

template <>
struct SystemCall<system_call::open> 
  : SystemCallHelper<library::c, int(const char *, int, mode_t)> 
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, int, mode_t)>("open") {}
};

} }

