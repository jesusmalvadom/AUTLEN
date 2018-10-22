#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if(p_p->letra){
		free(p_p->letra);
		p_p->letra=NULL;
	}
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

	
	p_p->tamanyo++;
	/*Reservar memoria p_p->letra*/
	/*(void*)p_p->letra = realloc((void*)p_p->letra, sizeof(char)*(p_p->tamanyo+1));*/

	p_p->letra[p_p->tamanyo] = strcpy(p_p->letra[p_p->tamanyo], letra);
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
		fprintf(stderr, "Error en los parámetros de palabraImprime\n");
		return ;}

	switch (p_p->tamanyo){
		case 0:
			fprintf(fd, "->%s", p_p->letra);
			break;
		case 1:
			fprintf(fd, "%s*", p_p->letra);
			break;
		case 2:
			fprintf(fd, "->%s*", p_p->letra);
			break;
		default:
			fprintf(fd, "%s", p_p->letra);
	} 
	return;
}

/*Devuelve la primera letra de la palabra 
Eliminándola de ella
*/
char * palabraQuitaInicio(Palabra * p_p){
	char * aux;
	
	/*Casos de error*/
	if(!p_p) return NULL;
	if(!p_p->letra){
		return NULL;
	} 
	
	aux = p_p->letra[p_p->tamanyo];
	/*p_p->letra[p_p->tamanyo] = NULL;*/
	/*p_p->letra = realloc(p_p->letra, sizeof(void*)*(p_p->tamanyo));	*/

	p_p->tamanyo--;
	return aux;
}

/*Devuelve el número de letras de la palabra*/
int palabraTamano(Palabra * p_p){
	if(!p_p) return -1;
	return (p_p->tamanyo+1);
}

