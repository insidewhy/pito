#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

#include <pito/interceptor/Library.hpp>
#include <pito/interceptor/lib/c_traits.hpp>
#include <pito/interceptor/SystemCall.hpp>

#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

#include <iostream>
#include <stdlib.h>

namespace pito { namespace interceptor {

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallHelper
#endif

template <>
struct SystemCall<system_call::chmod>
  : PITO_SYSTEM_CALL_BASE<system_call::chmod, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::chmod, library::c, int(const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::fchmod>
  : PITO_SYSTEM_CALL_BASE<system_call::fchmod, library::c, int(int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchmod, library::c, int(int, mode_t)>() {}
};

template <>
struct SystemCall<system_call::fchmodat>
  : PITO_SYSTEM_CALL_BASE<system_call::fchmodat, library::c, int(int, const char *, mode_t, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchmodat, library::c, int(int, const char *, mode_t, int)>() {}
};

template <>
struct SystemCall<system_call::chown>
  : PITO_SYSTEM_CALL_BASE<system_call::chown, library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::chown, library::c, int(const char *, uid_t, gid_t)>() {}
};

template <>
struct SystemCall<system_call::fchown>
  : PITO_SYSTEM_CALL_BASE<system_call::fchown, library::c, int(int, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchown, library::c, int(int, uid_t, gid_t)>() {}
};

template <>
struct SystemCall<system_call::fchownat>
  : PITO_SYSTEM_CALL_BASE<system_call::fchownat, library::c, int(int, const char *, uid_t, gid_t, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchownat, library::c, int(int, const char *, uid_t, gid_t, int)>() {}
};

template <>
struct SystemCall<system_call::open>
  : PITO_SYSTEM_CALL_BASE<system_call::open, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::open, library::c, int(const char *, int)>() {}
};

template <>
struct SystemCall<system_call::openat>
  : PITO_SYSTEM_CALL_BASE<system_call::openat, library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::openat, library::c, int(int, const char *, int, mode_t)>() {}
};

template <>
struct SystemCall<system_call::creat>
  : PITO_SYSTEM_CALL_BASE<system_call::creat, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::creat, library::c, int(const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::fopen>
  : PITO_SYSTEM_CALL_BASE<system_call::fopen, library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fopen, library::c, FILE *(const char *, const char *)>() {}
};

template <>
struct SystemCall<system_call::lchown>
  : PITO_SYSTEM_CALL_BASE<system_call::lchown, library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::lchown, library::c, int(const char *, uid_t, gid_t)>() {}
};

template <>
struct SystemCall<system_call::link>
  : PITO_SYSTEM_CALL_BASE<system_call::link, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::link, library::c, int(const char *, const char *)>() {}
};

template <>
struct SystemCall<system_call::linkat>
  : PITO_SYSTEM_CALL_BASE<system_call::linkat, library::c, int(int, const char *, int, const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::linkat, library::c, int(int, const char *, int, const char *, int)>() {}
};

template <>
struct SystemCall<system_call::mkdir>
  : PITO_SYSTEM_CALL_BASE<system_call::mkdir, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkdir, library::c, int(const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::mkdirat>
  : PITO_SYSTEM_CALL_BASE<system_call::mkdirat, library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkdirat, library::c, int(int, const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::opendir>
  : PITO_SYSTEM_CALL_BASE<system_call::opendir, library::c, DIR *(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::opendir, library::c, DIR *(const char *)>() {}
};

template <>
struct SystemCall<system_call::mknod>
  : PITO_SYSTEM_CALL_BASE<system_call::mknod, library::c, int(const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mknod, library::c, int(const char *, mode_t, dev_t)>() {}
};

template <>
struct SystemCall<system_call::mknodat>
  : PITO_SYSTEM_CALL_BASE<system_call::mknodat, library::c, int(int, const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mknodat, library::c, int(int, const char *, mode_t, dev_t)>() {}
};

// function todo: __xmknod
template <>
struct SystemCall<system_call::mkfifo>
  : PITO_SYSTEM_CALL_BASE<system_call::mkfifo, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkfifo, library::c, int(const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::mkfifoat>
  : PITO_SYSTEM_CALL_BASE<system_call::mkfifoat, library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkfifoat, library::c, int(int, const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::access>
  : PITO_SYSTEM_CALL_BASE<system_call::access, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::access, library::c, int(const char *, int)>() {}
};

template <>
struct SystemCall<system_call::faccessat>
  : PITO_SYSTEM_CALL_BASE<system_call::faccessat, library::c, int(int, const char *, int, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::faccessat, library::c, int(int, const char *, int, int)>() {}
};

template <>
struct SystemCall<system_call::rename>
  : PITO_SYSTEM_CALL_BASE<system_call::rename, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::rename, library::c, int(const char *, const char *)>() {}
};

template <>
struct SystemCall<system_call::renameat>
  : PITO_SYSTEM_CALL_BASE<system_call::renameat, library::c, int(int, const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::renameat, library::c, int(int, const char *, int, const char *)>() {}
};

template <>
struct SystemCall<system_call::rmdir>
  : PITO_SYSTEM_CALL_BASE<system_call::rmdir, library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::rmdir, library::c, int(const char *)>() {}
};

template <>
struct SystemCall<system_call::symlink>
  : PITO_SYSTEM_CALL_BASE<system_call::symlink, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::symlink, library::c, int(const char *, const char *)>() {}
};

template <>
struct SystemCall<system_call::symlinkat>
  : PITO_SYSTEM_CALL_BASE<system_call::symlinkat, library::c, int(const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::symlinkat, library::c, int(const char *, int, const char *)>() {}
};

template <>
struct SystemCall<system_call::truncate>
  : PITO_SYSTEM_CALL_BASE<system_call::truncate, library::c, int(const char *, off_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::truncate, library::c, int(const char *, off_t)>() {}
};

template <>
struct SystemCall<system_call::unlink>
  : PITO_SYSTEM_CALL_BASE<system_call::unlink, library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::unlink, library::c, int(const char *)>() {}
};

template <>
struct SystemCall<system_call::unlinkat>
  : PITO_SYSTEM_CALL_BASE<system_call::unlinkat, library::c, int(int, const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::unlinkat, library::c, int(int, const char *, int)>() {}
};

template <>
struct SystemCall<system_call::getcwd>
  : PITO_SYSTEM_CALL_BASE<system_call::getcwd, library::c, char *(char *, size_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::getcwd, library::c, char *(char *, size_t)>() {}
};

template <>
struct SystemCall<system_call::open64>
  : PITO_SYSTEM_CALL_BASE<system_call::open64, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::open64, library::c, int(const char *, int)>() {}
};

template <>
struct SystemCall<system_call::openat64>
  : PITO_SYSTEM_CALL_BASE<system_call::openat64, library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::openat64, library::c, int(int, const char *, int, mode_t)>() {}
};

template <>
struct SystemCall<system_call::creat64>
  : PITO_SYSTEM_CALL_BASE<system_call::creat64, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::creat64, library::c, int(const char *, mode_t)>() {}
};

template <>
struct SystemCall<system_call::fopen64>
  : PITO_SYSTEM_CALL_BASE<system_call::fopen64, library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fopen64, library::c, FILE *(const char *, const char *)>() {}
};

template <>
struct SystemCall<system_call::truncate64>
  : PITO_SYSTEM_CALL_BASE<system_call::truncate64, library::c, int(const char *, __off64_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::truncate64, library::c, int(const char *, __off64_t)>() {}
};

template <>
struct SystemCall<system_call::execve>
  : PITO_SYSTEM_CALL_BASE<system_call::execve, library::c, int(const char *, char *const[], char *const[])>
{
    typedef PITO_SYSTEM_CALL_BASE<system_call::execve, library::c, int(const char *, char *const[], char *const[])> base_t;
    SystemCall() : base_t() {}

    int operator()(const char *cmd, char *const argv[], char *const envp[]) {
        // TODO: force LD_PRELOAD back in envp if necessary
        return base_t::operator()(cmd, argv, envp);
    }
};

template <>
struct SystemCall<system_call::execv>
  : PITO_SYSTEM_CALL_BASE<system_call::execv, library::c, int(const char *, char *const[])>
{
    typedef PITO_SYSTEM_CALL_BASE<system_call::execv, library::c, int(const char *, char *const[])> base_t;
    SystemCall() : base_t() {}

    int operator()(const char *cmd, char *const argv[]) {
        // TODO: force LD_PRELOAD back in environ if necessary
        return base_t::operator()(cmd, argv);
    }
};

template <>
struct SystemCall<system_call::execvp>
  : PITO_SYSTEM_CALL_BASE<system_call::execvp, library::c, int(const char *, char *const[])>
{
    typedef PITO_SYSTEM_CALL_BASE<system_call::execvp, library::c, int(const char *, char *const[])> base_t;
    SystemCall() : base_t() {}

    int operator()(const char *cmd, char *const argv[]) {
        // TODO: force LD_PRELOAD back in environ if necessary
        return base_t::operator()(cmd, argv);
    }
};

template <>
struct SystemCall<system_call::utime>
  : PITO_SYSTEM_CALL_BASE<system_call::utime, library::c, int(const char *, const struct utimbuf *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utime, library::c, int(const char *, const struct utimbuf *)>() {}
};

template <>
struct SystemCall<system_call::utimes>
  : PITO_SYSTEM_CALL_BASE<system_call::utimes, library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utimes, library::c, int(const char *, const struct timeval[2])>() {}
};

template <>
struct SystemCall<system_call::utimensat>
  : PITO_SYSTEM_CALL_BASE<system_call::utimensat, library::c, int(int, const char *, const struct timespec[2], int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utimensat, library::c, int(int, const char *, const struct timespec[2], int)>() {}
};

template <>
struct SystemCall<system_call::futimesat>
  : PITO_SYSTEM_CALL_BASE<system_call::futimesat, library::c, int(int, const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::futimesat, library::c, int(int, const char *, const struct timeval[2])>() {}
};

template <>
struct SystemCall<system_call::lutimes>
  : PITO_SYSTEM_CALL_BASE<system_call::lutimes, library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::lutimes, library::c, int(const char *, const struct timeval[2])>() {}
};

} }

#endif
