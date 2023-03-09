#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int *array;
int N;
sem_t sem;


void *f(void *arg){
    
    int id= *(int*) arg;
    
    sem_wait(&sem);

    array[id]=id;//random()%11+1;
    array[N+id]=N+id;//random()%11+1;

    int suma=0;
    
    //sem_wait(&sem);
    for(int i=0;i<N*2;i++){
        suma+=array[i];
        printf("%d ", array[i]);
    }
    printf("\n %d\n", suma);
    sem_post(&sem);

    //printf("%d\n", id);
    
    free(arg);
    return NULL;
}


int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("Error\n");
        exit(1);
    }
    N=atoi(argv[1]);
    array=malloc((N*2)*sizeof(int));
    
    for(int i=0;i<N*2;i++)
        array[i]=0;
    
    pthread_t *T = malloc(sizeof(pthread_t)*N);
    sem_init(&sem, 0, 3);

    for(int i=0;i<N;i++){
        int *id;
        id=malloc(sizeof(int));
        *id=i;

        pthread_create(&T[i], NULL, f, (void*)id);
        
    }

    for(int i=0;i<N;i++){
        pthread_join(T[i], NULL);
    }

    free(T);
    free(array);
    sem_destroy(&sem);

    return 0;
}
