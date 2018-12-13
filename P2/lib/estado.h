
#ifndef ESTADO_H
#define ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3


typedef struct Estado{
    char *nombre;
    int tipo;
} Estado;

typedef int* VectorIndices;

/**
 * reserva espacio para el Estado
Incluyendo una copia en memoria propia del nombre que se 
* proporciona como argumento.
*/
Estado * estadoNuevo(char *nombre, int tipo);


/**elimina todos los recursos asociados con el estado 
 * que se proporciona como argumento
*/
void estadoElimina( Estado * p_s);


/*muestra por el FILE * fd el estado proporcionado como argumento*/
void estadoImprime( FILE * fd, Estado * p_s);


/*Que devuelve 1 si el estado argumento tiene el nombre argumento*/
int estadoEs(Estado * p_s, char * nombre);


/*devuelve un puntero (no una copia en memoria nueva) 
del nombre del estado argumento*/
char * estadoNombre(Estado * p_s);


/*devuelve el tipo del estado argumento */
int estadoTipo(Estado * p_s);

/* Devuelve el tipo pasado como argumento en formato cadena de caracteres */
char *nombreTipo(int tipo);


/****************************************************************************/
/****************************************************************************/
/**************************** VectorIndices *********************************/
/****************************************************************************/
/****************************************************************************/

/**
Dimensiona un vector de enteros de tamano posiciones.
Lo devuelve
*/
VectorIndices VectorIndicesNuevo(int tamano);

/** 
Elimina el vector de indices pasado como argumento
*/
void VectorIndicesElimina(VectorIndices vi);

/** 
Imprime el vector de indices 
*/
void VectorIndicesImprime(FILE *fd, VectorIndices vi, int tamano);

void VectorIndicesSetI(VectorIndices vi, int i);

void VectorIndicesUnsetI(VectorIndices vi, int i);

int VectorIndicesGetI(VectorIndices vi, int i);

#endif
