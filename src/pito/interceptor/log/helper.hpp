#ifndef _PITO_INTERCEPTOR_LOG_HELPER_
#define _PITO_INTERCEPTOR_LOG_HELPER_

#include <pito/interceptor/lib/c_traits.hpp>
#include <pito/interceptor/SystemCall.hpp>

#include <iostream>

namespace pito { namespace interceptor { namespace log {

template <class... Args> struct PrintArgs;
template <class... Args> struct PrintTailArgs;

template <>
struct PrintArgs<> {
    static void exec() {
    }
};

template <>
struct PrintTailArgs<> {
    static void exec() {
    }
};

template <class Arg, class... Args>
struct PrintTailArgs<Arg, Args...> {
    static void exec(Arg const& arg, Args... args) {
        std::cout << ", " << arg;
        PrintTailArgs<Args...>::exec(args...);
    }
};

template <class Arg, class... Args>
struct PrintArgs<Arg, Args...> {
    static void exec(Arg const& arg, Args... args) {
        std::cout << arg;
        PrintTailArgs<Args...>::exec(args...);
    }
};

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCall;

template <class Tag, class LibraryTag, class Ret, class... Args>
struct SystemCall<Tag, LibraryTag, Ret (Args...)> : SystemCallHelper<Tag, LibraryTag, Ret(Args...)> {
    typedef SystemCallHelper<Tag, LibraryTag, Ret(Args...)> base_t;

    // to handle variadic c argument lists
    template <class... OtherArgs>
    Ret operator()(OtherArgs... args) {
        std::cout << "calling " << system_call::traits<Tag>::name << "(";
        PrintArgs<OtherArgs...>::exec(args...);
        std::cout << ")" << std::endl;
        return base_t::operator()(args...);
    }
};

} } }

#endif
