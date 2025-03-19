#include "Tablero.h"

void asignacionTablero(){
	
	int x;

	printf("\n¿Qué modo de asignación de posición de barcos desea? (1. Manual\n2. Automático)\n");  //Se pide al usuario que elija si coloca los barcos  manualmente o que sea automaticamente
	scanf("%d",&x);
	
	switch (x){  //Distintas opciones en la elección
		
		case 1:

			char **asignacionManual();
		
		break;
		
		case 2:
		
			char **asignacionAutomatica();

		break;
		
		default:  //Vuelta al inicio si ha introducido algo distinto a un 1 o un 2
		
			printf("Opción no válida, seleccione la opción 1 o 2.\n");
        	asignacionTablero();
		
		break;
	}	
}

char **generarTablero(int n){
	int i;
	char **M;
	
	M=(char**) malloc(sizeof(char)*n);
	for(i=0;i<n;i++){
	
		M[i] = (char*) malloc(sizeof(char)*n);
	
	}
	return **M;
}

char **asignacionManual(){
	if (){  //Si el usuario sitúa un barco en una posición ya seleccionada
		printf("Esa casilla ya ha sido seleccionada.\n")
	}

	if (){  //Si el usuario sitúa un barco literalmente pegado a otro
		printf("Debe dejar al menos una casilla de espacio entre dos barcos.\n")
	}
	
	if (){  //Si el usuario selecciona una casilla que no está en los límites del tablero
		printf("No puede situar un barco fuera de los límites del tablero.\n")
	}

}

char **asignacionAutomatica(){
	Barco* VBarcos = cargarBarcos();

}

int comprobarTamaño(){
	if (){ //Devuelve un 1 si el tamaño es válido, y un 0 en caso contrario

	} 
}