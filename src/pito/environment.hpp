#ifndef PITO_ENVIRONMENT_HPP
#define PITO_ENVIRONMENT_HPP

#include <pito/config.hpp>

#if defined(PITO_APPLE)
#   include <crt_externs.h>
#   define environ (* _NSGetEnviron())
#elif defined(PITO_BSD)
    extern char **environ;
#else
#   include <unistd.h>
#endif

namespace pito {
/**
 * @brief mac can't use the system getenv in the init phase so this emulates it.
 */
char *getenv(char const *key) {
#ifdef PITO_APPLE
    char const *keyEnd = end(key);
    for (char **envp = environ; *envp != 0; ++envp) {
        if (std::equal(*envp, *envp + (keyEnd - key), key) &&
            '=' == (*envp)[keyEnd - key])
        {
            return *envp + (keyEnd - key) + 1;
        }
    }
    return 0;
#else
    return ::getenv(key);
#endif
}

}

#endif
