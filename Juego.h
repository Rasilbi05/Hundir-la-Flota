#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configuracion.h"
#include "Tablero.h"
//incluimos los .h necesarios

typedef struct{
    //mirar bien las variables que hacen falta
    int numDisparos;
    char** Flota, Oponente;
    int barcosRest; 

}jugador;

//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego();

//Precondición:
//Postcondición: Comenzar el juego
void jugarPartida();

//Precondición:
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida();

//Precondición:
//Postcondición: devuelve un resumen de los datos de la partida jugada
void resumenPartida();

//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico();

//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve 0 si ha fallado o 1 si ha impactado en un barco enemigo
int comprobarDisparo();

#endif