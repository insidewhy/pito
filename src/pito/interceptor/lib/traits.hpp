#ifndef _PITO_INTERCEPTOR_LIB_TRAITS_
#define _PITO_INTERCEPTOR_LIB_TRAITS_

#include <chilon/type/function.hpp>

namespace pito { namespace interceptor {

template <class Tag>
struct traits;

} }

// TODO: make the library tag a trait
#define PITO_SYSTEM_CALL_TRAIT(name_, lib_, signature_) \
    namespace system_call_tag { struct name_ {}; } \
    template <> struct traits<system_call_tag::name_> : chilon::type::function<signature_> { \
        static char const       name[]; \
        typedef library_tag::lib_   library; \
    }; \
    char const traits<system_call_tag::name_>::name[] = #name_;

#endif

