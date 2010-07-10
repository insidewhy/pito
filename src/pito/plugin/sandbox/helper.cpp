#include <pito/plugin/sandbox/helper.hpp>

#include <chilon/print.hpp>

namespace pito { namespace sandbox {

init context;

init::init() {
    char const *default_action = getenv(PITO_SANDBOX_DEFAULT);
    char const *whitelist      = getenv(PITO_SANDBOX_WHITELIST);
    char const *blacklist      = getenv(PITO_SANDBOX_BLACKLIST);
    char const *pretendlist    = getenv(PITO_SANDBOX_PRETENDLIST);
}

} }
