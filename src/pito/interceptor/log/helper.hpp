#ifndef _PITO_INTERCEPTOR_LOG_HELPER_
#define _PITO_INTERCEPTOR_LOG_HELPER_

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

template <class LibraryTag, class Ret, class... Args>
struct SystemCall;

template <class LibraryTag, class Ret, class... Args>
struct SystemCall<LibraryTag, Ret (Args...)> : SystemCallHelper<LibraryTag, Ret(Args...)> {
    typedef SystemCallHelper<LibraryTag, Ret(Args...)> base_t;
    SystemCall(std::string const& name) : base_t(name) {}

    Ret operator()(Args... args) {
        std::cout << "calling " << base_t::name() << "(";
        PrintArgs<Args...>::exec(args...);
        std::cout << ")" << std::endl;
        return base_t::operator()(args...);
    }
};

} } }

#endif
