#include <stdio.h>
#include <stdlib.h>
#include "palabra.h"

/*reserva memoria para una Palabra nueva de tamaño 0*/
Palabra * palabraNueva(){

	Palabra * p = (Palabra *) malloc (sizeof(Palabra));
	p->letra = (char **) malloc(sizeof(char*));
	
	p->tamanyo = 0;
	return p;
}

/*libera todos los recursos de la Palabra */
void palabraElimina(Palabra * p_p){

	if(!p_p) return;
	
	for (int i = p_p->tamanyo; i > 0; i--) {
		free(p_p->letra[i]);
	}
	free(p_p->letra);
	free(p_p);
	p_p=NULL;
	return ;
}


/*Reserva memoria nueva para realizar una copia de la letra argumento 
Redimensiona si es necesario la colección de letras de la Palabra argumento
Incluye la nueva letra al principio de la palabra
*/
Palabra * palabraInsertaLetra(Palabra * p_p, char * letra){
	/*Casos de error*/
	if(!p_p) return NULL;

	/*Reservar memoria p_p->letra*/
	p_p->letra = realloc(p_p->letra, sizeof(p_p->letra[0]) * p_p->tamanyo+1);
	++p_p->tamanyo;

    p_p->letra[p_p->tamanyo-1] = (char *) malloc(sizeof(char*) * MAX_LEN_LETRA);
    p_p->letra[p_p->tamanyo-1] = strcpy(p_p->letra[p_p->tamanyo-1], letra);

	return p_p;

}

/*Muestra por el FILE * argumento la Palabra*/
void palabraImprime(FILE * fd, Palabra * p_p){
	char **aux = NULL;
	if(!fd || !p_p){
		fprintf(stderr, "Error en los parámetros de palabraImprime\n");
		return;
	}
	if(!p_p->letra){
		fprintf(stderr, "Error: Palabra NULL\n");
		return ;
	}

	fprintf(fd, "[(%d) ", p_p->tamanyo);
	for (int i=0; i < p_p->tamanyo; i++) {
		fprintf(fd, "%s ", p_p->letra[i]);
	}
	fprintf(fd, "]\n");
	
	return;
}

/*Devuelve la primera letra de la palabra 
Eliminándola de ella
*/
char * palabraQuitaInicio(Palabra * p_p){
	void * aux;
	
	/*Casos de error*/
	if(!p_p) return NULL;
	if(!p_p->letra){
		return NULL;
	} 

	aux = (char *) malloc(sizeof(p_p->letra[0]));
	strcpy(aux, p_p->letra[0]);
	
	p_p->tamanyo--;
	memmove(p_p->letra, p_p->letra+1, p_p->tamanyo * sizeof(p_p->letra[0]));
	p_p->letra = realloc(p_p->letra, sizeof(p_p->letra[0]) * p_p->tamanyo);
	
	return aux;
}

/*Devuelve el número de letras de la palabra*/
int palabraTamano(Palabra * p_p){
	if(!p_p) return -1;
	return p_p->tamanyo;
}

