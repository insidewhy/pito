#ifndef PITO_LIB_TRAITS_HPP
#define PITO_LIB_TRAITS_HPP

#include <chilon/meta/function.hpp>

namespace pito {

template <class Tag>
struct traits;

}

// TODO: make the library tag a trait
#define PITO_SYSTEM_CALL_TRAIT(name_, lib_, signature_) \
    namespace system_call_tag { struct name_ {}; } \
    template <> struct traits<system_call_tag::name_> : chilon::meta::function<signature_> { \
        static char const *name() { return #name_; } \
        typedef library_tag::lib_   library; \
    };

#endif
