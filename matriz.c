# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <time.h>

typedef struct nodo{
	int x, y, valor;
	struct nodo * siguiente;
}nodo;
nodo * primeroMatriz1 = NULL;
nodo * ultimoMatriz1 = NULL;
nodo * primeroMatriz2 = NULL;
nodo * ultimoMatriz2 = NULL;
nodo * primeroMatrizR = NULL;
nodo * ultimoMatrizR = NULL;

void imprimir();
void insertarNodo(int x, int y, int valor, int tipoMatriz);
void *calculo();
sem_t sem1;
static int filaResultante=0;  //contendra la posicion de la fila resultante
static int columnaResultante=0;  //contendra la posicion de la fila resultante
static int numFilas, numColumnas2; //contiene las dimensiones de la matriz resultante  
static int numHiloGlobal =0; //contador de hilos global

int main (int argc, char *argv[]){
int columna1, fila2,valor;
columna1 = atoi(argv[2]); 	fila2 = atoi(argv[3]);
if (argc=5 && (columna1==fila2) ){
	int fila1,columna2,a,b;
	//se extraen las dimensiones de las matrices
	fila1 = atoi(argv[1]); 	 	columna2 = atoi(argv[4]); 	
 	int matriz1[fila1][columna1];

	srand (time(NULL));
	//se completan las dos matrices con valores aleatorios
	for (int i = 0; i < 3; ++i)
	{
		if(i==0){
			a=fila1;
			b=columna1;
		}else if(i==1){
			a=fila2;
			b=columna2;
		}else if(i==2){
			a=fila1;
			b=columna2;
		}


		for (int k = 0; k < a; ++k)
		{
			for (int j = 0; j < b; ++j)
			{
				if(i==0){
					valor=rand() % 10;
					insertarNodo(k,j,valor,i); //posicion, valor, tipo de matriz, 
				}else if(i==1){
					valor=rand() % 10;
					insertarNodo(k,j,valor,i);
				}else if(i==2){
					insertarNodo(k,j,0,i);

				}
			}
			printf("\n");

		}
			printf("\n");

	}

	sem_init(&sem1,0,1);
  numFilas=fila2;
  numColumnas2=columna2;
	int numHilos=fila1 * columna2;
	pthread_t hilos[numHilos];

	//CREAR HILOS
	a=0;
	while(a<numHilos){

		pthread_create(&hilos[a], NULL, calculo,NULL);
		a++;	
	}

	//UNIR HILOS
	a =0;
	while(a<numHilos){
		pthread_join(hilos[a], NULL);
		a++;
	}

	imprimir();
}else{
	printf("Datos incorrectos");
}


return 0;
}

void *calculo(){
	int aux=0, col=0, fil=0, valor1, valor2;
	sem_wait(&sem1);

	nodo * actual1 = (nodo*) malloc(sizeof(nodo));
  nodo * actual2 = (nodo*) malloc(sizeof(nodo));
	nodo * actualR = (nodo*) malloc(sizeof(nodo));
	actualR = primeroMatrizR;
	printf("Hilo%d: ",numHiloGlobal);
	
	while(fil<numFilas){
		actual1 = primeroMatriz1;
		actual2 = primeroMatriz2;
		while(1){
			if(actual1->x == filaResultante && actual1->y == col){
				valor1 = actual1->valor;
				break;
			}
			actual1 = actual1->siguiente;
		}
		while(1){
			if(actual2->x == fil && actual2->y == columnaResultante){
				valor2 = actual2->valor;
				break;
			}
			actual2 = actual2->siguiente;
		}

		printf("%d * %d ", valor1, valor2);
		
    aux= aux + valor1 * valor2;
    fil++;
    col++;
    if (fil<numFilas)
    	printf(" + ");
  }
   printf("\n");

  while(1){
  		if(actualR->x == filaResultante && actualR->y == columnaResultante ){
				actualR->valor=aux;
				break;
			}
			actualR = actualR->siguiente;

  }
  columnaResultante++;
  if (columnaResultante ==  numColumnas2){
  	columnaResultante=0;
    filaResultante++;
  }
  
  numHiloGlobal++;
  			printf("\n");

	sem_post(&sem1);

}

void insertarNodo(int x, int y, int valor, int tipoMatriz){
		nodo * nuevo = (nodo*) malloc (sizeof(nodo));
		nuevo->x = x;
		nuevo->y = y;
	 	nuevo->valor = valor;	

	if(tipoMatriz == 0){	  //se ingresa los valores en la matriz 1
			if(primeroMatriz1 == NULL){
				primeroMatriz1 = nuevo;
				primeroMatriz1 -> siguiente = NULL;
				ultimoMatriz1 = nuevo;
			}else{
				ultimoMatriz1->siguiente = nuevo;
				nuevo->siguiente = NULL;
				ultimoMatriz1 = nuevo;
			}
	}else if(tipoMatriz == 1){  //se ingresa los valores en la matriz 2
			if(primeroMatriz2 == NULL){
				primeroMatriz2 = nuevo;
				primeroMatriz2 -> siguiente = NULL;
				ultimoMatriz2 = nuevo;
			}else{
				ultimoMatriz2->siguiente = nuevo;
				nuevo->siguiente = NULL;
				ultimoMatriz2 = nuevo;
			}
	}else if(tipoMatriz == 2){  //se ingresa los valores en la matriz resultante
			if(primeroMatrizR == NULL){
				primeroMatrizR = nuevo;
				primeroMatrizR -> siguiente = NULL;
				ultimoMatrizR = nuevo;
			}else{
				ultimoMatrizR->siguiente = nuevo;
				nuevo->siguiente = NULL;
				ultimoMatrizR = nuevo;
			}

	}
}

void imprimir(){
	int aux=0;
	nodo * actual1 = (nodo*) malloc(sizeof(nodo));
  nodo * actual2 = (nodo*) malloc(sizeof(nodo));
	nodo * actualR = (nodo*) malloc(sizeof(nodo));
	actual1 = primeroMatriz1;
	actual2 = primeroMatriz2;
	actualR = primeroMatrizR;
	
printf("x   y  valor\n");

	while(actual1!= NULL){
		printf("%d  %d  %d\n",actual1->x, actual1->y, actual1->valor);	
			actual1 = actual1 -> siguiente;
  }
	

printf("  \n\n");

	while(actual2!= NULL){
		printf("%d  %d  %d\n",actual2->x, actual2->y, actual2->valor);	
			actual2 = actual2 -> siguiente;
  }
	


	printf("  \n\n");

	while(actualR!= NULL){
		printf("[%d]",actualR->valor);	

			actualR = actualR -> siguiente;
			if(actualR!= NULL){
				if(actualR->x != aux){
					aux=actualR->x;
					printf("\n");
				}
			}
  }
  					printf("\n");

	

}




