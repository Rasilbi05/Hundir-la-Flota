#include "Barcos.h"


Barco* cargarBarcos(){
    char linea[160];        //Variable que almacena la linea leida
    char* token;        //Variable que almacena el token
    FILE* f = fopen("Barcos.txt", "r");         //Abre el archivo en modo lectura
    if(f == NULL){          //Comprueba si se ha abierto correctamente
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    Barco* barcos = (Barco*)malloc(5* sizeof(Barco));          //Reserva memoria para el vector de estructuras
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
    for(int i = 0; i < 5; i++){          //Recorre el vector de estructuras
        printf("Nombre: %s\n", barcos[i].nombre);
        printf("Id: %s\n", barcos[i].Id_Barco);
        printf("Tamano: %d\n\n", barcos[i].Tam_Barco);
    }
}