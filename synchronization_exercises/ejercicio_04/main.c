#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

void *imprimirA()
{
	while (1)
	{

		printf("A \n");

		sleep(1);
	}
}

void *imprimirB()
{
	while (1)
	{

		printf("B \n");

		sleep(1);
	}
}

int main(void)
{

	
	pthread_t hiloA;
	pthread_t hiloB;

	pthread_create(&hiloA, NULL, imprimirA, NULL);
	pthread_create(&hiloB, NULL, imprimirB, NULL);

	pthread_join(hiloA, NULL);
	pthread_join(hiloB, NULL);

	return 0;
}
