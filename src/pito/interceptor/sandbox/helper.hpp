#ifndef _PITO_INTERCEPTOR_SANDBOX_HELPER_
#define _PITO_INTERCEPTOR_SANDBOX_HELPER_

#include <pito/interceptor/system_call.hpp>
#include <pito/interceptor/lib/traits.hpp>
#include <pito/interceptor/lib/c_traits.hpp>

#include <iostream>

namespace pito { namespace interceptor { namespace sandbox {

using namespace system_call_tag;

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : detail::system_call<Tag> {
    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
        return PITO_SUPER(Tag, args...);
    }
};

template <>
struct system_call<creat> : detail::system_call<creat> {
    PITO_RETURN(creat) operator()(const char *file, mode_t mode) {
        return PITO_SUPER(system_call_tag::creat, file, mode);
    }
};

} } }

#endif
