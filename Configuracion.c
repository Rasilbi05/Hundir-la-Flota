#include "Configuracion.h"


void menuConfiguracion(Configuracion *datos, Barco* barcos){
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
                    guardarDatos(datos, barcos);
                    break;
                case 5:
                    cargarDatos(datos, barcos);
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

void guardarDatos(Configuracion* datos, Barco* barcos){
    int Barcos = obtenerNBarcos();      //Obtiene el numero de barcos
    FILE *f = fopen("juego.txt", "w");      //Abre el fichero en modo escritura
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    fprintf(f,"%i-%i-%i\n", datos[0].tamTablero, datos[0].totalBarcos, datos[0].barRestantes);        //Escribe el tamaño del tablero y el numero de barcos
    for(int i = 0; i < Barcos; i++){
        if(datos[0].NBarcos[i] != 0)         //Si el numero de barcos es 0, no lo guarda
            fprintf(f, "%c-%i\n", barcos[i].Id_Barco, datos[0].NBarcos[i]);
    }
    for(int i = 0; i < 2; i++){         //Recorre el vector de estructuras para guardar los datos de cada jugador
        fprintf(f, "%i-%s-%i-", i+1, datos[i].nombre, datos[i].NDisparos);
        if(datos[i].tipoDisparo == 1){
            fprintf(f, "A-");
        }else{
            fprintf(f, "M-");
        }
        fprintf(f, "%i\n", datos[i].ganador);
        for(int l = 0; l < datos[i].tamTablero; l++){
            for(int c = 0; c < datos[i].tamTablero; c++){
                if(datos[i].flota[l][c] == ' ')
                    fprintf(f, "- ");
                else
                    fprintf(f, "%c ", datos[i].flota[l][c]);
            }
            fprintf(f, "\n");
        }
        for(int l = 0; l < datos[i].tamTablero; l++){
            for(int c = 0; c < datos[i].tamTablero; c++){
                if(datos[i].oponente[l][c] == ' ')
                    fprintf(f, "- ");
                else
                    fprintf(f, "%c ", datos[i].oponente[l][c]);
            }
            fprintf(f,"\n");
        }
    }
    fclose(f);
    printf("Datos guardados correctamente\n");
    system("pause");
}

void cargarDatos(Configuracion* datos, Barco* barcos){
    int Barcos = obtenerNBarcos();      //Obtiene el numero de barcos
    int l = 0, c = 0;         //Variables auxiliares para el bucle
    char* token;
    char linea[160];
    char ID_Barco;
    FILE *f;
    f = fopen("Juego.txt", "r");
    if(f == NULL){
        printf("Error al abrir el fichero\n");
        exit(1);
    }
    fgets(linea, 160, f);          //Lee una linea del archivo por cada iteracion
    token = strtok(linea, "-");
    datos[0].tamTablero = atoi(token);
    datos[1].tamTablero = atoi(token);
    token = strtok(NULL, "-");
    datos[0].totalBarcos = atoi(token);
    datos[1].totalBarcos = atoi(token);
    token = strtok(NULL, "\n");

    while(fgets(linea, 160, f) != NULL){          //Lee una linea del archivo por cada iteracion
        token = strtok(linea, "-");
        ID_Barco = linea[0];
        token = strtok(NULL, "\n");
        for(int j = 0; j < Barcos; j++){          //Busca el barco en el vector de estructuras
            if(barcos[j].Id_Barco == ID_Barco){          //Si lo encuentra, guarda el numero de barcos
                datos[0].NBarcos[j] = atoi(token);
                datos[1].NBarcos[j] = atoi(token);
            }else{
                datos[0].NBarcos[j] = 0;
                datos[1].NBarcos[j] = 0;
            }
        }
    }
    fgets(linea, 160, f);
    token = strtok(linea, "-");
    strcpy(datos[0].nombre, token);
    token = strtok(NULL, "-");
    datos[0].NDisparos = atoi(token);
    token = strtok(NULL, "-");
    printf("%c", linea[0]);
    if(linea[0] == 'A'){
        datos[0].tipoDisparo = 1;
    }else{
        datos[0].tipoDisparo = 0;
    }
    token = strtok(NULL, "\n");
    datos[0].ganador = atoi(token);
    while(l < datos[0].tamTablero && fgets(linea, 160, f) != NULL){
        token = strtok(linea, "-");
        if(token[0] == ' ')
            datos[0].flota[l][c] = ' ';
        else
            datos[0].flota[l][c] = token[0];
        c++;
        while(c < datos[0].tamTablero-1){
            token = strtok(NULL, " ");
            datos[0].flota[l][c] = token[0];
            c++;
        }
        token = strtok(linea, "\n");
        if(token[0] == '-')
            datos[0].flota[l][c] = ' ';
        else
            datos[0].flota[l][c] = token[0];
        l++;
    }
    l = 0;
    c = 0;
    
    while(l < datos[0].tamTablero && fgets(linea, 160, f) != NULL){
        token = strtok(linea, "-");
        if(token[0] == ' ')
            datos[0].oponente[l][c] = ' ';
        else
            datos[0].oponente[l][c] = token[0];
        c++;
        while(c < datos[0].tamTablero-1){
            token = strtok(NULL, " ");
            datos[0].oponente[l][c] = token[0];
            c++;
        }
        token = strtok(linea, "\n");
        if(token[0] == '-')
            datos[0].oponente[l][c] = ' ';
        else
            datos[0].oponente[l][c] = token[0];
        l++;
    }
    l = 0;
    c = 0;

    fgets(linea, 160, f);
    token = strtok(linea, "-");
    strcpy(datos[1].nombre, token);
    token = strtok(linea, "-");
    datos[1].NDisparos = atoi(token);
    token = strtok(linea, "-");
    if(token[0] == 'A'){
        datos[1].tipoDisparo = 1;
    }else{
        datos[1].tipoDisparo = 0;
    }
    token = strtok(linea, "\n");
    datos[1].ganador = atoi(token);

    while(l < datos[1].tamTablero && fgets(linea, 160, f) != NULL){
        token = strtok(linea, "-");
        if(token[0] == ' ')
            datos[1].flota[l][c] = ' ';
        else
            datos[1].flota[l][c] = token[0];
        c++;
        while(c < datos[1].tamTablero-1){
            token = strtok(NULL, " ");
            datos[1].flota[l][c] = token[0];
            c++;
        }
        token = strtok(linea, "\n");
        if(token[0] == '-')
            datos[1].flota[l][c] = ' ';
        else
            datos[1].flota[l][c] = token[0];
        l++;
    }
    l = 0;
    c = 0;
    
    while(l < datos[1].tamTablero && fgets(linea, 160, f) != NULL){
        token = strtok(linea, "-");
        if(token[0] == ' ')
            datos[1].oponente[l][c] = ' ';
        else
            datos[1].oponente[l][c] = token[0];
        c++;
        while(c < datos[1].tamTablero-1){
            token = strtok(NULL, " ");
            datos[1].oponente[l][c] = token[0];
            c++;
        }
        token = strtok(linea, "\n");
        if(token[0] == '-')
            datos[1].oponente[l][c] = ' ';
        else
            datos[1].oponente[l][c] = token[0];
        l++;
    }
    fclose(f);
    printf("Datos cargados correctamente\n");
    system("pause");
}