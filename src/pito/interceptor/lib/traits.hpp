#ifndef _PITO_INTERCEPTOR_LIB_TRAITS_
#define _PITO_INTERCEPTOR_LIB_TRAITS_

namespace pito { namespace interceptor { namespace system_call {

template <class Tag>
struct traits;

} } }

#define PITO_SYSTEM_CALL_TRAIT(name_) \
    namespace system_call { \
        struct name_ {}; \
        template <> struct traits<name_> { \
            static char const name[]; \
        }; \
        char const traits<name_>::name[] = #name_; \
    }

#endif
