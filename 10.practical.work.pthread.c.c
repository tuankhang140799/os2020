#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#define START 2
#define STOP 1000001

static sem_t sem;
#define SEM_PRINT_INT(s, n) do {	\
	sem_wait(&sem);			\
	printf(s " %d\n", (n));		\
	sem_post(&sem);			\
} while (0)

void *print_primes(void *args)
{
	char prime[STOP];
	memset(prime, 1, STOP);
    for (int i = START; i * i < STOP; ++i)
		if (prime[i])
			for (int j = i << 1; j < STOP; j += i)
				prime[j] = 0;
    for (int i = START; i < STOP; ++i)
		if (prime[i])
			SEM_PRINT_INT("prime number", i);
    return NULL;
}

void *print_fibos(void *args)
{
	int prev = 1, tmp;
    for (int current = START; current < STOP; current = prev + tmp) {
		SEM_PRINT_INT("fibonacci number", current);
		tmp = prev;
		prev = current;
	}
	return NULL;
}

int main()
{
	pthread_t prime_thread, fibo_thread;
	sem_init(&sem, 0, 1);
	pthread_create(&prime_thread, NULL, print_primes, NULL);
	pthread_create(&fibo_thread, NULL, print_fibos, NULL);
	pthread_join(prime_thread, NULL);
	pthread_join(fibo_thread, NULL);
	sem_destroy(&sem);
	return 0;
}
