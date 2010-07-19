#include <pito/config.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int ret = 0;

void check_status(char const *error_message, int const status) {
    if (status == 0) {
        fprintf(stderr, "!!! %s :(\n", error_message);
        ret = 1;
    }
}

void check_status2(char const *error_message, int const status) {
    if (status != -1) {
        fprintf(stderr, "!!! %s :(\n", error_message);
        ret = 1;
    }
}

void wait_for_return(char const *error_message) {
    int status;
    wait(&status);
    check_status(error_message, status);
}

int main(int argc, char *argv[]) {
    char * spartan_env[] = { "PUMP=DAGON", 0 };

    printf("*************** filesystem jail break test ***************\n");
    unsetenv(PITO_LD_PRELOAD);

    check_status2("open",
        open("open", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR));

    check_status2("creat",
        creat("creat", S_IWUSR));

    printf("*** execv\n");
    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        char* args[] = { "/bin/touch", "execv-touch", 0 };
        execv("/bin/touch", args);
        return 0;
    }
    wait_for_return("execv touch");

    printf("*** execve\n");
    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        char * args[] = { "/bin/touch", "execve-touch", 0 };
        execve("/bin/touch", args, spartan_env);
        return 0;
    }
    wait_for_return("execve touch");

    printf("*** system\n");
    unsetenv(PITO_LD_PRELOAD);
    check_status("system touch",
        system("/bin/touch system-touch"));

    printf("*** execl\n");
    if (! fork()) {
        unsetenv(PITO_LD_PRELOAD);
        execl("/bin/touch", "/bin/touch", "execl-touch1", "execl-touch2",
                (char *)0);
        return 0;
    }
    wait_for_return("execl touch");

    printf("*** symlink\n");
    symlink("existing", "symlink");

    printf("*** fchmod\n");
    int existing_fd = open("existing", O_RDONLY);
    check_status("fchmod", fchmod(existing_fd, S_IRWXU));

    return ret;
}
