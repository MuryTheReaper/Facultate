#include "common.h"

int main(int argc, char *argv[]){
    
    mkfifo(a2b, 0600);
    mkfifo(b2a, 0600);
    
    int  fd_a2b = open(a2b, O_WRONLY);
    int fd_b2a = open(b2a, O_RDONLY);

    char *x = "Hello";

    int n = strlen(x);

    write(fd_a2b, &n, sizeof(int));
    write(fd_a2b, x, sizeof(char)*n);

    int rez;

    read(fd_b2a, &rez, sizeof(int));

    printf("Len: %d\n",rez);

    close(fd_a2b);
    close(fd_b2a);
    unlink(a2b);
    unlink(b2a);

    return 0;
}
