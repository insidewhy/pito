#ifndef _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#define _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_

#include "config.hpp"

#include <algorithm>
#include <string>

#ifdef PITO_APPLE
#include <crt_externs.h>
#define environ (* _NSGetEnviron())
#else
#include <unistd.h>
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

void enforceEnvironment() {
    // TODO: append to existing LD_PRELOAD 
    //       also consider modifying environ directly (might avoid extra LD_PRELOAD start)
    setenv(PITO_LD_PRELOAD, preload.c_str(), 1);
#ifdef PITO_APPLE
    setenv("DYLD_FORCE_FLAT_NAMESPACE", "YES", 1);
#endif
}

void enforceEnvironment(char * const *env) {
}

} } }
#endif
