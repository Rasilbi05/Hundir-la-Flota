#ifndef _BARCOS_
#define _BARCOS_
#define NBarcos 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{         //Estructura de los barcos
    char nombre[20];
    char Id_Barco[1];
    int Tam_Barco;
}Barco;

Barco* cargarBarcos();      //Funcion que carga los barcos desde un fichero
void mostrarBarcos(Barco* barcos);      //Funcion que muestra los barcos

#endif // _BARCOS_