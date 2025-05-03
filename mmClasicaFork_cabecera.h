/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene las declaraciones
*	de las funciones utilizadas en el programa principal
*	y en la librería de funciones. Es la cabecera del proyecto.
***************************************************/

#ifndef MMCLASICA_FORK_CABECERA_H
#define MMCLASICA_FORK_CABECERA_H

#include <stdio.h>      // Para funciones de entrada/salida como printf
#include <stdlib.h>     // Para funciones de memoria dinámica como malloc y calloc
#include <unistd.h>     // Para funciones relacionadas con procesos como fork
#include <sys/wait.h>   // Para esperar la finalización de procesos hijos
#include <sys/time.h>   // Para medir el tiempo de ejecución
#include <time.h>       // Para inicializar el generador de números aleatorios

// Declaraciones de funciones
// Función para iniciar la medición del tiempo
void InicioMuestra();

// Función para finalizar la medición del tiempo y calcular la duración
void FinMuestra();

// Función para realizar la multiplicación de matrices en un rango de filas
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

// Función para imprimir una matriz en consola
void impMatrix(double *matrix, int D);

// Función para inicializar las matrices con valores aleatorios
void iniMatrix(double *mA, double *mB, int D);

#endif // MMCLASICA_FORK_CABECERA_H