#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_t threads[10];
pthread_mutex_t mut;
pthread_rwlock_t rwMut;

int x=0;
int index=0;

void * threadFunction(void * var) {
    int y=*((int*)var);
    
    pthread_rwlock_rdlock(&rwMut);
    if(index%2==0){
        pthread_mutex_lock(&mut);
        x++;
        pthread_mutex_unlock(&mut);
    }
    pthread_rwlock_rdunlock(&rwMut);

    printf("Thread: %d ->%d\n",y,x);
    free(var);
    return NULL;

}

void * threadUpdate(void *var){
    int y=*((int*)var);
    sleep(3);

    pthread_rwlock_wrlock(&rwMut);
        index++;
    pthread_rwlock_wrunlock(&rwMut);

    return NULL;
}

int main() {

    pthread_mutex_init(&mut, NULL);
    pthread_rwlock_init(&rwMut,NULL);
    int i, n=10;
    for(i = 0; i <  n; i++) { 
        int *c=malloc(sizeof(int));
        *c=i;
        pthread_create(&threads[i], NULL, threadFunction, c);
    }
    
    pthread_t t1,t2;
    pthread_create(&t1,NULL,threadUpdate,1);
    pthread_create(&t2,NULL,threadUpdate,2);

    for (i = 0; i <  n; i++) {
        pthread_join(threads[i], NULL);

    }
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mut);
    pthread_rwlock_destroy(&rwMut);
    
    return 0;
}
