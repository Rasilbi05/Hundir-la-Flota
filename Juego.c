#include "Juego.h"

//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego(){

    int n;

    printf("1. Jugar partida\n2. Reiniciar partida\n3. Resumen\n4. Volver\n--> ");  //mostramos al usuario las distintas opciones que tiene
    scanf("%d",&n);

    switch(n){

        case 1:

            jugarPartida(); //función encargada de comenzar la partida

        break;
        case 2:

            reiniciarPartida(); //función encargada de reiniciar los datos de la partida
            printf("\nPartida reiniciada.\n");
            menuJuego();    //llamamos de nuevo a la función menuJuego para que el usuario pueda iniciar la partida

        break;
        case 3:

            resumenPartida();   //función encargada de mostrar los datos de la última partida

        break;
        case 4:

            //llamar a la función encargada de mostrar la configuración

        break;

    }

}

//Precondición:
//Postcondición: Comenzar el juego
void jugarPartida(){



}

//Precondición:
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(){



}

//Precondición:
//Postcondición: devuelve un resumen de los datos de la partida jugada
void resumenPartida(){



}