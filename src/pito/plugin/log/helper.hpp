#ifndef PITO_LOG_HELPER_HPP
#define PITO_LOG_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/traits.hpp>

#include <iostream>

namespace pito { namespace log {

#ifdef PITO_LOG_PID
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
    PITO_RETURN(Tag) operator()(Args... args) {
#ifdef PITO_LOG_PID
        std::cerr << context.pid_ << " - ";
#endif
        std::cerr << "calling " << base_t::name << "(";
        PrintArgs<Args...>::exec(args...);
        std::cerr << ")" << std::flush;
        auto ret = PITO_SUPER(Tag, args...);
        std::cerr << " - " << ret << std::endl;
        return ret;
    }
};

} }

#endif
