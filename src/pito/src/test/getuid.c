#include <stdio.h>
#include <unistd.h>

int main() {
    printf( "user id: %d\n", getuid() );
    return 0;
}
