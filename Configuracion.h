#ifndef _CONFIGURACION_
#define _CONFIGURACION_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Barcos.h"

typedef struct{
    char nombre[20];
    int tipoDisparo;            //0: Disparo manual, 1: Disparo automático
    int *NBarcos;
    int comienza;               //0: Jugador1, 1: Jugador2
    int tamTablero;
    char **flota, **oponente;
    int NDisparos, agua, tocadas, hundidas, barHundidos, barRestantes, ganador, totalBarcos;      //0: perdedor, 1: ganador
}Configuracion;

//cabecera: Configuracion* menuConfiguracion()
//pre: -
//post: modifica el vector de estructuras de configuración
int menuConfiguracion(Configuracion *datos);
//cabecera: Configuracion* introducirDatos(Configuracion* configuracion)
//pre: -
//post: devuelve el vector de estructuras de configuración con los datos introducidos
void introducirDatos(Configuracion* configuracion);
//cabecera: void mostrarDatos(Configuracion* datos)
//pre: recibe el vector de estructuras de configuración
//post: muestra los datos introducidos
void mostrarDatos(Configuracion* datos);
//cabecera: void guardarDatos(Configuracion* datos)
//pre: recibe el vector de estructuras de configuración
//post: guarda los datos introducidos en un fichero
void guardarDatos(Configuracion* datos);
//cabecera: void cargarDatos(Configuracion* datos)
//pre: recibe el vector de estructuras de configuración
//post: carga los datos de un fichero
void cargarDatos(Configuracion* datos);
//int barcosHundidos(Configuracion* datos, int tamTablero)
//pre: recibe una matriz y el tamaño del tablero
//post: devuelve 1 si el tamaño del tablero es válido, 0 si no lo es
int barcosHundidos(char **oponente, int tamTablero);
//cabecera: void testBarcosHundidos(char **oponente, int tamTablero, int esperado)
//pre: recibe una matriz, el tamaño del tablero y el resultado esperado
//post: comprueba si el resultado es correcto
void testBarcosHundidos(char **oponente, int tamTablero, int esperado);
//Cabecera: int comprobarTamano(Configuracion*)
//Precondición: Se deben haber elegido el tamaño de los barcos, el número de cada uno de estos y un tamaño para el tablero 
//Postcondición: Devuelve 1 si el tamaño del tablero es válido (si hay alguna manera de que los barcos puedan situarse) y un 0 si no lo es
int comprobarTamano(Configuracion* datos);

#endif // _CONFIGURACION_