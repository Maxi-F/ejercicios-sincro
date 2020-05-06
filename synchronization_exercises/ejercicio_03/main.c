#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int cantidad_hilos = 6; // cantidad_hilos siendo la N del ejercicio

int variable_compartida = 1;
int impresoras = 3;

void usar_impresora()
{
    printf("IMP-U: El proceso %d esta utilizando una impresora\n", (int)syscall(__NR_gettid));
    sleep(1);
    printf("IMP-L: El proceso %d va a liberar una impresora\n", (int)syscall(__NR_gettid));
}

void usar_scanner()
{
    printf("SCAN-U: El proceso %d esta utilizando un scanner\n", (int)syscall(__NR_gettid));
    sleep(1);
    printf("SCAN-L: El proceso %d va a liberar un scanner\n", (int)syscall(__NR_gettid));
}

void *proceso_A()
{
    while (1)
    {

        usar_impresora();

        variable_compartida++;
    }
    return 0;
}
void *proceso_B()
{
    while (1)
    {

        variable_compartida++;

        usar_scanner();
    }
    return 0;
}

void *proceso_C()
{
    while (1)
    {

        usar_scanner();

        usar_impresora();
    }
    return 0;
}

int main()
{

    pthread_t threads_proceso_A[cantidad_hilos], threads_proceso_B[cantidad_hilos], threads_proceso_C[cantidad_hilos];
    int i = 0;
    while (i < cantidad_hilos)
    {
        pthread_create(&threads_proceso_A[i], NULL, proceso_A, NULL);
        pthread_create(&threads_proceso_B[i], NULL, proceso_B, NULL);
        pthread_create(&threads_proceso_C[i], NULL, proceso_C, NULL);
    }

    while (i < cantidad_hilos)
    {
        pthread_join(threads_proceso_A[i], NULL);
        pthread_join(threads_proceso_B[i], NULL);
        pthread_join(threads_proceso_C[i], NULL);
    }

    
    return 0;
}