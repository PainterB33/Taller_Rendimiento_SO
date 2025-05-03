/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: Thomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene el programa principal
*	que realiza la multiplicación de matrices utilizando
*	hilos POSIX. Divide el trabajo entre hilos y mide
*	el tiempo de ejecución.
***************************************************/
#include "mmClasicaPosix_cabecera.h"

int main(int argc, char *argv[]) {
    // Validación de argumentos: espera tamaño de matriz y número de hilos
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        exit(0);
    }

    int SZ = atoi(argv[1]);       // Dimensión de la matriz (matriz cuadrada de SZ x SZ)
    int n_threads = atoi(argv[2]); // Número de hilos a utilizar

    pthread_t p[n_threads];         // Arreglo de identificadores de hilos
    pthread_attr_t atrMM;           // Atributos para los hilos

    // Asignación de bloques de memoria para matrices A, B y C desde un arreglo estático
    mA = MEM_CHUNK;               // mA apunta al inicio del bloque
    mB = mA + SZ * SZ;            // mB apunta justo después de mA
    mC = mB + SZ * SZ;            // mC apunta justo después de mB

    // Inicialización e impresión de matrices A y B
    iniMatrix(SZ);
    impMatrix(SZ, mA);
    impMatrix(SZ, mB);

    InicioMuestra(); // Comienza la medición del tiempo de ejecución

    pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex 
    pthread_attr_init(&atrMM);           // Inicializa atributos de hilo
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Hilos se pueden unir al final

    // Creación de los hilos
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
        datos->idH = j;           // ID del hilo
        datos->nH  = n_threads;   // Número total de hilos
        datos->N   = SZ;          // Tamaño de la matriz

        pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos); // Crea el hilo
    }

    // Espera a que todos los hilos terminen
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

    FinMuestra(); // Finaliza la medición del tiempo
    impMatrix(SZ, mC); // Imprime la matriz resultado

    // Limpieza de recursos
    pthread_attr_destroy(&atrMM);   // Libera los atributos
    pthread_mutex_destroy(&MM_mutex); // Destruye el mutex
    pthread_exit(NULL);            // Finaliza el programa principal correctamente
}

