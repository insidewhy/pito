#ifndef _PITO_INTERCEPTOR_LIBRARY_
#define _PITO_INTERCEPTOR_LIBRARY_

#include <boost/pool/detail/singleton.hpp>

namespace pito { namespace interceptor { namespace library {

using boost::details::pool::singleton_default;

struct c {};

template <class LibraryName>
struct Library;

template <>
struct Library<c> : singleton_default< Library<c> > {

  private:
    void *handler_;
};

} } }

#endif
