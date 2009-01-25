#ifndef _PITO_INTERCEPTOR_TRAITS_
#define _PITO_INTERCEPTOR_TRAITS_

#include <pito/interceptor/lib/c_traits.hpp>

#include "config.hpp"

#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>

namespace pito { namespace interceptor {

namespace library {
    struct c {};
}

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

namespace system_call {

#define PITO_NARGS_chmod 2
PITO_SYSTEM_CALL_TRAIT(chmod, c, int(const char *, mode_t))
#define PITO_NARGS_fchmod 2
PITO_SYSTEM_CALL_TRAIT(fchmod, c, int(int, mode_t))
#define PITO_NARGS_fchmodat 4
PITO_SYSTEM_CALL_TRAIT(fchmodat, c, int(int, const char *, mode_t, int))
#define PITO_NARGS_chown 3
PITO_SYSTEM_CALL_TRAIT(chown, c, int(const char *, uid_t, gid_t))
#define PITO_NARGS_fchown 3
PITO_SYSTEM_CALL_TRAIT(fchown, c, int(int, uid_t, gid_t))
#define PITO_NARGS_fchownat 5
PITO_SYSTEM_CALL_TRAIT(fchownat, c, int(int, const char *, uid_t, gid_t, int))
#define PITO_NARGS_open 2
PITO_SYSTEM_CALL_TRAIT(open, c, int(const char *, int))
#define PITO_NARGS_openat 3
PITO_SYSTEM_CALL_TRAIT(openat, c, int(int, const char *, int))
#define PITO_NARGS_creat 2
PITO_SYSTEM_CALL_TRAIT(creat, c, int(const char *, mode_t))
#define PITO_NARGS_fopen 2
PITO_SYSTEM_CALL_TRAIT(fopen, c, FILE *(const char *, const char *))
#define PITO_NARGS_lchown 3
PITO_SYSTEM_CALL_TRAIT(lchown, c, int(const char *, uid_t, gid_t))
#define PITO_NARGS_link 2
PITO_SYSTEM_CALL_TRAIT(link, c, int(const char *, const char *))
#define PITO_NARGS_linkat 5
PITO_SYSTEM_CALL_TRAIT(linkat, c, int(int, const char *, int, const char *, int))
#define PITO_NARGS_mkdir 2
PITO_SYSTEM_CALL_TRAIT(mkdir, c, int(const char *, mode_t))
#define PITO_NARGS_mkdirat 3
PITO_SYSTEM_CALL_TRAIT(mkdirat, c, int(int, const char *, mode_t))
#define PITO_NARGS_opendir 1
PITO_SYSTEM_CALL_TRAIT(opendir, c, DIR *(const char *))
#define PITO_NARGS_mknod 3
PITO_SYSTEM_CALL_TRAIT(mknod, c, int(const char *, mode_t, dev_t))
#define PITO_NARGS_mknodat 4
PITO_SYSTEM_CALL_TRAIT(mknodat, c, int(int, const char *, mode_t, dev_t))
// function todo: __xmknod
#define PITO_NARGS_mkfifo 2
PITO_SYSTEM_CALL_TRAIT(mkfifo, c, int(const char *, mode_t))
#define PITO_NARGS_mkfifoat 3
PITO_SYSTEM_CALL_TRAIT(mkfifoat, c, int(int, const char *, mode_t))
#define PITO_NARGS_access 2
PITO_SYSTEM_CALL_TRAIT(access, c, int(const char *, int))
#define PITO_NARGS_faccessat 4
PITO_SYSTEM_CALL_TRAIT(faccessat, c, int(int, const char *, int, int))
#define PITO_NARGS_rename 2
PITO_SYSTEM_CALL_TRAIT(rename, c, int(const char *, const char *))
#define PITO_NARGS_renameat 4
PITO_SYSTEM_CALL_TRAIT(renameat, c, int(int, const char *, int, const char *))
#define PITO_NARGS_rmdir 1
PITO_SYSTEM_CALL_TRAIT(rmdir, c, int(const char *))
#define PITO_NARGS_symlink 2
PITO_SYSTEM_CALL_TRAIT(symlink, c, int(const char *, const char *))
#define PITO_NARGS_symlinkat 3
PITO_SYSTEM_CALL_TRAIT(symlinkat, c, int(const char *, int, const char *))
#define PITO_NARGS_truncate 2
PITO_SYSTEM_CALL_TRAIT(truncate, c, int(const char *, off_t))
#define PITO_NARGS_unlink 1
PITO_SYSTEM_CALL_TRAIT(unlink, c, int(const char *))
#define PITO_NARGS_unlinkat 3
PITO_SYSTEM_CALL_TRAIT(unlinkat, c, int(int, const char *, int))
#define PITO_NARGS_getcwd 2
PITO_SYSTEM_CALL_TRAIT(getcwd, c, char *(char *, size_t))
#define PITO_NARGS_open64 2
PITO_SYSTEM_CALL_TRAIT(open64, c, int(const char *, int))
#define PITO_NARGS_openat64 3
PITO_SYSTEM_CALL_TRAIT(openat64, c, int(int, const char *, int))
#define PITO_NARGS_creat64 2
PITO_SYSTEM_CALL_TRAIT(creat64, c, int(const char *, mode_t))
#define PITO_NARGS_fopen64 2
PITO_SYSTEM_CALL_TRAIT(fopen64, c, FILE *(const char *, const char *))
#define PITO_NARGS_truncate64 2
PITO_SYSTEM_CALL_TRAIT(truncate64, c, int(const char *, PITO_OFF64_TYPE))
#define PITO_NARGS_execve 3
PITO_SYSTEM_CALL_TRAIT(execve, c, int(const char *, char *const[], char *const[]))
#define PITO_NARGS_execv 2
PITO_SYSTEM_CALL_TRAIT(execv, c, int(const char *, char *const[]))
#define PITO_NARGS_execvp 2
PITO_SYSTEM_CALL_TRAIT(execvp, c, int(const char *, char *const[]))
#define PITO_NARGS_utime 2
PITO_SYSTEM_CALL_TRAIT(utime, c, int(const char *, const struct utimbuf *))
#define PITO_NARGS_utimes 2
PITO_SYSTEM_CALL_TRAIT(utimes, c, int(const char *, const struct timeval[2]))
#define PITO_NARGS_utimensat 4
PITO_SYSTEM_CALL_TRAIT(utimensat, c, int(int, const char *, const struct timespec[2], int))
#define PITO_NARGS_futimesat 3
PITO_SYSTEM_CALL_TRAIT(futimesat, c, int(int, const char *, const struct timeval[2]))
#define PITO_NARGS_lutimes 2
PITO_SYSTEM_CALL_TRAIT(lutimes, c, int(const char *, const struct timeval[2]))
#define PITO_NARGS_getuid 0
PITO_SYSTEM_CALL_TRAIT(getuid, c, int(void))

} } }

#endif
