#include "Tablero.h"

void tamTablero(){
	
	int x;

	printf("¿Qué modo de asignación de tamaño desea? (1. Manual\n2. Automático)\n");  //Se pregunta si desea asignar el tamaño el usuario o que se asigne aleatoriamente
	scanf("%d",&x);
	
	switch (x){  //
		
		case 1;
		
		int n;
		
			pritnf("Elija el número de casillas del lado del tablero que desees.\nTenga en cuenta que el tablero es cuadrado.\n");  //Se pide tamaño del lado del tablero para definir el tamaño de este
			scanf("%d",&n);
		
			//Función para determinar el tamaño del tablero manualmente
		
		break;
		
		case 2;
		
			//Función para determinar el tamaño del tablero aleatoriamente
		
		break;
		
		default;  //Vuelta al inicio si ha introducido algo distinto a un 1 o un 2
		
			printf("Opción no válida, seleccione la opción 1 o 2.\n");
        	tamTablero();
		
		break;
	}	
}
