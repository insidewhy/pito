#include <pito/config.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    fprintf(stderr, "*************** filesystem jail break test ***************\n");
    unsetenv(PITO_LD_PRELOAD);

    int ret = 0;
    if (-1 != open("/tmp/pito-open", O_RDWR | O_CREAT, S_IWUSR)) {
        fprintf(stderr, "!!! open succeeded :(\n");
        ret = 1;
    }

    if (-1 != creat("/tmp/pito-creat", S_IWUSR)) {
        fprintf(stderr, "!!! creat succeeded :(\n");
        ret = 1;
    }

    fprintf(stderr, "*** fork\n");
    int status;
    if (! fork())
        return -1 == creat("/tmp/pito-creat", S_IWUSR);

    wait(&status);
    if (status == 0) {
        fprintf(stderr, "!!! fork creat succeeded :(\n");
        ret = 1;
    }

    if (! fork()) {
        char* args[] = { "/bin/touch", "/tmp/pito-touch", 0 };
        fprintf(stderr, "*** execv\n");
        execv("/bin/touch", args);
        return 0;
    }
    wait(&status);
    if (status == 0) {
        fprintf(stderr, "!!! execv touch succeeded\n");
        ret = 1;
    }

    fprintf(stderr, "*** system\n");
    system("/bin/touch /tmp/cock");
    if (status == 0) {
        fprintf(stderr, "!!! system touch succeeded :(\n");
        ret = 1;
    }

    if (! fork()) {
        fprintf(stderr, "*** execl\n");
        execl("/bin/touch", "/bin/touch", "/tmp/pito-touch", 0);
        return 0;
    }
    wait(&status);

    if (status == 0) {
        fprintf(stderr, "!!! execl touch succeeded :(\n");
        ret = 1;
    }

    return ret;
}
