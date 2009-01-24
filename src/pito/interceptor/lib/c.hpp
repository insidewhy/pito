#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

#include <pito/interceptor/lib/c_traits.hpp>
#include <pito/interceptor/SystemCall.hpp>

#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

#include "config.hpp"

#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallBase
#endif

#ifndef PITO_JAIL_BASE
#define PITO_JAIL_BASE PITO_SYSTEM_CALL_BASE
#endif

namespace pito { namespace interceptor {

using namespace system_call;

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

#define PITO_ARG_NAME(idx) arg##idx
#define PITO_ARG_NAMES_0
#define PITO_ARG_NAMES_1   PITO_ARG_NAME(0)
#define PITO_ARG_NAMES_2   PITO_ARG_NAMES_1, PITO_ARG_NAME(1)
#define PITO_ARG_NAMES_3   PITO_ARG_NAMES_2, PITO_ARG_NAME(2)
#define PITO_ARG_NAMES_4   PITO_ARG_NAMES_3, PITO_ARG_NAME(3)
#define PITO_ARG_NAMES_5   PITO_ARG_NAMES_4, PITO_ARG_NAME(4)

#define PITO_ARG(idx, list) type::at<idx, list>::type PITO_ARG_NAME(idx)
#define PITO_ARGS_0(list)
#define PITO_ARGS_1(list)   PITO_ARG(0, list)
#define PITO_ARGS_2(list)   PITO_ARGS_1(list), PITO_ARG(1, list)
#define PITO_ARGS_3(list)   PITO_ARGS_2(list), PITO_ARG(2, list)
#define PITO_ARGS_4(list)   PITO_ARGS_3(list), PITO_ARG(3, list)
#define PITO_ARGS_5(list)   PITO_ARGS_4(list), PITO_ARG(4, list)

#define PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _nArgs, _base) \
    template <> \
    struct SystemCall<_name> \
      : _base <_name, library::_library, _retVal _argTypes> {}; \
    extern "C" { \
        _retVal _name ( PITO_ARGS_##_nArgs(SystemCall<_name>::arg_types) ) { \
            return PITO_SUPER(_name)( PITO_ARG_NAMES_##_nArgs ); \
        } \
    }

#define PITO_SYSTEM_CALL(_name, _library, _retVal, _argTypes, _nArgs) \
    PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _nArgs, PITO_SYSTEM_CALL_BASE)

////////////////////////////////////////////////////////////////////////////////
// security intercepts
PITO_SYSTEM_CALL(chmod, c, int, (const char *, mode_t), 2)
PITO_SYSTEM_CALL(fchmod, c, int, (int, mode_t), 2)
PITO_SYSTEM_CALL(fchmodat, c, int, (int, const char *, mode_t, int), 4)
PITO_SYSTEM_CALL(chown, c, int, (const char *, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(fchown, c, int, (int, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(fchownat, c, int, (int, const char *, uid_t, gid_t, int), 5)

template <>
struct SystemCall<open>
  : PITO_SYSTEM_CALL_BASE<open, library::c, int(const char *, int)> {};

extern "C" {
    int open(const char *pathname, int flags, ...) {
        if (flags & O_CREAT) {
            va_list ap;
            va_start(ap, flags);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_SUPER(open)(pathname, flags, mode);
        }
        else return PITO_SUPER(open)(pathname, flags);
    }
}

template <>
struct SystemCall<openat>
  : PITO_SYSTEM_CALL_BASE<openat, library::c, int(int, const char *, int)> {};

extern "C" {
    int openat(int dirfd, const char *pathname, int flags, ...) {
        if (flags & O_CREAT) {
            va_list ap;
            va_start(ap, flags);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_SUPER(openat)(dirfd, pathname, flags, mode);
        }
        else return PITO_SUPER(openat)(dirfd, pathname, flags);
    }
}

PITO_SYSTEM_CALL(creat, c, int, (const char *, mode_t), 2)
PITO_SYSTEM_CALL(fopen, c, FILE *, (const char *, const char *), 2)
PITO_SYSTEM_CALL(lchown, c, int, (const char *, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(link, c, int, (const char *, const char *), 2)
PITO_SYSTEM_CALL(linkat, c, int, (int, const char *, int, const char *, int), 5)
PITO_SYSTEM_CALL(mkdir, c, int, (const char *, mode_t), 2)
PITO_SYSTEM_CALL(mkdirat, c, int, (int, const char *, mode_t), 3)
PITO_SYSTEM_CALL(opendir, c, DIR *, (const char *), 1)
PITO_SYSTEM_CALL(mknod, c, int, (const char *, mode_t, dev_t), 3)
PITO_SYSTEM_CALL(mknodat, c, int, (int, const char *, mode_t, dev_t), 4)
// function todo: __xmknod
PITO_SYSTEM_CALL(mkfifo, c, int, (const char *, mode_t), 2)
PITO_SYSTEM_CALL(mkfifoat, c, int, (int, const char *, mode_t), 3)
PITO_SYSTEM_CALL(access, c, int, (const char *, int), 2)
PITO_SYSTEM_CALL(faccessat, c, int, (int, const char *, int, int), 4)
PITO_SYSTEM_CALL(rename, c, int, (const char *, const char *), 2)
PITO_SYSTEM_CALL(renameat, c, int, (int, const char *, int, const char *), 4)
PITO_SYSTEM_CALL(rmdir, c, int, (const char *), 1)
PITO_SYSTEM_CALL(symlink, c, int, (const char *, const char *), 2)
PITO_SYSTEM_CALL(symlinkat, c, int, (const char *, int, const char *), 3)
PITO_SYSTEM_CALL(truncate, c, int, (const char *, off_t), 2)
PITO_SYSTEM_CALL(unlink, c, int, (const char *), 1)
PITO_SYSTEM_CALL(unlinkat, c, int, (int, const char *, int), 3)
PITO_SYSTEM_CALL(getcwd, c, char *, (char *, size_t), 2)

template <>
struct SystemCall<open64>
  : PITO_SYSTEM_CALL_BASE<open64, library::c, int(const char *, int)> {};

extern "C" {
    int open64(const char *pathname, int flags, ...) {
        if (flags & O_CREAT) {
            va_list ap;
            va_start(ap, flags);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_SUPER(open64)(pathname, flags, mode);
        }
        else return PITO_SUPER(open64)(pathname, flags);
    }
}

template <>
struct SystemCall<openat64>
  : PITO_SYSTEM_CALL_BASE<openat64, library::c, int(int, const char *, int)> {};

extern "C" {
    int openat64(PITO_ARGS_3(SystemCall<openat64>::arg_types), ...) {
        if (arg2 & O_CREAT) {
            va_list ap;
            va_start(ap, arg2);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_SUPER(openat64)(arg0, arg1, arg2, mode);
        }
        else return PITO_SUPER(openat64)(arg0, arg1, arg2);
    }
}

PITO_SYSTEM_CALL(creat64, c, int, (const char *, mode_t), 2)
PITO_SYSTEM_CALL(fopen64, c, FILE *, (const char *, const char *), 2)
PITO_SYSTEM_CALL(truncate64, c, int, (const char *, PITO_OFF64_TYPE), 2)

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
PITO_SYSTEM_CALL_WITH_BASE(execve, c, int, (const char *, char *const[], char *const[]), 3, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execv, c, int, (const char *, char *const[]), 2, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execvp, c, int, (const char *, char *const[]), 2, PITO_JAIL_BASE)
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL(utime, c, int, (const char *, const struct utimbuf *), 2)
PITO_SYSTEM_CALL(utimes, c, int, (const char *, const struct timeval[2]), 2)
PITO_SYSTEM_CALL(utimensat, c, int, (int, const char *, const struct timespec[2], int), 4)
PITO_SYSTEM_CALL(futimesat, c, int, (int, const char *, const struct timeval[2]), 3)
PITO_SYSTEM_CALL(lutimes, c, int, (const char *, const struct timeval[2]), 2)
PITO_SYSTEM_CALL(getuid, c, int, (void), 0)

} }

#endif
