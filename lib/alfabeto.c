#include <stdio.h>
#include <stdlib.h>
#include "alfabeto.h"


/**
	Funcion que devuelve un alfabeto creado
*/
Alfabeto * alfabetoNuevo(char *nombre, int tamano) {
	Alfabeto *alfabeto ;

	alfabeto = (Alfabeto *) malloc(sizeof(Alfabeto) + tamano * sizeof(char *));
	alfabeto->nombre = nombre;
	alfabeto->tamano = tamano;

	return alfabeto; 
}

/**
	Funcion que libera un alfabeto
*/
void alfabetoElimina(Alfabeto * p_alfabeto) {
	for (int i = 0; i < p_alfabeto->tamano; i++) {
		free(p_alfabeto->simbolos[i]);
	}

	free(p_alfabeto->nombre);
	free(p_alfabeto);
}


