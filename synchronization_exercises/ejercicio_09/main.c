#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include "initializations.h"

void definirse_como_jugador();

void *arbitro()
{
	while (1)
	{

		dar_orden();

		validar_tiro();
	}
}

void *jugador()
{
	definirse_como_jugador();
	int mi_id = actual();
	while (1)
	{

		posicionarse_jugador();

		patear();

		if (gol)
		{
			festejarGol();
		}
		else
		{
			lamentarAtajada();
		}
	}
}

void *arquero()
{
	while (1)
	{

		posicionarse_arquero();

		atajar();

		if (!gol)
		{
			festejarAtajada();
		}
		else
		{
			lamentarGol();
		}
	}
}

void crear_y_esperar_hilos()
{
	pthread_t hilo_arquero, hilo_arbitro, hilos_jugadores[CANTIDAD_JUGADORES];

	pthread_create(&hilo_arquero, NULL, arquero, NULL);
	pthread_create(&hilo_arbitro, NULL, arbitro, NULL);
	int i = 0;
	while (i < CANTIDAD_JUGADORES)
	{
		pthread_create(&hilos_jugadores[i], NULL, jugador, NULL);
		i++;
	}

	pthread_join(hilo_arquero, NULL);
	pthread_join(hilo_arbitro, NULL);

	i = 0;
	while (i < CANTIDAD_JUGADORES)
	{
		pthread_join(hilos_jugadores[i], NULL);
		i++;
	}
	return;
}

int main(void)
{

	inicializar_semaforos();
	inicializar_semaforo_id_jugadores();

	crear_y_esperar_hilos();

	return 0;
}
