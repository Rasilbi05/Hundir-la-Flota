#include "Barcos.h"


Barco* cargarBarcos(){
    char linea[160];        //Variable que almacena la linea leida
    char* token;        //Variable que almacena el token
    int NBarcos = obtenerNBarcos();
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
        token = strtok(linea, "/");
        strcpy(barcos[i].nombre, token);
        token = strtok(NULL, "/");
        strcpy(barcos[i].Id_Barco, token);
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
        printf("Id: %s\n", barcos[i].Id_Barco);
        printf("Tamano: %d\n\n", barcos[i].Tam_Barco);
    }
}

void crearBarco(Barco* barcos){
    int NBarcos = obtenerNBarcos();
    printf("Introduce el nombre del barco: ");          //Pide al usuario que introduzca el nombre del barco
    fflush(stdin);
    fgets(barcos[NBarcos].nombre, 20, stdin);
    printf("Introduce el tamaño del barco: ");          //Pide al usuario que introduzca el tamaño del barco
    scanf("%i", barcos[NBarcos].Tam_Barco);
    barcos[NBarcos].Id_Barco = obtenerIDBarco(barcos);          //Obtiene el ID del barco
    guardarBarcos(barcos, NBarcos);          //Guarda los barcos en un fichero
}

void eliminarBarco(Barco* barcos){
    int NBarcos = obtenerNBarcos();
    int i, Id_Barco;
    printf("Escriba el Id que desee eliminar: ");
    scanf("%s", Id_Barco);
    for(i = 0 ; i < NBarcos ; i++){
        if(strcmp(Id_Barco , barcos[i].Id_Barco) == 0){
            strcpy(barcos[i].nombre , barcos[NBarcos-1].nombre);
            barcos[i].Id_Barco = barcos[NBarcos-1].Id_Barco;
            NBarcos--;
        }
    }
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

int obtenerIDBarco(Barco* barcos){
    int ID = 0, i = 0;
    int NBarcos = obtenerNBarcos();
    while(ID == barcos[i].Id_Barco && i < NBarcos){          //Recorre el vector de estructuras
        i++;
        ID++;
    }
    return ID;
}

void guardarBarcos(Barco* barcos, int NBarcos){
    int i;
    FILE* f = fopen("Barcos.txt","w");
    if(f!= NULL){
        for(i=0; i<NBarcos; i++){
            fprintf(f,"%s-%i-%i\n",barcos[i].nombre, barcos[i].Id_Barco, barcos[i].Tam_Barco);
        }
    }else{
        printf("Ha ocurrido un error con el guardado");
    }
    fclose(f);
}