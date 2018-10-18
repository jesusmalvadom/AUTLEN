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

/**
	Guarda en la colección de símbolos del alfabeto una copia en memoria nueva del argumento propocionado 
*/
Alfabeto * alfabetoInsertaSimbolo(Alfabeto * p_alfabeto, char * simbolo);

/**
	Imprime el alfabeto por el FILE * argumento
*/
void alfabetoImprime(FILE * fd, Alfabeto * p_alf);

/**
	Devuelve el símbolo que está en la posición pasada como argumento 
	en el alfabeto proporcionado como argumento.
	No se hace copia en memoria nueva, se devuelve un puntero a la cadena.
*/
char* alfabetoSimboloEn(Alfabeto * p_alf, int i);

/**
	Se devuelve la posición en la que está el alfabeto 
*/
int alfabetoIndiceDeSimbolo(Alfabeto * p_alf, char * simbolo);




