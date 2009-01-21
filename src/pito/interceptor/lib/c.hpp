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

#include "config.hpp"

namespace pito { namespace interceptor {

using namespace system_call;

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

// super experts can override this!
#ifndef PITO_SYSTEM_CALL_BASE
#define PITO_SYSTEM_CALL_BASE  SystemCallHelper
#endif

template <>
struct SystemCall<chmod>
  : PITO_SYSTEM_CALL_BASE<chmod, library::c, int(const char *, mode_t)> {};

template <>
struct SystemCall<fchmod>
  : PITO_SYSTEM_CALL_BASE<fchmod, library::c, int(int, mode_t)> {};

template <>
struct SystemCall<fchmodat>
  : PITO_SYSTEM_CALL_BASE<fchmodat, library::c, int(int, const char *, mode_t, int)> {};

template <>
struct SystemCall<chown>
  : PITO_SYSTEM_CALL_BASE<chown, library::c, int(const char *, uid_t, gid_t)> {};

template <>
struct SystemCall<fchown>
  : PITO_SYSTEM_CALL_BASE<fchown, library::c, int(int, uid_t, gid_t)> {};

template <>
struct SystemCall<fchownat>
  : PITO_SYSTEM_CALL_BASE<fchownat, library::c, int(int, const char *, uid_t, gid_t, int)> {};

template <>
struct SystemCall<open>
  : PITO_SYSTEM_CALL_BASE<open, library::c, int(const char *, int)> {};

template <>
struct SystemCall<openat>
  : PITO_SYSTEM_CALL_BASE<openat, library::c, int(int, const char *, int)> {};

template <>
struct SystemCall<creat>
  : PITO_SYSTEM_CALL_BASE<creat, library::c, int(const char *, mode_t)> {};

template <>
struct SystemCall<fopen>
  : PITO_SYSTEM_CALL_BASE<fopen, library::c, FILE *(const char *, const char *)> {};

template <>
struct SystemCall<lchown>
  : PITO_SYSTEM_CALL_BASE<lchown, library::c, int(const char *, uid_t, gid_t)> {};

template <>
struct SystemCall<link>
  : PITO_SYSTEM_CALL_BASE<link, library::c, int(const char *, const char *)> {};

template <>
struct SystemCall<linkat>
  : PITO_SYSTEM_CALL_BASE<linkat, library::c, int(int, const char *, int, const char *, int)> {};

template <>
struct SystemCall<mkdir>
  : PITO_SYSTEM_CALL_BASE<mkdir, library::c, int(const char *, mode_t)> {};

template <>
struct SystemCall<mkdirat>
  : PITO_SYSTEM_CALL_BASE<mkdirat, library::c, int(int, const char *, mode_t)> {};

template <>
struct SystemCall<opendir>
  : PITO_SYSTEM_CALL_BASE<opendir, library::c, DIR *(const char *)> {};

template <>
struct SystemCall<mknod>
  : PITO_SYSTEM_CALL_BASE<mknod, library::c, int(const char *, mode_t, dev_t)> {};

template <>
struct SystemCall<mknodat>
  : PITO_SYSTEM_CALL_BASE<mknodat, library::c, int(int, const char *, mode_t, dev_t)> {};

// function todo: __xmknod
template <>
struct SystemCall<mkfifo>
  : PITO_SYSTEM_CALL_BASE<mkfifo, library::c, int(const char *, mode_t)> {};

template <>
struct SystemCall<mkfifoat>
  : PITO_SYSTEM_CALL_BASE<mkfifoat, library::c, int(int, const char *, mode_t)> {};

template <>
struct SystemCall<access>
  : PITO_SYSTEM_CALL_BASE<access, library::c, int(const char *, int)> {};

template <>
struct SystemCall<faccessat>
  : PITO_SYSTEM_CALL_BASE<faccessat, library::c, int(int, const char *, int, int)> {};

template <>
struct SystemCall<rename>
  : PITO_SYSTEM_CALL_BASE<rename, library::c, int(const char *, const char *)> {};

template <>
struct SystemCall<renameat>
  : PITO_SYSTEM_CALL_BASE<renameat, library::c, int(int, const char *, int, const char *)> {};

template <>
struct SystemCall<rmdir>
  : PITO_SYSTEM_CALL_BASE<rmdir, library::c, int(const char *)> {};

template <>
struct SystemCall<symlink>
  : PITO_SYSTEM_CALL_BASE<symlink, library::c, int(const char *, const char *)> {};

template <>
struct SystemCall<symlinkat>
  : PITO_SYSTEM_CALL_BASE<symlinkat, library::c, int(const char *, int, const char *)> {};

template <>
struct SystemCall<truncate>
  : PITO_SYSTEM_CALL_BASE<truncate, library::c, int(const char *, off_t)> {};

template <>
struct SystemCall<unlink>
  : PITO_SYSTEM_CALL_BASE<unlink, library::c, int(const char *)> {};

template <>
struct SystemCall<unlinkat>
  : PITO_SYSTEM_CALL_BASE<unlinkat, library::c, int(int, const char *, int)> {};

template <>
struct SystemCall<getcwd>
  : PITO_SYSTEM_CALL_BASE<getcwd, library::c, char *(char *, size_t)> {};

template <>
struct SystemCall<open64>
  : PITO_SYSTEM_CALL_BASE<open64, library::c, int(const char *, int)> {};

template <>
struct SystemCall<openat64>
  : PITO_SYSTEM_CALL_BASE<openat64, library::c, int(int, const char *, int)> {};

template <>
struct SystemCall<creat64>
  : PITO_SYSTEM_CALL_BASE<creat64, library::c, int(const char *, mode_t)> {};

template <>
struct SystemCall<fopen64>
  : PITO_SYSTEM_CALL_BASE<fopen64, library::c, FILE *(const char *, const char *)> {};

template <>
struct SystemCall<truncate64>
  : PITO_SYSTEM_CALL_BASE<truncate64, library::c, int(const char *, PITO_OFF64_TYPE)> {};

template <>
struct SystemCall<execve>
  : PITO_SYSTEM_CALL_BASE<execve, library::c, int(const char *, char *const[], char *const[])> {};

template <>
struct SystemCall<execv>
  : PITO_SYSTEM_CALL_BASE<execv, library::c, int(const char *, char *const[])> {};

template <>
struct SystemCall<execvp>
  : PITO_SYSTEM_CALL_BASE<execvp, library::c, int(const char *, char *const[])> {};

template <>
struct SystemCall<utime>
  : PITO_SYSTEM_CALL_BASE<utime, library::c, int(const char *, const struct utimbuf *)> {};

template <>
struct SystemCall<utimes>
  : PITO_SYSTEM_CALL_BASE<utimes, library::c, int(const char *, const struct timeval[2])> {};

template <>
struct SystemCall<utimensat>
  : PITO_SYSTEM_CALL_BASE<utimensat, library::c, int(int, const char *, const struct timespec[2], int)> {};

template <>
struct SystemCall<futimesat>
  : PITO_SYSTEM_CALL_BASE<futimesat, library::c, int(int, const char *, const struct timeval[2])> {};

template <>
struct SystemCall<lutimes>
  : PITO_SYSTEM_CALL_BASE<lutimes, library::c, int(const char *, const struct timeval[2])> {};

} }

#endif
