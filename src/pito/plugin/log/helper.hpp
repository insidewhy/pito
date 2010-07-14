#ifndef PITO_LOG_HELPER_HPP
#define PITO_LOG_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/traits.hpp>

#include <chilon/print.hpp>

#include <iostream>

namespace pito { namespace log {

#ifdef PITO_LOG_PID
struct context {
    context() {
       pid_ = getpid();
    }
    pid_t   pid_;
};

// Object created in source file, ensures context constructor gets run
// as library is opened.
context ctxt;
#endif

// This is the system call handler, certain tags can be handled
// specially using template parameter specialisation on the tag
template <class Tag>
struct system_call : system_call_real<Tag> {

    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
#ifdef PITO_LOG_PID
        chilon::print(std::cerr, ctxt.pid_, " - ");
#endif
        // name() inherited from system_call_real, contains name of
        // system call as cstring. this-> is necessary due to call
        // through template base.
        chilon::print(std::cerr, "calling ", this->name(), "(");
        chilon::print_join(std::cerr, ", ", args...);
        std::cerr << ") - " << std::flush;

        // Call the real system call.
        auto ret = this->system(args...);
        chilon::println(std::cerr, ret);
        return ret;
    }
};

} }

#endif
