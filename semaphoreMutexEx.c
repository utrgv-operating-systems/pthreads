#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static sem_t sem;
static int shared_int = 0;

void* threadFunction(void* arg)
{
    for(int i = 0; i < 20; i++){
	    //wait
	    //sem_wait(&sem);
	    pthread_mutex_lock(&mutex);
	    printf("\nEntered..\n");
  
	    //critical section
	    //sleep(4);
	    int j = shared_int;
	    sched_yield();
	    shared_int = ++j;
      
	    //signal
	    printf("\nJust Exiting...\n");
	    pthread_mutex_unlock(&mutex);
	    //sem_post(&sem);

    }
}


int main(int argc, char *argv[]){
	pthread_t ThreadA; 
	pthread_t ThreadB;
	sem_init(&sem, 0, 1);

	pthread_create(&ThreadA, NULL, threadFunction, NULL);
	pthread_create(&ThreadB, NULL, threadFunction, NULL);

	pthread_join(ThreadB, NULL);
	pthread_join(ThreadA, NULL);

	printf("%d\n", shared_int);

	sem_destroy(&sem);
	pthread_mutex_destroy(&mutex);

	return 0;
}
