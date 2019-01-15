#ifndef AFND_H
#define AFND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"
#include "palabra.h"
#include "alfabeto.h"

#define MAX_LEN_NOMBRE 100

typedef struct AFND {
	char* nombre;
	Alfabeto* alfabeto;
	int num_estados;
	int num_estados_activos;
	int num_simbolos;
	
	Estado** estados;
	Estado** estados_activos;
	VectorIndices** transiciones;
	int** matriz_ltransiciones;
	//int** matriz_DOT;
	Palabra* cadena_actual; 

}AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);

void AFNDElimina(AFND * p_afnd);

void ImprimeMatriz(FILE* fd, int ** matriz, int size);

void AFNDImprime(FILE * fd, AFND* p_afnd);

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);

AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);

AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f );

AFND * AFNDInicializaCadenaActual (AFND * p_afnd );


void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd);

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd);

AFND * AFNDInicializaEstado (AFND * p_afnd);

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);

void AFNDTransita(AFND * p_afnd);

int AFNDGetEstadoIndice(AFND * p_afnd, char* nombre_estado);


/**********PRACTICA 2**********/

AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f );

AFND * AFNDCierraLTransicion (AFND * p_afnd);

/*******************************************************************************/

void addEstadosActivosLambda(AFND *p_afnd);

void addEstadosActivos(AFND* p_afnd);


/**********PRACTICA 3**********/

AFND * AFND1ODeSimbolo( char * simbolo);

AFND * AFND1ODeLambda();

AFND * AFND1ODeVacio();

AFND * AFNDAAFND1O(AFND * p_afnd);

AFND * AFND1OUne(AFND * p_afnd1O_1, AFND * p_afnd1O_2);

AFND * AFND1OConcatena(AFND * p_afnd_origen1, AFND * p_afnd_origen2);

AFND * AFND1OEstrella(AFND * p_afnd_origen);

void AFNDADot(AFND * p_afnd);

int insertarTransiciones(AFND *p_afnd_origen, AFND *p_afnd_destino, char prefix[]);

int contarSimbolos(AFND *p_afnd_origen1, AFND *p_afnd_origen2);

void unirAlfabetos(AFND *p_afnd_destino, AFND *p_afnd_origen1, AFND *p_afnd_origen2);


#endif