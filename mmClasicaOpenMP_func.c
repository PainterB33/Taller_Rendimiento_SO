/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción:  * Funciones auxiliares para la multiplicación clásica de matrices con OpenMP.
***************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <sys/time.h>
 #include <omp.h>
 #include "mmClasicaOpenMP_cabecera.h"
 
 // Variables globales para medición del tiempo
struct timeval inicio, fin;
 
 /*
  * iniMatrix:
  * Llena las matrices A y B con valores aleatorios entre 0 y 9.
  */
 void iniMatrix(size_t *m1, size_t *m2, int D){
	for(int i=0; i<D*D; i++, m1++, m2++){
		*m1 = i*2; // (size_t) rand()%10;	
		*m2 = i+2; // (size_t) rand()%10;	
	}
}
 
 /*
  * impMatrix:
  * Imprime una matriz cuadrada D x D. Útil para verificar valores con matrices pequeñas.
  */
 void impMatrix(size_t *matrix, int D){
	printf("\n");
	if(D < 9){
		for(int i=0; i<D*D; i++){
			if(i%D==0) printf("\n");
			printf("%zu ", matrix[i]);
		}
		printf("\n**-----------------------------**\n");
	}
}
 
 /*
  * InicioMuestra:
  * Registra el tiempo de inicio de la ejecución.
  */
 void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}
 
 /*
  * FinMuestra:
  * Calcula y muestra el tiempo de ejecución desde InicioMuestra.
  */
 void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec); 
	printf("%9.0f \n", tiempo);
}
 
 /*
  * multiMatrix:
  * Multiplicación clásica de matrices cuadradas usando OpenMP.
  * Utiliza aritmética de punteros (pA, pB) para optimizar el acceso.
  * Se paraleliza el bucle exterior con OpenMP.
  *
  * Parámetros:
  * - mA: matriz A de entrada
  * - mB: matriz B de entrada
  * - mC: matriz resultado
  * - D: dimensión de las matrices cuadradas
  */
 void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D) {
	 size_t Suma, *pA, *pB;
 
	 #pragma omp parallel
	 {
		 #pragma omp for
		 for (int i = 0; i < D; i++) {
			 for (int j = 0; j < D; j++) {
				 pA = mA + i * D;     // Apunta al inicio de la fila i de mA
				 pB = mB + j;         // Apunta a la columna j de mB (recorrido por filas)
				 Suma = 0.0;
 
				 for (int k = 0; k < D; k++, pA++, pB += D) {
					 Suma += *pA * *pB;  // Multiplicación acumulada
				 }
 
				 mC[i * D + j] = Suma;
			 }
		 }
	 }
 }