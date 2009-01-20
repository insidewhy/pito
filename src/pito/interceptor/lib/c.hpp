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

// super experts can override this!
#ifndef PITO_SYSTEMCALL_BASE
#define PITO_SYSTEMCALL_BASE  SystemCallHelper
#endif

template <>
struct SystemCall<system_call::chmod>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>("chmod") {}
};

template <>
struct SystemCall<system_call::fchmod>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, mode_t)>("fchmod") {}
};

template <>
struct SystemCall<system_call::fchmodat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t, int)>("fchmodat") {}
};

template <>
struct SystemCall<system_call::chown>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, uid_t, gid_t)>("chown") {}
};

template <>
struct SystemCall<system_call::fchown>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, uid_t, gid_t)>("fchown") {}
};

template <>
struct SystemCall<system_call::fchownat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, uid_t, gid_t, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, uid_t, gid_t, int)>("fchownat") {}
};

template <>
struct SystemCall<system_call::open>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, mode_t)>("open") {}
};

template <>
struct SystemCall<system_call::openat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, mode_t)>("openat") {}
};

template <>
struct SystemCall<system_call::creat>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>("creat") {}
};

template <>
struct SystemCall<system_call::fopen>
  : PITO_SYSTEMCALL_BASE<library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, FILE *(const char *, const char *)>("fopen") {}
};

template <>
struct SystemCall<system_call::lchown>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, uid_t, gid_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, uid_t, gid_t)>("lchown") {}
};

template <>
struct SystemCall<system_call::link>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>("link") {}
};

template <>
struct SystemCall<system_call::linkat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, const char *, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, const char *, int)>("linkat") {}
};

template <>
struct SystemCall<system_call::mkdir>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>("mkdir") {}
};

template <>
struct SystemCall<system_call::mkdirat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t)>("mkdirat") {}
};

template <>
struct SystemCall<system_call::opendir>
  : PITO_SYSTEMCALL_BASE<library::c, DIR *(const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, DIR *(const char *)>("opendir") {}
};

template <>
struct SystemCall<system_call::mknod>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t, dev_t)>("mknod") {}
};

template <>
struct SystemCall<system_call::mknodat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t, dev_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t, dev_t)>("mknodat") {}
};

// function todo: __xmknod
template <>
struct SystemCall<system_call::mkfifo>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>("mkfifo") {}
};

template <>
struct SystemCall<system_call::mkfifoat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, mode_t)>("mkfifoat") {}
};

template <>
struct SystemCall<system_call::access>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int)>("access") {}
};

template <>
struct SystemCall<system_call::faccessat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, int)>("faccessat") {}
};

template <>
struct SystemCall<system_call::rename>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>("rename") {}
};

template <>
struct SystemCall<system_call::renameat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, const char *)>("renameat") {}
};

template <>
struct SystemCall<system_call::rmdir>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *)>("rmdir") {}
};

template <>
struct SystemCall<system_call::symlink>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const char *)>("symlink") {}
};

template <>
struct SystemCall<system_call::symlinkat>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, const char *)>("symlinkat") {}
};

template <>
struct SystemCall<system_call::truncate>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, off_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, off_t)>("truncate") {}
};

template <>
struct SystemCall<system_call::unlink>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *)>("unlink") {}
};

template <>
struct SystemCall<system_call::unlinkat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int)>("unlinkat") {}
};

template <>
struct SystemCall<system_call::getcwd>
  : PITO_SYSTEMCALL_BASE<library::c, char *(char *, size_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, char *(char *, size_t)>("getcwd") {}
};

template <>
struct SystemCall<system_call::open64>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, int, mode_t)>("open64") {}
};

template <>
struct SystemCall<system_call::openat64>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, int, mode_t)>("openat64") {}
};

template <>
struct SystemCall<system_call::creat64>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, mode_t)>("creat64") {}
};

template <>
struct SystemCall<system_call::fopen64>
  : PITO_SYSTEMCALL_BASE<library::c, FILE *(const char *, const char *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, FILE *(const char *, const char *)>("fopen64") {}
};

template <>
struct SystemCall<system_call::truncate64>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, __off64_t)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, __off64_t)>("truncate64") {}
};

template <>
struct SystemCall<system_call::execve>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, char *const argv[], char *const[])>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, char *const argv[], char *const[])>("execve") {}
};

template <>
struct SystemCall<system_call::utime>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct utimbuf *)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct utimbuf *)>("utime") {}
};

template <>
struct SystemCall<system_call::utimes>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct timeval[2])>("utimes") {}
};

template <>
struct SystemCall<system_call::utimensat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, const struct timespec[2], int)>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, const struct timespec[2], int)>("utimensat") {}
};

template <>
struct SystemCall<system_call::futimesat>
  : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(int, const char *, const struct timeval[2])>("futimesat") {}
};

template <>
struct SystemCall<system_call::lutimes>
  : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct timeval[2])>
{
    SystemCall() : PITO_SYSTEMCALL_BASE<library::c, int(const char *, const struct timeval[2])>("lutimes") {}
};

} }

#endif
