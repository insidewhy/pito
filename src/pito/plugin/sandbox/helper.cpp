#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/environment.hpp>

#include <chilon/print.hpp>
#include <chilon/iterator_range.hpp>

namespace pito { namespace sandbox {

init& context = chilon::singleton<init>::instance();

init::init() {
    auto& jail_context = chilon::singleton<jail::init>::instance();

    for (auto it = jail_context.environment_.begin();
         it != jail_context.environment_.end(); ++it)
    {
        if (it->first == PITO_SANDBOX_DEFAULT) {
        }
        else if (it->first == PITO_SANDBOX_PATHS) {
        }
    }
}

} }
