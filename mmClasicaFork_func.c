/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene las definiciones
*	de las funciones utilizadas para la multiplicación
*	de matrices, inicialización, impresión y medición
*	del tiempo de ejecución.
***************************************************/

#include "mmClasicaFork_cabecera.h"

// Variables globales para medir el tiempo de ejecución
struct timeval inicio, fin;

// Función para iniciar la medición del tiempo
void InicioMuestra() {
    gettimeofday(&inicio, (void *)0); // Captura el tiempo actual
}

// Función para finalizar la medición del tiempo y calcular la duración
void FinMuestra() {
    gettimeofday(&fin, (void *)0); // Captura el tiempo actual al finalizar
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec); // Calcula el tiempo en microsegundos
    printf("%9.0f \n", tiempo); // Imprime el tiempo transcurrido
}

// Función para realizar la multiplicación de matrices en un rango de filas
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
    double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) { // Itera sobre las filas asignadas
        for (int j = 0; j < D; j++) { // Itera sobre las columnas
            Suma = 0;
            pA = mA + i * D; // Apunta al inicio de la fila actual en mA
            pB = mB + j;     // Apunta al inicio de la columna actual en mB
            for (int k = 0; k < D; k++, pA++, pB += D) { // Realiza el producto punto
                Suma += *pA * *pB;
            }
            mC[i * D + j] = Suma; // Almacena el resultado en la matriz resultante
        }
    }
}

// Función para imprimir una matriz en consola
void impMatrix(double *matrix, int D) {
    if (D < 9) { // Solo imprime matrices pequeñas para evitar saturar la consola
        printf("\nImpresión ...\n");
        for (int i = 0; i < D * D; i++, matrix++) {
            if (i % D == 0) printf("\n"); // Salto de línea al final de cada fila
            printf(" %f ", *matrix);
        }
        printf("\n ");
    }
}

// Función para inicializar las matrices con valores aleatorios
void iniMatrix(double *mA, double *mB, int D) {
    for (int i = 0; i < D * D; i++, mA++, mB++) {
        *mA = rand() % 10; // Genera un número aleatorio entre 0 y 9
        *mB = rand() % 10;
    }
}