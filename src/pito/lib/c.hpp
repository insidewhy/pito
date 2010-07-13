#ifndef PITO_LIB_C
#define PITO_LIB_C

#include <pito/lib/c_traits.hpp>
#include <pito/system_call.hpp>

#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  detail::system_call
#endif

#ifndef PITO_JAIL_BASE
#define PITO_JAIL_BASE PITO_SYSTEM_CALL_BASE
#endif

namespace pito {

using namespace system_call_tag;

////////////////////////////////////////////////////////////////////////////////
// security intercepts
PITO_SYSTEM_CALL(chmod)
PITO_SYSTEM_CALL(fchmod)
PITO_SYSTEM_CALL(fchmodat)
PITO_SYSTEM_CALL(chown)
PITO_SYSTEM_CALL(fchown)
PITO_SYSTEM_CALL(fchownat)

template <>
struct system_call<open>
 : PITO_SYSTEM_CALL_BASE<open> {};

extern "C" {
    int open(PITO_ARGS(open), ...) {
        if (arg1 & O_CREAT) {
            va_list ap;
            va_start(ap, arg1);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_CALL(open)(arg0, arg1, mode);
        }
        else return PITO_CALL(open)(arg0, arg1);
    }
}

template <>
struct system_call<open64>
  : PITO_SYSTEM_CALL_BASE<open64> {};

extern "C" {
    int open64(PITO_ARGS(open64), ...) {
        if (arg1 & O_CREAT) {
            va_list ap;
            va_start(ap, arg1);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_CALL(open64)(arg0, arg1, mode);
        }
        else return PITO_CALL(open64)(arg0, arg1);
    }
}

template <>
struct system_call<openat>
  : PITO_SYSTEM_CALL_BASE<openat> {};

extern "C" {
    int openat(PITO_ARGS(openat), ...) {
        if (arg2 & O_CREAT) {
            va_list ap;
            va_start(ap, arg2);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_CALL(openat)(arg0, arg1, arg2, mode);
        }
        else return PITO_CALL(openat)(arg0, arg1, arg2);
    }
}

template <>
struct system_call<openat64>
  : PITO_SYSTEM_CALL_BASE<openat64> {};

extern "C" {
    int openat64(PITO_ARGS(openat64), ...) {
        if (arg2 & O_CREAT) {
            va_list ap;
            va_start(ap, arg2);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_CALL(openat64)(arg0, arg1, arg2, mode);
        }
        else return PITO_CALL(openat64)(arg0, arg1, arg2);
    }
}

PITO_SYSTEM_CALL(creat)
PITO_SYSTEM_CALL(creat64)
PITO_SYSTEM_CALL(fopen)
PITO_SYSTEM_CALL(fopen64)
PITO_SYSTEM_CALL(lchown)
PITO_SYSTEM_CALL(link)
PITO_SYSTEM_CALL(linkat)
PITO_SYSTEM_CALL(mkdir)
PITO_SYSTEM_CALL(mkdirat)
PITO_SYSTEM_CALL(opendir)
PITO_SYSTEM_CALL(readdir)
PITO_SYSTEM_CALL(mknod)
PITO_SYSTEM_CALL(mknodat)
// function todo: __xmknod
PITO_SYSTEM_CALL(mkfifo)
PITO_SYSTEM_CALL(mkfifoat)
PITO_SYSTEM_CALL(access)
PITO_SYSTEM_CALL(faccessat)
PITO_SYSTEM_CALL(rename)
PITO_SYSTEM_CALL(renameat)
PITO_SYSTEM_CALL(rmdir)
PITO_SYSTEM_CALL(symlink)
PITO_SYSTEM_CALL(symlinkat)
PITO_SYSTEM_CALL(truncate)
PITO_SYSTEM_CALL(truncate64)
PITO_SYSTEM_CALL(unlink)
PITO_SYSTEM_CALL(unlinkat)
PITO_SYSTEM_CALL(getcwd)

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
PITO_SYSTEM_CALL_WITH_BASE(execve, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execv, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execvp, PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(system, PITO_JAIL_BASE)
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL(utime)
PITO_SYSTEM_CALL(utimes)
PITO_SYSTEM_CALL(utimensat)
PITO_SYSTEM_CALL(futimesat)
PITO_SYSTEM_CALL(lutimes)
PITO_SYSTEM_CALL(getuid)

}

#endif
