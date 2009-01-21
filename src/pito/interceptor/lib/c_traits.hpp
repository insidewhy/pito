#ifndef _PITO_LIB_TRAITS_
#define _PITO_LIB_TRAITS_

namespace pito { namespace interceptor { namespace system_call {

template <class Tag>
struct traits;

#define PITO_SYSTEM_CALL_TRAIT(name_) \
    struct name_ {}; \
    template <> struct traits<name_> { \
        static char const name[]; \
    }; \
    char const traits<name_>::name[] = #name_;

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

} } }

#endif
