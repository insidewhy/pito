#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>

namespace pito { namespace interceptor {

template <class LibraryTag>
struct SystemCall;

struct SystemCallHelper {
};

template <>
struct SystemCall<library::c> : SystemCallHelper {
};

} }

#endif
