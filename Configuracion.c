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
        Configuracion* datos[2];
        switch(opcion){
            case 1:
                *datos = introducirDatos(datos);
                menuConfiguracion();
                break;
            case 2:
                mostrarDatos(datos);
                menuConfiguracion();
                break;
            case 3:
                //guardarDatos(datos);
                break;
            case 4:
                //cargarDatos(datos);
                break;
            case 5:
                //menuPrincipal(datos);
                break;
            default:
                printf("Opcion no valida\n");
        }
    }while(opcion < 1 || opcion > 5);
}

Configuracion* introducirDatos(Configuracion* configuracion){
    for(int i = 0; i < 2; i++){             //Recorre el vector de estructuras para inicializar los datos
        printf("Introduce el nombre del jugador %d: ", i+1);
        fflush(stdin);
        fgets(configuracion[i].nombre, 20, stdin);
        fflush(stdin);
        printf("Introduce el tipo de disparo del jugador %d (0: Disparo normal, 1: Disparo automatico): ", i+1);
        scanf("%d", &configuracion[i].tipoDisparo);
        configuracion[i].NDisparos = 0;
        configuracion[i].agua = 0;
        configuracion[i].tocadas = 0;
        configuracion[i].casHundidas = 0;
        configuracion[i].barHundidos = 0;
    }
    printf("Introduce el numero de Portaaviones: ");
    scanf("%d", &configuracion[0].NPortaaviones, &configuracion[1].NPortaaviones);
    printf("Introduce el numero de Acorazados: ");
    scanf("%d", &configuracion[0].NAcorazado, &configuracion[1].NAcorazado);
    printf("Introduce el numero de Cruceros: ");
    scanf("%d", &configuracion[0].NCrucero, &configuracion[1].NCrucero);
    printf("Introduce el numero de Destructores: ");
    scanf("%d", &configuracion[0].NDestructor, &configuracion[1].NDestructor);
    printf("Introduce el numero de Fragatas: ");
    scanf("%d", &configuracion[0].NFragata, &configuracion[1].NFragata);
    configuracion[0].barRestantes = configuracion[0].NPortaaviones + configuracion[0].NAcorazado + configuracion[0].NCrucero + configuracion[0].NDestructor + configuracion[0].NFragata;
    configuracion[1].barRestantes = configuracion[1].NPortaaviones + configuracion[1].NAcorazado + configuracion[1].NCrucero + configuracion[1].NDestructor + configuracion[1].NFragata;
    int comienza;
    do{                    //Bucle para comprobar que se introduce una opcion valida
        printf("Introduce quien comienza (0: Jugador1, 1: Jugador2): ");
        scanf("%d", &comienza);
        switch(comienza){
            case 0:
                configuracion[0].comienza = 0;
                configuracion[1].comienza = 1;
                break;
            case 1:
                configuracion[0].comienza = 1;
                configuracion[1].comienza = 0;
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }while(comienza != 0 && comienza != 1);
    /*while(comprobar con funcion == 0){              //Bucle para comprobar que el tamaño del tablero es valido
        printf("Introduce el tamaño del tablero: ");
        scanf("%d", &configuracion[0].tamTablero);
    }
    //Para el tamaño del tablero preguntar a funcion de cristian para saber si es posible ese valor o no
    */
    return configuracion;
}

void mostrarDatos(Configuracion* datos){
    for(int i = 0; i < 2; i++){
        printf("Nombre: %s\n", datos[i].nombre);
        printf("Tipo de disparo: %d\n", datos[i].tipoDisparo);
        printf("Numero de Portaaviones: %d\n", datos[i].NPortaaviones);
        printf("Numero de Acorazados: %d\n", datos[i].NAcorazado);
        printf("Numero de Cruceros: %d\n", datos[i].NCrucero);
        printf("Numero de Destructores: %d\n", datos[i].NDestructor);
        printf("Numero de Fragatas: %d\n", datos[i].NFragata);
        printf("Comienza: %d\n", datos[i].comienza);
        printf("Tamaño del tablero: %d\n", datos[i].tamTablero);
        printf("Numero de disparos: %d\n", datos[i].NDisparos);
        printf("Agua: %d\n", datos[i].agua);
        printf("Tocadas: %d\n", datos[i].tocadas);
        printf("Casillas hundidas: %d\n", datos[i].casHundidas);
        printf("Barcos hundidos: %d\n", datos[i].barHundidos);
        printf("Barcos restantes: %d\n", datos[i].barRestantes);
    }
}