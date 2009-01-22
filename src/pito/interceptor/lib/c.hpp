#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

// TODO: handle the jail differently
#include <pito/interceptor/jail/libc.hpp>
#include <pito/interceptor/SystemCall.hpp>

#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

#include "config.hpp"

namespace pito { namespace interceptor {

using namespace system_call;

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallBase
#endif

#define PITO_SYSTEM_CALL(_name, _library, _retVal, _argTypes, _argVals, _argTypeVals ) \
    PITO_SYSTEM_CALL_TRAIT(_name) \
    template <> \
    struct SystemCall<_name> \
      : PITO_SYSTEM_CALL_BASE<_name, library::_library, _retVal _argTypes> {}; \
    extern "C" { \
        _retVal _name _argTypeVals { \
            return PITO_SUPER(_name) _argVals; \
        } \
    }

////////////////////////////////////////////////////////////////////////////////
// security intercepts
PITO_SYSTEM_CALL(chmod, c, int, (const char *, mode_t), (path, mode), (char const *path, mode_t mode))
PITO_SYSTEM_CALL(fchmod, c, int, (int, mode_t), (fd, mode), (int fd, mode_t mode))
PITO_SYSTEM_CALL(fchmodat, c, int, (int, const char *, mode_t, int), \
                                   (dirfd, path, mode, flags), \
                                   (int dirfd, char const *path, mode_t mode, int flags))

PITO_SYSTEM_CALL_TRAIT(chown)
template <>
struct SystemCall<chown>
  : PITO_SYSTEM_CALL_BASE<chown, library::c, int(const char *, uid_t, gid_t)> {};

extern "C" {
    int chown(const char *path, uid_t owner, gid_t group) {
        return PITO_SUPER(chown)(path, owner, group);
    }
}

PITO_SYSTEM_CALL_TRAIT(fchown)
template <>
struct SystemCall<fchown>
  : PITO_SYSTEM_CALL_BASE<fchown, library::c, int(int, uid_t, gid_t)> {};

extern "C" {
    int fchown(int fd, uid_t owner, gid_t group) {
        return PITO_SUPER(fchown)(fd, owner, group);
    }
}

PITO_SYSTEM_CALL_TRAIT(fchownat)
template <>
struct SystemCall<fchownat>
  : PITO_SYSTEM_CALL_BASE<fchownat, library::c, int(int, const char *, uid_t, gid_t, int)> {};

extern "C" {
    int fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags) {
        return PITO_SUPER(fchownat)(dirfd, pathname, owner, group, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(open)
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

PITO_SYSTEM_CALL_TRAIT(openat)
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

PITO_SYSTEM_CALL_TRAIT(creat)
template <>
struct SystemCall<creat>
  : PITO_SYSTEM_CALL_BASE<creat, library::c, int(const char *, mode_t)> {};

extern "C" {
    int creat(const char *pathname, mode_t mode) {
        return PITO_SUPER(creat)(pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(fopen)
template <>
struct SystemCall<fopen>
  : PITO_SYSTEM_CALL_BASE<fopen, library::c, FILE *(const char *, const char *)> {};

extern "C" {
    FILE *fopen(const char *path, const char *mode) {
        return PITO_SUPER(fopen)(path, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(lchown)
template <>
struct SystemCall<lchown>
  : PITO_SYSTEM_CALL_BASE<lchown, library::c, int(const char *, uid_t, gid_t)> {};

extern "C" {
    int lchown(const char *path, uid_t owner, gid_t group) {
        return PITO_SUPER(lchown)(path, owner, group);
    }
}

PITO_SYSTEM_CALL_TRAIT(link)
template <>
struct SystemCall<link>
  : PITO_SYSTEM_CALL_BASE<link, library::c, int(const char *, const char *)> {};

extern "C" {
    int link(const char *oldpath, const char *newpath) {
        return PITO_SUPER(link)(oldpath, newpath);
    }
}

PITO_SYSTEM_CALL_TRAIT(linkat)
template <>
struct SystemCall<linkat>
  : PITO_SYSTEM_CALL_BASE<linkat, library::c, int(int, const char *, int, const char *, int)> {};

extern "C" {
    int linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags) {
        return PITO_SUPER(linkat)(olddirfd, oldpath, newdirfd, newpath, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(mkdir)
template <>
struct SystemCall<mkdir>
  : PITO_SYSTEM_CALL_BASE<mkdir, library::c, int(const char *, mode_t)> {};

extern "C" {
    int mkdir(const char *pathname, mode_t mode) {
        return PITO_SUPER(mkdir)(pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(mkdirat)
template <>
struct SystemCall<mkdirat>
  : PITO_SYSTEM_CALL_BASE<mkdirat, library::c, int(int, const char *, mode_t)> {};

extern "C" {
    int mkdirat(int dirfd, const char *pathname, mode_t mode) {
        return PITO_SUPER(mkdirat)(dirfd, pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(opendir)
template <>
struct SystemCall<opendir>
  : PITO_SYSTEM_CALL_BASE<opendir, library::c, DIR *(const char *)> {};

extern "C" {
    DIR *opendir(const char *name) {
        return PITO_SUPER(opendir)(name);
    }
}

PITO_SYSTEM_CALL_TRAIT(mknod)
template <>
struct SystemCall<mknod>
  : PITO_SYSTEM_CALL_BASE<mknod, library::c, int(const char *, mode_t, dev_t)> {};

extern "C" {
    int mknod(const char *pathname, mode_t mode, dev_t dev) {
        return PITO_SUPER(mknod)(pathname, mode, dev);
    }
}

PITO_SYSTEM_CALL_TRAIT(mknodat)
template <>
struct SystemCall<mknodat>
  : PITO_SYSTEM_CALL_BASE<mknodat, library::c, int(int, const char *, mode_t, dev_t)> {};

extern "C" {
    int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev) {
        return PITO_SUPER(mknodat)(dirfd, pathname, mode, dev);
    }
}

// function todo: __xmknod
PITO_SYSTEM_CALL_TRAIT(mkfifo)
template <>
struct SystemCall<mkfifo>
  : PITO_SYSTEM_CALL_BASE<mkfifo, library::c, int(const char *, mode_t)> {};

extern "C" {
    int mkfifo(const char *pathname, mode_t mode) {
        return PITO_SUPER(mkfifo)(pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(mkfifoat)
template <>
struct SystemCall<mkfifoat>
  : PITO_SYSTEM_CALL_BASE<mkfifoat, library::c, int(int, const char *, mode_t)> {};

extern "C" {
    int mkfifoat(int dirfd, const char *pathname, mode_t mode) {
        return PITO_SUPER(mkfifoat)(dirfd, pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(access)
template <>
struct SystemCall<access>
  : PITO_SYSTEM_CALL_BASE<access, library::c, int(const char *, int)> {};

extern "C" {
    int access(const char *pathname, int mode) {
        return PITO_SUPER(access)(pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(faccessat)
template <>
struct SystemCall<faccessat>
  : PITO_SYSTEM_CALL_BASE<faccessat, library::c, int(int, const char *, int, int)> {};

extern "C" {
    int faccessat(int dirfd, const char *pathname, int mode, int flags) {
        return PITO_SUPER(faccessat)(dirfd, pathname, mode, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(rename)
template <>
struct SystemCall<rename>
  : PITO_SYSTEM_CALL_BASE<rename, library::c, int(const char *, const char *)> {};

extern "C" {
    int rename(const char *oldpath, const char *newpath) {
        return PITO_SUPER(rename)(oldpath, newpath);
    }
}

PITO_SYSTEM_CALL_TRAIT(renameat)
template <>
struct SystemCall<renameat>
  : PITO_SYSTEM_CALL_BASE<renameat, library::c, int(int, const char *, int, const char *)> {};

extern "C" {
    int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) {
        return PITO_SUPER(renameat)(olddirfd, oldpath, newdirfd, newpath);
    }
}

PITO_SYSTEM_CALL_TRAIT(rmdir)
template <>
struct SystemCall<rmdir>
  : PITO_SYSTEM_CALL_BASE<rmdir, library::c, int(const char *)> {};

extern "C" {
    int rmdir(const char *pathname) {
        return PITO_SUPER(rmdir)(pathname);
    }
}

PITO_SYSTEM_CALL_TRAIT(symlink)
template <>
struct SystemCall<symlink>
  : PITO_SYSTEM_CALL_BASE<symlink, library::c, int(const char *, const char *)> {};

extern "C" {
    int symlink(const char *oldpath, const char *newpath) {
        return PITO_SUPER(symlink)(oldpath, newpath);
    }
}

PITO_SYSTEM_CALL_TRAIT(symlinkat)
template <>
struct SystemCall<symlinkat>
  : PITO_SYSTEM_CALL_BASE<symlinkat, library::c, int(const char *, int, const char *)> {};

extern "C" {
    int symlinkat(const char *oldpath, int newdirfd, const char *newpath) {
        return PITO_SUPER(symlinkat)(oldpath, newdirfd, newpath);
    }
}

PITO_SYSTEM_CALL_TRAIT(truncate)
template <>
struct SystemCall<truncate>
  : PITO_SYSTEM_CALL_BASE<truncate, library::c, int(const char *, off_t)> {};

extern "C" {
    int truncate(const char *path, off_t length) {
        return PITO_SUPER(truncate)(path, length);
    }
}

PITO_SYSTEM_CALL_TRAIT(unlink)
template <>
struct SystemCall<unlink>
  : PITO_SYSTEM_CALL_BASE<unlink, library::c, int(const char *)> {};

extern "C" {
    int unlink(const char *pathname) {
        return PITO_SUPER(unlink)(pathname);
    }
}

PITO_SYSTEM_CALL_TRAIT(unlinkat)
template <>
struct SystemCall<unlinkat>
  : PITO_SYSTEM_CALL_BASE<unlinkat, library::c, int(int, const char *, int)> {};

extern "C" {
    int unlinkat(int dirfd, const char *pathname, int flags) {
        return PITO_SUPER(unlinkat)(dirfd, pathname, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(getcwd)
template <>
struct SystemCall<getcwd>
  : PITO_SYSTEM_CALL_BASE<getcwd, library::c, char *(char *, size_t)> {};

extern "C" {
    char *getcwd(char *buf, size_t size) {
        return PITO_SUPER(getcwd)(buf, size);
    }
}

PITO_SYSTEM_CALL_TRAIT(open64)
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

PITO_SYSTEM_CALL_TRAIT(openat64)
template <>
struct SystemCall<openat64>
  : PITO_SYSTEM_CALL_BASE<openat64, library::c, int(int, const char *, int)> {};

extern "C" {
    int openat64(int dirfd, const char *pathname, int flags, ...) {
        if (flags & O_CREAT) {
            va_list ap;
            va_start(ap, flags);
            mode_t mode = va_arg(ap, int);
            va_end(ap);
            return PITO_SUPER(openat64)(dirfd, pathname, flags, mode);
        }
        else return PITO_SUPER(openat64)(dirfd, pathname, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(creat64)
template <>
struct SystemCall<creat64>
  : PITO_SYSTEM_CALL_BASE<creat64, library::c, int(const char *, mode_t)> {};

extern "C" {
    int creat64(const char *pathname, mode_t mode) {
        return PITO_SUPER(creat64)(pathname, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(fopen64)
template <>
struct SystemCall<fopen64>
  : PITO_SYSTEM_CALL_BASE<fopen64, library::c, FILE *(const char *, const char *)> {};

extern "C" {
    FILE *fopen64(const char *path, const char *mode) {
        return PITO_SUPER(fopen64)(path, mode);
    }
}

PITO_SYSTEM_CALL_TRAIT(truncate64)
template <>
struct SystemCall<truncate64>
  : PITO_SYSTEM_CALL_BASE<truncate64, library::c, int(const char *, PITO_OFF64_TYPE)> {};

extern "C" {
    int truncate64(const char *path, PITO_OFF64_TYPE length) {
        return PITO_SUPER(truncate64)(path, length);
    }
}

////////////////////////////////////////////////////////////////////////////////
// jail
////////////////////////////////////////////////////////////////////////////////
// TODO: see previous TODO
PITO_SYSTEM_CALL_TRAIT(execve)
template <>
struct SystemCall<execve>
  : PITO_SYSTEM_CALL_BASE<execve, library::c, int(const char *, char *const[], char *const[])> {};

extern "C" {
    int execve(const char *filename, char *const argv[], char *const envp[]) {
        enforceEnvironment(envp);
        return PITO_SUPER(execve)(filename, argv, envp);
    }
}

PITO_SYSTEM_CALL_TRAIT(execv)
template <>
struct SystemCall<execv>
  : PITO_SYSTEM_CALL_BASE<execv, library::c, int(const char *, char *const[])> {};

extern "C" {
    int execv(const char *filename, char *const argv[]) {
        enforceEnvironment();
        return PITO_SUPER(execv)(filename, argv);
    }
}

PITO_SYSTEM_CALL_TRAIT(execvp)
template <>
struct SystemCall<execvp>
  : PITO_SYSTEM_CALL_BASE<execvp, library::c, int(const char *, char *const[])> {};

extern "C" {
    int execvp(const char *filename, char *const argv[]) {
        enforceEnvironment();
        return PITO_SUPER(execvp)(filename, argv);
    }
}
////////////////////////////////////////////////////////////////////////////////
// end jail
////////////////////////////////////////////////////////////////////////////////

PITO_SYSTEM_CALL_TRAIT(utime)
template <>
struct SystemCall<utime>
  : PITO_SYSTEM_CALL_BASE<utime, library::c, int(const char *, const struct utimbuf *)> {};

extern "C" {
    int utime(const char *filename, const struct utimbuf *times) {
        return PITO_SUPER(utime)(filename, times);
    }
}

PITO_SYSTEM_CALL_TRAIT(utimes)
template <>
struct SystemCall<utimes>
  : PITO_SYSTEM_CALL_BASE<utimes, library::c, int(const char *, const struct timeval[2])> {};

extern "C" {
    int utimes(const char *filename, const struct timeval times[2]) {
        return PITO_SUPER(utimes)(filename, times);
    }
}

PITO_SYSTEM_CALL_TRAIT(utimensat)
template <>
struct SystemCall<utimensat>
  : PITO_SYSTEM_CALL_BASE<utimensat, library::c, int(int, const char *, const struct timespec[2], int)> {};

extern "C" {
    int utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags) {
        return PITO_SUPER(utimensat)(dirfd, pathname, times, flags);
    }
}

PITO_SYSTEM_CALL_TRAIT(futimesat)
template <>
struct SystemCall<futimesat>
  : PITO_SYSTEM_CALL_BASE<futimesat, library::c, int(int, const char *, const struct timeval[2])> {};

extern "C" {
    int futimesat(int dirfd, const char *pathname, const struct timeval times[2]) {
        return PITO_SUPER(futimesat)(dirfd, pathname, times); 
    }
}

PITO_SYSTEM_CALL_TRAIT(lutimes)
template <>
struct SystemCall<lutimes>
  : PITO_SYSTEM_CALL_BASE<lutimes, library::c, int(const char *, const struct timeval[2])> {};

extern "C" {
    int lutimes(const char *filename, const struct timeval tv[2]) {
        return PITO_SUPER(lutimes)(filename, tv);
    }
}

PITO_SYSTEM_CALL_TRAIT(getuid)
template <>
struct SystemCall<getuid>
  : PITO_SYSTEM_CALL_BASE<getuid, library::c, int()> {};

extern "C" {
    uid_t getuid(void) {
        return PITO_SUPER(getuid)();
    }
}

    // function todo: __xmknod


// see what to do about optional argument

// function todo: __xmknod
} }

#endif
