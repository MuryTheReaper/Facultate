#include "common.h"

int main(int argc, char* argv[]){
    
    int  fd_a2b = open(a2b, O_RDONLY);
    int fd_b2a = open(b2a, O_WRONLY);


    int n;
    read(fd_a2b, &n, sizeof(int));

    char *temp = malloc(sizeof(char)*n+1);

    read(fd_a2b, temp, sizeof(char)*n);
    temp[n]=0;

    int x = strlen(temp);

    write(fd_b2a, &x, sizeof(int));
    
    close(fd_a2b);
    close(fd_b2a);

    return 0;

}
