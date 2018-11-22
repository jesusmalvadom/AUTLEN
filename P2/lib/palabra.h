#ifndef PALABRA_H
#define PALABRA_H

#include <stdio.h>
#include <string.h>

#define MAX_LEN_LETRA 100

typedef struct Palabra{
    char **letra;
    int tamanyo;
} Palabra;

/*reserva memoria para una Palabra nueva de tamaño 0*/
Palabra * palabraNueva();

/*libera todos los recursos de la Palabra */
void palabraElimina(Palabra * p_p);

/*Reserva memoria nueva para realizar una copia de la letra argumento 
Redimensiona si es necesario la colección de letras de la Palabra argumento
Incluye la nueva letra al principio de la palabra
*/
Palabra * palabraInsertaLetra(Palabra * p_p, char * letra);

/*Muestra por el FILE * argumento la Palabra*/
void palabraImprime(FILE * fd, Palabra * p_p);

/*Devuelve la primera letra de la palabra 
Eliminándola de ella
*/
char * palabraQuitaInicio(Palabra * p_p);

/*Devuelve el número de letras de la palabra*/
int palabraTamano(Palabra * p_p);

#endif