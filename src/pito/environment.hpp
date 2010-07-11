#ifndef PITO_ENVIRONMENT_HPP
#define PITO_ENVIRONMENT_HPP

#include <pito/config.hpp>

#include <chilon/print.hpp>

#if defined(PITO_APPLE)
#   include <crt_externs.h>
#   define environ (* _NSGetEnviron())
#elif defined(PITO_BSD)
    extern char **environ;
#else
#   include <unistd.h>
#endif

#include <vector>
#include <unordered_map>
#include <sstream>

namespace pito {

typedef std::unordered_map<std::string, std::string>  environment_map;

/**
 * @brief mac can't use the system getenv in the init phase so this emulates it.
 */
static inline char *getenv(char const *key) {
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

static inline void setenv(char const *key, char const *val, int override = 1) {
    ::setenv(key, val, override);
}

static inline void setenv(environment_map const& map) {
    for (auto it = map.begin(); it != map.end(); ++it)
        setenv(it->first.c_str(), it->second.c_str());
}

static char * const *setenv(environment_map const& map, char * const envp[]) {
    // TODO:
    return envp;
}

template <class T>
static void setenv_join(char const            *key,
                 std::vector<T> const&  values,
                 char const            *join = "\n")
{
    if (values.empty()) return;
    std::stringstream str;
    chilon::print_join(str, join, values);
    setenv(key, str.str().c_str());
}

}

#endif
