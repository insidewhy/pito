#ifndef _PITO_INTERCEPTOR_LOG_HELPER_
#define _PITO_INTERCEPTOR_LOG_HELPER_

#include <pito/interceptor/SystemCall.hpp>

#include <iostream>

namespace pito { namespace interceptor { namespace log {

template <class LibraryTag, class Ret, class... Args>
struct SystemCall;

template <class LibraryTag, class Ret, class... Args>
struct SystemCall<LibraryTag, Ret (Args...)> : SystemCallHelper<LibraryTag, Ret(Args...)> {
    typedef SystemCallHelper<LibraryTag, Ret(Args...)> base_t;
    SystemCall(std::string const& name) : base_t(name) {}

    Ret operator()(Args... args) {
        std::cout << "calling " << base_t::name() << std::endl;
        return base_t::operator()(args...);
    }
};

} } }

#endif
