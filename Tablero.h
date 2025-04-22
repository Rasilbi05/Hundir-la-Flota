#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Configuracion.h"
#include "Barcos.h"

//Cabecera: int comprobarTamano(Configuracion*)
//Precondición: Se deben haber elegido el tamaño de los barcos, el número de cada uno de estos y un tamaño para el tablero 
//Postcondición: Devuelve 1 si el tamaño del tablero es válido (si hay alguna manera de que los barcos puedan situarse) y un 0 si no lo es
int comprobarTamano(Configuracion* datos);

//Cabecera: char **generarTablero(int)
//Precondición: Se debe haber determinado que el tamaño del tablero respecto al espacio que ocuparán los barcos es válido
//Postcondición: Genera el tablero del tamaño deseado
char **generarTablero(int n);

//Cabecera: void asignacionManual(Configuracion*, int)
//Precondición: Se debe haber seleccionado el modo de asignación manual
//Postcondición: Modifica el tablero situando los barcos, totalmente a elección de los usuarios
void asignacionManual(Configuracion* datos, int u);

//Cabecera: void asignacionAutomatica(Configuracion*, int)
//Precondición: Se debe haber seleccionado el modo de asignación automática
//Postcondición: Modifica el tablero situando los barcos, aleatoriamente y sin intervención de los usuarios
void asignacionAutomatica(Configuracion* datos, int u);

#endif