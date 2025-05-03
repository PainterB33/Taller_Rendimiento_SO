 /************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Cabecera para funciones auxiliares de multiplicación de matrices con OpenMP.
***************************************************/

 #ifndef MMCLASICAOPENMP_CABECERA_H
 #define MMCLASICAOPENMP_CABECERA_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <sys/time.h>
 #include <omp.h>
 
 // Inicializa matrices A y B con valores aleatorios
 void iniMatrix(size_t *m1, size_t *m2, int D);
 
 // Imprime una matriz cuadrada D x D
 void impMatrix(size_t *matrix, int D);
 
 // Marca el inicio de la medición del tiempo
 void InicioMuestra();
 
 // Marca el final de la medición e imprime el tiempo transcurrido
 void FinMuestra();
 
 // Multiplicación de matrices con OpenMP, versión con punteros
 void multiMatrix(size_t *mA, size_t *mB, size_t *mC, int D);
 
 #endif