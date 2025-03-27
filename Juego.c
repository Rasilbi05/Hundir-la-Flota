#include "Juego.h"

//Cabecera: void menuJuego(Configuracion*)
//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego(Configuracion* conf){

    int n;

    printf("1. Jugar partida\n2. Reiniciar partida\n3. Resumen\n4. Volver\n--> ");  //mostramos al usuario las distintas opciones que tiene
    scanf("%d",&n);

    switch(n){

        case 1:

            jugarPartida(conf,0); //función encargada de comenzar la partida

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

//Cabecera: void jugarPartida(Configuracion*)
//Precondición: El usuario ha configurado todo para poder comenzar el juego
//Postcondición: Comenzar el juego
void jugarPartida(Configuracion* conf,int cargar){

    system("cls");
    
    //hay que concretar bien como va a funcionar al variable que indique quien comienza (de momento, se usa la asignación de i)
    int i=conf[0].comienza,cont=0,resp=0;    //i es un índice que nos servirá para poder elegir a los dos jugadores, 
    //el contador sirve para saber que hemos terminado con ambos jugadores
    //resp se utiliza para saber que opción elige el jugador
    
    //cargar es un entero que sirve para saber si se ha cargado partida, si fuese así, los tableros y la partida ya estaría definida,
    //por lo que no es necesario 
    if(cargar==0){
        //preguntamos si quieren colocar sus barcos de forma manual o automática
        while(cont<2){

            //generamos los tableros:
            conf[cont].flota=generarTablero(conf[cont].tamTablero);
            conf[cont].oponente=generarTablero(conf[cont].tamTablero);

            printf("\n¿De que forma desea colocar sus barcos %s?\n1. Manual\n2.Automático\n--> ",conf[cont].nombre);
            scanf("%d",&resp);

            //llamamos a la función respectiva pasando como parámetro el tablero FLOTA
            if(resp=1){

                //llamamos a la función encargada de realizar la asignación manual de los barcos

            }else{

                //llamamos a la función encargada de realizar la asignación automática de los barcos

            }

            cont++;

        }

    }

    int f=0,c=0,op=0;    //variables encargadas de las coordenadas que elija el jugador
    //op sirve para saber cual es el índice del oponente
    
    if(i==0)
        op++;
    else
        op--;

    //creamos el bucle principal para el juego
    while(conf[0].ganador!=1||conf[1].ganador!=1){

        printf("Turno de %s:\n",conf[i].nombre);

        //vemos si el disparo es manual o automático
        if(conf[i].tipoDisparo==0)/*disparo manual*/{

            printf("Elija las coordenadas del disparo:\n--> ");
            scanf("%d %d",&f,&c);

            //comprobamos si el disparo ha sido o no agua
            if(conf[op].flota[f][c]==' '){

                printf("\nAgua\n");
                conf[i].oponente[f][c]='*';

            }else{

                conf[i].oponente[f][c]='T'; //marcamos en estado de 'Tocado' en el tablero oponente
                
                while(conf[op].flota[f][c]!=' '){//hacemos que el jugador pueda seguir disparando hasta que de en agua
                    
                    comprobarDisparo(conf,f,c,i,op); //comprobamos si se ha hundido un barco
                    
                    printf("\nElija las coordenadas del disparo:\n--> ");
                    scanf("%d %d",&f,&c);

                }

                prinf("\nAgua\n");  //como ha salido del bucle al dar en agua, se lo indicamos

            }

        }else{

            disparoAutomatico(conf);    //llamamos a la función que realiza el disparo automático

        }

        //este condicional nos sirve para ir intercambiando entre los turnos de los jugadores
        if(i==0){
        
            op=i;
            i++;
        
        }else{
         
            op=i;
            i--;
        
        }

    }
    
    
    //CADA VEZ QUE SE DISPARA HAY QUE PEDIR SI SE QUIERE GUARDAR LA PARTIDA

}

//Cabecera: void reiniciarPartida(Configuracion*)
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

//Cabecera: void resumenPartida(Configuracion*)
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

//Cabecera: void comprobarDisparo(Configuracion*,int,int,int,int)
//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve si el barco ha sido hundido o no
void comprobarDisparo(Configuracion* conf, int f, int c, int at, int op){
    
    int fO=f, cO=c,i=1,j=1,tam=1,tocadas=1; //declaramos las variables para guardar las coordenadas del origen del barco
    //i nos sirve para ir comprobando las coordenadas origen
    //j nos sirve para comprobar la otra parte tras encontrar las coordenadas origen
    //tam sirve para ver el tamaño del barco (está a 1 ya que ya hemos dado a una casilla)
    //tocadas nos sirve para ver cuantas casillas están en estado 'Tocado' en nuestro tablero
    
    /*cuando encuentro un barco, necesito saber donde empieza este, asi que compruebo todas las casillas posibles
    si se encuentra una, intento buscar en la zona opuesta a la encontrada, para ver si sigue el barco por ahi,
    sino sigo por donde he dado previamente, hasta que se haya hundido el agua
    */

    if(conf[op].flota[f+1][c]=='X'){//El barco está en vertical (comprobando si sigue por arriba)

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i-1][c]!=' '){

            i--;    //vamos hacia abajo buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j+1][c]!=' '){

            j++;    //vamos hacia arriba hasta llegar al final del barco
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //Comprobamos si el usuario ha dado a todas las casillas
        while(conf[op].flota[fO+i][cO]!=' '){

            if(conf[at].oponente[fO+i][cO]=='T'){   //comprobamos si se han marcado como tocadas las posiciones del barco

                tocadas++;

            }

            i++;

        }

        if(tocadas==tam){//se ha tocado todo el barco

            i=0;

            while(conf[at].oponente[fO+i][cO]!=' '){

                conf[at].oponente[fO+i][cO]='H';    //vamos marcando como Hundido todas las casillas

                i++;

            }

            conf[at].casHundidas+=tam;

        }

    }

    if(conf[op].flota[f-1][c]=='X'){//El barco está en vertical (comprobando si sigue por abajo)

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i+1][c]!=' '){

            i++;    //vamos hacia arriba buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j-1][c]!=' '){

            j--;    //vamos hacia abajo hasta llegar al final del barco
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //Comprobamos si el usuario ha dado a todas las casillas
        while(conf[op].flota[fO-i][cO]!=' '){

            if(conf[at].oponente[fO-i][cO]=='T'){   //comprobamos si se han marcado como tocadas las posiciones del barco

                tocadas++;

            }

            i++;

        }

        if(tocadas==tam){//se ha tocado todo el barco

            i=0;

            while(conf[at].oponente[fO-i][cO]!=' '){

                conf[at].oponente[fO-i][cO]='H';    //vamos marcando como Hundido todas las casillas

                i++;

            }

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

}

//Cabecera: void disparoAutomatico(Configuracion*)
//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(Configuracion* conf){

    /*
        la maquina NO sabe donde esta el barco, lo que si puede suponer es que si da dos seguidas es que el barco esta
        en horizontal, vertical...
    */

}