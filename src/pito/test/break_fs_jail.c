#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    fprintf(stderr, "*************** filesystem jail break test ***************\n");

    int ret = 0;
    if (-1 != open("/tmp/pito-open", O_RDWR | O_CREAT, S_IWUSR)) {
        fprintf(stderr, "open succeeded\n");
        ret = 1;
    }

    if (-1 != creat("/tmp/pito-creat", S_IWUSR)) {
        fprintf(stderr, "creat succeeded\n");
        ret = 1;
    }

    fprintf(stderr, "\n");
    return ret;
}
