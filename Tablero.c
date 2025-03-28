#include "Tablero.h"

char **generarTablero(int n){
	int i, j;
	char **M;
	
	M=(char**) malloc(sizeof(char)*n);
	for(i=0;i<n;i++){
	
		M[i] = (char*) malloc(sizeof(char)*n);
	
	}
	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

		M[i][j] = ' ';

		}
	}
	return **M;
}

char **asignacionManual(){
	
	int t;
	
	for(t=0;t<tam;t++){
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
}

char **asignacionAutomatica(Configuracion* datos){
	
	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int j;
	
	for(j=0;j<i;j++){

		int k;
		
		for(k=0;k<datos[j].NBarcos;k++){

			int t;

			for(t=0;t<barcos[j].Tam_Barco;t++){

			}
		}
	}
		
	
}

int comprobarTamaño(){

	if (){ //Devuelve un 1 si el tamaño es válido, y un 0 en caso contrario
		
		return 1;
	
	} else {
		
		return 0;
	} 
}

//for(t=0;t<tam;<t++)
//Si el barco cabe j+t<tam
//if (flota [i] [j+t] = ' ')

//for(t=0;t<tam;t++)
//Si el barco cabe j-t>0
//if (flota [i] [j-t] = ' ')