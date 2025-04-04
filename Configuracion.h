#ifndef _CONFIGURACION_
#define _CONFIGURACION_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Barcos.h"
//#include "Tablero.h"


typedef struct{
    char nombre[20];
    int tipoDisparo;            //0: Disparo manual, 1: Disparo automático
    int *NBarcos;
    int comienza;               //0: Jugador1, 1: Jugador2
    int tamTablero;
    char **flota, **oponente;
    int NDisparos, agua, tocadas, casHundidas, barHundidos, barRestantes, ganador, totalBarcos;      //0: perdedor, 1: ganador
}Configuracion;

//cabecera: Configuracion* menuConfiguracion()
//pre: -
//post: modifica el vector de estructuras de configuración
void menuConfiguracion();
//cabecera: Configuracion* introducirDatos(Configuracion* configuracion)
//pre: -
//post: devuelve el vector de estructuras de configuración con los datos introducidos
void introducirDatos(Configuracion* configuracion);
//cabecera: void mostrarDatos(Configuracion* datos)
//pre: recibe el vector de estructuras de configuración
//post: muestra los datos introducidos
void mostrarDatos(Configuracion* datos);
//cabecera: void guardarDatos(Configuracion* datos, Barco* barcos)
//pre: recibe el vector de estructuras de configuración
//post: guarda los datos introducidos en un fichero
void guardarDatos(Configuracion* datos, Barco* barcos);
//cabecera: void cargarDatos(Configuracion* datos, Barco* barcos)
//pre: recibe el vector de estructuras de configuración
//post: carga los datos de un fichero
void cargarDatos(Configuracion* datos, Barco* barcos);

#endif // _CONFIGURACION_