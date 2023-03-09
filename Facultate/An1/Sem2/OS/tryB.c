#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv){
    

    printf("B starting\n");

    int fd_b2a = open("./b2a", O_WRONLY);
    int fd_a2b = open("./a2b", O_RDONLY);

    printf("B starting\n");
    while(1){
        int len;
        read(fd_a2b, &len, sizeof(int));
        if(len<0)
            break;
        printf("B: len =%d\n", len);

        char *temp = malloc(sizeof(char)*len+1);

        read(fd_a2b, temp, (sizeof(char)*len));
        temp[len]=0;
        //do stuff

        write(fd_b2a, temp, (sizeof(char)*len)); 
        free(temp);
    }


    close(fd_b2a);
    close(fd_a2b);
    
    return 0;

}
