#include <pito/config.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int ret = 0;

void nonzero(char const *cmd, int const status) {
    if (status == 0) {
        fprintf(stderr, "!!! %s :(\n", cmd);
        ret = 1;
    }
    else printf("%s :)\n", cmd);
}

void zero(char const *cmd, int const status) {
    if (status != 0) {
        fprintf(stderr, "!!! %s :(\n", cmd);
        ret = 1;
    }
    else printf("%s :)\n", cmd);
}

void not_minus1(char const *cmd, int const status) {
    if (status != -1) {
        fprintf(stderr, "!!! %s :(\n", cmd);
        ret = 1;
    }
    else printf("%s :)\n", cmd);
}

void wait_for_return(char const *cmd) {
    int status;
    wait(&status);
    nonzero(cmd, status);
}

int main(int argc, char *argv[]) {
    char * spartan_env[] = { "PUMP=DAGON", 0 };

    unsetenv(PITO_LD_PRELOAD);

    not_minus1("open", open("open", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR));

    not_minus1("creat", creat("creat", S_IWUSR));

    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        char* args[] = { "/bin/touch", "execv-touch", 0 };
        execv("/bin/touch", args);
        return 0;
    }
    wait_for_return("execv touch");

    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        char * args[] = { "/bin/touch", "execve-touch", 0 };
        execve("/bin/touch", args, spartan_env);
        return 0;
    }
    wait_for_return("execve touch");

    unsetenv(PITO_LD_PRELOAD);
    nonzero("system touch", system("/bin/touch system-touch"));

    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        execl("/bin/touch", "/bin/touch", "execl-touch1", "execl-touch2", 0);
        return 0;
    }
    wait_for_return("execl touch");

    not_minus1("symlink", symlink("file", "new-symlink"));

    int fd = open("file", O_RDONLY);
    not_minus1("fchmod", fchmod(fd, S_IRWXU));

    fd = open("dir", O_RDONLY);
    not_minus1("openat",
        openat(fd, "../bumbum", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR));

    not_minus1("unlinkat", unlinkat(fd, "../file", 0));
    close(fd);

    fd = open(".", O_RDONLY);
    not_minus1("link", link("file", "write/file_link"));
    not_minus1("linkat", linkat(fd, "file", fd, "write/file_link", 0));

    not_minus1("rename", rename("file", "write/read_file"));
    not_minus1("rename", rename("write/write_file", "write_file"));

    not_minus1("renameat", renameat(fd, "file", fd, "write/read_file"));
    not_minus1("renameat", renameat(fd, "write/write_file", fd, "write_file"));

    zero("fopen (w)", (size_t) fopen("fopen-file", "w"));
    zero("fopen (r+)", (size_t) fopen("file", "r+"));
    nonzero("fopen (r)", (size_t) fopen("file", "r"));

    return ret;
}
