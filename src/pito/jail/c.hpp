#ifndef PITO_JAIL_C_HPP
#define PITO_JAIL_C_HPP

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  system_call_real
#endif

#define PITO_JAIL_BASE jail::system_call

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>
#include <pito/jail/environment.hpp>
#include <pito/config.hpp>

#include <stdarg.h>
#include <fcntl.h>

#ifndef NDEBUG
#include <iostream>
#endif

namespace pito { namespace jail {

context& ctxt = chilon::singleton<context>::instance();

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : PITO_SYSTEM_CALL_BASE <Tag> {
    typedef PITO_SYSTEM_CALL_BASE <Tag> base_t;

    // to handle variadic c argument lists
    template <class... Args>
    typename base_t::return_type operator()(Args... args) {
        enforce_environment();
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
    typename base_t::return_type
    operator()(char const *path, char * const argv[], char * const envp[]) {
        return base_t::operator()(path, argv, enforce_environment(envp));
    }
};


} }

using namespace pito;
using namespace pito::jail;

#endif
