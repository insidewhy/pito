#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

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

namespace system_call {

#define PITO_SYSTEM_CALL_TRAIT(name_) \
    struct name_ { \
        static char const name[]; \
    }; \
    char const name_::name[] = "name_";

PITO_SYSTEM_CALL_TRAIT(chmod)
PITO_SYSTEM_CALL_TRAIT(fchmod)
PITO_SYSTEM_CALL_TRAIT(fchmodat)
PITO_SYSTEM_CALL_TRAIT(chown)
PITO_SYSTEM_CALL_TRAIT(fchown)
PITO_SYSTEM_CALL_TRAIT(fchownat)
PITO_SYSTEM_CALL_TRAIT(open)
PITO_SYSTEM_CALL_TRAIT(openat)
PITO_SYSTEM_CALL_TRAIT(creat)
PITO_SYSTEM_CALL_TRAIT(fopen)
PITO_SYSTEM_CALL_TRAIT(lchown)
PITO_SYSTEM_CALL_TRAIT(link)
PITO_SYSTEM_CALL_TRAIT(linkat)
PITO_SYSTEM_CALL_TRAIT(mkdir)
PITO_SYSTEM_CALL_TRAIT(mkdirat)
PITO_SYSTEM_CALL_TRAIT(opendir)
PITO_SYSTEM_CALL_TRAIT(mknod)
PITO_SYSTEM_CALL_TRAIT(mknodat)
    // function todo: __xmknod
PITO_SYSTEM_CALL_TRAIT(mkfifo)
PITO_SYSTEM_CALL_TRAIT(mkfifoat)
PITO_SYSTEM_CALL_TRAIT(access)
PITO_SYSTEM_CALL_TRAIT(faccessat)
PITO_SYSTEM_CALL_TRAIT(rename)
PITO_SYSTEM_CALL_TRAIT(renameat)
PITO_SYSTEM_CALL_TRAIT(rmdir)
PITO_SYSTEM_CALL_TRAIT(symlink)
PITO_SYSTEM_CALL_TRAIT(symlinkat)
PITO_SYSTEM_CALL_TRAIT(truncate)
PITO_SYSTEM_CALL_TRAIT(unlink)
PITO_SYSTEM_CALL_TRAIT(unlinkat)
PITO_SYSTEM_CALL_TRAIT(getcwd)
PITO_SYSTEM_CALL_TRAIT(open64)
PITO_SYSTEM_CALL_TRAIT(openat64)
PITO_SYSTEM_CALL_TRAIT(creat64)
PITO_SYSTEM_CALL_TRAIT(fopen64)
PITO_SYSTEM_CALL_TRAIT(truncate64)
PITO_SYSTEM_CALL_TRAIT(execve)
PITO_SYSTEM_CALL_TRAIT(execv)
PITO_SYSTEM_CALL_TRAIT(execvp)
PITO_SYSTEM_CALL_TRAIT(utime)
PITO_SYSTEM_CALL_TRAIT(utimes)
PITO_SYSTEM_CALL_TRAIT(utimensat)
PITO_SYSTEM_CALL_TRAIT(futimesat)
PITO_SYSTEM_CALL_TRAIT(lutimes)

}

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallHelper
#endif

template <>
struct SystemCall<system_call::chmod>
  : PITO_SYSTEM_CALL_BASE<system_call::chmod, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::chmod, library::c, int(const char *, mode_t)>("chmod") {}
};

template <>
struct SystemCall<system_call::fchmod>
  : PITO_SYSTEM_CALL_BASE<system_call::fchmod, library::c, int(int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchmod, library::c, int(int, mode_t)>("fchmod") {}
};

template <>
struct SystemCall<system_call::fchmodat>
  : PITO_SYSTEM_CALL_BASE<system_call::fchmodat, library::c, int(int, const char *, mode_t, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchmodat, library::c, int(int, const char *, mode_t, int)>("fchmodat") {}
};

template <>
struct SystemCall<system_call::chown>
  : PITO_SYSTEM_CALL_BASE<system_call::chown, library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::chown, library::c, int(const char *, uid_t, gid_t)>("chown") {}
};

template <>
struct SystemCall<system_call::fchown>
  : PITO_SYSTEM_CALL_BASE<system_call::fchown, library::c, int(int, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchown, library::c, int(int, uid_t, gid_t)>("fchown") {}
};

template <>
struct SystemCall<system_call::fchownat>
  : PITO_SYSTEM_CALL_BASE<system_call::fchownat, library::c, int(int, const char *, uid_t, gid_t, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fchownat, library::c, int(int, const char *, uid_t, gid_t, int)>("fchownat") {}
};

template <>
struct SystemCall<system_call::open>
  : PITO_SYSTEM_CALL_BASE<system_call::open, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::open, library::c, int(const char *, int)>("open") {}
};

template <>
struct SystemCall<system_call::openat>
  : PITO_SYSTEM_CALL_BASE<system_call::openat, library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::openat, library::c, int(int, const char *, int, mode_t)>("openat") {}
};

template <>
struct SystemCall<system_call::creat>
  : PITO_SYSTEM_CALL_BASE<system_call::creat, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::creat, library::c, int(const char *, mode_t)>("creat") {}
};

template <>
struct SystemCall<system_call::fopen>
  : PITO_SYSTEM_CALL_BASE<system_call::fopen, library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fopen, library::c, FILE *(const char *, const char *)>("fopen") {}
};

template <>
struct SystemCall<system_call::lchown>
  : PITO_SYSTEM_CALL_BASE<system_call::lchown, library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::lchown, library::c, int(const char *, uid_t, gid_t)>("lchown") {}
};

template <>
struct SystemCall<system_call::link>
  : PITO_SYSTEM_CALL_BASE<system_call::link, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::link, library::c, int(const char *, const char *)>("link") {}
};

template <>
struct SystemCall<system_call::linkat>
  : PITO_SYSTEM_CALL_BASE<system_call::linkat, library::c, int(int, const char *, int, const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::linkat, library::c, int(int, const char *, int, const char *, int)>("linkat") {}
};

template <>
struct SystemCall<system_call::mkdir>
  : PITO_SYSTEM_CALL_BASE<system_call::mkdir, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkdir, library::c, int(const char *, mode_t)>("mkdir") {}
};

template <>
struct SystemCall<system_call::mkdirat>
  : PITO_SYSTEM_CALL_BASE<system_call::mkdirat, library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkdirat, library::c, int(int, const char *, mode_t)>("mkdirat") {}
};

template <>
struct SystemCall<system_call::opendir>
  : PITO_SYSTEM_CALL_BASE<system_call::opendir, library::c, DIR *(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::opendir, library::c, DIR *(const char *)>("opendir") {}
};

template <>
struct SystemCall<system_call::mknod>
  : PITO_SYSTEM_CALL_BASE<system_call::mknod, library::c, int(const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mknod, library::c, int(const char *, mode_t, dev_t)>("mknod") {}
};

template <>
struct SystemCall<system_call::mknodat>
  : PITO_SYSTEM_CALL_BASE<system_call::mknodat, library::c, int(int, const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mknodat, library::c, int(int, const char *, mode_t, dev_t)>("mknodat") {}
};

// function todo: __xmknod
template <>
struct SystemCall<system_call::mkfifo>
  : PITO_SYSTEM_CALL_BASE<system_call::mkfifo, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkfifo, library::c, int(const char *, mode_t)>("mkfifo") {}
};

template <>
struct SystemCall<system_call::mkfifoat>
  : PITO_SYSTEM_CALL_BASE<system_call::mkfifoat, library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::mkfifoat, library::c, int(int, const char *, mode_t)>("mkfifoat") {}
};

template <>
struct SystemCall<system_call::access>
  : PITO_SYSTEM_CALL_BASE<system_call::access, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::access, library::c, int(const char *, int)>("access") {}
};

template <>
struct SystemCall<system_call::faccessat>
  : PITO_SYSTEM_CALL_BASE<system_call::faccessat, library::c, int(int, const char *, int, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::faccessat, library::c, int(int, const char *, int, int)>("faccessat") {}
};

template <>
struct SystemCall<system_call::rename>
  : PITO_SYSTEM_CALL_BASE<system_call::rename, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::rename, library::c, int(const char *, const char *)>("rename") {}
};

template <>
struct SystemCall<system_call::renameat>
  : PITO_SYSTEM_CALL_BASE<system_call::renameat, library::c, int(int, const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::renameat, library::c, int(int, const char *, int, const char *)>("renameat") {}
};

template <>
struct SystemCall<system_call::rmdir>
  : PITO_SYSTEM_CALL_BASE<system_call::rmdir, library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::rmdir, library::c, int(const char *)>("rmdir") {}
};

template <>
struct SystemCall<system_call::symlink>
  : PITO_SYSTEM_CALL_BASE<system_call::symlink, library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::symlink, library::c, int(const char *, const char *)>("symlink") {}
};

template <>
struct SystemCall<system_call::symlinkat>
  : PITO_SYSTEM_CALL_BASE<system_call::symlinkat, library::c, int(const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::symlinkat, library::c, int(const char *, int, const char *)>("symlinkat") {}
};

template <>
struct SystemCall<system_call::truncate>
  : PITO_SYSTEM_CALL_BASE<system_call::truncate, library::c, int(const char *, off_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::truncate, library::c, int(const char *, off_t)>("truncate") {}
};

template <>
struct SystemCall<system_call::unlink>
  : PITO_SYSTEM_CALL_BASE<system_call::unlink, library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::unlink, library::c, int(const char *)>("unlink") {}
};

template <>
struct SystemCall<system_call::unlinkat>
  : PITO_SYSTEM_CALL_BASE<system_call::unlinkat, library::c, int(int, const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::unlinkat, library::c, int(int, const char *, int)>("unlinkat") {}
};

template <>
struct SystemCall<system_call::getcwd>
  : PITO_SYSTEM_CALL_BASE<system_call::getcwd, library::c, char *(char *, size_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::getcwd, library::c, char *(char *, size_t)>("getcwd") {}
};

template <>
struct SystemCall<system_call::open64>
  : PITO_SYSTEM_CALL_BASE<system_call::open64, library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::open64, library::c, int(const char *, int)>("open64") {}
};

template <>
struct SystemCall<system_call::openat64>
  : PITO_SYSTEM_CALL_BASE<system_call::openat64, library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::openat64, library::c, int(int, const char *, int, mode_t)>("openat64") {}
};

template <>
struct SystemCall<system_call::creat64>
  : PITO_SYSTEM_CALL_BASE<system_call::creat64, library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::creat64, library::c, int(const char *, mode_t)>("creat64") {}
};

template <>
struct SystemCall<system_call::fopen64>
  : PITO_SYSTEM_CALL_BASE<system_call::fopen64, library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::fopen64, library::c, FILE *(const char *, const char *)>("fopen64") {}
};

template <>
struct SystemCall<system_call::truncate64>
  : PITO_SYSTEM_CALL_BASE<system_call::truncate64, library::c, int(const char *, __off64_t)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::truncate64, library::c, int(const char *, __off64_t)>("truncate64") {}
};

template <>
struct SystemCall<system_call::execve>
  : PITO_SYSTEM_CALL_BASE<system_call::execve, library::c, int(const char *, char *const[], char *const[])>
{
    typedef PITO_SYSTEM_CALL_BASE<system_call::execve, library::c, int(const char *, char *const[], char *const[])> base_t;
    SystemCall() : base_t("execve") {}

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
    SystemCall() : base_t("execv") {}

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
    SystemCall() : base_t("execvp") {}

    int operator()(const char *cmd, char *const argv[]) {
        // TODO: force LD_PRELOAD back in environ if necessary
        return base_t::operator()(cmd, argv);
    }
};

template <>
struct SystemCall<system_call::utime>
  : PITO_SYSTEM_CALL_BASE<system_call::utime, library::c, int(const char *, const struct utimbuf *)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utime, library::c, int(const char *, const struct utimbuf *)>("utime") {}
};

template <>
struct SystemCall<system_call::utimes>
  : PITO_SYSTEM_CALL_BASE<system_call::utimes, library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utimes, library::c, int(const char *, const struct timeval[2])>("utimes") {}
};

template <>
struct SystemCall<system_call::utimensat>
  : PITO_SYSTEM_CALL_BASE<system_call::utimensat, library::c, int(int, const char *, const struct timespec[2], int)>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::utimensat, library::c, int(int, const char *, const struct timespec[2], int)>("utimensat") {}
};

template <>
struct SystemCall<system_call::futimesat>
  : PITO_SYSTEM_CALL_BASE<system_call::futimesat, library::c, int(int, const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::futimesat, library::c, int(int, const char *, const struct timeval[2])>("futimesat") {}
};

template <>
struct SystemCall<system_call::lutimes>
  : PITO_SYSTEM_CALL_BASE<system_call::lutimes, library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEM_CALL_BASE<system_call::lutimes, library::c, int(const char *, const struct timeval[2])>("lutimes") {}
};

} }

#endif
