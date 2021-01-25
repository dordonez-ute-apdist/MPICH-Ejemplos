/* Programa MPI que calcula el promedio de un arreglo de enteros */

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //para time()
#include <mpi.h>

double promInts(int numeros[], int talla) {
	double promedio = 0.0;
	for(int i = 0; i < talla; i++) {
		promedio += numeros[i];
	}
	return promedio /= talla;
}

double promDbls(double numeros[], int talla) {
	double promedio = 0.0;
	for(int i = 0; i < talla; i++) {
		promedio += numeros[i];
	}
	return promedio /= talla;
}

int main(int argc, char *argv[]) {
	int master = 0;
	int rank,size;
	int cuantos = 200000;
	int numeros[cuantos];
	time_t t;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	srand((unsigned int)time(&t)+rank);

	//el master genera números aleatorios
	if(rank == master) {
		for(int i = 0; i < cuantos; i++) {
			numeros[i] = rand();
		}
		// solo para confirmar
		printf("Promedio de control: %f\n", promInts(numeros, cuantos));	
	}

	// se reparten los números
	int parte = cuantos / size;
	int misnumeros[parte];
	MPI_Scatter(numeros, parte, MPI_INT, misnumeros, parte, MPI_INT, master, MPI_COMM_WORLD);
	
	// cada uno calcula su promedio
	double mipromedio = promInts(misnumeros, parte);
	printf("Mi promedio( rank: %d): %f\n", rank, mipromedio);	

	// se recuperan los promedios parciales
	double lospromedios[size];	
	MPI_Gather(&mipromedio, 1, MPI_DOUBLE, lospromedios, 1, MPI_DOUBLE, master, MPI_COMM_WORLD);

	// el master calcula el promedio final
	if(rank == master) {
		printf("Promedio global: %f\n", promDbls(lospromedios, size));
	}

	MPI_Finalize();
	return 0; 
}