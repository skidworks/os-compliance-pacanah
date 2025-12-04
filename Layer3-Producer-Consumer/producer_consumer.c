#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

typedef struct {
	int buffer[BUFFER_SIZE];
	int in;
	int out;
	sem_t empty;   // Counts empty slots
   	sem_t full;    // Counts full slots
    	sem_t mutex;   // Binary lock
} buffer_t;

buffer_t shared;

//display buffer
void displayBuffer() {
    	printf("BUFFER: [");
    	for (int i = 0; i < BUFFER_SIZE; i++)
        	printf("%d ", shared.buffer[i]);
    		printf("]\n");
}

void* producer(void* arg) {
    	int id = *(int*)arg;

    	while (1) {
        	int item = rand() % 100;

        	sem_wait(&shared.empty);
        	sem_wait(&shared.mutex);

        	shared.buffer[shared.in] = item;
        	printf("Producer %d produced %d at index %d\n", id, item, shared.in);

        	shared.in = (shared.in + 1) % BUFFER_SIZE;

        	displayBuffer();

        	sem_post(&shared.mutex);
        	sem_post(&shared.full);

        	sleep(1);
    	}
}

void* consumer(void* arg) {
    	int id = *(int*)arg;

    	while (1) {
        	sem_wait(&shared.full);
        	sem_wait(&shared.mutex);

        	int item = shared.buffer[shared.out];
        	printf("Consumer %d consumed %d at index %d\n", id, item, shared.out);

        	shared.buffer[shared.out] = 0;
        	shared.out = (shared.out + 1) % BUFFER_SIZE;

        	displayBuffer();

        	sem_post(&shared.mutex);
        	sem_post(&shared.empty);

        	sleep(2);
    	}
}

int main() {
    	pthread_t prod[2], cons[3];
    	int prodID[2] = {1, 2};
    	int consID[3] = {1, 2, 3};

    	//init buffer
    	for (int i = 0; i < BUFFER_SIZE; i++)
        	shared.buffer[i] = 0;

    	shared.in = 0;
    	shared.out = 0;

    	//init semaphores
    	sem_init(&shared.empty, 0, BUFFER_SIZE);
    	sem_init(&shared.full, 0, 0);
    	sem_init(&shared.mutex, 0, 1);

    	//create threads
    	pthread_create(&prod[0], NULL, producer, &prodID[0]);
    	pthread_create(&prod[1], NULL, producer, &prodID[1]);

    	pthread_create(&cons[0], NULL, consumer, &consID[0]);
    	pthread_create(&cons[1], NULL, consumer, &consID[1]);
    	pthread_create(&cons[2], NULL, consumer, &consID[2]);

    	pthread_join(prod[0], NULL);
    	pthread_join(prod[1], NULL);
    	pthread_join(cons[0], NULL);
    	pthread_join(cons[1], NULL);
    	pthread_join(cons[2], NULL);

    	return 0;
}
