#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_t threads[10];
pthread_mutex_t mut;
pthread_rwlock_t rw_lock;
int threadVar = 0;
int index = 0;

int nsleep(int miliseconds){
   struct timespec req= {
       (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */ 
       (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */ 
   };
	
   return nanosleep(&req , NULL);
}

void * threadFunction(void * var) {
    int *y = (int *)var;
    
	while(1){
		nsleep(2000);
		pthread_rwlock_rdlock(&rw_lock);
		if(index % 2 == 0){
	    	pthread_mutex_lock(&mut);
    		printf("Thread nr : %d\n", *y);
			++threadVar;
	    	pthread_mutex_unlock(&mut);
		}
		pthread_rwlock_unlock(&rw_lock);
	}

	
	
   return NULL;
}

void * updateThreads(void * var){
	int *y = (int *)var;
	while(1){
		//pthread_rwlock_rdlock(&rw_lock);
		//printf("Before nsleep\n");
		nsleep( 2000 );
		//printf("After nsleep\n");
		pthread_rwlock_wrlock(&rw_lock);
		printf("Thread %d locks write to index.\n", *y);
		printf("Current threadVar=%d\n", threadVar);
		++index;
		pthread_rwlock_unlock(&rw_lock);
	}
}

int main() {

    pthread_mutex_init(&mut, NULL);
    pthread_rwlock_init(&rw_lock, NULL);
    int i;
    for(i = 0; i <  10; i++) {
    	int *c = malloc(sizeof(int));
    	*c = i;
   	 	pthread_create(&threads[i], NULL, threadFunction, c);
   
    }

	pthread_t t1, t2;
	int var1 = 11, var2 = 22;
	pthread_create(&t1, NULL, updateThreads, &var1);
	pthread_create(&t2, NULL, updateThreads, &var2);
	
    for (i = 0; i <  10; i++) {
   	 	pthread_join(threads[i], NULL);
    }
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
   	printf("%d\n", threadVar);
   	pthread_mutex_destroy(&mut);
    pthread_rwlock_destroy(&rw_lock);
return 1;
}

