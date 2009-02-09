#ifndef _PITO_INTERCEPTOR_LOG_HELPER_
#define _PITO_INTERCEPTOR_LOG_HELPER_

#include <pito/interceptor/system_call.hpp>
#include <pito/interceptor/lib/traits.hpp>

#include <iostream>

namespace pito { namespace interceptor { namespace log {

#ifdef PITO_INTERCEPTOR_LOG_PID
struct init {
    init() {
       pid_ = getpid(); 
    }
    pid_t   pid_;
};

init context;
#endif

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
        std::cerr << ", " << arg;
        PrintTailArgs<Args...>::exec(args...);
    }
};

template <class Arg, class... Args>
struct PrintArgs<Arg, Args...> {
    static void exec(Arg const& arg, Args... args) {
        std::cerr << arg;
        PrintTailArgs<Args...>::exec(args...);
    }
};

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : detail::system_call<Tag> {
    typedef detail::system_call<Tag> base_t;

    // to handle variadic c argument lists
    template <class... Args>
    typename base_t::return_type operator()(Args... args) {
#ifdef PITO_INTERCEPTOR_LOG_PID
        std::cerr << context.pid_ << " - ";
#endif
        std::cerr << "calling " << base_t::name << "(";
        PrintArgs<Args...>::exec(args...);
        std::cerr << ")" << std::flush;
        typename base_t::return_type ret = base_t::operator()(args...);
        std::cerr << " - " << ret << std::endl;
        return ret;
    }
};

} } }

#endif
