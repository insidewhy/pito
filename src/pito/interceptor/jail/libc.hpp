#include <stdarg.h>
#include <fcntl.h>

#include <iostream>
#include <algorithm>

namespace pito { namespace interceptor { namespace jail {

struct Init {
    Init() {
        char const *begin = getenv("LD_PRELOAD");
        char const *end = begin;
        while (*(++end) != '\0') {}

        char const *colon = begin;
        do {
            colon = std::find(colon, end, ':');
            std::cout << "got preload entry (" << begin << ")" << std::endl;
        } while (colon != end);
        // first find libpito_[a-z]*.so entry
    }
};

Init init;

} } }

extern "C" {

using namespace pito::interceptor;

// include this in a handler c file to include the pito jail
int execve(const char *filename, char *const argv[], char *const envp[]) {
    return PITO_SUPER(execve)(filename, argv, envp);
}

int execv(const char *filename, char *const argv[]) {
    return PITO_SUPER(execv)(filename, argv);
}

int execvp(const char *filename, char *const argv[]) {
    return PITO_SUPER(execvp)(filename, argv);
}

}
