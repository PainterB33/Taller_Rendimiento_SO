/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene las declaraciones
*	de las funciones utilizadas en mmClasicaPosix. Es la cabecera del proyecto.
***************************************************/
#ifndef MMCLASICA_POSIX_CABECERA_H
#define MMCLASICA_POSIX_CABECERA_H


#include <stdio.h>     // Para funciones de entrada/salida como printf  
#include <pthread.h>  // Para funciones de hilos como pthread_create y pthread_join
#include <unistd.h>  // Para funciones relacionadas con procesos como fork
#include <stdlib.h> // Para funciones de memoria dinámica como malloc y calloc
#include <time.h>   // Para inicializar el generador de números aleatorios
#include <sys/time.h> // Para medir el tiempo de ejecución

// Declaraciones de variables globales
extern double *mA, *mB, *mC;
extern double MEM_CHUNK[];
extern pthread_mutex_t MM_mutex;

// Estructura para parámetros
struct parametros {
    int nH;  // Número total de hilos
    int idH; // ID del hilo actual
    int N;   // Dimensión de las matrices cuadradas
};


// Declaraciones de funciones
// Función para iniciar la medición del tiempo
void InicioMuestra();
// Función para finalizar la medición del tiempo y calcular la duración
void FinMuestra();
// Función para inicializar las matrices con valores aleatorios
void iniMatrix(int SZ);
// Función para imprimir una matriz en consola
void impMatrix(int sz, double *matriz);
// Función para realizar la multiplicación de matrices en un rango de filas
void *multiMatrix(void *variables);

#endif // MMCLASICA_POSIX_CABECERA_H