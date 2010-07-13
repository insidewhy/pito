#ifndef PITO_SANDBOX_HELPER_HPP
#define PITO_SANDBOX_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>

#include <chilon/iterator_range.hpp>

#include <vector>

#define PITO_SANDBOX_DEFAULT  "PITO_SANDBOX_DEFAULT"
#define PITO_SANDBOX_PATHS    "PITO_SANDBOX_PATHS"

namespace pito { namespace sandbox {

enum write_mode {
    WRITE_MODE_PRETEND,
    WRITE_MODE_WHITELIST,
    WRITE_MODE_BLACKLIST
};

struct context {
    context();

    std::vector<range> paths;
    write_mode         mode;
};

extern context& ctxt;

} }

#endif
