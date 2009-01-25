#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>
#include <pito/interceptor/lib/traits.hpp>

#include <rbutil/type/list.hpp>
#include <rbutil/type/arguments.hpp>

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor {

using namespace rb::util;

template <class Tag>
struct SystemCall;

template <class Tag, class Ret, class... Args>
struct SystemCallBase;

template <class Tag, class Ret, class... Args>
struct SystemCallBase<Tag, Ret (Args...)> : system_call::traits<Tag> {
    typedef Ret (*call_t)(Args..., ...);
    typedef Ret                  return_type;
    typedef type::list<Args...>  arg_types;

    // to handle variadic c functions, must accept other args
    template <class... OtherArgs>
    return_type operator()(OtherArgs... args) {
        if (! call_) {
            // the following might be needed for another architecture
            // call_ = reinterpret_cast<call_t>(dlsym(library::instance<LibraryTag>().handle(), name_.c_str()));
            call_ = reinterpret_cast<call_t>(dlsym(RTLD_NEXT, system_call::traits<Tag>::name));
        }
        return call_(args...);
    }

    SystemCallBase() : call_(0) {}
  private:
    call_t call_;
};

namespace system_call {
    template <class Tag>
    SystemCall<Tag>& instance() {
        return singleton_default< SystemCall<Tag> >::instance();
    }
}

} }

#define PITO_SUPER(calltype)   system_call::instance<system_call:: calltype >()

#define PITO_SYSTEM_CALL_WITH_BASE(_name, _signature, _nArgs, _base) \
    template <> \
    struct SystemCall<_name> \
      : _base <_name, _signature> {}; \
    extern "C" { \
        SystemCall<_name>::return_type  _name ( RBUTIL_ARGS_##_nArgs(SystemCall<_name>::arg_types) ) { \
            return PITO_SUPER(_name)( RBUTIL_ARG_NAMES_##_nArgs ); \
        } \
    }

#define PITO_SYSTEM_CALL(_name, _signature, _nArgs) \
    PITO_SYSTEM_CALL_WITH_BASE(_name, _signature, _nArgs, PITO_SYSTEM_CALL_BASE)

#endif
