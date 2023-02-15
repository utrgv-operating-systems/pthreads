#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t x, y, z, wsem, rsem;
int readcount, writecount;

void *reader(void *arg){
	fprintf(stdout, "New reader running");
	while(1){
		sem_wait(&z);
			sem_wait(&rsem);
				sem_wait(&x);
					readcount++;
					if (readcount == 1) sem_wait(&wsem);
				sem_post(&x);
			sem_post(&rsem);
		sem_post(&z);
		// READ FILE
		printf("Reading file...");
                sleep(2);
		sem_wait(&x);
			readcount--;
			if (readcount == 0) sem_post(&wsem);
		sem_post(&x);
	}
}

void *writer(void *arg){
	fprintf(stdout, "New writer running");
        while(1){
                sem_wait(&y);
                	writecount++;
                        if (writecount == 1) sem_wait(&rsem);
                sem_post(&y);
                sem_wait(&wsem);
                // WRITE FILE
		printf("Writing to file...");
		sleep(2);
		sem_post(&wsem);
		sem_wait(&y);
                        writecount--;
                        if (writecount == 0) sem_post(&rsem);
                sem_post(&y);
        }
}

int main(int argc, char *argv[]){
	pthread_t readers[10], writers[10];
	
	readcount = 0;
	writecount = 0;
	sem_init(&x, 0, 1);
	sem_init(&y, 0, 1);
	sem_init(&z, 0, 1);
        sem_init(&wsem, 0, 1);
        sem_init(&rsem, 0, 1);


	for (int i = 0; i < 10; i++){
		pthread_create(&readers[i], NULL, reader, NULL);
		pthread_create(&writers[i], NULL, writer, NULL);
	}

	for (int i = 0; i < 10; i++){
                pthread_join(readers[i], 0);
                pthread_join(writers[i], 0);
        }

	return 0;
	
}

