#IFNDEF ESTADO_H
/**
 * reserva espacio para el Estado
Incluyendo una copia en memoria propia del nombre que se 
* proporciona como argumento.
*/
Estado * estadoNuevo( char * nombre, int tipo);


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




#ENDIF
