#ifndef PITO_LOG_HELPER_HPP
#define PITO_LOG_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/traits.hpp>

#include <chilon/print.hpp>

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

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : detail::system_call<Tag> {
    typedef detail::system_call<Tag> base_t;

    // to handle variadic c argument lists
    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
#ifdef PITO_LOG_PID
        chilon::print(std::cerr, context.pid_, " - ");
#endif
        chilon::print(std::cerr, "calling ", base_t::name, "(");
        chilon::print_join(std::cerr, ", ", args...);
        std::cerr << ") - " << std::flush;
        auto ret = PITO_SUPER(Tag, args...);
        chilon::println(std::cerr, ret);
        return ret;
    }
};

} }

#endif
