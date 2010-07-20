#include <pito/config.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int ret = 0;

void check_status(char const *cmd, int const status) {
    if (status == 0) {
        fprintf(stderr, "!!! %s :(\n", cmd);
        ret = 1;
    }
    else printf("%s :)\n", cmd);
}

void check_status2(char const *cmd, int const status) {
    if (status != -1) {
        fprintf(stderr, "!!! %s :(\n", cmd);
        ret = 1;
    }
    else printf("%s :)\n", cmd);
}

void wait_for_return(char const *cmd) {
    int status;
    wait(&status);
    check_status(cmd, status);
}

int main(int argc, char *argv[]) {
    char * spartan_env[] = { "PUMP=DAGON", 0 };

    unsetenv(PITO_LD_PRELOAD);

    check_status2("open",
        open("open", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR));

    check_status2("creat",
        creat("creat", S_IWUSR));

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
    check_status("system touch",
        system("/bin/touch system-touch"));

    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        execl("/bin/touch", "/bin/touch", "execl-touch1", "execl-touch2",
                (char *)0);
        return 0;
    }
    wait_for_return("execl touch");

    symlink("existing", "symlink");

    int fd = open("existing", O_RDONLY);
    check_status("fchmod", fchmod(fd, S_IRWXU));

    fd = open(".", O_RDONLY);
    check_status("openat",
        openat(fd, "../bumbum", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR));

    return ret;
}
