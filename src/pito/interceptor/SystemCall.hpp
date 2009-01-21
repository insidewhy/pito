#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor {

template <class Tag>
struct SystemCall;

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCallHelper;

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCallHelper<Tag, LibraryTag, Ret (Args...)> {
    typedef Ret (*call_t)(Args..., ...);

    // to handle variadic template parameters
    template <class... OtherArgs>
    Ret operator()(OtherArgs... args) {
        if (! call_) {
            // the following might be needed for another architecture
            // call_ = reinterpret_cast<call_t>(dlsym(library::instance<LibraryTag>().handle(), name_.c_str()));
            call_ = reinterpret_cast<call_t>(dlsym(RTLD_NEXT, system_call::traits<Tag>::name));
        }
        return call_(args...);
    }

    SystemCallHelper() : call_(0) {}
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

#endif
