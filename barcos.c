#include "Barcos.h"


void menuBarcos(){
    int opcion;
    Barco* barcos = cargarBarcos();
    while(opcion != 5){     //Bucle para mostrar el menu de configuracion, sale de el cuando se elige la opcion 5
        do{
            system("cls");
            printf("1. Crear barco\n");
            printf("2. Eliminar barco\n");
            printf("3. Modificar barco\n");
            printf("4. Mostrar barcos\n");
            printf("5. Salir\n");
            printf("Introduce una opcion: ");
            scanf("%i", &opcion);
            switch(opcion){
                case 1:
                    crearBarco(barcos);
                    break;
                case 2:
                    eliminarBarco(barcos);
                    break;
                case 3:
                    modificarBarco(barcos);
                    break;
                case 4:
                    mostrarBarcos(barcos);
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

Barco* cargarBarcos(){
    char linea[160];        //Variable que almacena la linea leida
    char* token;        //Variable que almacena el token
    int NBarcos = obtenerNBarcos();     //Obtiene el numero de barcos
    FILE* f = fopen("Barcos.txt", "r");         //Abre el archivo en modo lectura
    if(f == NULL){          //Comprueba si se ha abierto correctamente
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    Barco* barcos = (Barco*)malloc(NBarcos* sizeof(Barco));          //Reserva memoria para el vector de estructuras
    if(barcos == NULL){         //Comprueba si se ha reservado correctamente
        printf("No hay memoria suficiente\n");
        return NULL;
    }
    int i = 0;
    while(fgets(linea, 160, f)!=NULL){          //Lee una linea del archivo por cada iteracion
        token = strtok(linea, "-");
        strcpy(barcos[i].nombre, token);
        token = strtok(NULL, "-");
        barcos[i].Id_Barco = token[0];
        token = strtok(NULL, "\n");
        barcos[i].Tam_Barco = atoi(token);
        i++;
    }
    fclose(f);          //Cierra el archivo
    return barcos;      //Devuelve el vector de estructuras
}

void mostrarBarcos(Barco* barcos){
    int i = 0;
    int t = obtenerNBarcos();
    for(int i = 0; i < t; i++){          //Recorre el vector de estructuras
        printf("Nombre: %s\n", barcos[i].nombre);
        printf("Id: %c\n", barcos[i].Id_Barco);
        printf("Tamano: %i\n\n", barcos[i].Tam_Barco);
    }
    system("pause");
}

void crearBarco(Barco* barcos){
    system("cls");
    char nombre[20];
    int NBarcos = obtenerNBarcos();
    NBarcos += 1;
    barcos = (Barco*)realloc(barcos, (NBarcos)*sizeof(Barco));          //Reserva memoria para un barco mas
    if(barcos == NULL){         //Comprueba si se ha reservado correctamente
        printf("No hay memoria suficiente\n");
        return;
    }
    printf("Introduce el nombre del barco: ");          //Pide al usuario que introduzca el nombre del barco
    fflush(stdin);
    strcpy(barcos[NBarcos-1].nombre, leerCadena());
    fflush(stdin);
    printf("Introduce el tamano del barco: ");          //Pide al usuario que introduzca el tamaño del barco
    scanf("%i", &barcos[NBarcos-1].Tam_Barco);
    barcos[NBarcos-1].Id_Barco = obtenerIDBarco(barcos[NBarcos-1].nombre);          //Obtiene el ID del barco

    guardarBarcos(barcos, NBarcos);          //Guarda los barcos en un fichero
}

void eliminarBarco(Barco* barcos){
    system("cls");
    int NBarcos = obtenerNBarcos();
    int i; 
    char Id_Barco;
    mostrarBarcos(barcos);
    printf("Escriba el Id que desee eliminar: ");
    fflush(stdin);
    scanf("%c", &Id_Barco);          //Pide al usuario que introduzca el ID del barco a eliminar
    fflush(stdin);
    for(i = 0 ; i < NBarcos ; i++){
        if(Id_Barco == barcos[i].Id_Barco){          //Busca el barco por su ID
            strcpy(barcos[i].nombre , barcos[NBarcos-1].nombre);
            barcos[i].Id_Barco = barcos[NBarcos-1].Id_Barco;
            NBarcos--;
        }
    }
    barcos = (Barco*)realloc(barcos, (NBarcos)*sizeof(Barco));
    guardarBarcos(barcos, NBarcos);
}

void modificarBarco(Barco* barcos){
    system("cls");
    mostrarBarcos(barcos);
    int NBarcos = obtenerNBarcos();
    char Id_Barco;
    printf("Escriba el Id que desee modificar: ");
    fflush(stdin);
    scanf("%c", &Id_Barco);
    fflush(stdin);
    for(int i = 0 ; i < NBarcos ; i++){
        if(Id_Barco == barcos[i].Id_Barco){
            printf("Introduce el nombre del barco: ");          //Pide al usuario que introduzca el nombre del barco
            fflush(stdin);
            strcpy(barcos[i].nombre, leerCadena());
            fflush(stdin);
            printf("Introduce el tamano del barco: ");          //Pide al usuario que introduzca el tamaño del barco
            scanf("%i", &barcos[i].Tam_Barco);
        }
    }
    printf("Barco modificado correctamente\n");
    system("pause");
    guardarBarcos(barcos, NBarcos);
}

int obtenerNBarcos(){
    char linea[160];        //Variable que almacena la linea leida
    char* token;        //Variable que almacena el token
    FILE* f = fopen("Barcos.txt", "r");         //Abre el archivo en modo lectura
    if(f == NULL){          //Comprueba si se ha abierto correctamente
        printf("Error al abrir el archivo\n");
        return 0;
    }
    int NBarcos = 0;
    while(fgets(linea, 160, f)!=NULL){          //Lee una linea del archivo por cada iteracion
        token = strtok(linea, "\n");
        NBarcos++;
    }
    fclose(f);          //Cierra el archivo
    return NBarcos;      //Devuelve el numero de barcos
}

char obtenerIDBarco(char nombre[20]){
    char ID;
    ID = nombre[0];
    return ID;
}

void guardarBarcos(Barco* barcos, int NBarcos){
    int i;
    FILE* f = fopen("Barcos.txt","w");
    if(f!= NULL){
        for(i=0; i<NBarcos; i++){
            fprintf(f,"%s-%c-%i\n",barcos[i].nombre, barcos[i].Id_Barco, barcos[i].Tam_Barco);
        }
    }else{
        printf("Ha ocurrido un error con el guardado");
    }
    printf("Datos guardados correctamente\n");
    system("pause");
    fclose(f);
}

char* leerCadena(){
    int tamanoBuffer = 100;
    char *buffer = (char*)malloc(tamanoBuffer * sizeof(char));
    int i = 0;
    char caracter;
    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        buffer[i] = caracter;
        i++;
        if (i >= tamanoBuffer) {
            tamanoBuffer *= 2;
            buffer = (char*)realloc(buffer, tamanoBuffer * sizeof(char));
        }
    }
    buffer[i] = '\0';

    return buffer;
}