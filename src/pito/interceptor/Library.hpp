#ifndef _PITO_INTERCEPTOR_LIBRARY_HPP_
#define _PITO_INTERCEPTOR_LIBRARY_HPP_

#include <boost/pool/detail/singleton.hpp>
#include <dlfcn.h>
#include <string>

namespace pito { namespace interceptor { 

namespace library {
    struct c {};
}

using boost::details::pool::singleton_default;

struct LibraryHelper {
    LibraryHelper(std::string const& name) : handle_(0), name_(name) {}

    void *handle() {
        if (! handle_) {
            handle_ = dlopen(name_.c_str(), RTLD_LAZY);
        }
        return handle_;
    }

  private:
    void *handle_;
    std::string name_;
};

template <class LibraryTag>
struct Library;

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

namespace library {
    template <class LibraryTag>
    Library<LibraryTag>& instance() {
        return singleton_default< Library<LibraryTag> >::instance();
    }
}

} }

#endif
