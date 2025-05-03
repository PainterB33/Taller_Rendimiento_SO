 /************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: fichero principal para la multiplicación de matrices con OpenMP.
***************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include "mmClasicaOpenMP_cabecera.h"
 
 int main(int argc, char *argv[]){
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}

	int N = atoi(argv[1]);
	int TH = atoi(argv[2]);
	size_t *matrixA  = (size_t *)calloc(N*N, sizeof(size_t));
	size_t *matrixB  = (size_t *)calloc(N*N, sizeof(size_t));
	size_t *matrixC  = (size_t *)calloc(N*N, sizeof(size_t));
	srand(time(NULL));

	omp_set_num_threads(TH);

	iniMatrix(matrixA, matrixB, N);

	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	InicioMuestra();
	multiMatrix(matrixA, matrixB, matrixC, N);
	FinMuestra();

	impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}