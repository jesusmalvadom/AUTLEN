#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estado.h"



/*typedef int* VectorIndices;*/


/**
 * Que reserva espacio para el Estado
Incluyendo una copia en memoria propia del nombre que se 
* proporciona como argumento.
*/
Estado * estadoNuevo( char * nombre, int tipo){
	if(!nombre ){
		fprintf(stderr, "Error en los parámetros de estadoNuevo\n");
		return NULL;
	}
	Estado * e = (Estado *) malloc (sizeof(Estado));
	e->nombre = (char *) malloc(sizeof(char)*(strlen(nombre)+1));
	strcpy(e->nombre, nombre);
	e->tipo = tipo;
	return e;
	
}


/**Que elimina todos los recursos asociados con el estado 
 * que se proporciona como argumento
*/
void estadoElimina( Estado * p_s){
	if(!p_s) return;
	if(p_s->nombre){
		free(p_s->nombre);
		p_s->nombre=NULL;
	}
	free(p_s);
	p_s=NULL;
	return ;
}

/*Que muestra por el FILE * fd el estado proporcionado como argumento*/
void estadoImprime( FILE * fd, Estado * p_s){
	char * imp=NULL;
	if(!fd || !p_s){
		fprintf(stderr, "Error en los parámetros de estadoImprime\n");
		return ;
	}
	switch (p_s->tipo){
		case 0:
			fprintf(fd, "->%s", p_s->nombre);
			break;
		case 1:
			fprintf(fd, "%s*", p_s->nombre);
			break;
		case 2:
			fprintf(fd, "->%s*", p_s->nombre);
			break;
		default:
			fprintf(fd, "%s", p_s->nombre);
	} 
	return;
}

/*Que devuelve 1 si el estado argumento tiene el nombre argumento*/
int estadoEs(Estado * p_s, char * nombre){
	if(!p_s || !nombre){
		fprintf(stderr, "Error en los parámetros de estadoEs\n");
		return 0;
	}
	if(!strcmp(p_s->nombre, nombre)) return 1;
	return 0;
}

/*devuelve un puntero (no una copia en memoria nueva) 
del nombre del estado argumento*/
char * estadoNombre(Estado * p_s){
	if(!p_s){
		fprintf(stderr, "Error con el estado pasado en estadoNombre\n");
		return NULL;
	}
	return p_s->nombre;
}

/*devuelve el tipo del estado argumento */
int estadoTipo(Estado * p_s){
	if(!p_s){
		fprintf(stderr, "Error con el estado pasado en estadoTipo\n");
		return -1;
	}
	return p_s->tipo;
}











