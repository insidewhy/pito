#ifndef _PITO_CONFIG_HPP_
#define _PITO_CONFIG_HPP_

#define _PREFIX_  "@PREFIX@"
#define _LIB_DIR_ "@LIB_DIR@"
#define _SHARE_DIR_ "@SHARE_DIR@"
#define _CONFIG_DIR_ "@CONFIG_DIR@"
#define PITO_OFF64_TYPE @OFF64_TYPE@
#define _SHARED_LIB_FILE_EXTENSION_ "@CMAKE_SHARED_LIBRARY_SUFFIX@"
#cmakedefine APPLE
#ifdef APPLE
#define _LD_PRELOAD "DYLD_INSERT_LIBRARIES"
#else
#define _LD_PRELOAD "LD_PRELOAD"
#endif

#endif
