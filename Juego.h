#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
//incluimos los .h necesarios
#include "Configuracion.h"
#include "Tablero.h"

//Cabecera: void menuJuego(Configuracion*)
//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego(Configuracion* conf);

//Cabecera: void jugarPartida(Configuracion*, int)
//Precondición:
//Postcondición: Comenzar el juego
void jugarPartida(Configuracion* conf,int cargar);

//Cabecera: void reiniciarPartida(Configuracion*,int*)
//Precondición:
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(Configuracion* conf, int* cargar);

//Cabecera: void resumenPartida(Configuracion*)
//Precondición:
//Postcondición: devuelve un resumen de los datos de la partida jugada
void resumenPartida(Configuracion* conf);

//Cabecera: void MostrarTableros(Configuracion*,int)
//Precondición: se solicita ver el tablero del jugador
//Postcondición: muestra los tableros Flota y Oponente del jugador
void MostrarTableros(Configuracion* conf, int j);

//Cabecera: void disparoAutomatico(Configuracion*, int, int)
//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(Configuracion* conf, int at, int op);

//Cabecera: void comprobarDisparo(Configuracion*,int,int,int,int)
//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve si el barco ha sido hundido o no
void comprobarDisparo(Configuracion* conf, int f, int c, int at, int op);

//Cabecera: primerDisparo(Configuracion*, int*, int*, int, int, int*, int*)
//Precondición: el sistema va a realizar el primer disparo ya que no hay ningún barco tocado
//Postcondición: realiza el primer disparo del sistema
void primerDisparo(Configuracion* conf, int* x, int* y, int at, int op, int* sX, int* sY);

#endif