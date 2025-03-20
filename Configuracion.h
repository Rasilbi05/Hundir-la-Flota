#ifndef _CONFIGURACION_
#define _CONFIGURACION_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Juego.h"
//#include "Tablero.h"


typedef struct{
    char nombre[20];
    int tipoDisparo;            //0: Disparo normal, 1: Disparo automático
    int NPortaaviones, NAcorazado, NCrucero, NDestructor, NFragata;
    int comienza;               //0: Jugador1, 1: Jugador2
    int tamTablero;
    char **flota, **oponente;
    int NDisparos, agua, tocadas, casHundidas, barHundidos, barRestantes, ganador;      //0: perdedor, 1: ganador
}Configuracion;

//cabecera: Configuracion* menuConfiguracion();
//pre: -
//post: modifica el vector de estructuras de configuración
void menuConfiguracion();
//cabecera: Configuracion* introducirDatos(Configuracion* configuracion);
//pre: -
//post: devuelve el vector de estructuras de configuración con los datos introducidos
void introducirDatos(Configuracion* configuracion);
//cabecera: void mostrarDatos(Configuracion* datos);
//pre: recibe el vector de estructuras de configuración
//post: muestra los datos introducidos
void mostrarDatos(Configuracion* datos);
//cabecera: void menuPrincipal();
//pre: -
//post: muestra el menú principal
void menuPrincipal();

#endif // _CONFIGURACION_