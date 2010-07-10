#ifndef PITO_JAIL_ENVIRONMENT_HPP
#define PITO_JAIL_ENVIRONMENT_HPP

#include <pito/environment.hpp>

#include <algorithm>
#include <string>

namespace pito { namespace jail {

struct init {
    init() {
        auto& preload =
            environment_[PITO_LD_PRELOAD] = getenv(PITO_LD_PRELOAD);

        // apple can't handle output in the global construction phase.. check
        // only verified as working on linux
#if ! defined(NDEBUG) && ! defined(APPLE)
        std::cerr << "jail init with $" PITO_LD_PRELOAD " ("
                  << preload << ")\n";
#endif

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

init context;


template <class CharIt>
CharIt end(CharIt begin) {
    while (*begin != '\0') ++begin;
    return begin;
}

/**
 * @brief enforce_environment is used by the jail to ensure the jail cannot be removed from the
 *        library preload.
 */
void enforce_environment() {
    for (auto it = context.environment_.begin();
         it != context.environment_.end(); ++it)
    {
        setenv(it->first.c_str(), it->second.c_str());
    }
#ifdef PITO_APPLE
    setenv("DYLD_FORCE_FLAT_NAMESPACE", "YES");
#endif
}

/**
 * @brief Enforce environment in a string.
 * @param String representation of environment (e.g. environ).
 * @return The given environment modified with the enforced library preloads, allocated with new.
 */
char * const * enforce_environment(char * const envp[]) {
    return envp;
}

} }
#endif
