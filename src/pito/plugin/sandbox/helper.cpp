#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/environment.hpp>

#include <chilon/print.hpp>
#include <chilon/iterator_range.hpp>

namespace pito { namespace sandbox {

context& ctxt = chilon::singleton<context>::instance();

context::context() {
    auto& jail_ctxt = chilon::singleton<jail::context>::instance();

    for (auto it = jail_ctxt.environment_.begin();
         it != jail_ctxt.environment_.end(); ++it)
    {
        if (it->first == PITO_SANDBOX_DEFAULT) {
        }
        else if (it->first == PITO_SANDBOX_PATHS) {
        }
    }
}

} }
