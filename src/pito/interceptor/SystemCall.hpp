#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>
#include <pito/interceptor/lib/traits.hpp>

#include <rbutil/type/list.hpp>
#include <rbutil/type/function.hpp>

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor {

using namespace rb::util;

template <class Tag>
struct SystemCall;

template <class Tag>
struct SystemCallBase : system_call::traits<Tag> {
    typedef system_call::traits<Tag>  type_base;

    // to handle variadic c functions, must accept other args
    template <class... OtherArgs>
    typename type_base::return_type operator()(OtherArgs... args) {
        if (! call_) {
            // the following might be needed for another architecture
            // call_ = reinterpret_cast<call_t>(dlsym(library::instance<LibraryTag>().handle(), name_.c_str()));
            call_ = reinterpret_cast<typename type_base::call_t>(dlsym(RTLD_NEXT, system_call::traits<Tag>::name));
        }
        return call_(args...);
    }

    SystemCallBase() : call_(0) {}
  private:
    typename type_base::call_t call_;
};

namespace system_call {
    template <class Tag>
    SystemCall<Tag>& instance() {
        return singleton_default< SystemCall<Tag> >::instance();
    }
}

} }

#define PITO_SUPER(calltype)   system_call::instance<system_call:: calltype >()

#define PITO_SYSTEM_CALL_WITH_BASE(name_, nArgs_, base_) \
    template <> \
    struct SystemCall<name_> \
      : base_ <name_> {}; \
    extern "C" { \
        SystemCall<name_>::return_type  name_ ( RBUTIL_ARGS_##nArgs_(SystemCall<name_>::arg_types) ) { \
            return PITO_SUPER(name_)( RBUTIL_ARG_NAMES_##nArgs_ ); \
        } \
    }

#define PITO_SYSTEM_CALL(name_, nArgs_) \
    PITO_SYSTEM_CALL_WITH_BASE(name_, nArgs_, PITO_SYSTEM_CALL_BASE)

#endif
