#ifndef _BARCOS_
#define _BARCOS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{         //Estructura de los barcos
    char nombre[20];
    char Id_Barco[1];
    int Tam_Barco;
    int valido;
}Barco;

Barco* cargarBarcos();  //Funcion que carga los barcos desde un fichero
void mostrarBarcos(Barco* barcos);

#endif // _BARCOS_