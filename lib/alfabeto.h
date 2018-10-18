#ifndef ALFABETO_H
#define ALFABETO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_SIMBOLO 50

typedef struct Simbolos{
    char *nombre;
    int tamano;
} Simbolos;

typedef struct Alfabeto{
	char *nombre;
    char **simbolos;
    int tamano;
    int n_simbolos;
} Alfabeto;

Alfabeto * alfabetoNuevo(char *nombre, int tamano);
void alfabetoElimina(Alfabeto * p_alfabeto);
Alfabeto * alfabetoInsertaSimbolo(Alfabeto * p_alfabeto, char * simbolo);
void alfabetoImprime(FILE * fd, Alfabeto * p_alf);
char* alfabetoSimboloEn(Alfabeto * p_alf, int i);
int alfabetoIndiceDeSimbolo(Alfabeto * p_alf, char * simbolo);
int alfabetoTamano(Alfabeto * p_alf);

#endif