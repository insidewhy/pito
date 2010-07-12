#ifndef PITO_JAIL_ENVIRONMENT_HPP
#define PITO_JAIL_ENVIRONMENT_HPP

#include <pito/environment.hpp>

#include <chilon/singleton.hpp>

#include <algorithm>
#include <string>

namespace pito { namespace jail {

struct context {
    context() {
        auto& preload =
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
#ifdef PITO_APPLE
    ctxt.environment_["DYLD_FORCE_FLAT_NAMESPACE"] = "YES";
#endif
    return setenv(ctxt.environment_, envp);
}

} }
#endif
