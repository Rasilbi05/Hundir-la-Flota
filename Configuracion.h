#ifndef _CONFIGURACION_
#define _CONFIGURACION_
#include <string.h>
#include "Barcos.h"
//#include "Tablero.h"


typedef struct{
    char nombre[20];
    int tipoDisparo;            //0: Disparo normal, 1: Disparo automático
    int NPortaaviones, NAcorazado, NCrucero, NDestructor, NFragata;
    int comienza;               //0: Jugador1, 1: Jugador2
    int tamTablero;
    char **flota, **oponente;
    int NDisparos, agua, tocadas, casHundidas, barHundidos, barRestantes, ganador;
}Configuracion;

Configuracion* menuConfiguracion();
Configuracion* introducirDatos(Configuracion* configuracion);
void mostrarDatos(Configuracion* datos);



void menuPrincipal();

#endif // _CONFIGURACION_