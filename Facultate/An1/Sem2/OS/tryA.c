#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char** argv){

    mkfifo("./a2b", 0600);
    mkfifo("./b2a", 0600);
    int fd_a2b = open("./a2b", O_WRONLY);
    int fd_b2a = open("./b2a", O_RDONLY);
    
    int size = 0;
    for(int i=1;i<argc;i++){
        int len=strlen(argv[i]);
        size += len;
    }
    size+=1;
    char *rez = malloc((sizeof(char)*size+1));
    rez[0]=0;

    for(int i=1;i<argc;i++){
        int len = strlen(argv[i]);
        write(fd_a2b, &len, sizeof(int));
        write(fd_a2b, argv[i], (sizeof(char)*len+1));
        
        char *temp = malloc(sizeof(char)*len+1);
    
        read(fd_b2a, temp, (sizeof(char)*len+1));

        strcat(rez, temp);
        free(temp);
    }
    
    int stop = -1;
    write(fd_a2b, &stop, sizeof(int));
    
    printf("REZ: %s\n", rez);
    
    free(rez);
    close(fd_a2b);
    close(fd_b2a);
    unlink("./a2b");
    unlink("./b2a");
    return 0;
}
