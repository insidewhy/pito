#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>
#include <pito/interceptor/lib/traits.hpp>

#include <rbutil/type/type.hpp>

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor {

using namespace rb::util;

template <class Tag>
struct SystemCall;

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCallBase;

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCallBase<Tag, LibraryTag, Ret (Args...)> {
    typedef Ret (*call_t)(Args..., ...);
    typedef type::list<Args...>  arg_types;

    // to handle variadic c functions, must accept other args
    template <class... OtherArgs>
    Ret operator()(OtherArgs... args) {
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

#define PITO_ARG_NAME(idx) arg##idx
#define PITO_ARG_NAMES_0
#define PITO_ARG_NAMES_1   PITO_ARG_NAME(0)
#define PITO_ARG_NAMES_2   PITO_ARG_NAMES_1, PITO_ARG_NAME(1)
#define PITO_ARG_NAMES_3   PITO_ARG_NAMES_2, PITO_ARG_NAME(2)
#define PITO_ARG_NAMES_4   PITO_ARG_NAMES_3, PITO_ARG_NAME(3)
#define PITO_ARG_NAMES_5   PITO_ARG_NAMES_4, PITO_ARG_NAME(4)

#define PITO_ARG(idx, list) type::at<idx, list>::type PITO_ARG_NAME(idx)
#define PITO_ARGS_0(list)
#define PITO_ARGS_1(list)   PITO_ARG(0, list)
#define PITO_ARGS_2(list)   PITO_ARGS_1(list), PITO_ARG(1, list)
#define PITO_ARGS_3(list)   PITO_ARGS_2(list), PITO_ARG(2, list)
#define PITO_ARGS_4(list)   PITO_ARGS_3(list), PITO_ARG(3, list)
#define PITO_ARGS_5(list)   PITO_ARGS_4(list), PITO_ARG(4, list)

#define PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _nArgs, _base) \
    template <> \
    struct SystemCall<_name> \
      : _base <_name, library::_library, _retVal _argTypes> {}; \
    extern "C" { \
        _retVal _name ( PITO_ARGS_##_nArgs(SystemCall<_name>::arg_types) ) { \
            return PITO_SUPER(_name)( PITO_ARG_NAMES_##_nArgs ); \
        } \
    }

#define PITO_SYSTEM_CALL(_name, _library, _retVal, _argTypes, _nArgs) \
    PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _nArgs, PITO_SYSTEM_CALL_BASE)

#endif
