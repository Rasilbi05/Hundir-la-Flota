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
	int f_origen, c_origen; //Coordenadas que elige inicialmente el usuario
	int d; //Valor para elegir la dirección, se pondrá a 5 para indicar que ha habido fallo en alguna casilla (el barco no puede situarse en ese sentido)
	int s; //Valor para elegir el sentido dentro de cada dirección
	int j, k, t; //Índices para los bucles for
	int r1, r2; //Valores para indicar la repetición voluntaria de alguno de los do-while, ya sea para comprobar otros sentidos, otras direcciones o directamente introducir otras coordenadas (todo esto siempre en caso de fallo)

	for(j=0;j<i;j++){

		for(k=0;k<datos[0].NBarcos[j];k++){
			
			do{
			
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

														}

													}

													if(d != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{
												
															if(datos[u].flota[f][c-1] == 'X'){
															
																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco	
								
												if(d != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{	

														if(datos[u].flota[f-1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}
									
												if(d != 5){
										
													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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

														}

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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
										
											r1=1;

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

														}

													}

													if(d != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															if(datos[u].flota[f][c-1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(d != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(d != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;	
															t=barcos[j].Tam_Barco;

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

														}

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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

											r1=1;

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

														}

													}

													if(d != 5){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(d != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(d != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(d != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(d != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla izquierda
 
													}else{

														if(datos[u].flota[f][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;	

														}

													}
												}
									
												if(d != 5){
							
													if(datos[u].flota[f][c] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f][c] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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

											r1=1;

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

														}

													}

													if(d != 5){
											
														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(d != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(d != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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
							
														}

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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

											r1=1;

											break;
							
										default:

											printf("Elija una opción válida: 1, 2, 3 ó 4.");

											r1=5;

											break;
									}
							
									if(d = 5){ //Únicamente si ha habido fallo
								
									printf("Si quiere probar otro sentido diagonal introduzca un 5, si no, introduzca cualquier otro entero.\n");
									scanf("%d", &r1);
										
									}
								}while(r1 = 5); //Si el usuario no quiere seguir probando sentidos diagonales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
					
								r2=1;

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

														}

													}

													if(d != 5){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha
 
														}else{

															if(datos[u].flota[f+1][c+1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}
													}

												
												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
												if(d != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;	

														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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
														
															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}
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

											r1=1;

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

														}

													}

													if(d != 5){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															if(datos[u].flota[f-1][c+1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(d != 5){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															if(datos[u].flota[f-1][c] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, esto no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(d != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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

											r1=1;

											break;

										default:

											printf("Elija una opción válida: 1 ó 2.");

											r1=5;

											break;
									}
								
									if(d = 5){ //Únicaamente si ha habido fallo

									printf("Si quiere probar el otro sentido vertical introduzca un 5, si no, introduzca cualquier otro entero.\n");
									scanf("%d", &r1);
							
									}
								}while(r1 = 5); //Si el usuario no quiere seguir probando sentidos verticales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
					
								r2=1;

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

														}

													}

													if(d != 5){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															if(datos[u].flota[f+1][c+1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}
													}	

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(d != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}

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

											r1=1;

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

														}
													}

													if(d != 5){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															if(datos[u].flota[f+1][c-1] == 'X'){

																printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

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

															}

														}
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(d != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(d != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															printf("El barco no tiene al menos una casilla de separación con otro barco, este no es un sentido posible.\n");

															d=5;
															t=barcos[j].Tam_Barco;

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

															if(t != barcos[j].Tam_Barco-1){

																printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}
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

											r1=1;

											break;

										default:

											printf("Elija una opción válida: 1 ó 2.");
								
											r1=5;

											break;
									}
							
									if(d = 5){ //Únicamente si ha habido fallo

									printf("Si quiere probar el otro sentido horizontal introduzca un 5, si no, introduzca cualquier otro entero.\n");
									scanf("%d", &r1);

									}
								}while(r1 = 5); //Si el usuario no quiere seguir probando sentidos horizontales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
								
								r2=1;

								break;

							default: 
				
								printf("Elija una opción válida: 1, 2 ó 3.");

								r2=5;

								break;
						}
				
						if(d = 5 && r1 != 5){ //Primeramente si ha habido fallo, y luego si el usuario ha decidido no probar más sentidos, es decir, quiere elegir otra dirección u otras coordenadas

							printf("Si quieres seguir probando direcciones introduce un 5, si no, introduzca cualquier otro entero. Esta otra elección le llevará a introducir de nuevo otras coordenadas.\n");
							scanf("%d", &r2);

						}
					}while(r2 == 5); //Si el usuario no quiere seguir probando direcciones, pues se irá consecuentemente al siguiente while. Este también se repite si no ha introducido una dirección válida

				}else{

					if(datos[u].flota[f][c] == 'X'){
			
					printf("Introduzca otras coordenadas, estas ya están ocupadas por otro barco.");
		
					}else{
			
					printf("Introduzca otras coordenadas, estas se salen de los límites del tablero.");
				
					}
		
					return asignacionManual;
				}
			}while(d = 5 && r2 != 5); //Si ha habido algún fallo pero el usuario no quiere elegir otra dirección, se le pedirán otras coordenadas para el mismo barco
		}
	}
}

void asignacionAutomatica(Configuracion* datos, int u){
	
	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int f_origen, c_origen; //Coordenadas generadas inicialmente
	int d; //Valor para elegir la dirección
	int s; //Valor para elegir el sentido dentro de cada dirección
	int j, k, t; //Índices para los bucles for
	int r; //Valor para generar otras coordenadas válidas para el mismo barco (0 si queremos evitar la repetición y 1 si queremos otras coordenadas)
	int e; //Valor para detectar el error (estará a 5 en caso de fallo y a 0 para indicar que no hay)
	int v; //Valor para evitar analizar el resto de sentidos y direcciones (se asigna el valor 1 cuando el barco ya ha sido colocado)

	for(j=0;j<i;j++){
		
		for(k=0;k<datos[0].NBarcos[j];k++){
			
			do{
        		
				srand(time(NULL)); //Originará enteros distintos cada vez

				f_origen = rand() % datos[0].tamTablero;   //Origina una coordenada para la fila origen entre 0 y tamTablero-1
       			c_origen = rand() % datos[0].tamTablero;   //Origina una coordenada para la columna origen entre 0 y tamTablero-1

				int f=f_origen, c=c_origen;

				if(datos[u].flota[f][c] == ' '){

					for(d=0;d<3;d++){
		
						switch(d){

							case 0: //Diagonal

								for(s=0;s<4;s++){

									switch(s){

										case 0: //Arriba-derecha
										
											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){

												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{
												
														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{
												
															if(datos[u].flota[f][c-1] == 'X'){
															
																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{
	
															if(datos[u].flota[f+1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco	
								
												if(e != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{	

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}
									
												if(e != 5){
										
													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}
								
												if(e != 5){

													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f-1][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}	
												}
										
												f=f-1; 
												c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

											}
										
											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													f=f-1;
													c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

												}

												v=1;
												s=4;
												d=3;

											}

											break;

										case 1: //Abajo-derecha
								
											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){
									
												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															if(datos[u].flota[f][c-1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(e != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;	
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{	

														if(datos[u].flota[f][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}
												}	
										
												f=f+1;
												c=c+1;
										
											}
								
											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													f=f+1;
													c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

												}

												v=1;
												s=4;
												d=3;

											}

											break;

										case 2: //Arriba-izquierda

											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){
									
												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}	
									
													if(e != 5){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															if(datos[u].flota[f+1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(e != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(e != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(e != 5){

													if(datos[u].flota[f][c] == ' '){ //Casilla izquierda
 
													}else{

														if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;	

														}

													}
												}
									
												if(e != 5){
							
													if(datos[u].flota[f][c] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}
												}	
										
												f=f-1;
												c=c-1;
										
											}

											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'
 
												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													f=f-1;
													c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado	

												}

												v=1;
												s=4;
												d=3;

											}

											break;
						
										case 3: //Abajo-izquierda

											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){
									
												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha 
												
													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){
											
														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															if(datos[u].flota[f-1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}	

												if(e != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}	
												}

												if(e != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;
							
														}

													}		
												}

												if(e != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}
												}	
										
												f=f+1;
												c=c-1;
										
											}
										
											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
													
													f=f+1;
													c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

												}

												v=1,
												s=4;
												d=3;

											}

											break;
									}
								}

								break;
							
							case 1: //Vertical
								
								for(s=0;s<2;s++){	

									switch(s){

										case 0: //Arriba

											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){

												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
										
													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha
 
														}else{

															if(datos[u].flota[f+1][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															if(datos[u].flota[f+1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															if(datos[u].flota[f][c-1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

												
												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
												if(e != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;	

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

													}else{

														if(datos[u].flota[f-1][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{
														
															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}
														}

													}
												}	
										
												f=f-1;
										
											}

											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													f=f-1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

												}

												v=1;
												s=2;
												d=3;

											}

											break;

										case 1: //Abajo
							
											e=0;
										
											for(t=0;t<barcos[j].Tam_Barco;t++){

												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															if(datos[u].flota[f-1][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															if(datos[u].flota[f-1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															if(datos[u].flota[f][c-1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

													}else{

														if(datos[u].flota[f+1][c] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}
												}	
										
												f=f+1;
										
											}

											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													f=f+1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

												}

												v=1;
												s=2;
												d=3;

											}

											break;	
									}
								}	
								
								break;

							case 2: //Horizontal

								for(s=0;s<2;s++){	

									switch(s){

										case 0: //Izquierda

											e=0;

											for(t=0;t<barcos[j].Tam_Barco;t++){	

												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}

													if(e != 5){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															if(datos[u].flota[f+1][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															if(datos[u].flota[f][c+1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{	

															if(datos[u].flota[f-1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															if(datos[u].flota[f+1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}	

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

													}else{

														if(datos[u].flota[f+1][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

													}else{

														if(datos[u].flota[f][c-1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}

														}

													}
												}
										
												c=c-1;
										
											}

											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													c=c-1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

												}

												v=1;
												s=2;
												d=3;

											}

											break;

										case 1: //Derecha
							
											for(t=0;t<barcos[j].Tam_Barco;t++){

												if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
									
													if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

													}else{

														if(datos[u].flota[f-1][c-1] == 'X'){

															d=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															if(datos[u].flota[f+1][c-1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}
											
													if(e != 5){

														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															if(datos[u].flota[f][c-1] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){
										
														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															if(datos[u].flota[f-1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

													if(e != 5){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															if(datos[u].flota[f+1][c] == 'X'){

																e=5;
																t=barcos[j].Tam_Barco;

															}

														}
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

													}else{

														if(datos[u].flota[f-1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

													}else{

														if(datos[u].flota[f+1][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}

													}
												}

												if(e != 5){

													if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

													}else{

														if(datos[u].flota[f][c+1] == 'X'){

															e=5;
															t=barcos[j].Tam_Barco;

														}else{

															if(t != barcos[j].Tam_Barco-1){

																e=5;
																t=barcos[j].Tam_Barco;
															}
														}

													}
												}
										
												c=c+1;
										
											}	

											if(e != 5){ //Comprobamos si el bucle ha acabado exitosamente, y colocamos el barco en las casillas correspondientes marcándolas con una 'X'

												f=f_origen;
												c=c_origen; //Devuelve los valores de las coordenadas, modificadas en el bucle anterior, a los valores de origen

												for(t=0;t<barcos[j].Tam_Barco;t++){

													datos[u].flota[f][c] == 'X';
												
													c=c+1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

												}

												v=1;
												s=2;
												d=3;

											}

											break;
									}
								}

								break;
						}
					}
				
					if(v == 1){ //Si el barco se ha podido colocar, evitamos la reptición del do-while, es decir, no queremos otras coordenadas nuevas para este mismo barco, sino pasar al siguiente barco
					
						r=0;	

					}else{ //No se ha podido colocar el barco, por tanto generamos otras coordenadas

						r=1;
						v=0;

					}

				}else{ //Si las coordenadas originadas no son agua, se originarán otras
		
					r=1;
				}
			}while(r = 1); //Hace generar otras coordenadas para el mismo barco
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