/*
	This example shows a simple way of creating 5 threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *PrintHello(void *threadid){
	long tid;
	tid = (long) threadid; // cast the argument to what we wanted.
	printf("Hello world from thread #%d\n", tid);
	pthread_exit(NULL); // exit thread
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS]; 
	int rc;
	long t;
	for(t=0;t<NUM_THREADS;t++)  {
		printf("In main: creating thread %ld\n", t);
		rc =	pthread_create(&threads[t], NULL, PrintHello, (void *)t ); // create the thread using PrintHello
		if (rc) { // Zero return code is an error
			printf("ERROR; return code from pthread_create() is %d\n", rc); 
			exit(-1);
		}
	}
	pthread_exit(NULL); // exit thread
}


