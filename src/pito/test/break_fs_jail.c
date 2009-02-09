#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (-1 != open("/tmp/pito-open", O_RDWR | O_CREAT, S_IWUSR))
        return 1;

    if (-1 != creat("/tmp/pito-creat", S_IWUSR))
        return 1;
}
