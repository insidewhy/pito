#ifndef _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#define _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#include <unistd.h>

namespace pito { namespace interceptor { namespace jail {

// LD_PRELOAD entry
std::string preload;

void enforceEnvironment(char * const *env = environ) {
}

} } }
#endif
