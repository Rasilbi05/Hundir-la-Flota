#include "Juego.h"

//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego(Configuracion* conf){

    int n;

    printf("1. Jugar partida\n2. Reiniciar partida\n3. Resumen\n4. Volver\n--> ");  //mostramos al usuario las distintas opciones que tiene
    scanf("%d",&n);

    switch(n){

        case 1:

            jugarPartida(conf); //función encargada de comenzar la partida

        break;
        case 2:

            reiniciarPartida(conf); //función encargada de reiniciar los datos de la partida
            printf("\nPartida reiniciada.\n");
            menuJuego(conf);    //llamamos de nuevo a la función menuJuego para que el usuario pueda iniciar la partida

        break;
        case 3:

            resumenPartida(conf);   //función encargada de mostrar los datos de la última partida

        break;
        case 4:

            //llamar a la función encargada de mostrar la configuración

        break;
        default:
            printf("\nError, elija una de las opciones disponibles.\n");    //si el usuario escribe un número que no este entre 1-4, salta error
            menuJuego(conf);
        break;

    }

}

//Precondición: El usuario ha configurado todo para poder comenzar el juego
//Postcondición: Comenzar el juego
void jugarPartida(Configuracion* conf){

    printf("\n--------- Bienvenidos a Hundir La Flota ---------\n");

    //Prueba de como se generaría un tablero: conf->flota=generarTablero(conf.tamTablero);
    
    


}

//Precondición: Se ha jugado una partida previamente
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(Configuracion* conf){
    //limpiamos los tableros que se han jugado



}

//Precondición: Resumen de la partida que se ha estado jugando
//Postcondición: devuelve un resumen de los datos de la partida jugada, si no se ha jugado, no devuelve nada
void resumenPartida(Configuracion* conf){
    int vacia,ganador=0;

    //mostramos por pantalla el resumen
    printf("                       |         Valor de las casillas       |                       |\n");
    printf("        Jugador        |Disparos|Vacías|Agua|Tocadas|Hundidas|Hundidos|Restan|Ganador|\n");
    printf("-----------------------|--------|------|----|-------|--------|--------|------|-------|\n");
    for(int i=0;i<2;i++){

        //calculamos quien es el ganador
        if(conf[i].barRestantes==0)
            ganador=1;
        //calculamos las casillas vacías
        vacia = conf[i].NDisparos-pow(conf[i].tamTablero,2);

        printf("%s                     |     %d|   %d| %d|    %d|     %d|     %d|   %d|    %d|\n",conf[i].nombre,conf[i].NDisparos,vacia,conf[i].agua,conf[i].tocadas,conf[i].casHundidas,conf[i].barHundidos,conf[i].barRestantes,ganador);
    
    }

    int c=0;    //usamos esta variable para poder mostrar las casillas
    //mostramos los tableros de cada jugador
    for(int j=0;j<2;j++){

        printf("%s: FLOTA                       OPONENTE\n",conf[j].nombre);
        
        printf("  |");
        while(c<conf[j].tamTablero){

            printf("%d|",c);
            c++;
        }

        //bucles para imprimir la matriz
        for(int i=0;i<conf[j].tamTablero;i++){

            for(int c=0;c<conf[j].tamTablero;c++){



            }

        }


    }


}


//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve 0 si ha fallado o 1 si ha impactado en un barco enemigo
int comprobarDisparo(){



}

//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(){



}