#ifndef _PITO_INTERCEPTOR_LOG_HELPER_
#define _PITO_INTERCEPTOR_LOG_HELPER_

#include <pito/interceptor/system_call.hpp>
#include <pito/interceptor/lib/traits.hpp>

#include <iostream>

namespace pito { namespace interceptor { namespace log {

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : detail::system_call<Tag> {
    typedef detail::system_call<Tag> base_t;

    template <class... Args>
    typename base_t::return_type operator()(Args... args) {
        return base_t::operator()(args...);
    }
};

} } }

#endif
