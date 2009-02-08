#ifndef _PITO_INTERCEPTOR_LIBRARY_HPP_
#define _PITO_INTERCEPTOR_LIBRARY_HPP_

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor {

using boost::details::pool::singleton_default;

namespace detail {
    struct library {
        library(std::string const& name) : name_(name) {}

        void *handle() {
            static void *handle_ = 0;
            if (! handle_) {
                handle_ = dlopen(name_.c_str(), RTLD_LAZY);
                // TODO: error checking
            }
            return handle_;
        }

      private:
        std::string name_;
    };
}

template <class Tag>
struct library;

template <class Tag>
library<Tag>& library_instance() {
    return singleton_default< library<Tag> >::instance();
}

} }

#endif
