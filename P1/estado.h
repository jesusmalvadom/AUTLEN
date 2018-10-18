
#ifndef ESTADO_H
#define ESTADO_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define INICIAL	0
#define FINAL	1
#define INICIAL_Y_FINAL	2
#define NORMAL	3

typedef struct _Estado Estado;

Estado * estadoNuevo( char * nombre, int tipo);

void estadoElimina( Estado * p_s);

void estadoImprime( FILE * fd, Estado * p_s);

int estadoEs( Estado * p_s, char * nombre);

char * estadoNombre(Estado * p_s);

int estadoTipo(Estado * p_s);

int estadoCompara(Estado * p_s1, Estado * p_s2);

Estado * estado_copy(Estado * p_s);

#endif
