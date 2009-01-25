#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

#include <pito/interceptor/lib/c_traits.hpp>
#include <pito/interceptor/SystemCall.hpp>

#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

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
PITO_SYSTEM_CALL(chmod, 2)
PITO_SYSTEM_CALL(fchmod, 2)
PITO_SYSTEM_CALL(fchmodat, 4)
PITO_SYSTEM_CALL(chown, 3)
PITO_SYSTEM_CALL(fchown, 3)
PITO_SYSTEM_CALL(fchownat, 5)

template <>
struct SystemCall<open>
  : PITO_SYSTEM_CALL_BASE<open> {};

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
  : PITO_SYSTEM_CALL_BASE<openat> {};

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

PITO_SYSTEM_CALL(creat, 2)
PITO_SYSTEM_CALL(fopen, 2)
PITO_SYSTEM_CALL(lchown, 3)
PITO_SYSTEM_CALL(link, 2)
PITO_SYSTEM_CALL(linkat, 5)
PITO_SYSTEM_CALL(mkdir, 2)
PITO_SYSTEM_CALL(mkdirat, 3)
PITO_SYSTEM_CALL(opendir, 1)
PITO_SYSTEM_CALL(mknod, 3)
PITO_SYSTEM_CALL(mknodat, 4)
// function todo: __xmknod
PITO_SYSTEM_CALL(mkfifo, 2)
PITO_SYSTEM_CALL(mkfifoat, 3)
PITO_SYSTEM_CALL(access, 2)
PITO_SYSTEM_CALL(faccessat, 4)
PITO_SYSTEM_CALL(rename, 2)
PITO_SYSTEM_CALL(renameat, 4)
PITO_SYSTEM_CALL(rmdir, 1)
PITO_SYSTEM_CALL(symlink, 2)
PITO_SYSTEM_CALL(symlinkat, 3)
PITO_SYSTEM_CALL(truncate, 2)
PITO_SYSTEM_CALL(unlink, 1)
PITO_SYSTEM_CALL(unlinkat, 3)
PITO_SYSTEM_CALL(getcwd, 2)

template <>
struct SystemCall<open64>
  : PITO_SYSTEM_CALL_BASE<open64> {};

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
  : PITO_SYSTEM_CALL_BASE<openat64> {};

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

PITO_SYSTEM_CALL(creat64, 2)
PITO_SYSTEM_CALL(fopen64, 2)
PITO_SYSTEM_CALL(truncate64, 2)

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
PITO_SYSTEM_CALL_WITH_BASE(execve, 3, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execv, 2, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execvp, 2, PITO_JAIL_BASE)
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL(utime, 2)
PITO_SYSTEM_CALL(utimes, 2)
PITO_SYSTEM_CALL(utimensat, 4)
PITO_SYSTEM_CALL(futimesat, 3)
PITO_SYSTEM_CALL(lutimes, 2)
PITO_SYSTEM_CALL(getuid, 0)

} }

#endif
