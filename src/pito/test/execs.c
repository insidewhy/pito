#include <stdlib.h>

int main(int argc, char *argv[]) {
    int status;

    if (! fork()) {
        char* args[] = { "/bin/false", 0 };
        execv("/bin/false", args);
    }
    else {
        wait(&status);
        system("/bin/false");
    }
}
