#include <stdio.h>
#include <stdlib.h>
#include "estado.h"

#define INICIAL 0
#define FINAL   1
#define INICIAL_Y_FINAL 2
#define NORMAL 3

typedef struct Estado{
    char *nombre;
    int tipo;
} Estado;


/**
 * Que reserva espacio para el Estado
Incluyendo una copia en memoria propia del nombre que se 
* proporciona como argumento.
*/
Estado * estadoNuevo( char * nombre, int tipo){
	Estado *estado;
	
	estado = (Estado*)malloc(sizeof())
	
	
	return estado;
	
}


/**Que elimina todos los recursos asociados con el estado 
 * que se proporciona como argumento
*/
void estadoElimina( Estado * p_s){
	
}
