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
        default:
            printf("\nError, elija una de las opciones disponibles.\n");    //si el usuario escribe un número que no este entre 1-4, salta error
            menuJuego();
        break;

    }

}

//Precondición: El usuario ha configurado todo para poder comenzar el juego
//Postcondición: Comenzar el juego
void jugarPartida(){

    printf("\n--------- Bienvenidos a Hundir La Flota ---------\n");



}

//Precondición: Se ha jugado una partida previamente
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(){
    //limpiamos los tableros que se han jugado



}

//Precondición:
//Postcondición: devuelve un resumen de los datos de la partida jugada, si no se ha jugado, no devuelve nada
void resumenPartida(){



}

//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve 0 si ha fallado o 1 si ha impactado en un barco enemigo
int comprobarDisparo(){



}

//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(){



}