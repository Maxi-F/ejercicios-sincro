/*
 * main.c
 *
 *  Created on: 18/4/2017
 *      Author: alejandrokrumkamp
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "functions.h"

pthread_mutex_t mutex_pistas;

int cantidadAviones = 100;

void *avion()
{
	while (1)
	{

		mantenimiento();

		//pedir una pista y esperar

		despegar();

		volar();

		aterrizar();
	}
}

void *controladorEntrada()
{
	while (1)
	{

		otorgarUnaPista();

		pthread_mutex_lock(&mutex_pistas);
		pistasLibres--;
		pthread_mutex_unlock(&mutex_pistas);

		logger();
	}
}

void *controladorSalida()
{
	while (1)
	{

		liberarUnaPista();

		pthread_mutex_lock(&mutex_pistas);
		pistasLibres++;
		pthread_mutex_unlock(&mutex_pistas);

		logger();
	}
}

void generarAviones()
{
	int cantidadAvionesCreados = 0;
	pthread_t hiloAvion;
	while (cantidadAvionesCreados <= cantidadAviones)
	{
		pthread_create(&hiloAvion, NULL, avion, NULL);
		printf("Cantidad aviones creados: %i|", cantidadAvionesCreados);
		cantidadAvionesCreados++;
	}
}

void generarControladoresAereos()
{
	pthread_t hiloControladorEntrada, hiloControladorSalida;
	pthread_create(&hiloControladorEntrada, NULL, controladorEntrada, NULL);
	pthread_create(&hiloControladorSalida, NULL, controladorSalida, NULL);

	// Los joins se agregar para que main no termine.
	pthread_join(hiloControladorEntrada, NULL);
	pthread_join(hiloControladorSalida, NULL);
}

int main(void)
{

	
	generarAviones(cantidadAviones);
	generarControladoresAereos();
	return 0;
}
