// include this after #defining PITO_SYSTEM_CALL_BASE

#include <pito/interceptor/lib/c.hpp>

#include <iostream>

extern "C" {

using namespace pito::interceptor;

////////////////////////////////////////////////////////////////////////////////
// security intercepts
int chmod(const char *path, mode_t mode) {
    return PITO_SUPER(chmod)(path, mode);
}

int fchmod(int fd, mode_t mode) {
    return PITO_SUPER(fchmod)(fd, mode);
}

int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags) {
    return PITO_SUPER(fchmodat)(dirfd, pathname, mode, flags);
}

int chown(const char *path, uid_t owner, gid_t group) {
    return PITO_SUPER(chown)(path, owner, group);
}

int fchown(int fd, uid_t owner, gid_t group) {
    return PITO_SUPER(fchown)(fd, owner, group);
}

int fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags) {
    return PITO_SUPER(fchownat)(dirfd, pathname, owner, group, flags);
}

// see what to do about optional argument
int open(const char *pathname, int flags, mode_t mode) {
    return PITO_SUPER(open)(pathname, flags, mode);
}

int openat(int dirfd, const char *pathname, int flags, mode_t mode) {
    return PITO_SUPER(openat)(dirfd, pathname, flags, mode);
}

int creat(const char *pathname, mode_t mode) {
    return PITO_SUPER(creat)(pathname, mode);
}

FILE *fopen(const char *path, const char *mode) {
    return PITO_SUPER(fopen)(path, mode);
}

int lchown(const char *path, uid_t owner, gid_t group) {
    return PITO_SUPER(lchown)(path, owner, group);
}

int link(const char *oldpath, const char *newpath) {
    return PITO_SUPER(link)(oldpath, newpath);
}

int linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags) {
    return PITO_SUPER(linkat)(olddirfd, oldpath, newdirfd, newpath, flags);
}

int mkdir(const char *pathname, mode_t mode) {
    return PITO_SUPER(mkdir)(pathname, mode);
}

int mkdirat(int dirfd, const char *pathname, mode_t mode) {
    return PITO_SUPER(mkdirat)(dirfd, pathname, mode);
}

DIR *opendir(const char *name) {
    return PITO_SUPER(opendir)(name);
}

int mknod(const char *pathname, mode_t mode, dev_t dev) {
    return PITO_SUPER(mknod)(pathname, mode, dev);
}

int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev) {
    return PITO_SUPER(mknodat)(dirfd, pathname, mode, dev);
}

// function todo: __xmknod
int mkfifo(const char *pathname, mode_t mode) {
    return PITO_SUPER(mkfifo)(pathname, mode);
}

int mkfifoat(int dirfd, const char *pathname, mode_t mode) {
    return PITO_SUPER(mkfifoat)(dirfd, pathname, mode);
}

int access(const char *pathname, int mode) {
    return PITO_SUPER(access)(pathname, mode);
}

int faccessat(int dirfd, const char *pathname, int mode, int flags) {
    return PITO_SUPER(faccessat)(dirfd, pathname, mode, flags);
}

int rename(const char *oldpath, const char *newpath) {
    return PITO_SUPER(rename)(oldpath, newpath);
}

int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) {
    return PITO_SUPER(renameat)(olddirfd, oldpath, newdirfd, newpath);
}

int rmdir(const char *pathname) {
    return PITO_SUPER(rmdir)(pathname);
}

int symlink(const char *oldpath, const char *newpath) {
    return PITO_SUPER(symlink)(oldpath, newpath);
}

int symlinkat(const char *oldpath, int newdirfd, const char *newpath) {
    return PITO_SUPER(symlinkat)(oldpath, newdirfd, newpath);
}

int truncate(const char *path, off_t length) {
    return PITO_SUPER(truncate)(path, length);
}

int unlink(const char *pathname) {
    return PITO_SUPER(unlink)(pathname);
}

int unlinkat(int dirfd, const char *pathname, int flags) {
    return PITO_SUPER(unlinkat)(dirfd, pathname, flags);
}

char *getcwd(char *buf, size_t size) {
    return PITO_SUPER(getcwd)(buf, size);
}

int open64(const char *pathname, int flags, mode_t mode) {
    return PITO_SUPER(open)(pathname, flags, mode);
}

int openat64(int dirfd, const char *pathname, int flags, mode_t mode) {
    return PITO_SUPER(openat64)(dirfd, pathname, flags, mode);
}

int creat64(const char *pathname, mode_t mode) {
    return PITO_SUPER(creat64)(pathname, mode);
}

FILE *fopen64(const char *path, const char *mode) {
    return PITO_SUPER(fopen64)(path, mode);
}

int truncate64(const char *path, __off64_t length) {
    return PITO_SUPER(truncate64)(path, length);
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
    return PITO_SUPER(execve)(filename, argv, envp);
}

int execv(const char *filename, char *const argv[]) {
    return PITO_SUPER(execv)(filename, argv);
}

int execvp(const char *filename, char *const argv[]) {
    return PITO_SUPER(execvp)(filename, argv);
}

int utime(const char *filename, const struct utimbuf *times) {
    return PITO_SUPER(utime)(filename, times);
}

int utimes(const char *filename, const struct timeval times[2]) {
    return PITO_SUPER(utimes)(filename, times);
}

int utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags) {
    return PITO_SUPER(utimensat)(dirfd, pathname, times, flags);
}

int futimesat(int dirfd, const char *pathname, const struct timeval times[2]) {
    return PITO_SUPER(futimesat)(dirfd, pathname, times); 
}

int lutimes(const char *filename, const struct timeval tv[2]) {
    return PITO_SUPER(lutimes)(filename, tv);
}

}

