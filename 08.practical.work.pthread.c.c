#include <pthread.h>
#include <stdio.h>
#include <string.h>
#define START 2
#define STOP 1000001

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
			printf("prime number %d\n", i);
    return NULL;
}
void *print_fibos(void *args)
{
	int prev = 1, tmp;
    for (int current = START; current < STOP; current = prev + tmp) {
		printf("fibonacci number %d\n", current);
		tmp = prev;
		prev = current;
	}
    return NULL;
}
int main()
{
	pthread_t prime_thread, fibo_thread;
    pthread_create(&prime_thread, NULL, print_primes, NULL);
	pthread_create(&fibo_thread, NULL, print_fibos, NULL);
    pthread_join(prime_thread, NULL);
	pthread_join(fibo_thread, NULL);
    return 0;
}
