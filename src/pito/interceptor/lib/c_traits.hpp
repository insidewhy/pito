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

PITO_SYSTEM_CALL_TRAIT(chmod, c, int(const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(fchmod, c, int(int, mode_t))
PITO_SYSTEM_CALL_TRAIT(fchmodat, c, int(int, const char *, mode_t, int))
PITO_SYSTEM_CALL_TRAIT(chown, c, int(const char *, uid_t, gid_t))
PITO_SYSTEM_CALL_TRAIT(fchown, c, int(int, uid_t, gid_t))
PITO_SYSTEM_CALL_TRAIT(fchownat, c, int(int, const char *, uid_t, gid_t, int))
PITO_SYSTEM_CALL_TRAIT(open, c, int(const char *, int))
PITO_SYSTEM_CALL_TRAIT(openat, c, int(int, const char *, int))
PITO_SYSTEM_CALL_TRAIT(creat, c, int(const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(fopen, c, FILE *(const char *, const char *))
PITO_SYSTEM_CALL_TRAIT(lchown, c, int(const char *, uid_t, gid_t))
PITO_SYSTEM_CALL_TRAIT(link, c, int(const char *, const char *))
PITO_SYSTEM_CALL_TRAIT(linkat, c, int(int, const char *, int, const char *, int))
PITO_SYSTEM_CALL_TRAIT(mkdir, c, int(const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(mkdirat, c, int(int, const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(opendir, c, DIR *(const char *))
PITO_SYSTEM_CALL_TRAIT(mknod, c, int(const char *, mode_t, dev_t))
PITO_SYSTEM_CALL_TRAIT(mknodat, c, int(int, const char *, mode_t, dev_t))
    // function todo: __xmknod
PITO_SYSTEM_CALL_TRAIT(mkfifo, c, int(const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(mkfifoat, c, int(int, const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(access, c, int(const char *, int))
PITO_SYSTEM_CALL_TRAIT(faccessat, c, int(int, const char *, int, int))
PITO_SYSTEM_CALL_TRAIT(rename, c, int(const char *, const char *))
PITO_SYSTEM_CALL_TRAIT(renameat, c, int(int, const char *, int, const char *))
PITO_SYSTEM_CALL_TRAIT(rmdir, c, int(const char *))
PITO_SYSTEM_CALL_TRAIT(symlink, c, int(const char *, const char *))
PITO_SYSTEM_CALL_TRAIT(symlinkat, c, int(const char *, int, const char *))
PITO_SYSTEM_CALL_TRAIT(truncate, c, int(const char *, off_t))
PITO_SYSTEM_CALL_TRAIT(unlink, c, int(const char *))
PITO_SYSTEM_CALL_TRAIT(unlinkat, c, int(int, const char *, int))
PITO_SYSTEM_CALL_TRAIT(getcwd, c, char *(char *, size_t))
PITO_SYSTEM_CALL_TRAIT(open64, c, int(const char *, int))
PITO_SYSTEM_CALL_TRAIT(openat64, c, int(int, const char *, int))
PITO_SYSTEM_CALL_TRAIT(creat64, c, int(const char *, mode_t))
PITO_SYSTEM_CALL_TRAIT(fopen64, c, FILE *(const char *, const char *))
PITO_SYSTEM_CALL_TRAIT(truncate64, c, int(const char *, PITO_OFF64_TYPE))
PITO_SYSTEM_CALL_TRAIT(execve, c, int(const char *, char *const[], char *const[]))
PITO_SYSTEM_CALL_TRAIT(execv, c, int(const char *, char *const[]))
PITO_SYSTEM_CALL_TRAIT(execvp, c, int(const char *, char *const[]))
PITO_SYSTEM_CALL_TRAIT(utime, c, int(const char *, const struct utimbuf *))
PITO_SYSTEM_CALL_TRAIT(utimes, c, int(const char *, const struct timeval[2]))
PITO_SYSTEM_CALL_TRAIT(utimensat, c, int(int, const char *, const struct timespec[2], int))
PITO_SYSTEM_CALL_TRAIT(futimesat, c, int(int, const char *, const struct timeval[2]))
PITO_SYSTEM_CALL_TRAIT(lutimes, c, int(const char *, const struct timeval[2]))
PITO_SYSTEM_CALL_TRAIT(getuid, c, int(void))

} } }

#endif
