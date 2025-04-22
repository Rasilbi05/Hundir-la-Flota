#include "Juego.h"

//Cabecera: void menuJuego(Configuracion*)
//Precondición: se debe de haber configurado el juego para poder entrar a este menú
//Postcondición: devuelve la opción que elija el usuario
void menuJuego(Configuracion* conf){

    int n,cargar;

    system("cls");

    printf("1. Jugar partida\n2. Reiniciar partida\n3. Resumen\n4. Volver\n--> ");  //mostramos al usuario las distintas opciones que tiene
    scanf("%d",&n);

    switch(n){

        case 1:

            jugarPartida(conf,cargar); //función encargada de comenzar la partida

        break;
        case 2:

            reiniciarPartida(conf,&cargar); //función encargada de reiniciar los datos de la partida

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
    
    int i=0,cont=0,resp=0, turno=0;    //i es un índice que nos servirá para poder elegir a los dos jugadores (de forma predeterminada, es el jugador1), 
    //el contador sirve para saber que hemos terminado con ambos jugadores
    //resp se utiliza para saber que opción elige el jugador
    //turno nos sirve para conocer, en caso de que se haya cargado la partida, cual de los dos jugadores es el que tiene el primer turno
    
    //cargar es un entero que sirve para saber si se ha cargado partida, si fuese así, los tableros y la partida ya estaría definida,
    //por lo que no es necesario 
    if(cargar!=1){
        //preguntamos si quieren colocar sus barcos de forma manual o automática
        while(cont<2){

            //generamos los tableros:
            conf[cont].flota=generarTablero(conf[cont].tamTablero);
            conf[cont].oponente=generarTablero(conf[cont].tamTablero);


            do{

                printf("De que forma desea colocar sus barcos %s?\n1. Manual\n2.Automatico\n--> ",conf[cont].nombre);
                scanf("%d",&resp);

                switch(resp){

                    case 1:
                        asignacionManual(conf,i);   //llamamos a la función encargada de realizar la asignación manual de los barcos
                    break;

                    case 2:
                        asignacionAutomatica(conf,i);   //llamamos a la función encargada de realizar la asignación automática de los barcos
                    break;
                    default:
                        printf("Opcion no valida, elija de nuevo.");
                        system("cls");
                    break;
                }

            }while(resp<1||resp>2);

            cont++;

        }

    }else{  //si la partida ha sido cargada, preguntamos de que jugador es el primer turno

        printf("Cual es el jugador con el primer turno?\n1. %s\n2. %s\n--> ",conf[0].nombre, conf[1].nombre);
        scanf("%d",&turno);

        //definimos quien tiene el primer turno
        if(turno-1==0)
            conf[0].comienza=1;
        else
            conf[1].comienza=1;

    }

    system("cls");

    //comprobamos si es el jugador2 el que empieza
    if(conf[1].comienza==1)
        i=1;


    int f=0,c=0,op=0,restantes,hundidas;    //f y c son las variables encargadas de las coordenadas que elija el jugador
                                                //op sirve para saber cual es el índice del oponente
                                                //restantes sirve para saber las casillas restantes que le queda al jugador i para ganar
                                                //hundidas son las casillas que ha hundido el jugador i
    if(i==0)
        op++;

    //creamos el bucle principal para el juego
    while(conf[0].ganador!=1||conf[1].ganador!=1||resp!=3){

        printf("Turno de %s:\n",conf[i].nombre);

        //vemos si el disparo es manual o automático
        if(conf[i].tipoDisparo==0){//disparo manual

            //hacemos un do-while ya que si el usuario dispara en una casilla ya marcada, debe repetir el disparo
            do{
                printf("Elija las coordenadas del disparo (de 0 a ultima casilla - 1):\n--> ");
                scanf("%d %d",&f,&c);

                if(conf[i].oponente[f][c]!=' '){

                    //pedimos al jugador que elija otra posición y le mostramos cual es el estado de la que ha elegido
                    printf("La posición elegida ya ha sido marcada (%c), por favor, elija otra.\n",conf[i].oponente[f][c]);

                }

                if(f>conf[i].tamTablero-1||c>conf[i].tamTablero-1)
                    printf("Ha superado el limite. Escoja otras coordenadas.\n");

                system("cls");

            }while(conf[i].oponente[f][c]!=' '||f>conf[i].tamTablero-1||c>conf[i].tamTablero-1);

            //comprobamos si el disparo ha sido o no agua
            if(conf[op].flota[f][c]==' '){

                conf[i].NDisparos++;
                printf("Agua\n");
                conf[i].oponente[f][c]='*';

            }else{

                
                while(conf[op].flota[f][c]!=' '){//hacemos que el jugador pueda seguir disparando hasta que de en agua
                    
                    conf[i].oponente[f][c]='T'; //marcamos en estado de 'Tocado' en el tablero oponente
                    printf("Casilla tocada!!\n");
                    
                    comprobarDisparo(conf,f,c,i,op); //comprobamos si se ha hundido un barco
                        
                    conf[i].tocadas++;      //aumentamos las casillas que ha tocado el jugador
                    conf[i].NDisparos++;
                    
                    //preguntamos si quiere guardar la partida tras disparar
                    printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar\n--> ");
                    scanf("%d",&resp);

                    if(resp==1)
                        guardarDatos(conf);

                    do{
                        printf("Elija las coordenadas del disparo (de 0 a ultima casilla - 1):\n--> ");
                        scanf("%d %d",&f,&c);
        
                        if(conf[i].oponente[f][c]!=' '){
        
                            //pedimos al jugador que elija otra posición y le mostramos cual es el estado de la que ha elegido
                            printf("La posición elegida ya ha sido marcada (%c), por favor, elija otra.\n",conf[i].oponente[f][c]);
        
                        }
        
                        if(f>conf[i].tamTablero-1||c>conf[i].tamTablero-1)
                            printf("Ha superado el limite. Escoja otras coordenadas.\n");

                        system("cls");
        
                    }while(conf[i].oponente[f][c]!=' '||f>conf[i].tamTablero-1||c>conf[i].tamTablero-1);

                }

                //como ha salido del bucle al dar en agua, se lo indicamos y lo marcamos
                printf("Agua\n");  
                conf[i].oponente[f][c]='*';
                conf[i].NDisparos++;

            }

        }else{//disparo automático

            disparoAutomatico(conf,i,op);    //llamamos a la función que realiza el disparo automático

        }

        system("cls");

        //mostramos los tableros del jugador
        MostrarTableros(conf,i);

        //preguntamos al usuario si desea continuar, guardar o salir de la partida
        printf("Desea realizar alguna de las siguientes acciones?\n1. Guardar partida y continuar\n2. Continuar sin guardar\n3. Guardar y salir\n--> ");
        scanf("%d",&resp);
        
        //a no ser de que el usuario decida no guardar, guardamos la partida
        if(resp!=2)
            guardarDatos(conf);  
        else if(resp==3)    //y si ha decidido salir, termina el juego, habiendo guardado previamente la partida y despidiendo al jugador
            printf("Saliendo de la partida, que tenga un buen dia.");
        
        
        //comprobamos si ha ganado la partida
        restantes=0;
        hundidas=0;
        for(f=0;f<conf[i].tamTablero;f++){
            
            for(c=0;c<conf[i].tamTablero;c++){
                
                if(conf[i].oponente[f][c]=='H')
                hundidas++;
                else if(conf[op].flota[f][c]=='X')
                restantes++;
                
            }
            
        }
        
        if(restantes-hundidas==0)
            conf[i].ganador=1;
        
        //este condicional nos sirve para ir intercambiando entre los turnos de los jugadores
        if(i==0){
        
            op=i;
            i++;
        
        }else{
         
            op=i;
            i--;
        
        }

        system("cls");

    }

    //mostramos por pantalla si alguien ha ganado, si es así, se muestra cual de los dos ha ganado
    for(i=0;i<2;i++){

        if(conf[i].ganador==1){

            printf("FELICIDADES %s, HAS GANADO!!!", conf[i].nombre);
               
            //mostramos un resumen de la partida
            resumenPartida(conf);
        
        }
         
    }
    
}

//Cabecera: void reiniciarPartida(Configuracion*, int* cargar)
//Precondición: Se ha jugado una partida previamente
//Postcondición: Reinicia los datos de la partida
void reiniciarPartida(Configuracion* conf,int* cargar){
    
    system("cls");

    //ponemos cargar a 1, pues si los usuarios quieren reiniciar la partida, también querran usar los datos que no se reinician
    //por lo que indicamos 
    *cargar=1;

    //reiniciamos todas las variables del usuario
    for(int i=0;i<2;i++){

        conf[i].NDisparos=0;
        conf[i].ganador=0;
        conf[i].barHundidos=0;
        conf[i].tocadas=0;
        conf[i].hundidas=0;
        conf[i].barHundidos=0;
        conf[i].barRestantes=conf[i].totalBarcos;

        //Reiniciamos los tableros marcando sus casillas como agua para que sea como un tablero recién generado
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

    //confirmamos el reinicio y volvemos al menú
    printf("Partida reiniciada.");
    system("pause");

    menuJuego(conf);    //llamamos de nuevo a la función menuJuego para que el usuario pueda iniciar la partida

}

//Cabecera: void resumenPartida(Configuracion*)
//Precondición: Resumen de la partida que se ha estado jugando
//Postcondición: devuelve un resumen de los datos de la partida jugada, si no se ha jugado, no devuelve nada
void resumenPartida(Configuracion* conf){
    int vacia;

    //mostramos por pantalla el resumen
    printf("                     |         Valor de las casillas       |                       |\n");
    printf("       Jugador       |Disparos|Vacias|Agua|Tocadas|Hundidas|Hundidos|Restan|Ganador|\n");
    printf("---------------------|--------|------|----|-------|--------|--------|------|-------|\n");
    for(int i=0;i<2;i++){

        //calculamos las casillas vacías
        vacia = pow(conf[i].tamTablero,2)-conf[i].NDisparos;

        printf(" %20s| %7d| %5d| %3d| %6d| %7d| %7d| %5d| %6d|\n",conf[i].nombre,conf[i].NDisparos,vacia,conf[i].agua,conf[i].tocadas,conf[i].hundidas,conf[i].barHundidos,conf[i].barRestantes,conf[i].ganador);

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
                    
    //cuadramos la posición de FLOTA y OPONENTE
    printf("\n%20s: FLOTA",conf[j].nombre);

        for(int m=0;m<conf[j].tamTablero*3;m++)
            printf(" ");

    printf("%8cOPONENTE\n%21c|",' ',' ');

    //imrpimimos por pantalla la primera fila que indicará el número de columna
    for(int n=0;n<2;n++){

        //si se ha llegado al final del primer tablero, ponemos los espacios necesarios para que se muestre el segundo
        if(n==1){

            printf("%5c|",' ');

        }

        //vamos imprimiendo los números
        for(c=0;c<conf[j].tamTablero;c++){

            printf("%2d|",c);

        }
    }

    //imprimimos los espacios necesarios para mostrar bien cada fila
    for(int i=0;i<conf[j].tamTablero;i++){

        printf("\n%18c|%2d|",' ',i);

        //imprimimos las filas del tablero Flota
        for(int f=0;f<conf[j].tamTablero;f++)
          printf("%2c|",conf[j].flota[i][f]);

        printf("  |%2d|",i);

        //imprimimos las filas del tablero Oponente
        for(int f=0;f<conf[j].tamTablero;f++)
            printf("%2c|",conf[j].oponente[i][f]);  

    }

    printf("\n");

}

//Cabecera: void comprobarDisparo(Configuracion*,int,int,int,int)
//Precondición: El usuario ha realizado un disparo
//Postcondición: Devuelve si el barco ha sido hundido o no
void comprobarDisparo(Configuracion* conf, int f, int c, int at, int op){

    int fO=f, cO=c,i=1,j=1,tam=1,tocadas=1,comprobado=0; //declaramos las variables para guardar las coordenadas del origen del barco
    //i nos sirve para ir comprobando las coordenadas origen
    //j nos sirve para comprobar la otra parte tras encontrar las coordenadas origen
    //tam sirve para ver el tamaño del barco (está a 1 ya que ya hemos dado a una casilla)
    //tocadas nos sirve para ver cuantas casillas están en estado 'Tocado' en nuestro tablero
    //comprobado nos sirve para saber si se ha comprobado por ese lado previamente

    /*cuando encuentro un barco, necesito saber donde empieza este, asi que compruebo todas las casillas posibles
    si se encuentra una, intento buscar en la zona opuesta a la encontrada, para ver si sigue el barco por ahí,
    sino sigo por donde he dado previamente*/

    //El barco es de tamaño 1
    if(comprobado==0&&conf[op].flota[f+1][c]!='X'&&conf[op].flota[f+1][c+1]!='X'&&conf[op].flota[f+1][c-1]!='X'&&conf[op].flota[f-1][c]!='X'&&conf[op].flota[f-1][c+1]!='X'&&conf[op].flota[f-1][c-1]!='X'&&conf[op].flota[f][c+1]!='X'&&conf[op].flota[f][c-1]!='X'){

        comprobado++;

        conf[at].oponente[f][c]='H';
        //marcamos las casillas de alrededor como Agua
        if(c-1>=0)
            conf[at].oponente[f][c-1]='*';

        if(c+1<=conf[at].tamTablero-1)
            conf[at].oponente[f][c+1]='*';

        if(f-1>=0){

            conf[at].oponente[f-1][c]='*';

            if(c-1>=0)
                conf[at].oponente[f-1][c-1]='*';

            if(c+1<=conf[at].tamTablero-1)
                conf[at].oponente[f-1][c+1]='*';

        }

        if(f+1<=conf[at].tamTablero-1){

            conf[at].oponente[f+1][c]='*';

            if(c-1>=0)
                conf[at].oponente[f+1][c-1]='*';

            if(c+1<=conf[at].tamTablero-1)
                conf[at].oponente[f+1][c+1]='*';

        }

        conf[at].hundidas++;        //aumentamos el número de casillas
        conf[at].tocadas--;          //restamos las que estaban marcadas como tocadas
        conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
        conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

    }

    //El barco está en vertical (comprobando si sigue por arriba)
    if(conf[op].flota[f-1][c]=='X'&&comprobado==0&&f-1>=0){

        comprobado++;

        if(conf[op].flota[f+1][c]=='X')
            tocadas--;

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i+1][c]!=' '&&i<conf[at].tamTablero-1){

            i++;    //vamos hacia abajo buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j-1][c]!=' '&&j>0){

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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';
            }

            while(conf[at].oponente[fO-1][cO]!=' '&&fO>0){

                if(conf[at].oponente[fO-1][cO]=='T')
                    conf[at].oponente[fO-1][cO]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO-1][cO+1]='*';

                fO--;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO-1>=0){

                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO-1][cO+1]='*';

            }

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en vertical (comprobando si sigue por abajo)
    if(conf[op].flota[f+1][c]=='X'&&comprobado==0&&f+1<conf[at].tamTablero){

        comprobado++;

        i=f;
        j=f;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[i-1][c]!=' '&&i>0){

            i--;    //vamos hacia arriba buscando el origen del barco
            tam++;

        }

        fO=i;   //tenemos la coordenada X origen, la Y ya la tenemos ya que está en vertical

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[j+1][c]!=' '&&j<conf[at].tamTablero-1){

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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO-1>=0){
                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO-1][cO+1]='*';
            }

            while(conf[at].oponente[fO+1][cO]!=' '&&fO<conf[at].tamTablero-1){

                if(conf[at].oponente[fO+1][cO]=='T')
                    conf[at].oponente[fO+1][cO]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

                fO++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';
            }

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en horizontal (comprobando si sigue por la izquierda)
    if(conf[op].flota[f][c-1]=='X'&&comprobado==0&&c-1>=0){

        comprobado++;

        //comprobamos si la casilla se encuentra en el medio del barco,
        //ya que por la forma de recorrer el barco al comprobar si se encuentra en el medio la casilla la sumará de nuevo
        if(conf[op].flota[f][c+1]=='X')
            tocadas--;

        i=c;
        j=c;
        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[f][i+1]!=' '&&i<conf[at].tamTablero-1){

            i++;    //vamos hacia la derecha buscando el origen del barco
            tam++;

        }

        cO=i;   //tenemos la coordenada Y origen, la X ya la tenemos ya que está en horizontal

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[f][j-1]!=' '&&j>0){

            j--;    //vamos hacia la izquierda hasta llegar al final del barco
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //Comprobamos si el usuario ha dado a todas las casillas
        while(conf[op].flota[fO][cO-i]!=' '){

            if(conf[at].oponente[fO][cO-i]=='T'){   //comprobamos si se han marcado como tocadas las posiciones del barco

                tocadas++;

            }

            i++;

        }

        if(tocadas==tam){//se ha tocado todo el barco

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(fO-1>=0){
                conf[at].oponente[fO-1][cO]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO-1][cO+1]='*';

            }

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';
            }

            while(conf[at].oponente[fO][cO-1]!=' '&&cO>0){

                if(conf[at].oponente[fO][cO-1]=='T')
                    conf[at].oponente[fO][cO-1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                if(fO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';
                if(fO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO-1]='*';

                cO--;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(cO-1>=0){
                conf[at].oponente[fO][cO-1]='*';

                if(fO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';
                    
                if(fO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO-1]='*';

                
            }

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en horizontal (comprobando si sigue por la derecha)
    if(conf[op].flota[f][c+1]=='X'&&comprobado==0&&c+1<conf[at].tamTablero){

        comprobado++;

        i=c;
        j=c;

        //comprobamos cuales son las coordenadas iniciales
        while(conf[op].flota[f][i-1]!=' '&&i>0){

            i--;    //vamos hacia la izquierda buscando el origen del barco
            tam++;

        }

        cO=i;   //tenemos la coordenada y origen, la X ya la tenemos ya que está en horizontal

        //comprobamos el resto para determinar el tamaño total del barco
        while(conf[op].flota[f][j+1]!=' '&&j<conf[at].tamTablero-1){

            j++;    //vamos hacia la derecha hasta llegar al final del barco
            tam++;

        }

        i=1;    //reiniciamos la variable i

        //Comprobamos si el usuario ha dado a todas las casillas
        while(conf[op].flota[fO][cO+i]!=' '){

            if(conf[at].oponente[fO][cO+i]=='T'){   //comprobamos si se han marcado como tocadas las posiciones del barco

                tocadas++;

            }

            i++;

        }

        if(tocadas==tam){//se ha tocado todo el barco

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(fO-1>=0){

                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

            }

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';
            }

            while(conf[at].oponente[fO][cO+1]!=' '&&cO<conf[at].tamTablero-1){

                if(conf[at].oponente[fO][cO+1]=='T')
                    conf[at].oponente[fO][cO+1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                if(fO-1>=0)
                    conf[at].oponente[fO-1][cO+1]='*';
                
                if(fO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

                cO++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(cO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO][cO+1]='*';

                if(fO-1>=0)
                conf[at].oponente[fO-1][cO+1]='*';

                if(fO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

            }

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en diagonal (comprobando si sigue por arriba-izquierda)
    if(conf[op].flota[f-1][c-1]=='X'&&comprobado==0&&f-1>=0&&c-1>=0){

        comprobado++;

        //comprobamos si la casilla se encuentra en el medio del barco,
        //ya que por la forma de recorrer el barco al comprobar si se encuentra en el medio la casilla la sumará de nuevo
        if(conf[op].flota[f+1][c+1]=='X')
            tocadas--;


        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f+1][c+1]!=' '&&f<conf[at].tamTablero-1&&c<conf[at].tamTablero-1){

            //vamos avanzando en diagonal hacia abajo-derecha
            f++;
            c++;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i-1][j-1]!=' '&&i>0&&j>0){

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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

            }

            if(fO-1>=0){
                conf[at].oponente[fO-1][cO]='*';

                if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO-1][cO+1]='*';

            }

            while(conf[at].oponente[fO-1][cO-1]!=' '&&fO>0&&cO>0){

                if(conf[at].oponente[fO-1][cO-1]=='T')
                    conf[at].oponente[fO-1][cO-1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor

                if(cO-1-1>=0){

                    conf[at].oponente[fO-1][cO-1-1]='*';
                    conf[at].oponente[fO-1+1][cO-1-1]='*';

                }

                if(fO-1-1>=0){

                    conf[at].oponente[fO-1-1][cO-1]='*';
                    conf[at].oponente[fO-1-1][cO-1+1]='*';

                }

                fO--;
                cO--;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO-1>=0&&cO-1>=0)
                conf[at].oponente[fO-1][cO-1]='*';

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en diagonal (comprobando si sigue por arriba-derecha)
    if(conf[op].flota[f-1][c+1]=='X'&&comprobado==0&&f-1>=0&&c+1<conf[at].tamTablero){

        comprobado++;

        //comprobamos si la casilla se encuentra en el medio del barco,
        //ya que por la forma de recorrer el barco al comprobar si se encuentra en el medio la casilla la sumará de nuevo
        if(conf[op].flota[f+1][c-1]=='X')
            tocadas--;


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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

            }

            if(fO-1>=0){

                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

            }

            while(conf[at].oponente[fO-1][cO+1]!=' '&&fO>0&&cO<conf[at].tamTablero-1){

                if(conf[at].oponente[fO-1][cO+1]=='T')
                    conf[at].oponente[fO-1][cO+1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                if(fO-1-1>=0){

                    conf[at].oponente[fO-1-1][cO+1]='*';
                    conf[at].oponente[fO-1-1][cO+1-1]='*';

                }

                if(cO+1+1<=conf[at].tamTablero-1){

                    conf[at].oponente[fO-1][cO+1+1]='*';
                    conf[at].oponente[fO-1+1][cO+1+1]='*';

                }

                fO--;
                cO++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO-1>=0&&cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO-1][cO+1]='*';

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }

    }

    //El barco está en diagonal (comprobando si sigue por abajo-izquierda)
    if(conf[op].flota[f+1][c-1]=='X'&&comprobado==0&&f+1<conf[at].tamTablero&&c-1>=0){

        comprobado++;

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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO-1>=0){

                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO-1][cO+1]='*';

            }

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO+1][cO+1]='*';

            }

            while(conf[at].oponente[fO+1][cO-1]!=' '&&fO<conf[at].tamTablero-1&&cO>0){

                if(conf[at].oponente[fO+1][cO-1]=='T')
                    conf[at].oponente[fO+1][cO-1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor
                if(cO-1-1>=0){

                    conf[at].oponente[fO+1][cO-1-1]='*';
                    conf[at].oponente[fO+1-1][cO-1-1]='*';

                }

                if(fO+1+1<=conf[at].tamTablero-1){

                    conf[at].oponente[fO+1+1][cO-1]='*';
                    conf[at].oponente[fO+1+1][cO-1+1]='*';

                }

                fO++;
                cO--;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO+1<=conf[at].tamTablero-1&&cO-1>=0)
                conf[at].oponente[fO+1][cO-1]='*';

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
            conf[at].barRestantes--;    //resto 1 a los barcos restantes para que gane
            conf[op].barHundidos++;     //suma 1 a los barcos que tiene hundidos el oponente

        }


    }

    //El barco está en diagonal (comprobamos si sigue por abajo-derecha)
    if(conf[op].flota[f+1][c+1]=='X'&&comprobado==0&&f+1<conf[at].tamTablero&&c+1<conf[at].tamTablero){

        comprobado++;

        i=f;
        j=c;

        //buscamos el origen del barco
        while(conf[op].flota[f-1][c-1]!=' '&&f>0&&c>0){

            //vamos avanzando en diagonal hacia arriba-izquierda
            f--;
            c--;

            tam++;

        }

        fO=f;
        cO=c;

        //calculamos el tamaño del barco
        while(conf[op].flota[i+1][j+1]!=' '&&i<conf[at].tamTablero-1&&j<conf[at].tamTablero-1){

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

            //primero, marcamos las casillas cercanas al origen del barco como Agua, y la casilla de origen como Hundido
            conf[at].oponente[fO][cO]='H';

            if(cO-1>=0)
                conf[at].oponente[fO][cO-1]='*';

            if(cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO][cO+1]='*';

            if(fO-1>=0){

                conf[at].oponente[fO-1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO-1][cO-1]='*';

                if(cO+1<=conf[at].tamTablero-1)
                    conf[at].oponente[fO-1][cO+1]='*';

            }

            if(fO+1<=conf[at].tamTablero-1){

                conf[at].oponente[fO+1][cO]='*';

                if(cO-1>=0)
                    conf[at].oponente[fO+1][cO-1]='*';

            }

            while(conf[at].oponente[fO+1][cO+1]!=' '&&fO<conf[at].tamTablero-1&&cO<conf[at].tamTablero-1){

                if(conf[at].oponente[fO+1][cO+1]=='T')
                    conf[at].oponente[fO+1][cO+1]='H';    //vamos marcando como Hundido todas las casillas

                //marcamos como Agua las casillas de alrededor

                if(cO+1+1<=conf[at].tamTablero-1){

                    conf[at].oponente[fO+1][cO+1+1]='*';
                    conf[at].oponente[fO+1-1][cO+1+1]='*';
                }

                if(fO+1+1<=conf[at].tamTablero-1){

                    conf[at].oponente[fO+1+1][cO+1]='*';
                    conf[at].oponente[fO+1+1][cO+1-1]='*';

                }

                fO++;
                cO++;

            }

            //marcamos las casillas alrededor de la casilla final del barco como Agua
            if(fO+1<=conf[at].tamTablero-1&&cO+1<=conf[at].tamTablero-1)
                conf[at].oponente[fO+1][cO+1]='*';

            conf[at].hundidas+=tam;        //aumentamos el número de casillas
            conf[at].tocadas-=tam;          //restamos las que estaban marcadas como tocadas
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

    int x,y, resp=0,sX,sY,pDisparo=0;
                             //x e y son las coordenadas que elige la máquina
                            //resp nos sirve para saber si el usuario quiere guardar
                            //sX y sY nos sirve para saber el sentido que va elegir la máquina tras acertar el disparo
                            //pDisparo es para comprobar si es la primera vez que se ha disparado a un barco

    //comprobamos si ya se ha disparado previamente o no
    for(int i=0;i<conf[at].tamTablero;i++){

        for(int j=0;j<conf[at].tamTablero;j++){
            //comprobamos que ya se ha disparado previamente y guardamos la coordenada
            if(conf[at].oponente[i][j]=='T'){

                pDisparo++;

                //como hemos encontrado un barco tocado, guardamos las coordenadas para seguir desde ahí
                x=i;
                y=j;


            }

        }

    }


    if(pDisparo==0){

        //llamamos a la función encargada del primer disparo
        primerDisparo(conf,&x,&y,at,op,&sX,&sY);

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

        if(conf[at].oponente[x-1][y-1]==' '){//El barco sigue por abajo-izquierda

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

        x+=sX;
        y+=sY;

    }

    while(conf[op].flota[x][y]!=' '){//hacemos que la máquina pueda seguir disparando hasta que de en agua

        printf("Casilla tocada.\n");
    
        conf[at].tocadas++; //aumentamos el número de casillas tocadas
        conf[at].NDisparos++;

        //marcamos como tocado
        conf[at].oponente[x][y]='T';

        comprobarDisparo(conf,x,y,at,op); //comprobamos si se ha hundido un barco

        //preguntamos si quiere guardar la partida tras disparar
        printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar\n--> ");
        scanf("%d",&resp);

        if(resp==1)
            guardarDatos(conf);

        //disparamos en el sentido que la máquina ha elegido
        x+=sX;
        y+=sY;

        //si la siguiente casilla está marcada por agua, indicará que el barco se ha hundido, por lo que buscamos otra posición
        if(conf[at].oponente[x][y]=='*')
            primerDisparo(conf,&x,&y,at,op,&sX,&sY);


    }

    conf[at].NDisparos++;
    printf("\nAgua\n");
    conf[at].oponente[x][y]='*';

}

//Cabecera: primerDisparo(Configuracion*, int, int, int, int, int, int)
//Precondición: el sistema va a realizar el primer disparo ya que no hay ningún barco tocado
//Postcondición: realiza el primer disparo del sistema
void primerDisparo(Configuracion* conf, int* x, int* y, int at, int op, int* sX, int* sY){

    int resp=0;

    //hacemos que la máquina elija las coordenadas
    do{

        //hacemos que los números varíen en cada ejecución
        srand(time(NULL));
        *x = rand() % conf[at].tamTablero;   //elige un número entre 0 y tamTablero-1
        *y = rand() % conf[at].tamTablero;   //elige un número entre 0 y tamTablero-1

    }while(conf[at].oponente[*x][*y]!=' ');

    //La máquina dispara
    if(conf[op].flota[*x][*y]!=' '){  //acierta el tiro
            
        printf("Casilla tocada\n");

        conf[at].tocadas++; //aumentamos el número de casillas tocadas
        conf[at].NDisparos++;

        conf[at].oponente[*x][*y]='T'; //marcamos en estado de 'Tocado' en el tablero oponente

        comprobarDisparo(conf,*x,*y,at,op); //comprobamos si se ha hundido un barco

        //preguntamos si quiere guardar la partida tras disparar
        printf("Desea guardar la partida?\n1. Guardar partida\n2.Continuar sin guardar\n--> ");
        scanf("%d",&resp);

        if(resp==1)
            guardarDatos(conf);

        //la máquina decide donde disparar tras su primer disparo
        srand(time(NULL));
        *sX=(rand() % 3) - 1;    //elegimos un valor entre [-1,1]
        *sY=(rand() % 3) - 1;    //elegimos un valor entre [-1,1]

        //realizamos los cambios en las coordenadas
        *x+= *sX;
        *y+= *sY;

    }

}

