#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "functions.h"
#define INSTANCIAS_COMPILADOR 5

void *compilador()
{
    while (1)
    {
        int id_programa = obtener_nuevo_programa();
        int resultado = compilar_programa(id_programa);

        depositar_resultado(resultado, lista_resultados);

        sleep(1);
    }
}

void *notificador()
{
    while (1)
    {

        int resultado = retirar_resultado(lista_resultados);

        enviar_email(resultado);
        sleep(1);
    }
}

int main(void)
{

    pthread_t hilo_notificador, hilos_compilador[INSTANCIAS_COMPILADOR];

    pthread_create(&hilo_notificador, NULL, notificador, NULL);

    int i = 0;
    while (i < INSTANCIAS_COMPILADOR)
    {
        pthread_create(&hilos_compilador[i], NULL, compilador, NULL);
        i++;
    }

    pthread_join(hilo_notificador, NULL);
    i = 0;
    while (i < INSTANCIAS_COMPILADOR)
    {
        pthread_join(hilos_compilador[i], NULL);
        i++;
    }

    return 0;
}
