#ifndef AFND_H
#define AFND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _AFND * AFND;

AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos);

void AFNDElimina(AFND * p_afnd);

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);

void AFNDImprime(FILE * fd, AFND* p_afnd);

void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd);

AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo);

AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo);

AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra);

AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f );

AFND * AFNDInicializaCadenaActual (AFND * p_afnd );

#endif