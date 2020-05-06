#define CANTIDAD_JUGADORES 5
#include <semaphore.h>

typedef struct semaforo_id_jugador
{
    int id_jugador;

} semaforo_id_jugador;

int gol = 0;

semaforo_id_jugador semaforos_jugadores[CANTIDAD_JUGADORES];