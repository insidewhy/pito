#ifndef _PITO_INTERCEPTOR_LIBRARY_HPP_
#define _PITO_INTERCEPTOR_LIBRARY_HPP_

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor { 

using boost::details::pool::singleton_default;

struct LibraryHelper {
    LibraryHelper(std::string const& name) : name_(name) {}

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

template <class Tag>
struct Library;

namespace library {
    template <class Tag>
    Library<Tag>& instance() {
        return singleton_default< Library<Tag> >::instance();
    }
}

} }

#endif
