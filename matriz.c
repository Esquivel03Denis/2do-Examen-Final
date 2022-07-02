# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <time.h>



void *calculo();
sem_t sem1;
static int * matriz1Global;
static int * matriz2Global;
static int * matrizResultanteGlobal;

static int indiceGlobal=0;  //
static int filaResultante1=0;  //contendra la posicion de la fila resultante
static int columnaResultante1=0;  //contendra la posicion de la fila resultante
static int filaResultante2=0; 
static int columnaResultante2=0;  



int main (int argc, char *argv[]){

if(argc >=1 && argc<=4){
	int fila1,columna1,fila2,columna2,a,b;
	//se extraen las dimensiones de las matrices
	fila1 = atoi(argv[1]); 	columna1 = atoi(argv[2]); 	fila2 = atoi(argv[3]); 	columna2 = atoi(argv[4]);
	int matriz1[fila1][columna1]; 	
	int matriz2[fila2][columna2]; 	

	srand (time(NULL));
	//se completan las dos matrices con valores aleatorios
	for (int i = 0; i < 2; ++i)
	{
		if(i==0){
			a=fila1;
			b=columna1;
		}else{
			a=fila2;
			b=columna2;
		}

		for (int k = 0; k < a; ++k)
		{
			for (int j = 0; j < b; ++j)
			{
				if(i==0){
					matriz1[k][j]=rand();
					printf("%d\n",matriz1[k][j]);
				}else{
					matriz2[k][j]=rand();
					printf("%d\n",matriz2[k][j]);
				}
			}
		}
	}
	sem_init(&sem1,0,1);
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
	while(a<argumento2){
		pthread_join(hilos[a], NULL);
		a++;
	}

}else{
	printf("Datos incorrectos")
}
return 0;
}

void *calculo(){
	int aux=0;
	sem_wait(&sem1);

	for (int k = 0; k < a; ++k)
	{
		for (int j = 0; j < b; ++j)
		{

			aux = matriz1Global[k][k]


	
	sem_post(&sem1);
	printf("DESPUES%d\n",vectorGlobal[variableGlobalIndice].inicio );


	
}

