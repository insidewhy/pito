#ifndef _PITO_CONFIG_HPP_
#define _PITO_CONFIG_HPP_

/**
 * @file Configuration details for pito
 */

#define PITO_PREFIX  "@PREFIX@"
#define PITO_LIB_PREFIX "@LIB_DIR@/"
#define PITO_SHARE_PREFIX "@SHARE_DIR@/"
#define PITO_CONFIG_PREFIX "@CONFIG_DIR@/"
#define PITO_OFF64_TYPE @OFF64_TYPE@
#define PITO_SHARED_LIB_FILE_EXTENSION "@CMAKE_SHARED_LIBRARY_SUFFIX@"
#cmakedefine PITO_BSD
#cmakedefine PITO_APPLE
#ifndef PITO_APPLE
#define PITO_LD_PRELOAD      "LD_PRELOAD"
#define PITO_LD_LIBRARY_PATH "LD_LIBRARY_PATH"
#define PITO_PROC_FD         "/dev/fd"
#else
#define PITO_LD_PRELOAD      "DYLD_INSERT_LIBRARIES"
#define PITO_LD_LIBRARY_PATH "DYLD_LIBRARY_PATH"
#define PITO_PROC_FD         "/proc/self/fd"
#endif
#define PITO_MAX_FD_LENGTH   21

#endif
