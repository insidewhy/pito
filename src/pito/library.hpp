#ifndef PITO_LIBRARY_HPP
#define PITO_LIBRARY_HPP

#include <chilon/singleton.hpp>
#include <dlfcn.h>

namespace pito {

namespace detail {
    struct library {
        library(char const name[]) : name_(name) {}

        void *handle() {
            static void *handle_ = 0;
            if (! handle_) {
                handle_ = dlopen(name_, RTLD_LAZY);
                // TODO: error checking
            }
            return handle_;
        }

      private:
        char const *name_;
    };
}

template <class Tag>
struct library;

template <class Tag>
library<Tag>& library_instance() {
    return chilon::singleton< library<Tag> >::instance();
}

}

#endif
