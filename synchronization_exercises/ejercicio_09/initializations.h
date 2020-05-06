#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>

void inicializar_semaforo_id_jugadores()
{
    int i = 0;
    while (i < CANTIDAD_JUGADORES)
    {
        semaforos_jugadores[i].id_jugador = -1;
        i++;
    }
    return;
}

void inicializar_semaforos()
{

    /* este semaforo no es necesario en el ejercicio pero si para la implementacion */

    int i = 0;
    while (i < (CANTIDAD_JUGADORES - 1))
    {

        i++;
    }
}

void definirse_como_jugador()
{
    int i = 0;
    while (i < CANTIDAD_JUGADORES)
    {

        if (semaforos_jugadores[i].id_jugador == -1)
        {
            semaforos_jugadores[i].id_jugador = (int)syscall(__NR_gettid);

            return;
        }

        i++;
    }
}