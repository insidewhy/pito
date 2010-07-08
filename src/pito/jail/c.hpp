#ifndef PITO_JAIL_C_HPP
#define PITO_JAIL_C_HPP

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  detail::system_call
#endif

#define PITO_JAIL_BASE jail::system_call

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>
#include <pito/jail/environment.hpp>
#include <pito/config.hpp>

#include <stdarg.h>
#include <fcntl.h>

#include <algorithm>

#ifndef NDEBUG
#include <iostream>
#endif

namespace pito { namespace jail {

struct init {
    init() {
        char const *begin = getenv(PITO_LD_PRELOAD);
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

        // apple can't handle output in the global construction phase.. check
        // only verified as working on linux
#if ! defined(NDEBUG) && ! defined(APPLE)
        std::cerr << "jail init with $" PITO_LD_PRELOAD " (" << preload << ")" << std::endl;
#endif
    }
};

init context;

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : PITO_SYSTEM_CALL_BASE <Tag> {
    typedef PITO_SYSTEM_CALL_BASE <Tag> base_t;

    // to handle variadic c argument lists
    template <class... Args>
    typename base_t::return_type operator()(Args... args) {
#ifndef NDEBUG
        std::cerr << "jailed call" << std::endl;
#endif
        // TODO: enforce environment
        return base_t::operator()(args...);
    }
};

// TODO: make specialisations to match other exec calls
template <>
struct system_call<system_call_tag::execve>
  : PITO_SYSTEM_CALL_BASE <system_call_tag::execve>
{
    typedef PITO_SYSTEM_CALL_BASE <system_call_tag::execve> base_t;

    // to handle variadic c argument lists
    template <class... Args>
    typename base_t::return_type operator()(Args... args) {
#ifndef NDEBUG
        std::cerr << "jailed call with environment" << std::endl;
#endif
        // TODO: enforce environment
        return base_t::operator()(args...);
    }
};


} }

using namespace pito;
using namespace pito::jail;

#endif
