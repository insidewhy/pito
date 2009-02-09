#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;
    fprintf(stderr, "*************** ldpreopen jail break test ***************\n");

    fprintf(stderr, "*** fork\n");
    if (! fork()) {
        access("/tmp/cock", R_OK);
        char* args[] = { "/bin/touch", "/tmp/cock", 0 };
        fprintf(stderr, "*** execv\n");
        execv("/bin/touch", args);
    }
    wait(&status);
    fprintf(stderr, "*** system\n");
    system("/bin/touch /tmp/cock");

    fprintf(stderr, "*** execl\n");

    if (! fork()) {
        execl("/bin/touch", "/bin/touch", "/tmp/cock", 0);
        return 0;
    }
    wait(&status);
    fprintf(stderr, "\n");
    return 0;
}
