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

void asignacionManual(Configuracion* datos, int i){
	
	int c, f;

	printf("Elija las coordenadas de inicio del barco (c f), siendo c columna y f fila.\n");
	scanf("%d %d", &c, &f);
	
	int d;

	if(datos[i].flota[c][f] == ' '){

		do{
			printf("A continuación, elija en qué dirección desea situar el barco:\n 1. Diagonal\n 2. Vertical\n 3. Horizontal\n");
			scanf("%d", &d);

			int s;
		
			switch(d){

				case 1: 

					do{
						
						printf("Elija en qué sentido diagonal se situará el barco:\n 1. Arriba-derecha\n 2. Abajo-derecha\n 3. Arriba-izquierda\n 4. Abajo-izquierda\n");
						scanf("%d", &s);

						switch(s){

							case 1:

								for(){
									
									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

										if(){

										}else{
							
										}

										if(d != 5){

											if(){

											}else{
												
											}
										}

										if(d != 5){

											if(){

											}else{
	
											}	
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco

									}	
								
									if(d != 5){

										if(){

										}else{

										}	
									}
									
									if(d != 5){
										
										if(){

										}else{

										}	
									}
									
									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}
								}

								break;

							case 2:
								
								for(){
									
									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}	
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco

									}	
							
									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}
									}	
								}
								
								break;

							case 3:

								for(){
									
									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}	
									
										if(d != 5){

											if(){

											}else{

											}	
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco

									}	
							
									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}
									}
									
									if(d != 5){
							
										if(){

										}else{

										}
									}	
								}

								break;
						
							case 4:

								for(){
									
									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

										if(){

										}else{

										}

										if(d != 5){
											
											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco

									}	
									
									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}	
									}

									if(d != 5){

										if(){

										}else{

										}
									}	
								}
							
								break;
							
							default:

								printf("Elija una opción válida: 1, 2, 3 ó 4.");

								break;
							}
					}while(1<s||s>4);
					
					break;

				case 2: 
					do{
						printf("Elija en qué sentido vertical se situará el barco:\n 1. Arriba\n 2. Abajo\n");
						scanf("%d", &s);

						switch(s){

							case 1:

								for(){

									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
										
										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}	
									}
								}

								break;

							case 2:
							
								for(){

									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}	
									}
								}

								break;

							default:

								printf("Elija una opción válida: 1 ó 2.");

								break;
						}
					}while(1<s||s>2);
					
					break;

				case 3: 
					do{
						printf("Elija en qué sentido horizontal se situará el barco:\n 1. Izquierda\n 2. Derecha\n");
						scanf("%d", &s);

						switch(s){

							case 1:

								for(){

									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{	

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}	

									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}
									}
								}

								break;

							case 2:
							
								for(){

									if(){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
										if(){

										}else{

										}

										if(d != 5){

											if(){

											}else{

											}
										}
											
										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){
										
											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}
									
									}else{ //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}

										if(d != 5){

											if(){

											}else{

											}
										}
									}
								}	

								break;

							default:

								printf("Elija una opción válida: 1 ó 2.");
								
								break;
						}
					}while(1<s||s>2);
					
					break;

				default: 
				
					printf("Elija una opción válida: 1, 2 ó 3.");

					break;
				}
		}while(d<1||d>3);		

	}else{

		if([c][f] == 'X'){
			
			printf("Introduzca otras coordenadas, estas ya están ocupadas por otro barco.");
		
		}else{
			
			printf("Introduzca otras coordenadas, estas se salen de los límites del tablero.");
		}
		
		return asignacionManual();
	}
}

void asignacionAutomatica(Configuracion* datos, int u){
	
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