#ifndef _CONFIGURACION_
#define _CONFIGURACION_
#include "Barcos.h"
#include "Tablero.h"


typedef struct{
    char nombre[20];
    int tipoDisparo;            //0: Disparo normal, 1: Disparo automático
    int NPortaaviones, NAcorazado, NCrucero, NDestructor, NFragata;
    int comienza;               //0: Jugador1, 1: Jugador2
    int NDisparos;
    int BarcosRest;
    char** flota, oponente;
}Configuracion;

#endif // _CONFIGURACION_