#ifndef _BARCOS_
#define _BARCOS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{         //Estructura de los barcos
    char nombre[20];
    char Id_Barco;
    int Tam_Barco;
}Barco;


//cabecera: void menuBarcos()
//pre: -
//post: muestra el menu de barcos
void menuBarcos();
//cabecera: int obtenerNBarcos()
//pre: -
//post: devuelve el numero de barcos
int obtenerNBarcos();
//cabecera: int obtenerIDBarco(char *nombre)
//pre: recibe el nombre del barco
//post: devuelve el ID del barco
char obtenerIDBarco(char *nombre);
//cabecera: void guardarBarcos(Barco* barcos, int NBarcos)
//pre: recibe un vector de estructuras de barcos y el numero de barcos
//post: guarda los barcos en un fichero
void guardarBarcos(Barco* barcos, int NBarcos);
//cabecera: Barco* cargarBarcos()
//pre: -
//post: carga los barcos desde un fichero
Barco* cargarBarcos();
//cabecera: void crearBarco(Barco* barcos)
//pre: recibe un vector de estructuras de barcos
//post: crea un barco
void crearBarco(Barco* barcos);
//cabecera: void eliminarBarco(Barco* barcos)
//pre: recibe un vector de estructuras de barcos
//post: elimina un barco
void eliminarBarco(Barco* barcos);
//cabecera: void modificarBarco(Barco* barcos)
//pre: recibe un vector de estructuras de barcos
//post: modifica un barco
void modificarBarco(Barco* barcos);
//cabecera: void mostrarBarcos(Barco* barcos)
//pre: recibe un vector de estructuras de barcos
//post: muestra los barcos
void mostrarBarcos(Barco* barcos);
//cabecera: char* leerCadena()
//pre: -
//post: devuelve una cadena de caracteres
char* leerCadena();

#endif // _BARCOS_