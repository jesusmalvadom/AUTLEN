#include <stdio.h>
#include <stdlib.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3


typedef struct Simbolos{
    char *;
    int tamanyo;
} Simbolos;

typedef struct Alfabeto{
	char *nombre;
    char **simbolos;
    int tamanyo;
} Alfabeto;

typedef struct Palabra{
    char **simbolos;
    int tamanyo;
} Palabra;

typedef struct Estado{
    char *nombre;
    int tipo;
} Estado;
