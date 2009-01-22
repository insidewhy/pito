#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;

    printf("*** fork\n");
    if (! fork()) {
        char* args[] = { "/bin/touch", "/tmp/cock", 0 };
        printf("*** execv\n");
        execv("/bin/touch", args);
    }
    wait(&status);
    printf("*** system\n");
    system("/bin/touch /tmp/cock");

    printf("*** execl\n");
    execl("/bin/touch", "/bin/touch", "/tmp/cock", 0);
}
