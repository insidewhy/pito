#ifndef _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_
#define _PITO_INTERCEPTOR_SYSTEM_CALL_HPP_

#include <pito/interceptor/Library.hpp>
#include <sys/types.h>

namespace pito { namespace interceptor {

namespace system_call {
    struct open {};
};

template <class Tag>
struct SystemCall;

template <class LibraryTag, class Ret, class... Args>
struct SystemCallHelper {
    typedef Ret (*call_t)(Args...);

    SystemCallHelper(std::string const& name) : call_(0), name_(name) {}

    Ret operator()(Args... args) {
        if (! call_) {
            call_ = dlsym(library::instance<LibraryTag>().handle(), name_.c_str());
        }
        return call_(args...);
    }

  private:
    call_t call_;
    std::string name_;
};

template <>
struct SystemCall<system_call::open> 
  : SystemCallHelper<library::c, int, const char *, int, mode_t> 
{
    SystemCall() : SystemCallHelper<library::c, int, const char *, int, mode_t>("open") {}
};

} }

#endif
