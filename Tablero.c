#include "Tablero.h"

char **generarTablero(int n){
	int i, j;
	char **M;
	
	M = (char**) malloc(sizeof(char*)*n);
	for(i=0;i<n;i++){
	
		M[i] = (char*) malloc(sizeof(char)*n);
	
	}
	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

		M[i][j] = ' ';

		}
	}
	return M;
}

void asignacionManual(Configuracion* datos, int u){
	
	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int f_origen, c_origen;
	int d;
	int s;
	int j, k, t;

	for(j=0;j<i;j++){

		for(k=0;k<datos[0].NBarcos[j];k++){
			printf("Elija las coordenadas de inicio de un barco de tamaño %d (f c), siendo f fila y c columna.\n", barcos[j].Tam_Barco);
			scanf("%d, %d", &f_origen, &c_origen);

			int f=f_origen, c=c_origen;

			if(datos[u].flota[f][c] == ' '){

				do{
					printf("A continuación, elija en qué dirección desea situar el barco:\n 1. Diagonal\n 2. Vertical\n 3. Horizontal\n");
					scanf("%d", &d);
		
					switch(d){

						case 1: //Diagonal

							do{
						
								printf("Elija en qué sentido diagonal se situará el barco:\n 1. Arriba-derecha\n 2. Abajo-derecha\n 3. Arriba-izquierda\n 4. Abajo-izquierda\n");
								scanf("%d", &s);

								switch(s){

									case 1: //Arriba-derecha
										
										for(t=0;t<barcos[j].Tam_Barco;t++){
									
											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

												if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

												}else{
												
													if(datos[u].flota[f+1][c-1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{
												
														if(datos[u].flota[f][c-1] == 'X'){
															
															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{
	
														if(datos[u].flota[f+1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}	
												}

											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco	
								
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{	

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}
									
											if(d != 5){
										
												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}
								
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}
										
											f=f-1; 
											c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

										}
										
										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f-1;
												c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

											}

										}
										
										break;

									case 2: //Abajo-derecha
								
										for(t=0;t<barcos[j].Tam_Barco;t++){
									
											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

												if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

												}else{

													if(datos[u].flota[f-1][c-1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}
												}

											if(d != 5){

												if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{	

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}	
										
											f=f+1;
											c=c+1;
										
										}
								
										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f+1;
												c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

											}

										}

										break;

									case 3: //Arriba-izquierda

										for(t=0;t<barcos[j].Tam_Barco;t++){
									
											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

												if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

												}else{

													if(datos[u].flota[f+1][c+1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}
												}	
									
												if(d != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}	
												}

											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}	

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}	

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}
									
											if(d != 5){
							
												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}	
										
											f=f-1;
											c=c-1;
										
										}

										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'
 
											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f-1;
												c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

											}

										}

										break;
						
									case 4: //Abajo-izquierda

										for(t=0;t<barcos[j].Tam_Barco;t++){
									
											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

												if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha 
												
												}else{

													if(datos[u].flota[f-1][c+1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){
											
													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f-1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{



														}

													}
												}

											}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
									
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}	

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}	
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;
							
													}else{



													}

												}		
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}	
										
											f=f+1;
											c=c-1;
										
										}
										
										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f+1;
												c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

											}

										}

										break;
							
									default:

										printf("Elija una opción válida: 1, 2, 3 ó 4.");

										break;
								}
							}while(1<s||s>4);
					
							break;

						case 2: //Vertical
							do{
								printf("Elija en qué sentido vertical se situará el barco:\n 1. Arriba\n 2. Abajo\n");
								scanf("%d", &s);

								switch(s){

									case 1: //Arriba

										for(t=0;t<barcos[j].Tam_Barco;t++){

											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
										
												if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

												}else{

													if(datos[u].flota[f+1][c-1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha
 
													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												
											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}	
										
											f=f-1;
										
										}

										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f-1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

											}

										}

										break;

									case 2: //Abajo
							
										for(t=0;t<barcos[j].Tam_Barco;t++){

											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
												if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

												}else{

													if(datos[u].flota[f-1][c-1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f-1][c] == 'X'){

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

											}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}	
										
											f=f+1;
										
										}

										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												f=f+1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

											}

										}

										break;

									default:

										printf("Elija una opción válida: 1 ó 2.");

										break;
								}
							}while(1<s||s>2);
					
							break;

						case 3: //Horizontal
							do{
								printf("Elija en qué sentido horizontal se situará el barco:\n 1. Izquierda\n 2. Derecha\n");
								scanf("%d", &s);

								switch(s){

									case 1: //Izquierda

										for(t=0;t<barcos[j].Tam_Barco;t++){

											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
												if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

												}else{

													if(datos[u].flota[f-1][c+1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{	

														if(datos[u].flota[f-1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}
										
											c=c-1;
										
										}

										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												c=c-1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

											}

										}

										break;

									case 2: //Derecha
							
										for(t=0;t<barcos[j].Tam_Barco;t++){

											if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
												if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

												}else{

													if(datos[u].flota[f-1][c-1] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}

												if(d != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}
											
												if(d != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){
										
													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f-1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{
	
	
	
														}

													}
												}

											} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}

											if(d != 5){

												if(datos[u].flota[f][c] == ' '){

												}else{

													if(datos[u].flota[f][c] == 'X'){

														printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

														d=5;
														t=barcos[j].Tam_Barco;

													}else{



													}

												}
											}
										
											c=c+1;
										
										}	

										if(d != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

											f=f_origen;
											c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen que proporciona el usuario

											for(t=0;t<barcos[j].Tam_Barco;t++){

												datos[u].flota[f][c] == 'X';
												
												c=c+1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

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

				if(datos[u].flota[f][c] == 'X'){
			
					printf("Introduzca otras coordenadas, estas ya están ocupadas por otro barco.");
		
				}else{
			
					printf("Introduzca otras coordenadas, estas se salen de los límites del tablero.");
				
				}
		
				return asignacionManual;
			}
		}
	}
}

void asignacionAutomatica(Configuracion* datos, int u){
	
	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int j;
	int k;

	for(j=0;j<i;j++){
		
		for(k=0;k<datos[0].NBarcos[j];k++){

		}
	}
}		
	


int comprobarTamano(Configuracion* datos){

	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int j;
	int k;
	int t_total=0;

	for(j=0;j<i;j++){

		t_total=t_total+(barcos[j].Tam_Barco+(8+4*(barcos[j].Tam_Barco-1)))*datos[0].NBarcos[j];

	}

	if(t_total<=datos[0].tamTablero){ //Devuelve un 1 si el tamaño es válido, y un 0 en caso contrario
		
		return 1;
	
	} else {
		
		return 0;
	} 
}