GCC = gcc
CFLAGS = -lm
FOPENMP = -fopenmp -O3
POSIX = -lpthread

modulo = inter.c

PROGRAMAS = mmClasicaOpenMP mmClasicaFork mmClasicaPosix

ALL: $(PROGRAMAS)

mmClasicaPosix:
	$(GCC) $(CFLAGS) $@_cabecera.h $@_func.c $@_main.c -o $@ $(POSIX)

mmClasicaFork:
	$(GCC) $(CFLAGS) $@_cabecera.h $@_func.c $@_main.c -o $@ 

mmClasicaOpenMP:
	$(GCC) $(CFLAGS) $@_cabecera.h $@_func.c $@_main.c -o $@ $(FOPENMP)

clean:
	$(RM) $(PROGRAMAS)