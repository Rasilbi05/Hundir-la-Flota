#include "Tablero.h"

void asignacionTablero(){
	
	int x;

	printf("\n¿Qué modo de asignación de posición de barcos desea? (1. Manual\n2. Automático)\n");  //Se pide al usuario que elija si coloca los barcos  manualmente o que sea automaticamente
	scanf("%d",&x);
	
	switch (x){  //
		
		case 1:

			asignacionManual();
		
		break;
		
		case 2:
		
			asignacionAutomatica();

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
	//Falta  comprobar si caben los barcos en el tablero
	M=(char**) malloc(sizeof(char)*n);
	for(i=0;i<n;i++){
	
		M[i] = (char*) malloc(sizeof(char)*n);
	
	}
	return **M;
}

