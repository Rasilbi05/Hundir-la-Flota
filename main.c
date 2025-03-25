#include "Configuracion.h"
//#include "Juego.h"

int main(){
    
    printf("Hola mundo\n");     // PONER EL TITULO DEL JUEGO
    system("pause");
    int opcion = 0, configurado = 0;
    Configuracion *datos;       //Declaro el vector de estructuras
    datos = malloc(sizeof(Configuracion)*2);        //Reservo memoria para el vector de estructuras
    if(datos == NULL){      //Compruebo que se haya reservado la memoria correctamente
        printf("Error al reservar memoria\n");
        exit(1);
    }
    while(opcion != 3){     //Bucle para mostrar el menu principal, sale de el cuando se elige la opcion 3
        do{
            system("cls");
            printf("1. Configuracion\n\n");
            printf("2. Jugar\n\n");
            printf("3. Salir\n\n");
            printf("Introduzca un numero para continuar\n\n\n");
            scanf("%d", &opcion);
            switch(opcion){
                case 1:
                    menuConfiguracion(datos);
                    configurado = 1;
                    break;
                case 2:
                    if(configurado == 0){
                        printf("Primero debes configurar el juego\n");
                        system("pause");
                    }else{
                        //menuJuego(datos);
                    }
                    break;
                case 3:
                    free(datos);
                    break;
                default:
                    printf("Opcion no valida\n");
                    break;
            }
        }while(opcion < 1 || opcion > 3);
    }

    return 0;
}