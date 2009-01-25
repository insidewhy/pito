#ifndef _PITO_INTERCEPTOR_TRAITS_
#define _PITO_INTERCEPTOR_TRAITS_

#include <pito/interceptor/lib/c_traits.hpp>

namespace pito { namespace interceptor {

namespace library {
    struct c {};
}

template <>
struct Library<library::c> : LibraryHelper {
    Library() : LibraryHelper("libc.so") {}
};

namespace system_call {

PITO_SYSTEM_CALL_TRAIT(chmod, c)
PITO_SYSTEM_CALL_TRAIT(fchmod, c)
PITO_SYSTEM_CALL_TRAIT(fchmodat, c)
PITO_SYSTEM_CALL_TRAIT(chown, c)
PITO_SYSTEM_CALL_TRAIT(fchown, c)
PITO_SYSTEM_CALL_TRAIT(fchownat, c)
PITO_SYSTEM_CALL_TRAIT(open, c)
PITO_SYSTEM_CALL_TRAIT(openat, c)
PITO_SYSTEM_CALL_TRAIT(creat, c)
PITO_SYSTEM_CALL_TRAIT(fopen, c)
PITO_SYSTEM_CALL_TRAIT(lchown, c)
PITO_SYSTEM_CALL_TRAIT(link, c)
PITO_SYSTEM_CALL_TRAIT(linkat, c)
PITO_SYSTEM_CALL_TRAIT(mkdir, c)
PITO_SYSTEM_CALL_TRAIT(mkdirat, c)
PITO_SYSTEM_CALL_TRAIT(opendir, c)
PITO_SYSTEM_CALL_TRAIT(mknod, c)
PITO_SYSTEM_CALL_TRAIT(mknodat, c)
    // function todo: __xmknod
PITO_SYSTEM_CALL_TRAIT(mkfifo, c)
PITO_SYSTEM_CALL_TRAIT(mkfifoat, c)
PITO_SYSTEM_CALL_TRAIT(access, c)
PITO_SYSTEM_CALL_TRAIT(faccessat, c)
PITO_SYSTEM_CALL_TRAIT(rename, c)
PITO_SYSTEM_CALL_TRAIT(renameat, c)
PITO_SYSTEM_CALL_TRAIT(rmdir, c)
PITO_SYSTEM_CALL_TRAIT(symlink, c)
PITO_SYSTEM_CALL_TRAIT(symlinkat, c)
PITO_SYSTEM_CALL_TRAIT(truncate, c)
PITO_SYSTEM_CALL_TRAIT(unlink, c)
PITO_SYSTEM_CALL_TRAIT(unlinkat, c)
PITO_SYSTEM_CALL_TRAIT(getcwd, c)
PITO_SYSTEM_CALL_TRAIT(open64, c)
PITO_SYSTEM_CALL_TRAIT(openat64, c)
PITO_SYSTEM_CALL_TRAIT(creat64, c)
PITO_SYSTEM_CALL_TRAIT(fopen64, c)
PITO_SYSTEM_CALL_TRAIT(truncate64, c)
PITO_SYSTEM_CALL_TRAIT(execve, c)
PITO_SYSTEM_CALL_TRAIT(execv, c)
PITO_SYSTEM_CALL_TRAIT(execvp, c)
PITO_SYSTEM_CALL_TRAIT(utime, c)
PITO_SYSTEM_CALL_TRAIT(utimes, c)
PITO_SYSTEM_CALL_TRAIT(utimensat, c)
PITO_SYSTEM_CALL_TRAIT(futimesat, c)
PITO_SYSTEM_CALL_TRAIT(lutimes, c)
PITO_SYSTEM_CALL_TRAIT(getuid, c)

} } }

#endif
