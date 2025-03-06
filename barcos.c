#include "Barcos.h"

#define llega printf("Llega\n");


Barco* cargarBarcos(){
    char linea[160];
    char* token;
    FILE* f = fopen("Barcos.txt", "r");
    if(f == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    Barco* barcos = (Barco*)malloc(sizeof(Barco));
    if(barcos == NULL){
        printf("No hay memoria suficiente\n");
        return NULL;
    }
    int NBarcos = 0;
    while(fgets(linea, 160, f)!=NULL){
        barcos = (Barco*)realloc((barcos),(NBarcos+1)*sizeof(Barco));
        if(barcos == NULL){
            printf("No hay memoria suficiente\n");
            return NULL;
        }
        token = strtok(linea, "/");
        strcpy(barcos[NBarcos].nombre, token);
        token = strtok(NULL, "/");
        strcpy(barcos[NBarcos].Id_Barco, token);
        token = strtok(NULL, "/");
        barcos[NBarcos].Tam_Barco = atoi(token);
        token = strtok(NULL, "\n");
        barcos[NBarcos].valido = atoi(token);
        NBarcos++;
    }
    fclose(f);
    return barcos;
}

void mostrarBarcos(Barco* barcos){
    int i = 0;
    while(barcos[i].valido == 1){
        printf("Nombre: %s\n", barcos[i].nombre);
        printf("Id: %s\n", barcos[i].Id_Barco);
        printf("Tamano: %d\n\n", barcos[i].Tam_Barco);
        i++;
    }
}