#ifndef PITO_SANDBOX_SYSTEM_CALL_HPP
#define PITO_SANDBOX_SYSTEM_CALL_HPP
#include <pito/plugin/sandbox/helper.hpp>

namespace pito { namespace sandbox {

using namespace system_call_tag;

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : system_call_real<Tag> {
    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
        return this->system(args...);
    }
};

template <>
struct system_call<chmod> : sandbox_call<chmod> {};

template <>
struct system_call<fchmod> : sandbox_fd_call<fchmod> {};

template <>
struct system_call<fchmodat> : sandbox_fd_call<fchmodat, 0, 1> {};

template <>
struct system_call<chown> : sandbox_call<chown> {};

template <>
struct system_call<fchown> : sandbox_fd_call<fchown> {};

template <>
struct system_call<fchownat> : sandbox_fd_call<fchownat, 0, 1> {};

template <>
struct system_call<open> : sandbox_call_open<open> {};

template <>
struct system_call<open64> : sandbox_call_open<open64> {};

template <>
struct system_call<openat> : system_call_real<openat> {
    PITO_RETURN(openat) operator()(int fd, const char *path, int flags) {
        return system(fd, path, flags);
    }

    PITO_RETURN(openat) operator()(int fd, const char *path, int flags, int mode) {
        return system(fd, path, flags, mode);
    }
};

template <>
struct system_call<openat64> : system_call_real<openat64> {
    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags) {
        return system(fd, path, flags);
    }

    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags, int mode) {
        return system(fd, path, flags, mode);
    }
};

template <>
struct system_call<creat> : system_call_real<creat> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<creat64> : system_call_real<creat64> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<fopen> : system_call_real<fopen> {
    PITO_RETURN(fopen) operator()(const char *path, const char *mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<fopen64> : system_call_real<fopen64> {
    PITO_RETURN(fopen64) operator()(const char *path, const char *mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<lchown> : system_call_real<lchown> {
    PITO_RETURN(lchown) operator()(const char *path, uid_t uid, gid_t gid) {
        return system(path, uid, gid);
    }
};

template <>
struct system_call<link> : sandbox_call<link, 1> {};

template <>
struct system_call<linkat> : sandbox_fd_call<linkat, 2, 3> {};

template <>
struct system_call<mkdir> : sandbox_call<mkdir> {};

template <>
struct system_call<mkdirat> : sandbox_fd_call<mkdirat, 0, 1> {};

template <>
struct system_call<mknod> : sandbox_call<mknod> {};

template <>
struct system_call<mknodat> : sandbox_fd_call<mknodat, 0, 1> {};

template <>
struct system_call<mkfifo> : sandbox_call<mkfifo> {};

template <>
struct system_call<mkfifoat> : sandbox_fd_call<mkfifoat, 0, 1> {};

template <>
struct system_call<rename> : system_call_real<rename> {
    PITO_RETURN(rename) operator()(const char *oldpath, const char *newpath) {
        return system(oldpath, newpath);
    }
};

template <>
struct system_call<renameat> : system_call_real<renameat> {
    PITO_RETURN(renameat) operator()(int olddirfd, const char *oldpath,
                                     int newdirfd, const char *newpath) {
        return system(olddirfd, oldpath, newdirfd, newpath);
    }
};

template <>
struct system_call<rmdir> : sandbox_call<rmdir> {};

template <>
struct system_call<symlink> : sandbox_call<symlink, 1> {};

template <>
struct system_call<symlinkat> : sandbox_fd_call<symlinkat, 1, 2> {};

template <>
struct system_call<truncate> : sandbox_call<truncate> {};

template <>
struct system_call<truncate64> : sandbox_call<truncate64> {};


template <>
struct system_call<unlink> : sandbox_call<unlink> {};

template <>
struct system_call<unlinkat> : sandbox_fd_call<unlinkat, 0, 1> {};

template <>
struct system_call<utime> : sandbox_call<utime> {};

template <>
struct system_call<utimes> : sandbox_call<utimes> {};

template <>
struct system_call<utimensat> : sandbox_fd_call<utimensat, 0, 1> {};

template <>
struct system_call<futimesat> : sandbox_fd_call<futimesat, 0, 1> {};

template <>
struct system_call<lutimes> : system_call_real<lutimes> {
    PITO_RETURN(lutimes) operator()(const char *path, const struct timeval time[2]) {
        return system(path, time);
    }
};

} }

#endif
