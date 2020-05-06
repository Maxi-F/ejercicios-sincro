#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int a = 1;
int b = 1;

void *proceso2()
{
    int d = 1;
    while (1)
    {
        sleep(1);
        printf("datos en proceso2: a=%d, b=%d, d=%d\n", a, b, d);

        a = a + d;

        d = d * d;

        b = b - d;

        printf("datos en proceso2 finales: a=%d, b=%d, d=%d\n", a, b, d);
    }
    return 0;
}

void *proceso1()
{
    int e = 2;

    while (1)
    {

        sleep(1);
        printf("datos en proceso1: a=%d, b=%d, e=%d\n", a, b, e);

        b = b * e;

        e = pow(e, e); // equivalente a e = e ^ e;

        a++;

        printf("datos en proceso1 finales: a=%d, b=%d, e=%d\n", a, b, e);
    }
    return 0;
}
int main()
{

    pthread_t threadProceso1, threadProceso2;
    pthread_create(&threadProceso1, NULL, proceso1, NULL);
    pthread_create(&threadProceso2, NULL, proceso2, NULL);

    pthread_join(threadProceso1, NULL);
    pthread_join(threadProceso2, NULL);

    return 0;
}