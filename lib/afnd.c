#include "afnd.h"
#include "estado.h"
#include "palabra.h"
#include "alfabeto.h"

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos) {
	AFND *p_afnd = NULL;
	if (nombre[0] == '\0' || num_estados < 0 || num_simbolos < 0) return NULL;

	p_afnd = (AFND *) malloc(sizeof(char) * MAX_LEN_NOMBRE);
	strcpy(p_afnd->nombre, nombre);

	p_afnd->num_estados = num_estados;
	p_afnd->num_simbolos = num_simbolos;

	char nombre_alfabeto[MAX_LEN_NOMBRE];
	sprintf(nombre_alfabeto, "alf_%s", nombre);
	p_afnd->alfabeto = alfabetoNuevo(nombre_alfabeto, num_simbolos);
	if (p_afnd->alfabeto == NULL) return NULL;

	p_afnd->estados = (Estado **) malloc(sizeof(Estado) * num_estados);
	if (p_afnd->estados == NULL) return NULL;

	p_afnd->cadena_actual = palabraNueva();
	if (p_afnd->cadena_actual == NULL) return NULL;



	return p_afnd;
}

void AFNDElimina(AFND * p_afnd) {
	if (p_afnd == NULL) return;

	free(p_afnd->nombre);

	alfabetoElimina(p_afnd->alfabeto);

	for (int i = 0; i < p_afnd->num_estados; i++) {
		estadoElimina(p_afnd->estados[i]);
	}
	
	free(p_afnd->estados);

	palabraElimina(p_afnd->cadena_actual);

	return;
}

void AFNDImprime(FILE * fd, AFND* p_afnd) {
	return;
}

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo) {
	return NULL;
}

AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo) {
	return NULL;
}

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra) {
	return NULL;
}

AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f ) {
	return NULL;
}

AFND * AFNDInicializaCadenaActual (AFND * p_afnd ) {
	return NULL;
}


void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd) {
	return;
}

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd) {
	return;
}

AFND * AFNDInicializaEstado (AFND * p_afnd) {
	return NULL;
}

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd) {
	return;
}

void AFNDTransita(AFND * p_afnd) {
	return;
}
