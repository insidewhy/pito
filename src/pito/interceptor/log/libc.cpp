////////////////////////////////////////////////////////////////////////////////
// security intercepts
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags);
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags);
// see what to do about optional argument
int open(const char *pathname, int flags, mode_t mode);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
FILE *fopen(const char *path, const char *mode);
int lchown(const char *path, uid_t owner, gid_t group);
int link(const char *oldpath, const char *newpath);
int linkat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath, int flags);
int mkdir(const char *pathname, mode_t mode);
int mkdirat(int dirfd, const char *pathname, mode_t mode);
DIR *opendir(const char *name);
int mknod(const char *pathname, mode_t mode, dev_t dev);
int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev);
// function todo: __xmknod
int mkfifo(const char *pathname, mode_t mode);
int mkfifoat(int dirfd, const char *pathname, mode_t mode);
int access(const char *pathname, int mode);
int faccessat(int dirfd, const char *pathname, int mode, int flags);
int rename(const char *oldpath, const char *newpath);
int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath);
int rmdir(const char *pathname);
int symlink(const char *oldpath, const char *newpath);
int symlinkat(const char *oldpath, int newdirfd, const char *newpath);
int truncate(const char *path, off_t length);
int unlink(const char *pathname);
int unlinkat(int dirfd, const char *pathname, int flags);
char *getcwd(char *buf, size_t size);
int open64(const char *pathname, int flags, mode_t mode);
int openat64(int dirfd, const char *pathname, int flags, mode_t mode);
int creat64(const char *pathname, mode_t mode);
FILE *fopen64(const char *path, const char *mode);
int truncate64(const char *path, off_t length);
int execve(const char *filename, char *const argv[], char *const envp[]);
int utime(const char *filename, const struct utimbuf *times);
int utimes(const char *filename, const struct timeval times[2]);
int utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags);
int futimesat(int dirfd, const char *pathname, const struct timeval times[2]); 
int lutimes(const char *filename, const struct timeval tv[2]);
uid_t getuid(void);
