////////////////////////////////////////////////////////////////////////////////
// security intercepts
// function todo: chmod
// function todo: fchmodat
// function todo: chown
// function todo: fchownat

// see what to do about optional argument
int open(const char *pathname, int flags, mode_t mode) {
}

// function todo: openat
int creat(const char *pathname, mode_t mode) {
}

// function todo: fopen
// function todo: lchown
// function todo: link
// function todo: linkat
// function todo: mkdir
// function todo: mkdirat
// function todo: opendir
// function todo: mknod
// function todo: mknodat
// function todo: __xmknod
// function todo: mkfifo
// function todo: mkfifoat
// function todo: access
// function todo: faccessat
// function todo: rename
// function todo: renameat
// function todo: rmdir
// function todo: symlink
// function todo: symlinkat
// function todo: truncate
// function todo: unlink
// function todo: unlinkat
// function todo: getcwd
// function todo: open64
// function todo: openat64
// function todo: creat64
// function todo: fopen64
// function todo: truncate64
// function todo: execve
// function todo: utime
// function todo: utimes
// function todo: utimensat
// function todo: futimesat
// function todo: lutimes

////////////////////////////////////////////////////////////////////////////////
// extra intercepts
uid_t getuid(void) {
    return 0;
}

