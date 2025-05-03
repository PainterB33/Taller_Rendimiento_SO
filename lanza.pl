#!/usr/bin/perl
# **************************************************************
# 	PONTIFICIA UNIVERSIDAD JAVERIANA
# 	Autor: Sebastian Vargas Casquete, Thomas Arevalo Rodriguez, Diego Castrillon
# 	Asignatura: Sistemas Operativos
# 	Clase: 2154
# 	Fecha: 02 - 05 - 2025
# 	Tema: Taller de Evaluación de Rendimiento
# 	Descripción: Este script automatiza la ejecución por lotes
# 	de un programa de multiplicación de matrices. Genera 
# 	archivos de salida con los resultados para diferentes 
# 	tamaños de matrices y números de hilos en formato CSV.
# **************************************************************

# Obtiene el directorio actual de trabajo
$Path = `pwd`;          # Ejecuta el comando `pwd` para obtener el directorio actual
chomp($Path);           # Elimina el salto de línea al final del path

# Lista de nombres de ejecutables que se van a ejecutar
@Ejecutables = ("mmClasicaPosix", "mmClasicaFork", "mmClasicaOpenMP");

# Lista de tamaños de matrices a probar
@Size_Matriz = ("200", "300"); # Tamaños de matrices que se usarán en las pruebas

# Lista de números de hilos a utilizar
@Num_Hilos = (1, 2, 4); # Cantidad de hilos que se asignarán para cada prueba

# Número de repeticiones para cada combinación de tamaño e hilos
$Repeticiones = 30; # Número de veces que se ejecutará cada combinación

# Itera sobre cada ejecutable
foreach $Nombre_Ejecutable (@Ejecutables) {
	# Itera sobre cada tamaño de matriz
	foreach $size (@Size_Matriz) {
    		# Itera sobre cada número de hilos
    		foreach $hilo (@Num_Hilos) {
        		# Nombre del archivo donde se almacenarán los resultados en formato CSV
        		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".csv";

        		# Abre el archivo en modo escritura
        		open(my $fh, '>', $file) or die "No se pudo abrir el archivo '$file' $!";

        		# Escribe la cabecera del archivo CSV
        		print $fh "Ejecucion;Tiempo\n";

        		# Ejecuta el programa el número de veces especificado
        		for ($i = 1; $i <= $Repeticiones; $i++) {
            			# Ejecuta el programa y captura el tiempo de ejecución
            			my $output = `$Path/$Nombre_Ejecutable $size $hilo`;
            			chomp($output);

            			# Escribe el resultado en el archivo CSV
            			print $fh "$i;$output\n";

            			# Imprime el comando que se ejecutaría (para depuración)
            			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
        		}

        		# Cierra el archivo
        		close($fh);
    		}
	}
}
