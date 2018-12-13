
#include "alfabeto.h"


/**
	Funcion que devuelve un alfabeto creado
*/
Alfabeto * alfabetoNuevo(char *nombre, int tamano) {
	if (!nombre) return NULL;

	Alfabeto *alfabeto;
	alfabeto = (Alfabeto *) malloc(sizeof(Alfabeto) + tamano * strlen(nombre));

	alfabeto->nombre = strdup(nombre);
	alfabeto->tamano = tamano;

    alfabeto->simbolos = (char **) malloc(tamano * sizeof(char *));
    for (int i=0; i < tamano; i++){
    	alfabeto->simbolos[i] = (char *) malloc(sizeof(char) * MAX_LEN_SIMBOLO);
    }

    alfabeto->n_simbolos = 0;

	return alfabeto; 
}

/**
	Funcion que libera un alfabeto
*/
void alfabetoElimina(Alfabeto * p_alfabeto) {
	if (p_alfabeto == NULL) return;
	for (int i = 0; i < p_alfabeto->tamano; i++) {
		free(p_alfabeto->simbolos[i]);
	}

	free(p_alfabeto->simbolos);
	free(p_alfabeto->nombre);
	free(p_alfabeto);
}

/**
	Guarda en la colección de símbolos del alfabeto una copia en memoria nueva del argumento propocionado 
*/
Alfabeto * alfabetoInsertaSimbolo(Alfabeto * p_alfabeto, char * simbolo) {
	if (p_alfabeto == NULL || simbolo == NULL) return NULL;

	/* Comprobamos que el simbolo no esta ya en el alfabeto */
	for (int i=0; i<p_alfabeto->n_simbolos; i++) {
		if (strcmp(p_alfabeto->simbolos[i], simbolo) == 0) return p_alfabeto;
	}

	p_alfabeto->simbolos[p_alfabeto->n_simbolos] = strcpy(p_alfabeto->simbolos[p_alfabeto->n_simbolos], simbolo);
	p_alfabeto->n_simbolos++;
	return p_alfabeto;
}

/**
	Imprime el alfabeto por el FILE * argumento
*/
void alfabetoImprime(FILE * fd, Alfabeto * p_alf) {
	if (fd == NULL || p_alf == NULL) return;

	fprintf(fd, "%s={ ", p_alf->nombre);
	for (int i=0; i < p_alf->n_simbolos; i++) {
		fprintf(fd, "%s ", p_alf->simbolos[i]);
	}
	fprintf(fd, "}\n");
}

/**
	Devuelve el símbolo que está en la posición pasada como argumento 
	en el alfabeto proporcionado como argumento.
	No se hace copia en memoria nueva, se devuelve un puntero a la cadena.
*/
char* alfabetoSimboloEn(Alfabeto * p_alf, int i) {
	if (p_alf == NULL) return NULL;
	if (i >= p_alf->n_simbolos) return NULL;

	return p_alf->simbolos[i];
}

/**
	Se devuelve la posición en la que está el alfabeto 
*/
int alfabetoIndiceDeSimbolo(Alfabeto * p_alf, char * simbolo) {
	if (p_alf == NULL) return -1;
	for (int i=0; i < p_alf->n_simbolos; i++) {
		if (strcmp(p_alf->simbolos[i], simbolo) == 0)
			return i;
	}
	return -1;
}

int alfabetoTamano(Alfabeto * p_alf) {
	if (p_alf == NULL) return -1;
	return p_alf->tamano;
}




