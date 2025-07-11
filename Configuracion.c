#include "Configuracion.h"

int menuConfiguracion(Configuracion *datos){
    int opcion = 0, completado = 0, opcionB = 0, cargado = 0;
    while(opcion != 6 && completado == 0){     //Bucle para mostrar el menu de configuracion, sale de el cuando se elige la opcion 5
        do{
            system("cls");
            printf("1. Introducir datos\n");
            printf("2. Barcos\n");
            printf("3. Mostrar datos\n");
            printf("4. Guardar datos\n");
            printf("5. Cargar datos\n");
            printf("6. Salir\n");
            printf("Introduce una opcion\n\n\n--> ");
            scanf("%i", &opcion);
            switch(opcion){
                case 1:
                    printf("Desea crear, modificar o eliminar barcos?(1-SI || 2-NO)\n\n-->");
                    scanf("%i", &opcionB);
                    if(opcionB == 1)
                        menuBarcos();
                    datos[0].NBarcos = (int*)malloc(obtenerNBarcos()*sizeof(int));        //Reserva memoria para el vector de barcos
                    datos[1].NBarcos = (int*)malloc(obtenerNBarcos()*sizeof(int));        //Reserva memoria para el vector de barcos
                    introducirDatos(datos);
                    completado = 1;        //Si se ha completado la configuracion, se cambia la variable a 1
                    break;
                case 2:
                    menuBarcos();
                    datos[0].NBarcos = (int*)malloc(obtenerNBarcos()*sizeof(int));        //Reserva memoria para el vector de barcos
                    datos[1].NBarcos = (int*)malloc(obtenerNBarcos()*sizeof(int));        //Reserva memoria para el vector de barcos
                    break;
                case 3:
                    mostrarDatos(datos);
                    break;
                case 4:
                    guardarDatos(datos);
                    break;
                case 5:
                    cargarDatos(datos);
                    cargado = 1;
                    completado = 1;        //Si se ha completado la configuracion, se cambia la variable a 1
                    break;
                case 6:
                    break;
                default:
                    printf("Opcion no valida\n");
                    system("pause");
                    break;
            }
        }while(opcion < 1 || opcion > 6);
    }
    if(cargado == 1){
        return 1;
    }
    return 0;
}

void introducirDatos(Configuracion* configuracion){
    int suma = 0, comienza = 0, aleatorio;        //Variables auxiliares para el numero de barcos y la suma de ellos y para saber quien comienza
    char opcion;        //Variable para elegir el tiro
    int Barcos = obtenerNBarcos();      //Obtiene el numero de barcos
    Barco* barcos = cargarBarcos();     //Carga los barcos
    configuracion[0].NBarcos = (int*)malloc(Barcos*sizeof(int));        //Reserva memoria para el vector de barcos
    configuracion[1].NBarcos = (int*)malloc(Barcos*sizeof(int));        //Reserva memoria para el vector de barcos
    for(int i = 0; i < 2; i++){             //Recorre el vector de estructuras para inicializar los datos
        system("cls");
        printf("Introduce el nombre del jugador %i\n\n--> ", i+1);
        fflush(stdin);
        fgets(configuracion[i].nombre, 20, stdin);
        fflush(stdin);
        system("cls");
        printf("Introduce el tipo de disparo del jugador %i (0: Disparo normal, 1: Disparo automatico)\n\n--> ", i+1);
        scanf("%d", &configuracion[i].tipoDisparo);
        configuracion[i].NDisparos = 0;
        configuracion[i].agua = 0;
        configuracion[i].tocadas = 0;
        configuracion[i].hundidas = 0;
        configuracion[i].barHundidos = 0;
    }
    for(int i = 0; i < Barcos; i++){
        system("cls");
        printf("Introduce el numero de %s\n\n--> ", barcos[i].nombre);
        scanf("%i", &configuracion[0].NBarcos[i]);
        configuracion[1].NBarcos[i] = configuracion[0].NBarcos[i];
        suma += configuracion[0].NBarcos[i];
    }
    configuracion[0].totalBarcos = suma;
    configuracion[1].totalBarcos = suma;
    configuracion[0].barRestantes = suma;
    configuracion[1].barRestantes = suma;
    
    do{
        system("cls");
        printf("Introduce como quieres seleccionar quien comienza (M: Manual, A: Aleatorio)\n\n--> ");
        fflush(stdin);
        scanf("%c", &opcion);
        fflush(stdin);
        switch(opcion){
            case 'M':
                do{                    //Bucle para comprobar que se introduce una opcion valida
                    system("cls");
                    printf("Introduce quien comienza (0: Jugador1, 1: Jugador2)\n\n--> ");
                    scanf("%i", &comienza);
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
                        system("pause");
                        break;
                    }
                }while(comienza != 0 && comienza != 1);
                break;
            case 'A':
                    system("cls");
                    srand(time(NULL));        //Inicializa la semilla del generador de numeros aleatorios
                    aleatorio = rand()%2;        //Genera un numero aleatorio entre 0 y 1
                    if(aleatorio == 0){
                        configuracion[0].comienza = 1;
                        configuracion[1].comienza = 0;
                    }else{
                        configuracion[0].comienza = 0;
                        configuracion[1].comienza = 1;
                    }
                break;
            default:
                printf("Opcion no valida\n");
                system("pause");
                break;
        }
    }while(opcion != 'M' && opcion != 'A');        //Bucle para comprobar que se introduce una opcion valida
    
    printf("Introduce el tamano del tablero: ");
    scanf("%d", &configuracion[0].tamTablero);

    while(comprobarTamano(configuracion) == 0){              //Bucle para comprobar que el tamaño del tablero es valido
        printf("El tamano del tablero no es valido\n");
        printf("Introduce el tamano del tablero: ");
        scanf("%d", &configuracion[0].tamTablero);
    }
}

void mostrarDatos(Configuracion* datos){
    system("cls");
    int Barcos = obtenerNBarcos();
    Barco* barcos = cargarBarcos();
    printf("---Barcos disponibles---\n\n");
    for(int j = 0; j < Barcos; j++){
        printf("Numero de %s: %d\n", barcos[j].nombre, datos[0].NBarcos[j]);
    }
    printf("\n\n---Datos de los jugadores---\n\n");
    for(int i = 0; i < 2; i++){
        printf("Nombre:                     %s\n", datos[i].nombre);
        if(datos[i].tipoDisparo == 0)
            printf("Disparo manual\n");
        else
            printf("Disparo automatico\n");
        printf("Comienza:                   %d\n", datos[i].comienza);
        printf("Tamano del tablero:         %d\n", datos[i].tamTablero);
        printf("Numero de disparos:         %d\n", datos[i].NDisparos);
        printf("Agua:                       %d\n", datos[i].agua);
        printf("Tocadas:                    %d\n", datos[i].tocadas);
        printf("Hundidas:                   %d\n", datos[i].hundidas);
        printf("Barcos hundidos:            %d\n", datos[i].barHundidos);
        printf("Barcos restantes:           %d\n\n\n", datos[i].barRestantes);
    }
    system("pause");
}

void guardarDatos(Configuracion* datos){
    Barco* barcos = cargarBarcos();     //Carga los barcos
    int Barcos = obtenerNBarcos();      //Obtiene el numero de barcos
    FILE *f = fopen("juego.txt", "w");      //Abre el fichero en modo escritura
    system("cls");
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
        if(datos[i].tipoDisparo == 1)
            fprintf(f, "A-");
        else
            fprintf(f, "M-");

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
            fprintf(f, "\n");
        }
    }
    fclose(f);
    printf("Datos guardados correctamente\n");
    system("pause");
}

void cargarDatos(Configuracion* datos){
    system("cls");
    Barco* barcos = cargarBarcos();     //Carga los barcos
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
    datos[0].comienza = 1;
    datos[1].comienza = 0;

    for(int i = 0; i < Barcos; i++){            //Inizializa el vector de numero de barcos a 0
        datos[0].NBarcos[i] = 0;
        datos[1].NBarcos[i] = 0;
    }
    datos[0].tocadas = 0;       //Inicializa el numero de barcos tocados a 0
    datos[0].agua = 0;       //Inicializa el numero de barcos hundidos a 0
    datos[0].hundidas = 0;       //Inicializa el numero de barcos hundidos a 0
    datos[1].tocadas = 0;       //Inicializa el numero de barcos tocados a 0
    datos[1].agua = 0;       //Inicializa el numero de barcos hundidos a 0
    datos[1].hundidas = 0;       //Inicializa el numero de barcos hundidos a 0

    while(fgets(linea, 160, f) != NULL && atoi((token = strtok(linea, "-"))) != 1){          //Lee una linea del archivo por cada iteracion
        ID_Barco = linea[0];
        token = strtok(NULL, "\n");
        for(int j = 0; j < Barcos; j++){          //Busca el barco en el vector de estructuras
            if(barcos[j].Id_Barco == ID_Barco){          //Si lo encuentra, guarda el numero de barcos
                datos[0].NBarcos[j] = atoi(token);
                datos[1].NBarcos[j] = atoi(token);
            }
        }
    }
    token = strtok(NULL, "-");
    strcpy(datos[0].nombre, token);
    token = strtok(NULL, "-");
    datos[0].NDisparos = atoi(token);
    token = strtok(NULL, "-");
    if(token[0] == 'A'){
        datos[0].tipoDisparo = 1;
    }else{
        datos[0].tipoDisparo = 0;
    }
    token = strtok(NULL, "\n");
    datos[0].ganador = atoi(token);
    
    datos[0].flota = (char**)malloc(datos[0].tamTablero*sizeof(char*));        //Reserva memoria para el tablero de flota del jugador 1
    for(int i = 0; i < datos[0].tamTablero; i++){
        datos[0].flota[i] = (char*)malloc(datos[0].tamTablero*sizeof(char));        //Reserva memoria para cada fila del tablero de flota del jugador 1
    }
    datos[0].oponente = (char**)malloc(datos[0].tamTablero*sizeof(char*));        //Reserva memoria para el tablero de flota del jugador 1
    for(int i = 0; i < datos[0].tamTablero; i++){
        datos[0].oponente[i] = (char*)malloc(datos[0].tamTablero*sizeof(char));        //Reserva memoria para cada fila del tablero de flota del jugador 1
    }
    datos[1].flota = (char**)malloc(datos[1].tamTablero*sizeof(char*));        //Reserva memoria para el tablero de flota del jugador 2
    for(int i = 0; i < datos[0].tamTablero; i++){
        datos[1].flota[i] = (char*)malloc(datos[1].tamTablero*sizeof(char));        //Reserva memoria para cada fila del tablero de flota del jugador 1
    }
    datos[1].oponente = (char**)malloc(datos[1].tamTablero*sizeof(char*));        //Reserva memoria para el tablero de flota del jugador 1
    for(int i = 0; i < datos[0].tamTablero; i++){
        datos[1].oponente[i] = (char*)malloc(datos[1].tamTablero*sizeof(char));        //Reserva memoria para cada fila del tablero de flota del jugador 1
    }
    
    while(l < datos[0].tamTablero && fgets(linea, 160, f) != NULL){             //Lee el tablero de flota del jugador 1
        token = strtok(linea, " ");
        if(token[0] == '-')
            datos[0].flota[l][c] = ' ';
        else
            datos[0].flota[l][c] = token[0];
        c++;
        while(c < datos[0].tamTablero-1){
            token = strtok(NULL, " ");
            if(token[0] == '-')
                datos[0].flota[l][c] = ' ';
            else
                datos[0].flota[l][c] = token[0];
            c++;
        }
        token = strtok(NULL, "\n");
        if(token[0] == '-')
            datos[0].flota[l][c] = ' ';
        else
            datos[0].flota[l][c] = token[0];
        l++;
        c = 0;
    }
    l = 0;
    c = 0;

    while(l < datos[0].tamTablero && fgets(linea, 160, f) != NULL){             //Lee el tablero de oponente del jugador 1
        token = strtok(linea, " ");
        switch(token[0]){
            case '-':
                datos[0].oponente[l][c] = ' ';
                break;
            case 'T':
                datos[0].oponente[l][c] = token[0];
                datos[0].tocadas++;
                break;
            case 'H':
                datos[0].oponente[l][c] = token[0];
                datos[0].hundidas++;
                break;
            case '*':
                datos[0].oponente[l][c] = token[0];
                datos[0].agua++;
                break;
            default:
                break;
        }
        c++;
        while(c < datos[0].tamTablero-1){
            token = strtok(NULL, " ");
            switch(token[0]){
                case '-':
                    datos[0].oponente[l][c] = ' ';
                    break;
                case 'T':
                    datos[0].oponente[l][c] = token[0];
                    datos[0].tocadas++;
                    break;
                case 'H':
                    datos[0].oponente[l][c] = token[0];
                    datos[0].hundidas++;
                    break;
                case '*':
                    datos[0].oponente[l][c] = token[0];
                    datos[0].agua++;
                    break;
                default:
                    break;    
            }
            c++;
        }
        token = strtok(NULL, "\n");
        switch(token[0]){
            case '-':
                datos[0].oponente[l][c] = ' ';
                break;
            case 'T':
                datos[0].oponente[l][c] = token[0];
                datos[0].tocadas++;
                break;
            case 'H':
                datos[0].oponente[l][c] = token[0];
                datos[0].hundidas++;
                break;
            case '*':
                datos[0].oponente[l][c] = token[0];
                datos[0].agua++;
                break;
            default:
                break;
        }
        c = 0;
        l++;
    }
    l = 0;
    c = 0;

    fgets(linea, 160, f);
    token = strtok(linea, "-");
    token = strtok(NULL, "-");
    strcpy(datos[1].nombre, token);
    token = strtok(NULL, "-");
    datos[1].NDisparos = atoi(token);
    token = strtok(NULL, "-");
    if(token[0] == 'A'){
        datos[1].tipoDisparo = 1;
    }else{
        datos[1].tipoDisparo = 0;
    }
    token = strtok(NULL, "\n");
    datos[1].ganador = atoi(token);

    while(l < datos[1].tamTablero && fgets(linea, 160, f) != NULL){             //Lee el tablero de flota del jugador 2
        token = strtok(linea, " ");
        if(token[0] == '-')
            datos[1].flota[l][c] = ' ';
        else
            datos[1].flota[l][c] = token[0];
        c++;
        while(c < datos[1].tamTablero-1){
            token = strtok(NULL, " ");
            if(token[0] == '-')
                datos[1].flota[l][c] = ' ';
            else
                datos[1].flota[l][c] = token[0];
            c++;
        }
        token = strtok(NULL, "\n");
        if(token[0] == '-')
            datos[1].flota[l][c] = ' ';
        else
            datos[1].flota[l][c] = token[0];
        l++;
        c = 0;
    }
    l = 0;
    c = 0;
    
    while(l < datos[1].tamTablero && fgets(linea, 160, f) != NULL){             //Lee el tablero de oponente del jugador 2
        token = strtok(linea, " ");
        switch(token[0]){
            case '-':
                datos[1].oponente[l][c] = ' ';
                break;
            case 'T':
                datos[1].oponente[l][c] = token[0];
                datos[1].tocadas++;
                break;
            case 'H':
                datos[1].oponente[l][c] = token[0];
                datos[1].hundidas++;
                break;
            case '*':
                datos[1].oponente[l][c] = token[0];
                datos[1].agua++;
                break;
            default:
                break;    
        }
        c++;
        while(c < datos[1].tamTablero-1){
            token = strtok(NULL, " ");
            switch(token[0]){
                case '-':
                    datos[1].oponente[l][c] = ' ';
                    break;
                case 'T':
                    datos[1].oponente[l][c] = token[0];
                    datos[1].tocadas++;
                    break;
                case 'H':
                    datos[1].oponente[l][c] = token[0];
                    datos[1].hundidas++;
                    break;
                case '*':
                    datos[1].oponente[l][c] = token[0];
                    datos[1].agua++;
                    break;
                default:
                    break;    
            }
            c++;
        }
        token = strtok(NULL, "\n");
        switch(token[0]){
            case '-':
                datos[1].oponente[l][c] = ' ';
                break;
            case 'T':
                datos[1].oponente[l][c] = token[0];
                datos[1].tocadas++;
                break;
            case 'H':
                datos[1].oponente[l][c] = token[0];
                datos[1].hundidas++;
                break;
            case '*':
                datos[1].oponente[l][c] = token[0];
                datos[1].agua++;
                break;
            default:
                break;    
        }
        c = 0;
        l++;
    }

    for(int i = 0; i < 2; i++){
        datos[i].barHundidos = barcosHundidos(datos[i].oponente, datos[i].tamTablero);        //Calcula el numero de barcos hundidos
        datos[i].barRestantes = datos[i].totalBarcos - datos[i].barHundidos;        //Calcula el numero de barcos restantes
    }

    fclose(f);
    printf("Datos cargados correctamente\n");
    system("pause");
}

int barcosHundidos(char **oponente, int tamTablero){
    int hundidos = 0;
    
    for(int f = 0; f < tamTablero; f++){
        for(int c = 0; c < tamTablero; c++){
            if(f == 0){
                if(c == 0){
                    if(oponente[f][c] == 'H'){
                        hundidos++;
                    }
                }else{
                    if(oponente[f][c] == 'H' && oponente[f][c-1] != 'H'){
                        hundidos++;
                    }
                }
            }else{
                if(c == tamTablero){
                    if(oponente[f][c] == 'H' && oponente[f-1][c] != 'H' && oponente[f-1][c-1] != 'H'){
                        hundidos++;
                    }
                }else{
                    if(c == 0){
                        if(oponente[f][c] == 'H' && oponente[f-1][c] != 'H' && oponente[f-1][c+1] != 'H'){
                            hundidos++;
                        }
                    }else{
                        if(oponente[f][c] == 'H' && (oponente[f][c-1] != 'H' && oponente[f-1][c-1] != 'H' && oponente[f-1][c] != 'H' && oponente[f-1][c+1] != 'H')){
                        hundidos++;
                        }
                    }
                }
            }
        }
    }

    return hundidos;
}

void testBarcosHundidos(char **oponente, int tamTablero, int esperado){
    int hundidos = barcosHundidos(oponente, tamTablero);
    printf("Esperados: %i\nObtenidos: %i\nResultado: %s", esperado, hundidos, (esperado == hundidos) ? "Correcto" : "Incorrecto");
}

int comprobarTamano(Configuracion* datos){

	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int j;
	int t_total=0;
    for(j=0;j<i;j++){
        t_total=t_total+(barcos[j].Tam_Barco+(8+4*(barcos[j].Tam_Barco-1)))*datos[0].NBarcos[j]; //Va almacenando en t_total: lo que habia en t_total + (el nº de casillas que ocupa cada barco + el nº de casillas que debe tener libre alrededor) * el número de barcos que haya de ese tipo
    }
    if(t_total<=datos[0].tamTablero*datos[0].tamTablero){ //Devuelve un 1 si el tamaño es válido, y un 0 en caso contrario
		return 1;
	} else {
		return 0;
	} 
}