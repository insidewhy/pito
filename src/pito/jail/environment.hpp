#ifndef PITO_JAIL_ENVIRONMENT_HPP
#define PITO_JAIL_ENVIRONMENT_HPP

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

namespace pito { namespace jail {

// LD_PRELOAD entry
std::string preload;

template <class CharIt>
CharIt end(CharIt begin) {
    while (*begin != '\0') ++begin;
    return begin;
}

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

/**
 * @brief enforce_environment is used by the jail to ensure the jail cannot be removed from the
 *        library preload.
 */
void enforce_environment() {
    // TODO: append to existing LD_PRELOAD
    //       also consider modifying environ directly with the above call
    setenv(PITO_LD_PRELOAD, preload.c_str(), 1);
#ifdef PITO_APPLE
    setenv("DYLD_FORCE_FLAT_NAMESPACE", "YES", 1);
#endif
}

/**
 * @brief Enforce environment in a string.
 * @param String representation of environment (e.g. environ).
 * @return The given environment modified with the enforced library preloads, allocated with new.
 */
char * const *enforce_environment(char * const *env) {
    // TODO: return pointer to enforced environment
    // don't have to care about memory management in this process as it
    // is about to be thrown away
    return env;
}

} }
#endif
