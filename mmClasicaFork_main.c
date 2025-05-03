/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene el programa principal
*	que realiza la multiplicación de matrices utilizando
*	procesos hijos. Divide el trabajo entre procesos y mide
*	el tiempo de ejecución.
***************************************************/

#include "mmClasicaFork_cabecera.h"

int main(int argc, char *argv[]) {
    // Validación de argumentos
    if (argc < 3) {
        printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
        exit(0);
    }

    // Tamaño de la matriz y número de procesos
    int N = (int)atoi(argv[1]);
    int num_P = (int)atoi(argv[2]);

    // Reserva de memoria para las matrices
    double *matA = (double *)calloc(N * N, sizeof(double));
    double *matB = (double *)calloc(N * N, sizeof(double));
    double *matC = (double *)calloc(N * N, sizeof(double));

    srand(time(0)); // Inicializa el generador de números aleatorios

    // Inicialización e impresión de las matrices
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);

    // División del trabajo entre procesos
    int rows_per_process = N / num_P;

    InicioMuestra(); // Inicia la medición del tiempo
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork(); // Crea un proceso hijo

        if (pid == 0) { // Código del proceso hijo
            int start_row = i * rows_per_process;
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;

            multiMatrix(matA, matB, matC, N, start_row, end_row); // Multiplica las filas asignadas

            if (N < 9) { // Imprime la porción calculada por este hijo
                printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row - 1);
                for (int r = start_row; r < end_row; r++) {
                    for (int c = 0; c < N; c++) {
                        printf(" %f ", matC[N * r + c]);
                    }
                    printf("\n");
                }
            }
            exit(0); // El hijo termina su ejecución
        } else if (pid < 0) { // Error al crear el proceso
            perror("fork failed");
            exit(1);
        }
    }

    // El padre espera a que todos los hijos terminen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    FinMuestra(); // Finaliza la medición del tiempo

    // Libera la memoria asignada
    free(matA);
    free(matB);
    free(matC);

    return 0;
}