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

            printf("Volviendo al inicio.\n");

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
    
    
    //CADA VEZ QUE SE DISPARA HAY QUE PEDIR SI SE QUIERE GUARDAR LA PARTIDA

}

//Precondición: Se ha jugado una partida previamente
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(Configuracion* conf){
    
    //reiniciamos todas las variables del usuario
    for(int i=0;i<2;i++){

        conf[i].NDisparos=0;
        conf[i].ganador=0;
        conf[i].tocadas=0;
        conf[i].casHundidas=0;
        conf[i].barHundidos=0;
        conf[i].barRestantes=conf[i].NAcorazado+conf[i].NCrucero+conf[i].NFragata+conf[i].NPortaaviones+conf[i].NDestructor;

        //Hacemos otro bucle para limpiar los tableros
        for(int f=0;f<conf[i].tamTablero;f++){

            for(int c=0;c<conf[i].tamTablero;c++){

                if(conf[i].flota[f][c]!=' '){

                    conf[i].flota[f][c]=' ';

                }else if(conf[i].oponente[f][c]!=' '){

                    conf[i].oponente[f][c]=' ';

                }

            }

        }

    }

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

        //calculamos las casillas vacías
        vacia = conf[i].NDisparos-pow(conf[i].tamTablero,2);

        printf("%s                     |     %d|   %d| %d|    %d|     %d|     %d|   %d|    %d|\n",conf[i].nombre,conf[i].NDisparos,vacia,conf[i].agua,conf[i].tocadas,conf[i].casHundidas,conf[i].barHundidos,conf[i].barRestantes,conf[i].ganador);
    
    }

    int c=0;    //usamos esta variable para poder mostrar las casillas

    //hacemos un bucle principal para poder mostrar los datos de ambos jugadores
    for(int j=0;j<2;j++){

        printf("%s: FLOTA                       OPONENTE\n",conf[j].nombre);
        
      
        while(c<conf[j].tamTablero){

            printf("%d|",c);
            c++;
        }

        //imprimimos el tablero
        for(int i=0;i<conf[j].tamTablero;i++){

            printf("%d|",i);            

            //imprimimos las filas del tablero Flota
            for(int f=0;f<conf[j].tamTablero;f++){
     
              printf("%c|",conf[j].flota[i][f]);  //vamos mostrando cada casilla de Flota      

            }

            printf("  %d|",i);

            //imprimimos las filas del tablero Oponente
            for(int f=0;f<conf[j].tamTablero;f++){

                printf("%c|",conf[j].oponente[i][f]);  //vamos mostrando cada casilla de Oponente

            }

            printf("\n");   //saltamos a la siguiente fila

        }

        
    }
    
    //le pedimos al usuario que confirme pulsando una tecla para poder continuar 
    system("Pause");
    system("cls");

}


//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve 0 si ha fallado o 1 si ha impactado en un barco enemigo
int comprobarDisparo(){



}

//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(){

    /*cuando encuentro un barco, necesito saber donde empieza este, asi que compruebo todas las casillas posibles
        si se encuentra una, intento buscar en la zona opuesta a la encontrada, para ver si sigue el barco por ahi,
        sino sigo por donde he dado previamente, hasta que se haya hundido el agua
    */

}