#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define locked 1
#define unlocked 0

#define THREAD_NUM 2

extern void lock_mutex(void *mutex);
extern void unlock_mutex(void *mutex);

pthread_t tid[THREAD_NUM];
int counter;
unsigned int mutexlock = unlocked;

void *doSomeThing(void *arg)
{
	lock_mutex(&mutexlock); 
	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d started\n", counter);

	for (i = 0; i < (0xFFFFFFFF); i++);

	printf("\n Job %d finished\n", counter);

	unlock_mutex(&mutexlock);
	return NULL;
}

int main(void)
{
	int i = 0;
	int err;

	while (i < THREAD_NUM) {
		err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
		if (err != 0)
			printf("\ncan't create thread :[%s]", strerror(err));
		i++;
	}

	for(i = 0; i < THREAD_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
