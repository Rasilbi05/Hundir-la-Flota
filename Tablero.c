#include "Tablero.h"

//Cabecera: char **generarTablero(int)
//Precondición: Se debe haber determinado que el tamaño del tablero respecto al espacio que ocuparán los barcos es válido
//Postcondición: Genera el tablero del tamaño deseado
char **generarTablero(int n){
	int i, j;
	char **M;
	
	M = (char**) malloc(sizeof(char*)*n); //Reserva las filas 
	
	for(i=0;i<n;i++){
	
		M[i] = (char*) malloc(sizeof(char)*n); //Reserva las columnas
	
	}
	
	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

		M[i][j] = ' '; //Recorre la matriz dinámica y rellena cada casilla con huecos en blanco

		}
	}
	
	return M;
}

//Cabecera: void asignacionManual(Configuracion*, int)
//Precondición: Se debe haber seleccionado el modo de asignación manual
//Postcondición: Modifica el tablero situando los barcos, totalmente a elección de los usuarios
void asignacionManual(Configuracion* datos, int u){
	
	int i=obtenerNBarcos();
	Barco* barcos = malloc(sizeof(Barco)*i);
	barcos = cargarBarcos();
	int f_origen, c_origen; //Coordenadas que elige inicialmente el usuario
	int d; //Valor para elegir la dirección, se pondrá a 5 para indicar que ha habido fallo en alguna casilla (el barco no puede situarse en ese sentido), se pondrá a 0 en cada caso para reiniciar el valor y poder cumplir su función de verificación de fallo
	int s; //Valor para elegir el sentido dentro de cada dirección
	int j, k, t; //Índices para los bucles for
	int r1, r2; //Valores para indicar la repetición voluntaria de alguno de los do-while, ya sea para comprobar otros sentidos, otras direcciones o directamente introducir otras coordenadas (todo esto siempre en caso de fallo)
				//r1 se pondrá a 1, valor disntinto de 5 y no se repita el bucle, o cualquier entero distinto de 5 introducido por el usuario cuando no se desee elegir otro sentido
				//r2 se pondrá a 1, valor disntinto de 5 y no se repita el bucle, o cualquier entero distinto de 5 introducido por el usuario cuando no se desee elegir otra dirección

	for(j=0;j<i;j++){

		for(k=0;k<datos[0].NBarcos[j];k++){
			
			do{
			
				printf("Elija las coordenadas de inicio de un barco de tamaño %d (f,c), siendo f fila y c columna.\n", barcos[j].Tam_Barco);
				scanf("%d, %d", &f_origen, &c_origen);

				int f=f_origen, c=c_origen;
				
				if((f > -1 && f < datos[0].tamTablero) && (c > -1 && c < datos[0].tamTablero)){ //Para comprobar si las coordenadas están dentro del tablero
					
					if(datos[u].flota[f][c] == ' '){ //Una vez están dentro comprobamos si es agua, en caso contrario, será un barco

						do{
							printf("A continuacion, elija en que direccion desea situar el barco:\n 1. Diagonal\n 2. Vertical\n 3. Horizontal\n");
							scanf("%d", &d);
			
							switch(d){

								case 1: //Diagonal

									do{

										printf("Elija en que sentido diagonal se situara el barco:\n 1. Arriba-derecha\n 2. Abajo-derecha\n 3. Arriba-izquierda\n 4. Abajo-izquierda\n");
										scanf("%d", &s);

										switch(s){

											case 1: //Arriba-derecha
											
												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){
										
													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

														if(f != datos[0].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}

														}	
														
														if(d != 5){

															if(c != 0){
															
																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{
																
																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){
															if(f != datos[0].tamTablero-1){
															
																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}	
															}
														}

													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco	
									
													if(d != 5){

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{	

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){
											
														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{
																	
																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}	

													if(d != 5){

														if(f != 0){
														
															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && (f == 0 || c == datos[j].tamTablero-1)){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != 0 && c != datos[j].tamTablero-1){

																if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														f=f-1;
														c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

													}

												}
											
												r1=1;

												break;

											case 2: //Abajo-derecha
									
												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){
										
													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){

															if(c != 0){

																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(f != 0){
															
																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}	
															}
														}

													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
								
													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;	
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{	

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && (f == datos[j].tamTablero-1 || c == datos[j].tamTablero-1)){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != datos[j].tamTablero-1 && c != datos[j].tamTablero-1){

																if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														f=f+1;
														c=c+1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

													}

												}

												r1=1;

												break;

											case 3: //Arriba-izquierda

												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){
										
													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){

															if(c != datos[0].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}	
										
														if(d != 5){

															if(f != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}	
															}
														}

													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
								
													if(d != 5){

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f][c] == ' '){ //Casilla arriba-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != 0){

															if(datos[u].flota[f][c] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}	
													}

													if(d != 5){

														if(f != 0){

															if(datos[u].flota[f][c] == ' '){ //Casilla arriba

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}	
													}

													if(d != 5){

														if(c != 0){

															if(datos[u].flota[f][c] == ' '){ //Casilla izquierda
	
															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}
										
													if(d != 5){
								
														if(t != barcos[j].Tam_Barco-1 && (f == 0 || c == 0)){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != 0 && c != 0){

																if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														f=f-1;
														c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado	

													}

												}

												r1=1;

												break;
							
											case 4: //Abajo-izquierda

												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){
										
													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha 
													
															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");
															
																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){
												
															if(c != datos[0].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(f != 0){

																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

													}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
										
													if(d != 5){

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}	

													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}	
														}
													}

													if(d != 5){

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}		
														}
													}

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && (f == datos[j].tamTablero-1 || c == 0)){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != datos[j].tamTablero-1 && c != 0){

																if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
														
														f=f+1;
														c=c-1; //Para ir moviéndome de casilla diagonalmente en el sentido indicado

													}

												}

												r1=1;

												break;
								
											default:

												printf("Elija una opcion valida: 1, 2, 3 o 4.");

												r1=5;

												break;
										}
								
										if(d == 5){ //Únicamente si ha habido fallo
									
										printf("Si quiere probar otro sentido diagonal introduzca un 5, si no, introduzca cualquier otro entero.\n");
										scanf("%d", &r1);
											
										}
									}while(r1 == 5); //Si el usuario no quiere seguir probando sentidos diagonales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
						
									r2=1;

									break;

								case 2: //Vertical
								
									do{
									
										printf("Elija en que sentido vertical se situara el barco:\n 1. Arriba\n 2. Abajo\n");
										scanf("%d", &s);

										switch(s){

											case 1: //Arriba

												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){

													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
														
														if(f != datos[0].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){

															if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha
	
																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(f != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(c != 0){

																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(c != datos[0].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

													
													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
											
													if(d != 5){

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;	

															}
														}
													}

													if(d != 5){

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && f == 0){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != 0){

																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														f=f-1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

													}

												}

												r1=1;

												break;

											case 2: //Abajo
								
												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){

													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
														
														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){
															
															if(f != 0 && c != datos[j].tamTablero-1){
															
																if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}	

														if(d != 5){

															if(f != 0){

																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, esto no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(c != 0){

																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(c != datos[0].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

													}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
													if(d != 5){

														if(f != datos[0].tamTablero-1 && c!= 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}	

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && f == datos[0].tamTablero-1){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(f != datos[j].tamTablero-1){

																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														f=f+1; //Para ir moviéndome de casilla verticalmente en el sentido indicado

													}

												}

												r1=1;

												break;

											default:

												printf("Elija una opción valida: 1 o 2.");

												r1=5;

												break;
										}
									
										if(d == 5){ //Únicamente si ha habido fallo

										printf("Si quiere probar el otro sentido vertical introduzca un 5, si no, introduzca cualquier otro entero.\n");
										scanf("%d", &r1);
								
										}
									}while(r1 == 5); //Si el usuario no quiere seguir probando sentidos verticales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
						
									r2=1;

									break;

								case 3: //Horizontal
								
									do{

										printf("Elija en que sentido horizontal se situara el barco:\n 1. Izquierda\n 2. Derecha\n");
										scanf("%d", &s);

										switch(s){

											case 1: //Izquierda

												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){	

													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
										
														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}

														if(d != 5){

															if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(c != datos[0].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

														if(d != 5){

															if(f != 0){

																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}
															
														if(d != 5){

															if(f != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}	

													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
													if(d != 5){

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){

														if(t != barcos[j].Tam_Barco-1 && c == 0){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(c != 0){

																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
													
														c=c-1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

													}

												}

												r1=1;

												break;

											case 2: //Derecha
								
												d=0;

												for(t=0;t<barcos[j].Tam_Barco;t++){

													if(t == 0){ //Cuando es la primera posición del barco debo analizar todas las casillas alrededor
										
														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;
															}
														}

														if(d != 5){

															if(f != datos[0].tamTablero-1 && c != 0){

																if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}
															
														if(d != 5){

															if(c != 0){

																if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;
					
																}
															}
														}

														if(d != 5){
															
															if(f != 0){

																if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}	
														}

														if(d != 5){
															if(f != datos[0].tamTablero-1){

																if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

																}else{

																	printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																	d=5;
																	t=barcos[j].Tam_Barco;

																}
															}
														}

													} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
													if(d != 5){

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(d != 5){
													
														if(t != barcos[j].Tam_Barco-1 && c == datos[0].tamTablero-1){

															printf("El barco se sale del tablero, este no es un sentido posible.\n");

																d=5;
																t=barcos[j].Tam_Barco;

														}else{

															if(c != datos[j].tamTablero-1){

																if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

																}else{

																printf("El barco no tiene al menos una casilla de separacion con otro barco, este no es un sentido posible.\n");

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

														datos[u].flota[f][c] = 'X';
												
														c=c+1; //Para ir moviéndome de casilla horizontalmente en el sentido indicado

													}

												}

												r1=1;

												break;

											default:

												printf("Elija una opcion valida: 1 o 2.");
								
												r1=5;

												break;
										}
							
										if(d == 5){ //Únicamente si ha habido fallo

										printf("Si quiere probar el otro sentido horizontal introduzca un 5, si no, introduzca cualquier otro entero.\n");
										scanf("%d", &r1);

										}
									}while(r1 == 5); //Si el usuario no quiere seguir probando sentidos horizontales, tal vez querrá probar otras direcciones, y no directamente cambiar de coordenadas. Este también se repite si no ha introducido un sentido válido
								
									r2=1;

									break;

								default: 
				
									printf("Elija una opcion valida: 1, 2 o 3.");

									r2=5;

									break;
							}
				
							if(d == 5 && r1 != 5){ //Primeramente si ha habido fallo, y luego si el usuario ha decidido no probar más sentidos, es decir, quiere elegir otra dirección u otras coordenadas

								printf("Si quieres seguir probando direcciones introduce un 5, si no, introduzca cualquier otro entero. Esta otra eleccion le llevara a introducir de nuevo otras coordenadas.\n");
								scanf("%d", &r2);

							}
						}while(r2 == 5); //Si el usuario no quiere seguir probando direcciones, pues se irá consecuentemente al siguiente while. Este también se repite si no ha introducido una dirección válida

					}else{
			
						printf("Introduzca otras coordenadas, estas ya estan ocupadas por otro barco.");
		
						d=5;
						r2=1;
					}
				}else{

					printf("Introduzca otras coordenadas, estas no estan dentro de los limites del tablero.");
		
					d=5;
					r2=1;
				}

			}while(d == 5 && r2 != 5); //Si ha habido algún fallo pero el usuario no quiere elegir otra dirección, se le pedirán otras coordenadas para el mismo barco
		}
	}
}

//Cabecera: void asignacionAutomatica(Configuracion*, int)
//Precondición: Se debe haber seleccionado el modo de asignación automática
//Postcondición: Modifica el tablero situando los barcos, aleatoriamente y sin intervención de los usuarios
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

				f_origen=rand() % datos[0].tamTablero;  //Origina una coordenada para la fila origen entre 0 y tamTablero-1
       			c_origen=rand() % datos[0].tamTablero;  //Origina una coordenada para la columna origen entre 0 y tamTablero-1

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

													if(f != datos[0].tamTablero-1 && c != 0){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{
													
															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco	
								
												if(e != 5){

													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{	

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}
									
												if(e != 5){
										
													if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}
								
												if(e != 5){

													if(f != 0){

														if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(c != datos[0].tamTablero-1){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && (f == 0 || c == datos[j].tamTablero-1)){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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

													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){
														if(f != 0){
															
															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(e != 5){

													if(f != datos[0].tamTablero-1 && c != 0){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(f != 0 && c != datos[j].tamTablero-1){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															e=5;	
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(f != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(c != datos[0].tamTablero-1){

														if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

														}else{	

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && (f == datos[j].tamTablero-1 || c == datos[j].tamTablero-1)){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != datos[j].tamTablero-1 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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

													if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}	
									
													if(e != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}	
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
							
												if(e != 5){

													if(f != 0 && c != datos[j].tamTablero-1){

														if(datos[u].flota[f][c] == ' '){ //Casilla arriba-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(f != datos[0].tamTablero-1 && c != 0){

														if(datos[u].flota[f][c] == ' '){ //Casilla abajo-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}	

												if(e != 5){

													if(f != 0){

														if(datos[u].flota[f][c] == ' '){ //Casilla arriba

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}	

												if(e != 5){

													if(c != 0){

														if(datos[u].flota[f][c] == ' '){ //Casilla izquierda
	
														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}
									
												if(e != 5){
							
													if(t != barcos[j].Tam_Barco-1 && (f == 0 || c == 0)){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != 0 && c != 0){

															if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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

													if(f != 0 && c != datos[j].tamTablero-1){
														
														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha 
													
														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){
											
														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != 0){
															
															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay tres anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(f != 0 && c != 0){
														
														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{
		
															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}	

												if(e != 5){

													if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(f != datos[0].tamTablero-1){
														
														if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}	
												}

												if(e != 5){

													if(c != 0){
														
														if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}		
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && (f == datos[j].tamTablero-1 || c == 0)){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != datos[j].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
													
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
										
													if(f != datos[j].tamTablero-1 && c != 0){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha
	
															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

												
												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
										
												if(e != 5){

													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){
													
													if(f != 0 && c != datos[j].tamTablero-1){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && f == 0){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != 0){

															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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
									
													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(f != 0 && c != datos[j].tamTablero-1){

															if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != 0){

															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(c != 0){
															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

												}//Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(f != datos[j].tamTablero-1 && c != 0){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && f == datos[j].tamTablero-1){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(f != datos[j].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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
													
													if(f != 0 && c != datos[j].tamTablero-1){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(c != datos[0].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != 0){

															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{	

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}	

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(f != datos[j].tamTablero-1 && c != 0){

														if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && c == 0){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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
									
													if(f != 0 && c != 0){

														if(datos[u].flota[f-1][c-1] == ' '){ //Casilla arriba-izquierda

														}else{

															d=5;
															t=barcos[j].Tam_Barco;
														}
													}

													if(e != 5){

														if(f != datos[j].tamTablero-1 && c != 0){

															if(datos[u].flota[f+1][c-1] == ' '){ //Casilla abajo-izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}
											
													if(e != 5){

														if(c != 0){

															if(datos[u].flota[f][c-1] == ' '){ //Casilla izquierda

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){
										
														if(f != 0){

															if(datos[u].flota[f-1][c] == ' '){ //Casilla arriba

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

													if(e != 5){

														if(f != datos[0].tamTablero-1){

															if(datos[u].flota[f+1][c] == ' '){ //Casilla abajo

															}else{

																e=5;
																t=barcos[j].Tam_Barco;

															}
														}
													}

												} //Cuando son las siguientes iteraciones solo debo analizar algunas en concreto, hay cinco anteriormente analizadas y una de estas es la posición asignada al barco
									
												if(e != 5){

													if(f != 0 && c != datos[j].tamTablero-1){

														if(datos[u].flota[f-1][c+1] == ' '){ //Casilla arriba-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;

														}
													}
												}

												if(e != 5){

													if(f != datos[0].tamTablero-1 && c != datos[0].tamTablero-1){

														if(datos[u].flota[f+1][c+1] == ' '){ //Casilla abajo-derecha

														}else{

															e=5;
															t=barcos[j].Tam_Barco;
				
														}		
													}
												}

												if(e != 5){

													if(t != barcos[j].Tam_Barco-1 && c == datos[j].tamTablero-1){

														d=5;
														t=barcos[j].Tam_Barco;

													}else{

														if(c != datos[j].tamTablero-1){

															if(datos[u].flota[f][c+1] == ' '){ //Casilla derecha

															}else{

																d=5;
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

													datos[u].flota[f][c] = 'X';
												
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
			}while(r == 1); //Hace generar otras coordenadas para el mismo barco
		}
	}
}		