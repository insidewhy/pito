#ifndef _PITO_INTERCEPTOR_LIB_C_
#define _PITO_INTERCEPTOR_LIB_C_

#include <pito/interceptor/SystemCall.hpp>
#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

namespace pito { namespace interceptor {

namespace system_call {
    struct chmod {};
    struct fchmod {};
    struct fchmodat {};
    struct chown {};
    struct fchown {};
    struct fchownat {};
    struct open {};
    struct openat {};
    struct creat {};
    struct fopen {};
    struct lchown {};
    struct link {};
    struct linkat {};
    struct mkdir {};
    struct mkdirat {};
    struct opendir {};
    struct mknod {};
    struct mknodat {};
    // function todo: __xmknod
    struct mkfifo {};
    struct mkfifoat {};
    struct access {};
    struct faccessat {};
    struct rename {};
    struct renameat {};
    struct rmdir {};
    struct symlink {};
    struct symlinkat {};
    struct truncate {};
    struct unlink {};
    struct unlinkat {};
    struct getcwd {};
    struct open64 {};
    struct openat64 {};
    struct creat64 {};
    struct fopen64 {};
    struct truncate64 {};
    struct execve {};
    struct utime {};
    struct utimes {};
    struct utimensat {};
    struct futimesat {};
    struct lutimes {};
};

template <>
struct SystemCall<system_call::chmod>
  : SystemCallHelper<library::c, int(const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t)>("chmod") {}
};

template <>
struct SystemCall<system_call::fchmod>
  : SystemCallHelper<library::c, int(int, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, mode_t)>("fchmod") {}
};

template <>
struct SystemCall<system_call::fchmodat>
  : SystemCallHelper<library::c, int(int, const char *, mode_t, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, mode_t, int)>("fchmodat") {}
};

template <>
struct SystemCall<system_call::chown>
  : SystemCallHelper<library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, uid_t, gid_t)>("chown") {}
};

template <>
struct SystemCall<system_call::fchown>
  : SystemCallHelper<library::c, int(int, uid_t, gid_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, uid_t, gid_t)>("fchown") {}
};

template <>
struct SystemCall<system_call::fchownat>
  : SystemCallHelper<library::c, int(int, const char *, uid_t, gid_t, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, uid_t, gid_t, int)>("fchownat") {}
};

template <>
struct SystemCall<system_call::open>
  : SystemCallHelper<library::c, int(const char *, int, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, int, mode_t)>("open") {}
};

template <>
struct SystemCall<system_call::openat>
  : SystemCallHelper<library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int, mode_t)>("openat") {}
};

template <>
struct SystemCall<system_call::creat>
  : SystemCallHelper<library::c, int(const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t)>("creat") {}
};

template <>
struct SystemCall<system_call::fopen>
  : SystemCallHelper<library::c, FILE *(const char *, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, FILE *(const char *, const char *)>("fopen") {}
};

template <>
struct SystemCall<system_call::lchown>
  : SystemCallHelper<library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, uid_t, gid_t)>("lchown") {}
};

template <>
struct SystemCall<system_call::link>
  : SystemCallHelper<library::c, int(const char *, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const char *)>("link") {}
};

template <>
struct SystemCall<system_call::linkat>
  : SystemCallHelper<library::c, int(int, const char *, int, const char *, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int, const char *, int)>("linkat") {}
};

template <>
struct SystemCall<system_call::mkdir>
  : SystemCallHelper<library::c, int(const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t)>("mkdir") {}
};

template <>
struct SystemCall<system_call::mkdirat>
  : SystemCallHelper<library::c, int(int, const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, mode_t)>("mkdirat") {}
};

template <>
struct SystemCall<system_call::opendir>
  : SystemCallHelper<library::c, DIR *(const char *)>
{
    SystemCall() : SystemCallHelper<library::c, DIR *(const char *)>("opendir") {}
};

template <>
struct SystemCall<system_call::mknod>
  : SystemCallHelper<library::c, int(const char *, mode_t, dev_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t, dev_t)>("mknod") {}
};

template <>
struct SystemCall<system_call::mknodat>
  : SystemCallHelper<library::c, int(int, const char *, mode_t, dev_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, mode_t, dev_t)>("mknodat") {}
};

// function todo: __xmknod
template <>
struct SystemCall<system_call::mkfifo>
  : SystemCallHelper<library::c, int(const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t)>("mkfifo") {}
};

template <>
struct SystemCall<system_call::mkfifoat>
  : SystemCallHelper<library::c, int(int, const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, mode_t)>("mkfifoat") {}
};

template <>
struct SystemCall<system_call::access>
  : SystemCallHelper<library::c, int(const char *, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, int)>("access") {}
};

template <>
struct SystemCall<system_call::faccessat>
  : SystemCallHelper<library::c, int(int, const char *, int, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int, int)>("faccessat") {}
};

template <>
struct SystemCall<system_call::rename>
  : SystemCallHelper<library::c, int(const char *, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const char *)>("rename") {}
};

template <>
struct SystemCall<system_call::renameat>
  : SystemCallHelper<library::c, int(int, const char *, int, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int, const char *)>("renameat") {}
};

template <>
struct SystemCall<system_call::rmdir>
  : SystemCallHelper<library::c, int(const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *)>("rmdir") {}
};

template <>
struct SystemCall<system_call::symlink>
  : SystemCallHelper<library::c, int(const char *, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const char *)>("symlink") {}
};

template <>
struct SystemCall<system_call::symlinkat>
  : SystemCallHelper<library::c, int(const char *, int, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, int, const char *)>("symlinkat") {}
};

template <>
struct SystemCall<system_call::truncate>
  : SystemCallHelper<library::c, int(const char *, off_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, off_t)>("truncate") {}
};

template <>
struct SystemCall<system_call::unlink>
  : SystemCallHelper<library::c, int(const char *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *)>("unlink") {}
};

template <>
struct SystemCall<system_call::unlinkat>
  : SystemCallHelper<library::c, int(int, const char *, int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int)>("unlinkat") {}
};

template <>
struct SystemCall<system_call::getcwd>
  : SystemCallHelper<library::c, char *(char *, size_t)>
{
    SystemCall() : SystemCallHelper<library::c, char *(char *, size_t)>("getcwd") {}
};

template <>
struct SystemCall<system_call::open64>
  : SystemCallHelper<library::c, int(const char *, int, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, int, mode_t)>("open64") {}
};

template <>
struct SystemCall<system_call::openat64>
  : SystemCallHelper<library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, int, mode_t)>("openat64") {}
};

template <>
struct SystemCall<system_call::creat64>
  : SystemCallHelper<library::c, int(const char *, mode_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, mode_t)>("creat64") {}
};

template <>
struct SystemCall<system_call::fopen64>
  : SystemCallHelper<library::c, FILE *(const char *, const char *)>
{
    SystemCall() : SystemCallHelper<library::c, FILE *(const char *, const char *)>("fopen64") {}
};

template <>
struct SystemCall<system_call::truncate64>
  : SystemCallHelper<library::c, int(const char *, __off64_t)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, __off64_t)>("truncate64") {}
};

template <>
struct SystemCall<system_call::execve>
  : SystemCallHelper<library::c, int(const char *, char *const argv[], char *const[])>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, char *const argv[], char *const[])>("execve") {}
};

template <>
struct SystemCall<system_call::utime>
  : SystemCallHelper<library::c, int(const char *, const struct utimbuf *)>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const struct utimbuf *)>("utime") {}
};

template <>
struct SystemCall<system_call::utimes>
  : SystemCallHelper<library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const struct timeval[2])>("utimes") {}
};

template <>
struct SystemCall<system_call::utimensat>
  : SystemCallHelper<library::c, int(int, const char *, const struct timespec[2], int)>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, const struct timespec[2], int)>("utimensat") {}
};

template <>
struct SystemCall<system_call::futimesat>
  : SystemCallHelper<library::c, int(int, const char *, const struct timeval[2])>
{
    SystemCall() : SystemCallHelper<library::c, int(int, const char *, const struct timeval[2])>("futimesat") {}
};

template <>
struct SystemCall<system_call::lutimes>
  : SystemCallHelper<library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : SystemCallHelper<library::c, int(const char *, const struct timeval[2])>("lutimes") {}
};

} }

#endif
