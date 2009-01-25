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

////////////////////////////////////////////////////////////////////////////////
// security intercepts
PITO_SYSTEM_CALL(chmod, int(const char *, mode_t), 2)
PITO_SYSTEM_CALL(fchmod, int(int, mode_t), 2)
PITO_SYSTEM_CALL(fchmodat, int(int, const char *, mode_t, int), 4)
PITO_SYSTEM_CALL(chown, int(const char *, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(fchown, int(int, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(fchownat, int(int, const char *, uid_t, gid_t, int), 5)

template <>
struct SystemCall<open>
  : PITO_SYSTEM_CALL_BASE<open, int(const char *, int)> {};

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
  : PITO_SYSTEM_CALL_BASE<openat, int(int, const char *, int)> {};

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

PITO_SYSTEM_CALL(creat, int(const char *, mode_t), 2)
PITO_SYSTEM_CALL(fopen, FILE *(const char *, const char *), 2)
PITO_SYSTEM_CALL(lchown, int(const char *, uid_t, gid_t), 3)
PITO_SYSTEM_CALL(link, int(const char *, const char *), 2)
PITO_SYSTEM_CALL(linkat, int(int, const char *, int, const char *, int), 5)
PITO_SYSTEM_CALL(mkdir, int(const char *, mode_t), 2)
PITO_SYSTEM_CALL(mkdirat, int(int, const char *, mode_t), 3)
PITO_SYSTEM_CALL(opendir, DIR *(const char *), 1)
PITO_SYSTEM_CALL(mknod, int(const char *, mode_t, dev_t), 3)
PITO_SYSTEM_CALL(mknodat, int(int, const char *, mode_t, dev_t), 4)
// function todo: __xmknod
PITO_SYSTEM_CALL(mkfifo, int(const char *, mode_t), 2)
PITO_SYSTEM_CALL(mkfifoat, int(int, const char *, mode_t), 3)
PITO_SYSTEM_CALL(access, int(const char *, int), 2)
PITO_SYSTEM_CALL(faccessat, int(int, const char *, int, int), 4)
PITO_SYSTEM_CALL(rename, int(const char *, const char *), 2)
PITO_SYSTEM_CALL(renameat, int(int, const char *, int, const char *), 4)
PITO_SYSTEM_CALL(rmdir, int(const char *), 1)
PITO_SYSTEM_CALL(symlink, int(const char *, const char *), 2)
PITO_SYSTEM_CALL(symlinkat, int(const char *, int, const char *), 3)
PITO_SYSTEM_CALL(truncate, int(const char *, off_t), 2)
PITO_SYSTEM_CALL(unlink, int(const char *), 1)
PITO_SYSTEM_CALL(unlinkat, int(int, const char *, int), 3)
PITO_SYSTEM_CALL(getcwd, char *(char *, size_t), 2)

template <>
struct SystemCall<open64>
  : PITO_SYSTEM_CALL_BASE<open64, int(const char *, int)> {};

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
  : PITO_SYSTEM_CALL_BASE<openat64, int(int, const char *, int)> {};

extern "C" {
    int openat64(RBUTIL_ARGS_3(SystemCall<openat64>::arg_types), ...) {
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

PITO_SYSTEM_CALL(creat64, int(const char *, mode_t), 2)
PITO_SYSTEM_CALL(fopen64, FILE *(const char *, const char *), 2)
PITO_SYSTEM_CALL(truncate64, int(const char *, PITO_OFF64_TYPE), 2)

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
PITO_SYSTEM_CALL_WITH_BASE(execve, int(const char *, char *const[], char *const[]), 3, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execv, int(const char *, char *const[]), 2, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execvp, int(const char *, char *const[]), 2, PITO_JAIL_BASE)
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL(utime, int(const char *, const struct utimbuf *), 2)
PITO_SYSTEM_CALL(utimes, int(const char *, const struct timeval[2]), 2)
PITO_SYSTEM_CALL(utimensat, int(int, const char *, const struct timespec[2], int), 4)
PITO_SYSTEM_CALL(futimesat, int(int, const char *, const struct timeval[2]), 3)
PITO_SYSTEM_CALL(lutimes, int(const char *, const struct timeval[2]), 2)
PITO_SYSTEM_CALL(getuid, int(void), 0)

} }

#endif
