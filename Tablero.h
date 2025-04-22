#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Configuracion.h"
#include "Barcos.h"


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