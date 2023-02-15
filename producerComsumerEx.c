#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static sem_t full, empty;
const int BUFFER_SIZE = 10;
static int shared_buffer[10];
static int producerIndex = 0, consumerIndex = 0;

void *consumer_function(void *arg){
	while(consumerIndex < 1000){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int val = shared_buffer[consumerIndex%BUFFER_SIZE];
		printf("Consuming value %d at index %d\n", val, consumerIndex%BUFFER_SIZE);
		consumerIndex++;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		
	}
}

void *producer_function(void *arg){
	while(producerIndex < 1000){
                sem_wait(&empty);
                pthread_mutex_lock(&mutex);
                shared_buffer[producerIndex%BUFFER_SIZE] = producerIndex;
		printf("Producing value %d at index %d\n", producerIndex, producerIndex%BUFFER_SIZE);
		producerIndex++;
                pthread_mutex_unlock(&mutex);
                sem_post(&full);
        }
}


int main(int argc, char *argv[]){

	pthread_t consumer[5], producer[5];
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);

	for (int i = 0; i < 5; i++){
		pthread_create(&consumer[i], NULL, consumer_function, NULL);
		pthread_create(&producer[i], NULL, producer_function, NULL);

	}
	for (int i = 0; i < 5; i++){
		pthread_join(consumer[i], 0);
                pthread_join(producer[i], 0);
	}
	return 0;
}
