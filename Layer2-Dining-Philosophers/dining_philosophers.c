#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t chopsticks[NUM_PHILOSOPHERS];

void think(int id) {
	printf("Philosopher %d is thinking...\n", id);
	usleep(200000); //0.2 secs
}

void eat(int id) {
	printf("Philosopher %d is EATING!\n", id);
	usleep(300000); //0.3 secs
}

void pick_up_chopsticks(int id) {
	int left = id;
	int right = (id + 1) % NUM_PHILOSOPHERS;

	if (id % 2 == 0) { //even philosophers pick RIGHT then LEFT
		sem_wait(&chopsticks[right]);
		printf("Philosopher %d picked RIGHT chopstick.\n", id);
		
		sem_wait(&chopsticks[left]);
		printf("Philosopher %d picked LEFT chopstick.\n", id);
	} else { //odd philosophers pick LEFT then RIGHT
		sem_wait(&chopsticks[left]);
                printf("Philosopher %d picked LEFT chopstick.\n", id);
		
		sem_wait(&chopsticks[right]);
                printf("Philosopher %d picked RIGHT chopstick.\n", id);
	}
}

void put_down_chopsticks(int id) {
	int left = id;
	int right = (id + 1) % NUM_PHILOSOPHERS;

	sem_post(&chopsticks[left]);
	sem_post(&chopsticks[right]);

	printf("Philosopher %d put down chopsticks.\n", id);
}

void* philosopher(void* num) {
	int id = *(int*)num;

	while (1) {
		think(id);
		pick_up_chopsticks(id);
		eat(id);
		put_down_chopsticks(id);
	}
	return NULL;
}

int main() {
	int ids[NUM_PHILOSOPHERS];

	for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
		sem_init(&chopsticks[i], 0, 1);
	} //initialize chopstick semaphores

	for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
		ids[i] = i;
		pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
	} //create philosopher threads

	for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
		pthread_join(philosophers[i], NULL);
	} //wait for threads to finish, but it's an infinite loop in this case

	return 0;
}
