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
struct system_call<chmod> : sandbox_call<chmod> {
    PITO_RETURN(chmod) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<fchmod> : sandbox_call<fchmod> {
    PITO_RETURN(fchmod) operator()(int fd, mode_t mode) {
        return system(fd, mode);
    }
};

template <>
struct system_call<fchmodat> : sandbox_call<fchmodat> {
    PITO_RETURN(fchmodat) operator()(int arg1, const char *arg2, mode_t arg3, int arg4) {
        return system(arg1, arg2, arg3, arg4);
    }
};

template <>
struct system_call<chown> : sandbox_call<chown> {
    PITO_RETURN(chown) operator()(const char *path, uid_t uid, gid_t gid) {
        return system(path, uid, gid);
    }
};

template <>
struct system_call<fchown> : sandbox_call<fchown> {
    PITO_RETURN(fchown) operator()(int fd, uid_t uid, gid_t gid) {
        return system(fd, uid, gid);
    }
};

template <>
struct system_call<fchownat> : sandbox_call<fchownat> {
    PITO_RETURN(fchownat) operator()(int fd, const char *path, uid_t uid, gid_t gid, int flags) {
        return system(fd, path, uid, gid, flags);
    }
};

template <>
struct system_call<open> : sandbox_call_open<open> {};

template <>
struct system_call<open64> : sandbox_call_open<open64> {};

template <>
struct system_call<openat> : sandbox_call<openat> {
    PITO_RETURN(openat) operator()(int fd, const char *path, int flags) {
        return system(fd, path, flags);
    }

    PITO_RETURN(openat) operator()(int fd, const char *path, int flags, int mode) {
        return system(fd, path, flags, mode);
    }
};

template <>
struct system_call<openat64> : sandbox_call<openat64> {
    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags) {
        return system(fd, path, flags);
    }

    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags, int mode) {
        return system(fd, path, flags, mode);
    }
};

template <>
struct system_call<creat> : sandbox_call<creat> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<creat64> : sandbox_call<creat64> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<fopen> : sandbox_call<fopen> {
    PITO_RETURN(fopen) operator()(const char *path, const char *mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<fopen64> : sandbox_call<fopen64> {
    PITO_RETURN(fopen64) operator()(const char *path, const char *mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<lchown> : sandbox_call<lchown> {
    PITO_RETURN(lchown) operator()(const char *path, uid_t uid, gid_t gid) {
        return system(path, uid, gid);
    }
};

template <>
struct system_call<link> : sandbox_call<link> {
    PITO_RETURN(link) operator()(const char *oldpath, const char *newpath) {
        return system(oldpath, newpath);
    }
};

template <>
struct system_call<linkat> : sandbox_call<linkat> {
    PITO_RETURN(linkat) operator()(int olddirfd,
                                   const char *oldpath,
                                   int newdirfd,
                                   const char *newpath,
                                   int flags)
    {
        return system(olddirfd, oldpath, newdirfd, newpath, flags);
    }
};

template <>
struct system_call<mkdir> : sandbox_call<mkdir> {
    PITO_RETURN(mkdir) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<mkdirat> : sandbox_call<mkdirat> {
    PITO_RETURN(mkdirat) operator()(int fd, const char *path, mode_t mode) {
        return system(fd, path, mode);
    }
};

template <>
struct system_call<opendir> : sandbox_call<opendir> {
    PITO_RETURN(opendir) operator()(const char *path) {
        return system(path);
    }
};

template <>
struct system_call<readdir> : sandbox_call<readdir> {
    PITO_RETURN(readdir) operator()(DIR *dir) {
        return system(dir);
    }
};

template <>
struct system_call<mknod> : sandbox_call<mknod> {
    PITO_RETURN(mknod) operator()(const char *path, mode_t mode, dev_t dev) {
        return system(path, mode, dev);
    }
};

template <>
struct system_call<mknodat> : sandbox_call<mknodat> {
    PITO_RETURN(mknodat) operator()(int fd, const char *path, mode_t mode, dev_t dev) {
        return system(fd, path, mode, dev);
    }
};

template <>
struct system_call<mkfifo> : sandbox_call<mkfifo> {
    PITO_RETURN(mkfifo) operator()(const char *path, mode_t mode) {
        return system(path, mode);
    }
};

template <>
struct system_call<mkfifoat> : sandbox_call<mkfifoat> {
    PITO_RETURN(mkfifoat) operator()(int fd, const char *path, mode_t mode) {
        return system(fd, path, mode);
    }
};

template <>
struct system_call<access> : sandbox_call<access> {
    PITO_RETURN(access) operator()(const char *path, int amode) {
        return system(path, amode);
    }
};

template <>
struct system_call<faccessat> : sandbox_call<faccessat> {
    PITO_RETURN(faccessat) operator()(int fd, const char *path,
                                      int mode, int flags)
    {
        return system(fd, path, mode, flags);
    }
};

template <>
struct system_call<rename> : sandbox_call<rename> {
    PITO_RETURN(rename) operator()(const char *oldpath, const char *newpath) {
        return system(oldpath, newpath);
    }
};

template <>
struct system_call<renameat> : sandbox_call<renameat> {
    PITO_RETURN(renameat) operator()(int olddirfd, const char *oldpath,
                                     int newdirfd, const char *newpath) {
        return system(olddirfd, oldpath, newdirfd, newpath);
    }
};

template <>
struct system_call<rmdir> : sandbox_call<rmdir> {
    PITO_RETURN(rmdir) operator()(const char *path) {
        return system(path);
    }
};

template <>
struct system_call<symlink> : sandbox_call<symlink> {
    PITO_RETURN(symlink) operator()(const char *entry, const char *path) {
        return system(entry, path);
    }
};

template <>
struct system_call<symlinkat> : sandbox_call<symlinkat> {
    PITO_RETURN(symlinkat) operator()(const char *oldpath,
                                      int newdirfd, const char *newpath) {
        return system(oldpath, newdirfd, newpath);
    }
};

template <>
struct system_call<truncate> : sandbox_call<truncate> {
    PITO_RETURN(truncate) operator()(const char *path, off_t length) {
        return system(path, length);
    }
};

template <>
struct system_call<truncate64> : sandbox_call<truncate64> {
    PITO_RETURN(truncate64) operator()(const char *path, PITO_OFF64_TYPE length) {
        return system(path, length);
    }
};


template <>
struct system_call<unlink> : sandbox_call<unlink> {
    PITO_RETURN(unlink) operator()(const char *path) {
        return system(path);
    }
};

template <>
struct system_call<unlinkat> : sandbox_call<unlinkat> {
    PITO_RETURN(unlinkat) operator()(int fd, const char *path, int flags) {
        return system(fd, path, flags);
    }
};

template <>
struct system_call<utime> : sandbox_call<utime> {
    PITO_RETURN(utime) operator()(const char *path, const struct utimbuf *time) {
        return system(path, time);
    }
};

template <>
struct system_call<utimes> : sandbox_call<utimes> {
    PITO_RETURN(utimes) operator()(const char *path, const struct timeval times[2]) {
        return system(path, times);
    }
};

template <>
struct system_call<utimensat> : sandbox_call<utimensat> {
    PITO_RETURN(utimensat) operator()(
        int fd, const char *path, const struct timespec time[2], int flags)
    {
        return system(fd, path, time, flags);
    }
};

template <>
struct system_call<futimesat> : sandbox_call<futimesat> {
    PITO_RETURN(futimesat) operator()(
        int fd, const char *path, const struct timeval time[2])
    {
        return system(fd, path, time);
    }
};

template <>
struct system_call<lutimes> : sandbox_call<lutimes> {
    PITO_RETURN(lutimes) operator()(const char *path, const struct timeval time[2]) {
        return system(path, time);
    }
};


} }

#endif
