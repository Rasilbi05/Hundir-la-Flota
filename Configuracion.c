#include "Configuracion.h"


void menuConfiguracion(){
    int opcion;
    do{
        printf("1. Introducir datos\n");
        printf("2. Mostrar datos\n");
        printf("3. Guardar datos\n");
        printf("4. Cargar datos\n");
        printf("5. Salir\n");
        printf("Introduce una opcion: ");
        scanf("%d", &opcion);
        Configuracion* datos;
        switch(opcion){
            case 1:
                datos = introducirDatos();
                break;
            case 2:
                mostrarDatos();
                break;
            case 3:
                guardarDatos();
                break;
            case 4:
                cargarDatos();
                break;
            case 5:
                salir(datos);
                break;
            default:
                printf("Opcion no valida\n");
        }
    }while(opcion < 1 || opcion > 5);
}

Configuracion* introducirDatos(){
    Configuracion configuracion[2];         //Vector de estructuras
    for(int i = 0; i < 2; i++){             //Recorre el vector de estructuras para inicializar los datos
        printf("Introduce el nombre del jugador %d: ", i+1);
        scanf("%s", &configuracion[i].nombre);
        printf("Introduce el tipo de disparo del jugador %d (0: Disparo normal, 1: Disparo automatico): ", i+1);
        scanf("%d", &configuracion[i].tipoDisparo);
        printf("Introduce el numero de Portaaviones del jugador %d: ", i+1);
        scanf("%d", &configuracion[i].NPortaaviones);
        printf("Introduce el numero de Acorazados del jugador %d: ", i+1);
        scanf("%d", &configuracion[i].NAcorazado);
        printf("Introduce el numero de Cruceros del jugador %d: ", i+1);
        scanf("%d", &configuracion[i].NCrucero);
        printf("Introduce el numero de Destructores del jugador %d: ", i+1);
        scanf("%d", &configuracion[i].NDestructor);
        printf("Introduce el numero de Fragatas del jugador %d: ", i+1);
        scanf("%d", &configuracion[i].NFragata);
        printf("Introduce quien comienza (0: Jugador1, 1: Jugador2): ");
        scanf("%d", &configuracion[i].comienza);
        configuracion[i].NDisparos = 0;
        configuracion[i].BarcosRest = configuracion[i].NPortaaviones + configuracion[i].NAcorazado + configuracion[i].NCrucero + configuracion[i].NDestructor + configuracion[i].NFragata;
    }
    return configuracion;
}

