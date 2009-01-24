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
#define PITO_ARG_NAMES_1(idx)   PITO_ARG_NAME(0)
#define PITO_ARG_NAMES_2(idx)   PITO_ARG_NAME_1, PITO_ARG_NAME(1)
#define PITO_ARG_NAMES_3(idx)   PITO_ARG_NAME_2, PITO_ARG_NAME(2)
#define PITO_ARG_NAMES_4(idx)   PITO_ARG_NAME_3, PITO_ARG_NAME(3)
#define PITO_ARG_NAMES_5(idx)   PITO_ARG_NAME_4, PITO_ARG_NAME(4)

#define PITO_ARG(idx, list) type::at<idx, list>::type PITO_ARG_NAME(idx)
#define PITO_ARGS_1(list)   PITO_ARG(0, list)
#define PITO_ARGS_2(list)   PITO_ARGS_1(list), PITO_ARG(1, list)
#define PITO_ARGS_3(list)   PITO_ARGS_2(list), PITO_ARG(2, list)
#define PITO_ARGS_4(list)   PITO_ARGS_3(list), PITO_ARG(3, list)
#define PITO_ARGS_5(list)   PITO_ARGS_4(list), PITO_ARG(4, list)

#define PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _argVals, _argTypeVals, _base) \
    template <> \
    struct SystemCall<_name> \
      : _base <_name, library::_library, _retVal _argTypes> {}; \
    extern "C" { \
        _retVal _name _argTypeVals { \
            return PITO_SUPER(_name) _argVals; \
        } \
    }

#define PITO_SYSTEM_CALL(_name, _library, _retVal, _argTypes, _argVals, _argTypeVals) \
    PITO_SYSTEM_CALL_WITH_BASE(_name, _library, _retVal, _argTypes, _argVals, _argTypeVals, PITO_SYSTEM_CALL_BASE)

////////////////////////////////////////////////////////////////////////////////
// security intercepts
PITO_SYSTEM_CALL(chmod, c, int, (const char *, mode_t), \
                 (path, mode), \
                 (char const *path, mode_t mode))
PITO_SYSTEM_CALL(fchmod, c, int, (int, mode_t), \
                 (fd, mode), \
                 (int fd, mode_t mode))
PITO_SYSTEM_CALL(fchmodat, c, int, (int, const char *, mode_t, int), \
                 (dirfd, path, mode, flags), \
                 (int dirfd, char const *path, mode_t mode, int flags))
PITO_SYSTEM_CALL(chown, c, int, (const char *, uid_t, gid_t), \
                 (path, owner, group), \
                 (const char *path, uid_t owner, gid_t group))
PITO_SYSTEM_CALL(fchown, c, int, (int, uid_t, gid_t), \
                 (fd, owner, group), \
                 (int fd, uid_t owner, gid_t group))
PITO_SYSTEM_CALL(fchownat, c, int, (int, const char *, uid_t, gid_t, int), \
                 (dirfd, pathname, owner, group, flags), \
                 (int dirfd, const char *pathname, uid_t owner, gid_t group, int flags))

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

PITO_SYSTEM_CALL(creat, c, int, (const char *, mode_t), \
                 (pathname, mode), \
                 (const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(fopen, c, FILE *, (const char *, const char *), \
                 (path, mode), \
                 (const char *path, const char *mode))
PITO_SYSTEM_CALL(lchown, c, int, (const char *, uid_t, gid_t), \
                 (path, owner, group), \
                 (const char *path, uid_t owner, gid_t group))
PITO_SYSTEM_CALL(link, c, int, (const char *, const char *), \
                 (oldpath, newpath), \
                 (const char *oldpath, const char *newpath))
PITO_SYSTEM_CALL(linkat, c, int, (int, const char *, int, const char *, int), \
                 (olddirfd, oldpath, newdirfd, newpath, flags), \
                 (int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags))
PITO_SYSTEM_CALL(mkdir, c, int, (const char *, mode_t), \
                 (pathname, mode), \
                 (const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(mkdirat, c, int, (int, const char *, mode_t), \
                 (dirfd, pathname, mode), \
                 (int dirfd, const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(opendir, c, DIR *, (const char *), \
                 (name), \
                 (const char *name))
PITO_SYSTEM_CALL(mknod, c, int, (const char *, mode_t, dev_t), \
                 (pathname, mode, dev), \
                 (const char *pathname, mode_t mode, dev_t dev))
PITO_SYSTEM_CALL(mknodat, c, int, (int, const char *, mode_t, dev_t), \
                 (dirfd, pathname, mode, dev), \
                 (int dirfd, const char *pathname, mode_t mode, dev_t dev))
// function todo: __xmknod
PITO_SYSTEM_CALL(mkfifo, c, int, (const char *, mode_t), \
                 (pathname, mode), \
                 (const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(mkfifoat, c, int, (int, const char *, mode_t), \
                 (dirfd, pathname, mode), \
                 (int dirfd, const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(access, c, int, (const char *, int), \
                 (pathname, mode), \
                 (const char *pathname, int mode))
PITO_SYSTEM_CALL(faccessat, c, int, (int, const char *, int, int), \
                 (dirfd, pathname, mode, flags), \
                 (int dirfd, const char *pathname, int mode, int flags))
PITO_SYSTEM_CALL(rename, c, int, (const char *, const char *), \
                 (oldpath, newpath), \
                 (const char *oldpath, const char *newpath))
PITO_SYSTEM_CALL(renameat, c, int, (int, const char *, int, const char *), \
                 (olddirfd, oldpath, newdirfd, newpath), \
                 (int olddirfd, const char *oldpath, int newdirfd, const char *newpath))
PITO_SYSTEM_CALL(rmdir, c, int, (const char *), \
                 (pathname), \
                 (const char *pathname))
PITO_SYSTEM_CALL(symlink, c, int, (const char *, const char *), \
                 (oldpath, newpath), \
                 (const char *oldpath, const char *newpath))
PITO_SYSTEM_CALL(symlinkat, c, int, (const char *, int, const char *), \
                 (oldpath, newdirfd, newpath), \
                 (const char *oldpath, int newdirfd, const char *newpath))
PITO_SYSTEM_CALL(truncate, c, int, (const char *, off_t), \
                 (path, length), \
                 (const char *path, off_t length))
PITO_SYSTEM_CALL(unlink, c, int, (const char *), \
                 (pathname), \
                 (const char *pathname))
PITO_SYSTEM_CALL(unlinkat, c, int, (int, const char *, int), \
                 (dirfd, pathname, flags), \
                 (int dirfd, const char *pathname, int flags))
PITO_SYSTEM_CALL(getcwd, c, char *, (char *, size_t), \
                 (buf, size), \
                 (char *buf, size_t size))

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

PITO_SYSTEM_CALL(creat64, c, int, (const char *, mode_t), \
                 (pathname, mode), \
                 (const char *pathname, mode_t mode))
PITO_SYSTEM_CALL(fopen64, c, FILE *, (const char *, const char *), \
                 (path, mode), \
                 (const char *path, const char *mode))
PITO_SYSTEM_CALL(truncate64, c, int, (const char *, PITO_OFF64_TYPE), \
                 (path, length), \
                 (const char *path, PITO_OFF64_TYPE length))

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
PITO_SYSTEM_CALL_WITH_BASE(execve, c, int, (const char *, char *const[], char *const[]), \
                           (filename, argv, envp), \
                           (const char *filename, char *const argv[], char *const envp[]), \
                           PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execv, c, int, (const char *, char *const[]), \
                           (filename, argv), \
                           (const char *filename, char *const argv[]), \
                           PITO_JAIL_BASE)
PITO_SYSTEM_CALL_WITH_BASE(execvp, c, int, (const char *, char *const[]), \
                           (filename, argv), \
                           (const char *filename, char *const argv[]), \
                           PITO_JAIL_BASE)
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL(utime, c, int, (const char *, const struct utimbuf *), \
                 (filename, times), \
                 (const char *filename, const struct utimbuf *times))
PITO_SYSTEM_CALL(utimes, c, int, (const char *, const struct timeval[2]), \
                 (filename, times), \
                 (const char *filename, const struct timeval times[2]))
PITO_SYSTEM_CALL(utimensat, c, int, (int, const char *, const struct timespec[2], int), \
                 (dirfd, pathname, times, flags), \
                 (int dirfd, const char *pathname, const struct timespec times[2], int flags))
PITO_SYSTEM_CALL(futimesat, c, int, (int, const char *, const struct timeval[2]), \
                 (dirfd, pathname, times), \
                 (int dirfd, const char *pathname, const struct timeval times[2]))
PITO_SYSTEM_CALL(lutimes, c, int, (const char *, const struct timeval[2]), \
                 (filename, tv), \
                 (const char *filename, const struct timeval tv[2]))
PITO_SYSTEM_CALL(getuid, c, int, (void), (), ())

} }

#endif
