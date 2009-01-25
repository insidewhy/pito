#ifndef _PITO_INTERCEPTOR_JAIL_LIBC_HPP_
#define _PITO_INTERCEPTOR_JAIL_LIBC_HPP_

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallBase
#endif

#define PITO_USING_JAIL
#define PITO_JAIL_BASE jail::SystemCall

#include <pito/interceptor/SystemCall.hpp>

#include <pito/interceptor/lib/c_traits.hpp>
#include <pito/interceptor/jail/environment.hpp>
#include "config.hpp"

#include <stdarg.h>
#include <fcntl.h>

#include <algorithm>

#ifndef NDEBUG
#include <iostream>
#endif

namespace pito { namespace interceptor { namespace jail {

struct Init {
    Init() {
        char const *begin = jail::getenv(PITO_LD_PRELOAD);
        if (begin) {
            preload = begin;
            // TODO: find the library properly like this
            // char const *end = begin;
            // while (*(++end) != '\0') {}

            // char const *colon = begin;
            // do {
            //     colon = std::find(colon + 1, end, ':');
            //     // std::cout << "got preload entry (" << begin << ")" << std::endl;
            //     // TODO: test if range(begin,colon) matches libpito_[a-z]+.so

            //     begin = colon;
            // } while (colon != end);
        }
#if ! defined(NDEBUG) && ! defined(APPLE)
        std::cerr << "jail init with $" PITO_LD_PRELOAD " (" << preload << ")" << std::endl;
#endif
    }
};

Init init;

template <class Tag>
struct SystemCall;

template <class Tag>
struct SystemCall : PITO_SYSTEM_CALL_BASE <Tag> {
    typedef PITO_SYSTEM_CALL_BASE <Tag> base_t;

    // to handle variadic c argument lists
    template <class... OtherArgs>
    typename base_t::return_type operator()(OtherArgs... args) {
#ifndef NDEBUG
        std::cerr << "jailed call" << std::endl;
#endif
        // TODO: enforce environment
        return base_t::operator()(args...);
    }
};

// TODO: make specialisations to match other exec calls
template <>
struct SystemCall<system_call::execve> 
  : PITO_SYSTEM_CALL_BASE <system_call::execve> {
    typedef PITO_SYSTEM_CALL_BASE <system_call::execve> base_t;

    // to handle variadic c argument lists
    template <class... OtherArgs>
    typename base_t::return_type operator()(OtherArgs... args) {
#ifndef NDEBUG
        std::cerr << "jailed call with environment" << std::endl;
#endif
        // TODO: enforce environment
        return base_t::operator()(args...);
    }
};


} } }

extern "C" {

using namespace pito::interceptor;
using namespace pito::interceptor::jail;

}

#endif
