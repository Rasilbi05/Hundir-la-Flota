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
    int i=0,cont=0,resp=0;    //i es un índice que nos servirá para poder elegir a los dos jugadores (de forma predeterminada, es el jugador1), 
    //el contador sirve para saber que hemos terminado con ambos jugadores
    //resp se utiliza para saber que opción elige el jugador
    
    //comprobamos si es el jugador2 el que empieza
    if(conf[1].comienza==1)
        i=1;

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
            if(resp==1){

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
        if(conf[i].tipoDisparo==0){//disparo manual

            //hacemos un do-while ya que si el usuario dispara en una casilla ya marcada, debe repetir el disparo
            do{
                printf("Elija las coordenadas del disparo:\n--> ");
                scanf("%d %d",&f,&c);

                if(conf[i].oponente[f][c]!=' '){

                    //pedimos al jugador que elija otra posición y le mostramos cual es el estado de la que ha elegido
                    printf("La posición elegida ya ha sido marcada (%c), por favor, elija otra.\n",conf[i].oponente[f][c]);

                }

            }while(conf[i].oponente[f][c]!=' ');

            //comprobamos si el disparo ha sido o no agua
            if(conf[op].flota[f][c]==' '){

                printf("\nAgua\n");
                conf[i].oponente[f][c]='*';

            }else{

                conf[i].oponente[f][c]='T'; //marcamos en estado de 'Tocado' en el tablero oponente
                
                while(conf[op].flota[f][c]!=' '){//hacemos que el jugador pueda seguir disparando hasta que de en agua
                    
                    comprobarDisparo(conf,f,c,i,op); //comprobamos si se ha hundido un barco
                    
                    do{

                        //preguntamos si quiere guardar la partida tras disparar
                        printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar");
                        scanf("%d",resp);

                        if(resp==1)
                            guardarDatos(conf);

                        printf("Elija las coordenadas del disparo:\n--> ");
                        scanf("%d %d",&f,&c);
        
                        if(conf[i].oponente[f][c]!=' '){

                            //pedimos al jugador que elija otra posición y le mostramos cual es el estado de la que ha elegido
                            printf("La posición elegida ya ha sido marcada (%c), por favor, elija otra.\n",conf[i].oponente[f][c]);
        
                        }
        
                    }while(conf[i].oponente[f][c]!=' ');

                }

                //como ha salido del bucle al dar en agua, se lo indicamos y lo marcamos
                printf("\nAgua\n");  
                conf[i].oponente[f][c]='*';

            }

            //preguntamos si quiere guardar la partida tras disparar
            printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar");
            scanf("%d",resp);

        if(resp==1)
            guardarDatos(conf);

        }else{//disparo automático

            disparoAutomatico(conf,f,c,i,op);    //llamamos a la función que realiza el disparo automático

        }

        //mostramos los tableros del jugador
        MostrarTableros(conf,i);


        //este condicional nos sirve para ir intercambiando entre los turnos de los jugadores
        if(i==0){
        
            op=i;
            i++;
        
        }else{
         
            op=i;
            i--;
        
        }

    }

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
    int vacia,hundidas;

    //mostramos por pantalla el resumen
    printf("                       |         Valor de las casillas       |                       |\n");
    printf("        Jugador        |Disparos|Vacías|Agua|Tocadas|Hundidas|Hundidos|Restan|Ganador|\n");
    printf("-----------------------|--------|------|----|-------|--------|--------|------|-------|\n");
    for(int i=0;i<2;i++){

        //marcamos primero como las casillas hundidas a 0
        hundidas=0;

        //vemos el número de casillas hundidas del jugador
        for(int f = 0;f<conf[i].tamTablero;f++){
         
            for(int c=0;c<conf[i].tamTablero;c++){

                //si la casilla está marcada como hundida, aumentamos hundidas
                if(conf[i].oponente[f][c]=='H')
                    hundidas++;

        
            }

        }

        //calculamos las casillas vacías
        vacia = conf[i].NDisparos-pow(conf[i].tamTablero,2);

        printf("%s                     |     %d|   %d| %d|    %d|     %d|     %d|   %d|    %d|\n",conf[i].nombre,conf[i].NDisparos,vacia,conf[i].agua,conf[i].tocadas,hundidas,conf[i].barHundidos,conf[i].barRestantes,conf[i].ganador);

    }

    //hacemos un bucle principal para poder mostrar los datos de ambos jugadores
    for(int j=0;j<2;j++){

        MostrarTableros(conf,j);    //llamamos a la función encargada de mostrar los tableros del jugador
        printf("\n");
        
    }
    
    //le pedimos al usuario que confirme pulsando una tecla para poder continuar 
    system("Pause");
    system("cls");

}

//Cabecera: void MostrarTableros(Configuracion*,int)
//Precondición: se solicita ver el tablero del jugador
//Postcondición: muestra los tableros Flota y Oponente del jugador
void MostrarTableros(Configuracion* conf, int j){

    int c=0;    //c se refiere a la casilla

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
    si se encuentra una, intento buscar en la zona opuesta a la encontrada, para ver si sigue el barco por ahí,
    sino sigo por donde he dado previamente*/

    //El barco es de tamaño 1
    if(conf[op].flota[f-1][c]==' '&&conf[op].flota[f+1][c]==' '&&conf[op].flota[f][c-1]==' '&&conf[op].flota[f][c+1]==' '&&conf[op].flota[f-1][c-1]==' '&&conf[op].flota[f-1][c+1]==' '&&conf[op].flota[f+1][c-1]==' '&&conf[op].flota[f+1][c+1]==' '){

        //marcamos las casillas de alrededor como Agua
        conf[op].flota[f-1][c]='*';
        conf[op].flota[f+1][c]='*';
        conf[op].flota[f][c-1]='*';
        conf[op].flota[f][c+1]='*';
        conf[op].flota[f-1][c-1]='*';
        conf[op].flota[f-1][c+1]='*';
        conf[op].flota[f+1][c-1]='*';
        conf[op].flota[f+1][c+1]='*';

        conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
        conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
        conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

    }

    //El barco está en vertical (comprobando si sigue por arriba)
    if(conf[op].flota[f-1][c]=='X'){

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i+1][c]!=' '){

            i++;    //vamos hacia abajo buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j-1][c]!=' '){

            j--;    //vamos hacia arriba hasta llegar al final del barco
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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO-1]='*';
            conf[at].oponente[fO+1][cO+1]='*';

            while(conf[at].oponente[fO-i][cO]!=' '){

                conf[at].oponente[fO-i][cO]='H';    //vamos marcando como Hundido todas las casillas
                
                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO-i][cO-1]='*';
                conf[at].oponente[fO-i][cO+1]='*';

                i++;

            }
            
            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO-i][cO]='*';
            conf[at].oponente[fO-i][cO-1]='*';
            conf[at].oponente[fO-i][cO+1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        }

    }

    //El barco está en vertical (comprobando si sigue por abajo)    
    if(conf[op].flota[f+1][c]=='X'){

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i-1][c]!=' '){

            i--;    //vamos hacia arriba buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j+1][c]!=' '){

            j++;    //vamos hacia abajo hasta llegar al final del barco
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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO-1][cO-1]='*';
            conf[at].oponente[fO-1][cO+1]='*';

            while(conf[at].oponente[fO+i][cO]!=' '){

                conf[at].oponente[fO+i][cO]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO+i][cO-1]='*';
                conf[at].oponente[fO+i][cO+1]='*';

                i++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO-1]='*';
            conf[at].oponente[fO+1][cO+1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en horizontal (comprobando si sigue por la izquierda)
    if(conf[op].flota[f][c-1]=='X'){

        i=c;
        f=c;

        //Comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[f][i+1]!=' '){

            i++;    //vamos avanzando hacia la derecha
            tam++;

        }

        cO=i;   //tenemos la coordenada Y origen, la X ya la tenemos ya que está en horizontal

        //comprobamos el resto para determinar el tamaño del barco
        while(conf[op].flota[f][j-1]!=' '){

            j--;    //vamos avanzando hacia la izquierda
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //comprobamos si el jugador ha tocado todas las casillas del barco
        while(conf[op].flota[fO][cO-i]!=' '){

            if(conf[at].oponente[fO][cO-i]=='T'){

                tocadas++;

            }

            i++;
            
        }

        //si ha dado a todas, marcamos el barco como hundido
        if(tam==tocadas){

            i=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO-1][cO+1]='*';
            conf[at].oponente[fO+1][cO+1]='*';

            while(conf[at].oponente[fO][cO-i]!=' '){

                conf[at].oponente[fO][cO-i]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO+1][cO-i]='*';
                conf[at].oponente[fO-1][cO-i]='*';

                i++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO+1][cO-1]='*';
            conf[at].oponente[fO-1][cO-1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //El barco está en horizontal (comprobando si sigue por la derecha)
    if(conf[op].flota[f][c+1]=='X'){

        i=c;
        f=c;

        //Comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[f][i-1]!=' '){

            i--;    //vamos avanzando hacia la izquierda
            tam++;

        }

        cO=i;   //tenemos la coordenada Y origen, la X ya la tenemos ya que está en horizontal

        //comprobamos el resto para determinar el tamaño del barco
        while(conf[op].flota[f][j+1]!=' '){

            j++;    //vamos avanzando hacia la derecha
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //comprobamos si el jugador ha tocado todas las casillas del barco
        while(conf[op].flota[fO][cO+i]!=' '){

            if(conf[at].oponente[fO][cO+i]=='T'){

                tocadas++;

            }

            i++;
            
        }

        //si ha dado a todas, marcamos el barco como hundido
        if(tam==tocadas){

            i=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO-1][cO-1]='*';
            conf[at].oponente[fO+1][cO-1]='*';

            while(conf[at].oponente[fO][cO+i]!=' '){

                conf[at].oponente[fO][cO+i]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO+1][cO+i]='*';
                conf[at].oponente[fO-1][cO+i]='*';

                i++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO+1][cO+1]='*';
            conf[at].oponente[fO-1][cO+1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //El barco está en diagonal (comprobando si sigue por arriba-izquierda)
    if(conf[op].flota[f-1][c-1]=='X'){

        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f+1][c+1]!=' '){

            //vamos avanzando en diagonal hacia abajo-derecha
            f++;
            c++;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i-1][j-1]!=' '){

            //vamos avanzando en diagonal hacia arriba-izquierda
            i--;
            j--;
            
            tam++;

        }

        //reiniciamos las variables
        i=1;
        j=1;

        //comprobamos si el jugador ha tocado todas las casillas
        while(conf[op].flota[fO-i][cO-j]!=' '){

            if(conf[at].oponente[fO-i][cO-j]=='T'){

                tocadas++;  //comprobamos si se han marcado como tocadas las posiciones del barco

            }

            i++;
            j++;

        }

        //comprobamos si se ha hundido el barco
        if(tam==tocadas){

            i=0;
            j=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO-1]='*';
            conf[at].oponente[fO+1][cO+1]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO-1][cO+1]='*';

            while(conf[at].oponente[fO-i][cO-j]!=' '){

                conf[at].oponente[fO-i][cO-j]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO-i][cO-j-1]='*';
                conf[at].oponente[fO-i+1][cO-j-1]='*';
                conf[at].oponente[fO-i-1][cO-j]='*';
                conf[at].oponente[fO-i-1][cO-j+1]='*';

                i++;
                j++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO-i-1][cO-j-1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //El barco está en diagonal (comprobando si sigue por arriba-derecha)
    if(conf[op].flota[f-1][c+1]=='X'){

        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f+1][c-1]!=' '){

            //vamos avanzando en diagonal hacia abajo-izquierda
            f++;
            c--;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i-1][j+1]!=' '){

            //vamos avanzando en diagonal hacia arriba-derecha
            i--;
            j++;
            
            tam++;

        }

        //reiniciamos las variables
        i=1;
        j=1;

        //comprobamos si el jugador ha tocado todas las casillas
        while(conf[op].flota[fO-i][cO+j]!=' '){

            if(conf[at].oponente[fO-i][cO+j]=='T'){

                tocadas++;  //comprobamos si se han marcado como tocadas las posiciones del barco

            }

            i++;
            j++;

        }

        //comprobamos si se ha hundido el barco
        if(tam==tocadas){

            i=0;
            j=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO-1][cO-1]='*';
            conf[at].oponente[fO-1][cO+1]='*';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO-1]='*';

            while(conf[at].oponente[fO-i][cO+j]!=' '){

                conf[at].oponente[fO-i][cO+j]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO-i][cO-j+1]='*';
                conf[at].oponente[fO-i+1][cO-j+1]='*';
                conf[at].oponente[fO-i-1][cO-j]='*';
                conf[at].oponente[fO-i-1][cO-j-1]='*';

                i++;
                j++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO-i-1][cO-j+1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //El barco está en diagonal (comprobando si sigue por abajo-izquierda)
    if(conf[op].flota[f+1][c-1]=='X'){

        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f-1][c+1]!=' '){

            //vamos avanzando en diagonal hacia arriba-derecha
            f--;
            c++;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i+1][j-1]!=' '){

            //vamos avanzando en diagonal hacia abajo-izquierda
            i++;
            j--;
            
            tam++;

        }

        //reiniciamos las variables
        i=1;
        j=1;

        //comprobamos si el jugador ha tocado todas las casillas
        while(conf[op].flota[fO+i][cO-j]!=' '){

            if(conf[at].oponente[fO+i][cO-j]=='T'){

                tocadas++;  //comprobamos si se han marcado como tocadas las posiciones del barco

            }

            i++;
            j++;

        }

        //comprobamos si se ha hundido el barco
        if(tam==tocadas){

            i=0;
            j=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO-1][cO-1]='*';
            conf[at].oponente[fO-1][cO+1]='*';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO+1]='*';

            while(conf[at].oponente[fO+i][cO-j]!=' '){

                conf[at].oponente[fO+i][cO-j]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO-i][cO-j-1]='*';
                conf[at].oponente[fO-i-1][cO-j-1]='*';
                conf[at].oponente[fO-i+1][cO-j]='*';
                conf[at].oponente[fO-i+1][cO-j+1]='*';

                i++;
                j++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO-i+1][cO-j-1]='*';

            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //El barco está en diagonal (comprobamos si sigue por abajo-derecha)
    if(conf[op].flota[f+1][c+1]=='X'){

        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f-1][c-1]!=' '){

            //vamos avanzando en diagonal hacia arriba-izquierda
            f--;
            c--;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i+1][j+1]!=' '){

            //vamos avanzando en diagonal hacia abajo-derecha
            i++;
            j++;
            
            tam++;

        }

        //reiniciamos las variables
        i=1;
        j=1;

        //comprobamos si el jugador ha tocado todas las casillas
        while(conf[op].flota[fO+i][cO+j]!=' '){

            if(conf[at].oponente[fO+i][cO+j]=='T'){

                tocadas++;  //comprobamos si se han marcado como tocadas las posiciones del barco

            }

            i++;
            j++;

        }

        //comprobamos si se ha hundido el barco
        if(tam==tocadas){

            i=0;
            j=0;

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';
            conf[at].oponente[fO][cO-1]='*';
            conf[at].oponente[fO][cO+1]='*';
            conf[at].oponente[fO-1][cO]='*';
            conf[at].oponente[fO-1][cO-1]='*';
            conf[at].oponente[fO-1][cO+1]='*';
            conf[at].oponente[fO+1][cO]='*';
            conf[at].oponente[fO+1][cO-1]='*';

            while(conf[at].oponente[fO+i][cO+j]!=' '){

                conf[at].oponente[fO+i][cO+j]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                conf[at].oponente[fO-i][cO-j+1]='*';
                conf[at].oponente[fO-i-1][cO-j+1]='*';
                conf[at].oponente[fO-i+1][cO-j]='*';
                conf[at].oponente[fO-i+1][cO-j-1]='*';

                i++;
                j++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            conf[at].oponente[fO-i+1][cO-j+1]='*';


            conf[at].casHundidas+=tam;  //aumentamos el número de casillas que ha hundido
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente
        

        }

    }

    //hacemos un último if para mostrar por pantalla si se ha hundido el barco
    if(tam==tocadas){

        printf("\nBarco hundido.\n");

    }

}

//Cabecera: void disparoAutomatico(Configuracion*,int,int)
//Precondición: El usuario ha elegido que haya disparo automático
//Postcondición: El programa realiza los disparos de forma autática
void disparoAutomatico(Configuracion* conf, int at, int op){

    int i=0,j=0, x=0,y=0, resp=0,sX=0,sY=0,pDisparo=0;  //i y j nos sirven para comprobar si se ha disparado previamente
                             //x e y son las coordenadas que elige la máquina
                            //resp nos sirve para saber si el usuario quiere guardar
                            //sX y sY nos sirve para saber el sentido que va elegir la máquina tras acertar el disparo
                            //pDisparo es para comprobar si es la primera vez que se ha disparado a un barco

    //comprobamos si ya se ha disparado previamente o no
    while(conf[at].oponente[i][j]!='T'||i<conf[at].tamTablero){

        while(conf[at].oponente[i][j]!='T'||j<conf[at].tamTablero){
            //comprobamos que ya se ha disparado previamente y guardamos la coordenada
            if(conf[at].oponente[i][j]=='T'){
            
                pDisparo++;
                
                //como hemos encontrado un barco tocado, guardamos las coordenadas para seguir desde ahí
                x=i;
                y=j;

            }

            j++;
            
        }
        
        i++;
    }

    if(pDisparo==0){
        
        //llamamos a la función encargada del primer disparo
        primerDisparo(conf,x,y,at,op,sX,sY);

    }else{

        //comprobamos por donde puede seguir el barco 
        if(conf[at].oponente[x+1][y]==' '){//El barco puede que siga por arriba

            sX=1;
            sY=0;

        }     
        
        if(conf[at].oponente[x+1][y+1]==' '){//El barco puede que siga por arriba-derecha
        
            sX=1;
            sY=1;
        
        }

        if(conf[at].oponente[x+1][y-1]==' '){//El barco puede que siga por arriba-izquierda
            
            sX=1;
            sY=-1;
        
        }

        if(conf[at].oponente[x-1][y]==' '){//El barco puede que siga por abajo
            
            sX=-1;
            sX=0;
            
        }

        if(conf[at].oponente[x-1][y+1]==' '){//El barco puede que siga por abajo-derecha
            
            sX=-1;
            sY=1;
        
        }

        if(conf[at].oponente[x-1][y-1]==' '){//El barco sigue por abajo-derecha
        
            sX=-1;
            sY=-1;
        
        }

        if(conf[at].oponente[x][y+1]==' '){//El barco sigue por la derecha
            
            sX=0;
            sY=1;
        
        }

        if(conf[at].oponente[x][y-1]==' '){//El barco sigue por la izquierda
        
            sX=0;
            sY=-1;
        
        }

    }


    while(conf[op].flota[x][y]!=' '){//hacemos que la máquina pueda seguir disparando hasta que de en agua

        
        comprobarDisparo(conf,x,y,at,op); //comprobamos si se ha hundido un barco
        
        //preguntamos si quiere guardar la partida tras disparar
        printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar");
        scanf("%d",resp);
        
        
        if(resp==1)
        guardarDatos(conf);
        
        //disparamos en el sentido que la máquina ha elegido
        x+=sX;
        y+=sY;
        
        //si la siguiente casilla está marcada por agua, indicará que el barco se ha hundido, por lo que buscamos otra posición
        if(conf[at].oponente[x][y]=='*')
            primerDisparo(conf,x,y,at,op,sX,sY)
    
    }

    printf("\nAgua\n");  
    conf[at].oponente[x][y]='*';

}


//Cabecera: primerDisparo(Configuracion*, int, int, int, int, int, int)
//Precondición: el sistema va a realizar el primer disparo ya que no hay ningún barco tocado
//Postcondición: realiza el primer disparo del sistema
void primerDisparo(Configuracion* conf, int x, int y, int at, int op, int sX, int sY){

    int resp=0;

    //hacemos que la máquina elija las coordenadas
    do{

        //hacemos que los números varíen en cada ejecución
        srand(time(NULL));
        x = rand() % conf[at].tamTablero;   //elige un número entre 0 y tamTablero-1
        
        //hacemos que los números varíen en cada ejecución
        srand(time(NULL));
        y = rand();                         //elige un número entre 0 y tamTablero-1

    }while(conf[at].oponente[x][y]!=' ');

    //La máquina dispara
    if(conf[op].flota[x][y]==' '){  //da en agua

        printf("\nAgua\n");
        conf[at].oponente[x][y]='*';

    }else{  //acierta el tiro

        conf[at].oponente[x][y]='T'; //marcamos en estado de 'Tocado' en el tablero oponente

        comprobarDisparo(conf,x,y,at,op); //comprobamos si se ha hundido un barco

        //preguntamos si quiere guardar la partida tras disparar
        printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar");
        scanf("%d",resp);

        if(resp==1)
        guardarDatos(conf);

        //la máquina decide donde disparar tras su primer disparo
        srand(time(NULL));
        sX=(rand() % 3) - 1;    //elegimos un valor entre [-1,1]
        srand(time(NULL));
        sY=(rand() % 3) - 1;    //elegimos un valor entre [-1,1]

        //realizamos los cambios en las coordenadas
        x+=sX;
        y+=sY;
        
    }

}