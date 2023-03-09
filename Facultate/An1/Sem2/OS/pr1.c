#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    
    int n=atoi(argv[1]);

    int i;
    for(i=0;i<n;i++){
        int f=fork();
        if(f==0){
            printf("C: %d, P: %d\n",getpid(),getppid());
            exit(0);
        }
        else{
            printf("P: %d, Parent: %d\n",f,getpid());
        }
    }

    for(i=0;i<n;i++){
        wait(0);
    }
    
    return 0;
}
