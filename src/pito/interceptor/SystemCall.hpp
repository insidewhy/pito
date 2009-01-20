#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

#include <sys/types.h>

namespace pito { namespace interceptor {

template <class Tag>
struct SystemCall;

template <class LibraryTag, class Ret, class... Args>
struct SystemCallHelper;

template <class LibraryTag, class Ret, class... Args>
struct SystemCallHelper<LibraryTag, Ret (Args...)> {
    typedef Ret (*call_t)(Args...);

    SystemCallHelper(std::string const& name) : call_(0), name_(name) {}

    Ret operator()(Args... args) {
        if (! call_) {
            // the following might be needed for another architecture
            // call_ = reinterpret_cast<call_t>(dlsym(library::instance<LibraryTag>().handle(), name_.c_str()));
            call_ = reinterpret_cast<call_t>(dlsym(RTLD_NEXT, name_.c_str()));
        }
        return call_(args...);
    }

  private:
    call_t call_;
    std::string name_;
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
