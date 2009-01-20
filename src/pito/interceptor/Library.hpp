#ifndef _PITO_INTERCEPTOR_LIBRARY_HPP_
#define _PITO_INTERCEPTOR_LIBRARY_HPP_

#include <boost/pool/detail/singleton.hpp>

namespace pito { namespace interceptor { 

namespace library {
    struct c {};
}

using boost::details::pool::singleton_default;

class LibraryBase {
    void *handler_;

    LibraryBase() : handler_(0) {}
};

template <class LibraryName>
struct Library;

template <>
struct Library<library::c> : LibraryBase, singleton_default< Library<library::c> > {
};

} }

#endif
