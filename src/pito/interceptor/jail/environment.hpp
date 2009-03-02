#ifndef _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#define _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_

#include <pito/config.hpp>

#include <algorithm>
#include <string>

#if defined(PITO_APPLE)
#   include <crt_externs.h>
#   define environ (* _NSGetEnviron())
#elif defined(PITO_BSD)
    extern char **environ;
#else
#   include <unistd.h>
#endif

namespace pito { namespace interceptor { namespace jail {

// LD_PRELOAD entry
std::string preload;

template <class CharIt>
CharIt end(CharIt begin) {
    while (*begin != '\0') ++begin;
    return begin;
}

// mac can't use the real getenv in the init
char *getenv(char const *key) {
    char const *keyEnd = end(key);
    for (char **envp = environ; *envp != 0; ++envp) {
        if (std::equal(*envp, *envp + (keyEnd - key), key) && 
            '=' == (*envp)[keyEnd - key]) 
        {
            return *envp + (keyEnd - key) + 1;
        }
    }
    return 0;
}

char * const *enforce_environment(char * const *env) {
    // TODO: return pointer to enforced environment
    // don't have to care about memory management in this process as it
    // is about to be thrown away
    return env;
}

void enforce_environment() {
    // TODO: append to existing LD_PRELOAD 
    //       also consider modifying environ directly with the above call
    setenv(PITO_LD_PRELOAD, preload.c_str(), 1);
#ifdef PITO_APPLE
    setenv("DYLD_FORCE_FLAT_NAMESPACE", "YES", 1);
#endif
}

} } }
#endif
