#ifndef PITO_SANDBOX_HELPER_HPP
#define PITO_SANDBOX_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>

#include <chilon/singleton.hpp>
#include <chilon/iterator_range.hpp>

#include <vector>

#define PITO_SANDBOX_DEFAULT  "PITO_SANDBOX_DEFAULT"
#define PITO_SANDBOX_PATHS    "PITO_SANDBOX_PATHS"

namespace pito { namespace sandbox {

enum write_mode {
    WRITE_MODE_PRETEND,
    WRITE_MODE_WHITELIST,
    WRITE_MODE_BLACKLIST
};

struct context {
    context();

    std::vector<range> paths;
    write_mode         mode;
};

extern context& ctxt;

using namespace system_call_tag;

template <class Tag>
struct system_call;

template <class Tag>
struct system_call : detail::system_call<Tag> {
    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
        return PITO_SUPER(Tag, args...);
    }
};

template <>
struct system_call<chmod> : detail::system_call<chmod> {
    PITO_RETURN(chmod) operator()(const char *path, mode_t mode) {
        return PITO_SUPER(chmod, path, mode);
    }
};

template <>
struct system_call<fchmod> : detail::system_call<fchmod> {
    PITO_RETURN(fchmod) operator()(int fd, mode_t mode) {
        return PITO_SUPER(fchmod, fd, mode);
    }
};

template <>
struct system_call<fchmodat> : detail::system_call<fchmodat> {
    PITO_RETURN(fchmodat) operator()(int arg1, const char *arg2, mode_t arg3, int arg4) {
        return PITO_SUPER(fchmodat, arg1, arg2, arg3, arg4);
    }
};

template <>
struct system_call<chown> : detail::system_call<chown> {
    PITO_RETURN(chown) operator()(const char *path, uid_t uid, gid_t gid) {
        return PITO_SUPER(chown, path, uid, gid);
    }
};

template <>
struct system_call<fchown> : detail::system_call<fchown> {
    PITO_RETURN(fchown) operator()(int fd, uid_t uid, gid_t gid) {
        return PITO_SUPER(fchown, fd, uid, gid);
    }
};

template <>
struct system_call<fchownat> : detail::system_call<fchownat> {
    PITO_RETURN(fchownat) operator()(int fd, const char *path, uid_t uid, gid_t gid, int flags) {
        return PITO_SUPER(fchownat, fd, path, uid, gid, flags);
    }
};

template <>
struct system_call<open> : detail::system_call<open> {
    PITO_RETURN(open) operator()(const char *path, int flag) {
        return PITO_SUPER(open, path, flag);
    }

    PITO_RETURN(open) operator()(const char *path, int flag, int mode) {
        return PITO_SUPER(open, path, flag, mode);
    }
};

template <>
struct system_call<open64> : detail::system_call<open64> {
    PITO_RETURN(open64) operator()(const char *path, int flag) {
        return PITO_SUPER(open64, path, flag);
    }

    PITO_RETURN(open64) operator()(const char *path, int flag, int mode) {
        return PITO_SUPER(open64, path, flag, mode);
    }
};

template <>
struct system_call<openat> : detail::system_call<openat> {
    PITO_RETURN(openat) operator()(int fd, const char *path, int flags) {
        return PITO_SUPER(openat, fd, path, flags);
    }

    PITO_RETURN(openat) operator()(int fd, const char *path, int flags, int mode) {
        return PITO_SUPER(openat, fd, path, flags, mode);
    }
};

template <>
struct system_call<openat64> : detail::system_call<openat64> {
    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags) {
        return PITO_SUPER(openat64, fd, path, flags);
    }

    PITO_RETURN(openat64) operator()(int fd, const char *path, int flags, int mode) {
        return PITO_SUPER(openat64, fd, path, flags, mode);
    }
};

template <>
struct system_call<creat> : detail::system_call<creat> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return PITO_SUPER(creat, path, mode);
    }
};

template <>
struct system_call<creat64> : detail::system_call<creat64> {
    PITO_RETURN(creat) operator()(const char *path, mode_t mode) {
        return PITO_SUPER(creat64, path, mode);
    }
};

template <>
struct system_call<fopen> : detail::system_call<fopen> {
    PITO_RETURN(fopen) operator()(const char *path, const char *mode) {
        return PITO_SUPER(fopen, path, mode);
    }
};

template <>
struct system_call<fopen64> : detail::system_call<fopen64> {
    PITO_RETURN(fopen64) operator()(const char *path, const char *mode) {
        return PITO_SUPER(fopen64, path, mode);
    }
};

template <>
struct system_call<lchown> : detail::system_call<lchown> {
    PITO_RETURN(lchown) operator()(const char *path, uid_t uid, gid_t gid) {
        return PITO_SUPER(lchown, path, uid, gid);
    }
};

template <>
struct system_call<link> : detail::system_call<link> {
    PITO_RETURN(link) operator()(const char *oldpath, const char *newpath) {
        return PITO_SUPER(link, oldpath, newpath);
    }
};

template <>
struct system_call<linkat> : detail::system_call<linkat> {
    PITO_RETURN(linkat) operator()(int olddirfd,
                                   const char *oldpath,
                                   int newdirfd,
                                   const char *newpath,
                                   int flags)
    {
        return PITO_SUPER(linkat, olddirfd, oldpath, newdirfd, newpath, flags);
    }
};

template <>
struct system_call<mkdir> : detail::system_call<mkdir> {
    PITO_RETURN(mkdir) operator()(const char *path, mode_t mode) {
        return PITO_SUPER(mkdir, path, mode);
    }
};

template <>
struct system_call<mkdirat> : detail::system_call<mkdirat> {
    PITO_RETURN(mkdirat) operator()(int fd, const char *path, mode_t mode) {
        return PITO_SUPER(mkdirat, fd, path, mode);
    }
};

template <>
struct system_call<opendir> : detail::system_call<opendir> {
    PITO_RETURN(opendir) operator()(const char *path) {
        return PITO_SUPER(opendir, path);
    }
};

template <>
struct system_call<readdir> : detail::system_call<readdir> {
    PITO_RETURN(readdir) operator()(DIR *dir) {
        return PITO_SUPER(readdir, dir);
    }
};

template <>
struct system_call<mknod> : detail::system_call<mknod> {
    PITO_RETURN(mknod) operator()(const char *path, mode_t mode, dev_t dev) {
        return PITO_SUPER(mknod, path, mode, dev);
    }
};

template <>
struct system_call<mknodat> : detail::system_call<mknodat> {
    PITO_RETURN(mknodat) operator()(int fd, const char *path, mode_t mode, dev_t dev) {
        return PITO_SUPER(mknodat, fd, path, mode, dev);
    }
};

template <>
struct system_call<mkfifo> : detail::system_call<mkfifo> {
    PITO_RETURN(mkfifo) operator()(const char *path, mode_t mode) {
        return PITO_SUPER(mkfifo, path, mode);
    }
};

template <>
struct system_call<mkfifoat> : detail::system_call<mkfifoat> {
    PITO_RETURN(mkfifoat) operator()(int fd, const char *path, mode_t mode) {
        return PITO_SUPER(mkfifoat, fd, path, mode);
    }
};

template <>
struct system_call<access> : detail::system_call<access> {
    PITO_RETURN(access) operator()(const char *path, int amode) {
        return PITO_SUPER(access, path, amode);
    }
};

template <>
struct system_call<faccessat> : detail::system_call<faccessat> {
    PITO_RETURN(faccessat) operator()(int fd, const char *path,
                                      int mode, int flags)
    {
        return PITO_SUPER(faccessat, fd, path, mode, flags);
    }
};

template <>
struct system_call<rename> : detail::system_call<rename> {
    PITO_RETURN(rename) operator()(const char *oldpath, const char *newpath) {
        return PITO_SUPER(rename, oldpath, newpath);
    }
};

template <>
struct system_call<renameat> : detail::system_call<renameat> {
    PITO_RETURN(renameat) operator()(int olddirfd, const char *oldpath,
                                     int newdirfd, const char *newpath) {
        return PITO_SUPER(renameat,
                olddirfd, oldpath, newdirfd, newpath);
    }
};

template <>
struct system_call<rmdir> : detail::system_call<rmdir> {
    PITO_RETURN(rmdir) operator()(const char *path) {
        return PITO_SUPER(rmdir, path);
    }
};

template <>
struct system_call<symlink> : detail::system_call<symlink> {
    PITO_RETURN(symlink) operator()(const char *entry, const char *path) {
        return PITO_SUPER(symlink, entry, path);
    }
};

template <>
struct system_call<symlinkat> : detail::system_call<symlinkat> {
    PITO_RETURN(symlinkat) operator()(const char *oldpath,
                                      int newdirfd, const char *newpath) {
        return PITO_SUPER(symlinkat, oldpath, newdirfd, newpath);
    }
};

template <>
struct system_call<truncate> : detail::system_call<truncate> {
    PITO_RETURN(truncate) operator()(const char *path, off_t length) {
        return PITO_SUPER(truncate, path, length);
    }
};

template <>
struct system_call<truncate64> : detail::system_call<truncate64> {
    PITO_RETURN(truncate64) operator()(const char *path, PITO_OFF64_TYPE length) {
        return PITO_SUPER(truncate64, path, length);
    }
};


template <>
struct system_call<unlink> : detail::system_call<unlink> {
    PITO_RETURN(unlink) operator()(const char *path) {
        return PITO_SUPER(unlink, path);
    }
};

template <>
struct system_call<unlinkat> : detail::system_call<unlinkat> {
    PITO_RETURN(unlinkat) operator()(int fd, const char *path, int flags) {
        return PITO_SUPER(unlinkat, fd, path, flags);
    }
};

template <>
struct system_call<utime> : detail::system_call<utime> {
    PITO_RETURN(utime) operator()(const char *path, const struct utimbuf *time) {
        return PITO_SUPER(utime, path, time);
    }
};

template <>
struct system_call<utimes> : detail::system_call<utimes> {
    PITO_RETURN(utimes) operator()(const char *path, const struct timeval times[2]) {
        return PITO_SUPER(utimes, path, times);
    }
};

template <>
struct system_call<utimensat> : detail::system_call<utimensat> {
    PITO_RETURN(utimensat) operator()(
        int fd, const char *path, const struct timespec time[2], int flags)
    {
        return PITO_SUPER(utimensat, fd, path, time, flags);
    }
};

template <>
struct system_call<futimesat> : detail::system_call<futimesat> {
    PITO_RETURN(futimesat) operator()(
        int fd, const char *path, const struct timeval time[2])
    {
        return PITO_SUPER(futimesat, fd, path, time);
    }
};

template <>
struct system_call<lutimes> : detail::system_call<lutimes> {
    PITO_RETURN(lutimes) operator()(const char *path, const struct timeval time[2]) {
        return PITO_SUPER(lutimes, path, time);
    }
};

} }

#endif
