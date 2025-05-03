/************************************************
*	PONTIFICIA UNIVERSIDAD JAVERIANA
*	Autor: SThomas Arevalo Rodriguez, Diego Castrillon, Sebastian Vargas Casquete
*	Asignatura: Sistemas Operativos
*	Clase: 2154
*	Fecha: 01 - 05 - 2025
*   Tema: Taller de Evaluación de Rendimiento
*	Descripción: Este archivo contiene las definiciones
*	de las funciones utilizadas para la multiplicación
*	de matrices, inicialización, impresión y medición
*	del tiempo de ejecución en mmClasica con POSIX.
***************************************************/
#include "mmClasicaPosix_cabecera.h" // Incluye el encabezado con las definiciones necesarias
#define DATA_SIZE (1024*1024*64*3) // Tamaño del bloque de memoria reservado (en doubles)

// Declaración de un mutex para sincronización entre hilos
pthread_mutex_t MM_mutex;

// Reservamos un bloque grande de memoria para matrices
double MEM_CHUNK[DATA_SIZE];

// Punteros para las matrices A, B y C
double *mA, *mB, *mC;


// Variables globales para medir el tiempo de ejecución
struct timeval inicio, fin;

// Función para iniciar la medición del tiempo
void InicioMuestra() {
    gettimeofday(&inicio, (void *)0); // Captura el tiempo actual
}

// Función para finalizar la medición del tiempo y calcular la duración
void FinMuestra() {
    gettimeofday(&fin, (void *)0); // Captura el tiempo al final
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec); // Calcula el tiempo en microsegundos
    printf("%9.0f \n", tiempo); // Imprime el tiempo transcurrido
}

// Función para inicializar las matrices A y B con valores aleatorios y C en cero
void iniMatrix(int SZ) {
    for (int i = 0; i < SZ * SZ; i++) {
        mA[i] = rand() % 10; // Valor aleatorio entre 0 y 9
        mB[i] = rand() % 10;
        mC[i] = 0;           // Inicializa matriz C en cero
    }
}

// Función para imprimir una matriz en consola
void impMatrix(int sz, double *matriz) {
    if (sz < 12) { // Imprime solo si la matriz es pequeña
        for (int i = 0; i < sz * sz; i++) {
            if (i % sz == 0) printf("\n"); // Salto de línea al cambiar de fila
            printf(" %.3f ", matriz[i]);
        }
        printf("\n>-------------------->\n");
    }
}

// Función que ejecuta la multiplicación de matrices en un hilo
void *multiMatrix(void *variables) {
    struct parametros *data = (struct parametros *)variables; // Casteo de los argumentos

    // Extracción de parámetros desde la estructura
    int idH = data->idH; // ID del hilo actual
    int nH  = data->nH;  // Número total de hilos
    int N   = data->N;   // Dimensión de la matriz

    // Determina el rango de filas que este hilo debe procesar
    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    // Multiplicación de matrices por bloques de filas asignadas al hilo
    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA, *pB, sumaTemp = 0.0;
            pA = mA + (i * N); // Apunta al inicio de la fila i en A
            pB = mB + j;       // Apunta al inicio de la columna j en B

            for (int k = 0; k < N; k++, pA++, pB += N) { // Producto punto fila-columna
                sumaTemp += (*pA * *pB);
            }

            mC[i * N + j] = sumaTemp; // Almacena el resultado en la matriz C
        }
    }

    // Sección crítica vacía — se reserva para sincronización futura si se necesita
    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);

    pthread_exit(NULL); // Finaliza el hilo
}
