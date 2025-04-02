#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Barcos.h"
#include "Configuracion.h"
#include "Juego.h"

char **generarTablero(int n);
void asignacionManual(Configuracion* datos, int i);
void asignacionAutomatica(Configuracion* datos, int u);
int comprobarTamaño();

#endif