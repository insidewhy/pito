#ifndef _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#define _PITO_INTERCEPTOR_JAIL_ENVIRONMENT_HPP_
#include <unistd.h>
#include <config.hpp>

namespace pito { namespace interceptor { namespace jail {

// LD_PRELOAD entry
std::string preload;

void enforceEnvironment() {
    // TODO: append to existing LD_PRELOAD 
    //       also consider modifying environ directly (might avoid extra LD_PRELOAD start)
    setenv(_LD_PRELOAD, preload.c_str(), 1);
}

void enforceEnvironment(char * const *env) {
}

} } }
#endif
