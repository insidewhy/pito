#ifndef _PITO_INTERCEPTOR_JAIL_LIBC_HPP_
#define _PITO_INTERCEPTOR_JAIL_LIBC_HPP_

#include <pito/interceptor/jail/environment.hpp>
#include "config.hpp"

#include <stdarg.h>
#include <fcntl.h>

#include <algorithm>

namespace pito { namespace interceptor { namespace jail {

struct Init {
    Init() {
        char const *begin = jail::getenv(PITO_LD_PRELOAD);
        if (begin) {
            preload = begin;
            // TODO: find the library properly like this
            // char const *end = begin;
            // while (*(++end) != '\0') {}

            // char const *colon = begin;
            // do {
            //     colon = std::find(colon + 1, end, ':');
            //     // std::cout << "got preload entry (" << begin << ")" << std::endl;
            //     // TODO: test if range(begin,colon) matches libpito_[a-z]+.so

            //     begin = colon;
            // } while (colon != end);
        }
    }
};

Init init;

} } }

extern "C" {

using namespace pito::interceptor;
using namespace pito::interceptor::jail;

// include this in a handler c file to include the pito jail
int execve(const char *filename, char *const argv[], char *const envp[]) {
    enforceEnvironment(envp);
    return PITO_SUPER(execve)(filename, argv, envp);
}

int execv(const char *filename, char *const argv[]) {
    enforceEnvironment();
    return PITO_SUPER(execv)(filename, argv);
}

int execvp(const char *filename, char *const argv[]) {
    enforceEnvironment();
    return PITO_SUPER(execvp)(filename, argv);
}

}

#endif
