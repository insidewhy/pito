#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;

    printf("*** fork\n");
    if (! fork()) {
        char* args[] = { "/bin/false", 0 };
        printf("*** execv\n");
        execv("/bin/false", args);
    }
    wait(&status);
    printf("*** system\n");
    system("/bin/false");

    printf("*** execl\n");
    execl("/bin/ls", "-l", 0);
}
