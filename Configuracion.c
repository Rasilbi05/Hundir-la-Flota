#include "Configuracion.h"


void menuConfiguracion(Configuracion *datos){
    int opcion;
    while(opcion != 6){     //Bucle para mostrar el menu de configuracion, sale de el cuando se elige la opcion 5
        do{
            system("cls");
            printf("1. Introducir datos\n");
            printf("2. Barcos\n");
            printf("3. Mostrar datos\n");
            printf("4. Guardar datos\n");
            printf("5. Cargar datos\n");
            printf("6. Salir\n");
            printf("Introduce una opcion: ");
            scanf("%d", &opcion);
            switch(opcion){
                case 1:
                    introducirDatos(datos);
                    break;
                case 2:
                    menuBarcos();
                    break;
                case 3:
                    mostrarDatos(datos);
                    break;
                case 4:
                    guardarDatos(datos);
                    break;
                case 5:
                    cargarDatos(datos);
                    break;
                case 6:
                    break;
                default:
                    printf("Opcion no valida\n");
                    break;
            }
        }while(opcion < 1 || opcion > 6);
    }
}

void introducirDatos(Configuracion* configuracion){
    int suma = 0, comienza = 0;        //Variables auxiliares para el numero de barcos y la suma de ellos y para saber quien comienza
    int Barcos = obtenerNBarcos();      //Obtiene el numero de barcos
    Barco* barcos = cargarBarcos();     //Carga los barcos
    configuracion[0].NBarcos = (int*)malloc(Barcos*sizeof(int));        //Reserva memoria para el vector de barcos
    configuracion[1].NBarcos = (int*)malloc(Barcos*sizeof(int));        //Reserva memoria para el vector de barcos
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
    for(int i = 0; i < Barcos; i++){
        printf("Introduce el numero de %s: ", barcos[i].nombre);
        scanf("%i", &configuracion[0].NBarcos[i]);
        configuracion[1].NBarcos[i] = configuracion[0].NBarcos[i];
        suma += configuracion[0].NBarcos[i];
    }
    configuracion[0].totalBarcos = suma;
    configuracion[1].totalBarcos = suma;
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
    int Barcos = obtenerNBarcos();
    Barco* barcos = cargarBarcos();
    for(int i = 0; i < 2; i++){
        printf("Nombre: %s\n", datos[i].nombre);
        printf("Tipo de disparo: %d\n", datos[i].tipoDisparo);
        for(int j = 0; j < Barcos; j++){
            printf("Numero de %s: %d\n", barcos[j].nombre, datos[i].NBarcos[j]);
        }
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
    int Barcos = obtenerNBarcos();
    FILE *f;
    f = fopen("juego.txt", "w");
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    fprintf(f,"%i-%i\n",datos[0].tamTablero,datos[0].NBarcos);
    for(int i = 0; i < Barcos-1; i++){
        fprintf(f,"%i-",datos[0].NBarcos[i]);
    }
    fprintf(f,"%i\n",datos[0].NBarcos[Barcos-1]);
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
    char* token;
    char linea[160];
    int j = 0;
    FILE *f;
    f = fopen("Juego.txt", "r");
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    for(int i = 0; i < 2; i++){
        fscanf(f,"%i-%i\n",datos[i].tamTablero, datos[i].NBarcos);
        while(fgets(linea, 160, f)!=NULL){
            token = strtok(linea, "-");
            while(token != NULL){
                datos[0].NBarcos[j] = atoi(token);
                datos[1].NBarcos[j] = atoi(token);
                token = strtok(NULL, "-");
            }
        }
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