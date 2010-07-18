#ifndef PITO_JAIL_ENVIRONMENT_HPP
#define PITO_JAIL_ENVIRONMENT_HPP

#include <pito/environment.hpp>

#include <chilon/singleton.hpp>

#include <algorithm>
#include <string>
#include <cstring>

namespace pito { namespace jail {

struct context {
    context() {
        environment_[PITO_LD_PRELOAD] = getenv(PITO_LD_PRELOAD);

        char const key[] = "PITO_";
        for (char **envp = environ; *envp != 0; ++envp) {
            if (std::equal(*envp, *envp + sizeof(key) - 1, key)) {
                auto equal = *envp + sizeof(key) - 1;
                while ('=' != *equal) {
                    if ('\0' == *(++equal)) break;
                }

                environment_[ std::string(*envp, equal) ] = std::string(equal + 1);
            }
        }
    }

    environment_map  environment_;
};

extern context& ctxt;

/**
 * @brief enforce_environment is used by the jail to ensure the jail cannot be removed from the
 *        library preload.
 */
static void enforce_environment() {
#ifdef PITO_APPLE
    setenv("DYLD_FORCE_FLAT_NAMESPACE", "YES");
#endif
    setenv(ctxt.environment_);
}

/**
 * @brief Enforce environment in a string.
 * @param String representation of environment (e.g. environ).
 * @return The given environment modified with the enforced library preloads, allocated with new.
 */
static char * const * enforce_environment(char * const envp[]) {
    int newSize = ctxt.environment_.size();
#ifdef PITO_APPLE
    ctxt.environment_["DYLD_FORCE_FLAT_NAMESPACE"] = "YES";
    ++newSize;
#endif

    char const key[] = "PITO_";
    for (auto ptr = envp; *ptr != 0; ++ptr) {
        if (! std::equal(*ptr, *ptr + sizeof(key) - 1, key)) {
            ++newSize;
        }
    }

    // don't care about memory, about to throw this process away
    auto new_env = static_cast<char **>(calloc(newSize, sizeof(char *)));

    auto env_it = new_env;
    for (auto it = ctxt.environment_.begin();
         it != ctxt.environment_.end(); ++it)
    {
        auto const key_size = it->first.size();
        auto entry = static_cast<char *>(
            calloc(key_size + it->second.size() + 2, sizeof(char)));
        std::strncpy(entry, it->first.c_str(), key_size);
        entry[key_size] = '=';
        std::strcpy(entry + key_size + 1, it->second.c_str());

        *env_it = entry;
        ++env_it;
    }

    for (auto ptr = envp; *ptr != 0; ++ptr) {
        if (! std::equal(*ptr, *ptr + sizeof(key) - 1, key)) {
            *env_it = *ptr;
            ++env_it;
        }
    }

    *env_it = 0;

    return new_env;
}

} }
#endif
