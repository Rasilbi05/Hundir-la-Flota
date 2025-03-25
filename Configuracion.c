#include "Configuracion.h"


void menuConfiguracion(Configuracion *datos){
    int opcion;
    while(opcion != 5){     //Bucle para mostrar el menu de configuracion, sale de el cuando se elige la opcion 5
        do{
            system("cls");
            printf("1. Introducir datos\n");
            printf("2. Mostrar datos\n");
            printf("3. Guardar datos\n");
            printf("4. Cargar datos\n");
            printf("5. Salir\n");
            printf("Introduce una opcion: ");
            scanf("%d", &opcion);
            switch(opcion){
                case 1:
                    introducirDatos(datos);
                    break;
                case 2:
                    mostrarDatos(datos);
                    break;
                case 3:
                    guardarDatos(datos);
                    break;
                case 4:
                    cargarDatos(datos);
                    break;
                case 5:
                    break;
                default:
                    printf("Opcion no valida\n");
                    break;
            }
        }while(opcion < 1 || opcion > 5);
    }
}

void introducirDatos(Configuracion* configuracion){
    int aux = 0, suma = 0, comienza = 0;        //Variables auxiliares para el numero de barcos y la suma de ellos y para saber quien comienza
    
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
    scanf("%d", &aux);
    suma += aux;
    configuracion[0].NPortaaviones = aux;
    configuracion[1].NPortaaviones = aux;
    printf("Introduce el numero de Acorazados: ");
    scanf("%d", &aux);
    suma += aux;
    configuracion[0].NAcorazado = aux;
    configuracion[1].NAcorazado = aux;
    printf("Introduce el numero de Cruceros: ");
    scanf("%d", &aux);
    suma += aux;
    configuracion[0].NCrucero = aux;
    configuracion[1].NCrucero = aux;
    printf("Introduce el numero de Destructores: ");
    scanf("%d", &aux);
    suma += aux;
    configuracion[0].NDestructor = aux;
    configuracion[1].NDestructor = aux;
    printf("Introduce el numero de Fragatas: ");
    scanf("%d", &aux);
    suma += aux;
    configuracion[0].NFragata = aux;
    configuracion[1].NFragata = aux;
    configuracion[0].NBarcos = suma;
    configuracion[1].NBarcos = suma;
    configuracion[0].barRestantes = suma;
    configuracion[1].barRestantes = suma;
    do{                    //Bucle para comprobar que se introduce una opcion valida
        printf("Introduce quien comienza (0: Jugador1, 1: Jugador2): ");
        scanf("%d", &comienza);
        switch(comienza){
            case 0:
                configuracion[0].comienza = 1;
                configuracion[1].comienza = 0;
                break;
            case 1:
                configuracion[0].comienza = 0;
                configuracion[1].comienza = 1;
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }while(comienza != 0 && comienza != 1);


    configuracion[0].tamTablero = 10;        //Tamaño del tablero fijo
    configuracion[1].tamTablero = 10;




    /*while(comprobar con funcion == 0){              //Bucle para comprobar que el tamaño del tablero es valido
        printf("Introduce el tamaño del tablero: ");
        scanf("%d", &configuracion[0].tamTablero);
    }
    //Para el tamaño del tablero preguntar a funcion de cristian para saber si es posible ese valor o no
    */
}

void mostrarDatos(Configuracion* datos){
    system("cls");
    for(int i = 0; i < 2; i++){
        printf("Nombre: %s\n", datos[i].nombre);
        printf("Tipo de disparo: %d\n", datos[i].tipoDisparo);
        printf("Numero de Portaaviones: %d\n", datos[i].NPortaaviones);
        printf("Numero de Acorazados: %d\n", datos[i].NAcorazado);
        printf("Numero de Cruceros: %d\n", datos[i].NCrucero);
        printf("Numero de Destructores: %d\n", datos[i].NDestructor);
        printf("Numero de Fragatas: %d\n", datos[i].NFragata);
        printf("Comienza: %d\n", datos[i].comienza);
        printf("Tamano del tablero: %d\n", datos[i].tamTablero);
        printf("Numero de disparos: %d\n", datos[i].NDisparos);
        printf("Agua: %d\n", datos[i].agua);
        printf("Tocadas: %d\n", datos[i].tocadas);
        printf("Casillas hundidas: %d\n", datos[i].casHundidas);
        printf("Barcos hundidos: %d\n", datos[i].barHundidos);
        printf("Barcos restantes: %d\n", datos[i].barRestantes);
    }
    system("pause");
}

void guardarDatos(Configuracion* datos){
    FILE *f;
    f = fopen("juego.txt", "w");
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    fprintf(f,"%i-%i\n",datos[0].tamTablero,datos[0].NBarcos);
    fprintf(f,"%i-%i-%i-%i-%i",datos[0].NPortaaviones,datos[0].NAcorazado,datos[0].NCrucero,datos[0].NDestructor,datos[0].NFragata);
    for(int i = 0; i < 2; i++){
        fprintf(f,"%s-%i-%i-%i-%i\n",datos[i].nombre, datos[i].NDisparos, datos[i].tipoDisparo, datos[i].ganador, datos[i].comienza);
        for(int i = 0; i < datos[0].tamTablero; i++){
            for(int j = 0; j < datos[0].tamTablero; j++){
                fprintf(f,"%c", datos[i].flota[i][j]);
            }
            fprintf(f,"\n");
        }
    }
    fclose(f);
    printf("Datos guardados correctamente\n");
    system("pause");
}

void cargarDatos(Configuracion* datos){
    FILE *f;
    f = fopen("Juego.txt", "r");
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    for(int i = 0; i < 2; i++){
        fscanf(f,"%i-%i\n",datos[i].tamTablero, datos[i].NBarcos);
        fscanf(f,"%i-%i-%i-%i-%i",datos[i].NPortaaviones,datos[i].NAcorazado,datos[i].NCrucero,datos[i].NDestructor,datos[i].NFragata);
        fscanf(f,"%s-%i-%i-%i\n",datos[i].nombre, datos[i].NDisparos, datos[i].tipoDisparo, datos[i].ganador);
        for(int i = 0; i < datos[0].tamTablero; i++){
            for(int j = 0; j < datos[0].tamTablero; j++){
                fscanf(f,"%c", &datos[i].flota[i][j]);
            }
        }
    }
    fclose(f);
    printf("Datos cargados correctamente\n");
    system("pause");
}