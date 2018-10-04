#ifndef ALFABETO_H
#define ALFABETO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Simbolos{
    char *nombre;
    int tamano;
} Simbolos;

typedef struct Alfabeto{
	char *nombre;
    char **simbolos;
    int tamano;
} Alfabeto;

Alfabeto * alfabetoNuevo(char *nombre, int tamano);
void alfabetoElimina(Alfabeto * p_alfabeto);

#endif