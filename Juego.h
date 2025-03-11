#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//incluir los .h necesarios

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

#endif