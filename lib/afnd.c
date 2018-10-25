#include "afnd.h"
#include "estado.h"
#include "palabra.h"
#include "alfabeto.h"


/*Genera un nuevo AFND*/
AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos) {
	AFND *p_afnd = NULL;
	if (nombre[0] == '\0' || num_estados < 0 || num_simbolos < 0) return NULL;
	
	p_afnd = (AFND *) malloc(sizeof(AFND));

	p_afnd->nombre = strdup(nombre);

	p_afnd->num_estados = num_estados;
	p_afnd->num_simbolos = num_simbolos;

	char nombre_alfabeto[MAX_LEN_NOMBRE];
	sprintf(nombre_alfabeto, "alf_%s", nombre);

	p_afnd->alfabeto = alfabetoNuevo(nombre_alfabeto, num_simbolos);

	if (p_afnd->alfabeto == NULL) return NULL;

	p_afnd->estados = (Estado **) malloc(sizeof(Estado *) * num_estados);
	if (p_afnd->estados == NULL) return NULL;

	p_afnd->cadena_actual = palabraNueva();
	if (p_afnd->cadena_actual == NULL) return NULL;

	return p_afnd;
}

/*Libera adecuadamente todos los recursos
 asociados con un autómata finito no determinista.*/
void AFNDElimina(AFND * p_afnd) {
	if (p_afnd == NULL) return;
	printf("HOLA1\n");
	fflush(stdout);
	free(p_afnd->nombre);
	printf("HOLA2\n");
	fflush(stdout);

	alfabetoElimina(p_afnd->alfabeto);
	printf("HOLA3\n");
	fflush(stdout);

	for (int i = 0; i < p_afnd->num_estados; i++) {
		printf("HOLA4_%d\n", i);
		fflush(stdout);
		if (p_afnd->estados[i] != NULL) estadoElimina(p_afnd->estados[i]);
	}
	printf("HOLA5\n");
	fflush(stdout);
	free(p_afnd->estados);
	printf("HOLA6\n");
	fflush(stdout);
	palabraElimina(p_afnd->cadena_actual);
	printf("HOLA7\n");
	fflush(stdout);
	return;
}

/*Imprime en el FILE * proporcionado como
 argumento el autómata finito proporcionado como argumento.*/
void AFNDImprime(FILE * fd, AFND* p_afnd) {
	return;
}

/*Inserta en el alfabeto de entrada del 
autómata proporcionado como primer argumento
 un nuevo símbolo de entrada cuyo nombre se 
 proporciona como segundo argumento*/
AFND * AFNDInsertaSimbolo(AFND * p_afnd, char * simbolo) {

	if(p_afnd && p_afnd->alfabeto && simbolo){
		alfabetoInsertaSimbolo(p_afnd->alfabeto, simbolo);
		return p_afnd;
	}
	return NULL;
}
/*Inserta en el conjunto de estados 
del autómata proporcionado como primer
 argumento un nuevo estado cuyo nombre 
 se proporciona como segundo argumento 
 y del tipo proporcionado como tercer parámetro.*/
AFND * AFNDInsertaEstado(AFND * p_afnd, char * nombre, int tipo) {
	int i;
	if(p_afnd && nombre){
		for(i = 0; i < p_afnd->num_estados; i++){
			if(p_afnd->estados[i] == NULL) break;
		}
		p_afnd->estados[i] = estadoNuevo(nombre, tipo);
		if(p_afnd->estados[i] != NULL) return p_afnd;
	}
	return NULL;
}

/*Inserta una letra nueva en la cadena de entrada 
que tiene que procesar el autómata.
*/
AFND * AFNDInsertaLetra(AFND * p_afnd, char * letra) {
	if(p_afnd && letra){
		palabraInsertaLetra(p_afnd->cadena_actual, letra);
		return p_afnd;
	}
	return NULL;
}

/*Inserta en la función de transición guardada 
en el autómata proporcionado como primer argumento
 una nueva transición*/
AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f ) {


    return NULL;
}

/*Imprime la cadena que se está procesando
 en el instante actual (la pendiente de 
 procesar) con el formato que puedes ver en 
 el ejemplo*/
AFND * AFNDInicializaCadenaActual (AFND * p_afnd ) {
	return NULL;
}


void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd) {
	/*int i;
	fprintf(fd, "ACTUALMENTE EN {->");
	for(i=0; i<p_afnd->tam_estados; i++){
		if(p_afnd->cadena_actual[i]){
			if(p_afnd->estados[i]->tipo == FINAL || p_afnd->estados[i]->tipo == INICIAL_Y_FINAL){
				fprintf(fd, "%s* ", p_afnd->estados[i]->nombre);
			}else{
				fprintf(fd, "%s ", p_afnd->estados[i]->nombre);
			}
		}
	}
	fprintf(fd, "}\n");*/
	return;
}

void AFNDImprimeCadenaActual(FILE *fd, AFND * p_afnd) {
	int i;
	if(p_afnd==NULL)
		return;
	fprintf(fd, "[(%d)", p_afnd->cadena_actual->tamanyo);
	for(i=0;i<p_afnd->cadena_actual->tamanyo;i++){
		fprintf(fd, " %s", p_afnd->cadena_actual->letra[i]);
	}
	fprintf(fd, "]\n");
	return;
}

/*Establece como estado inicial del autómata 
el que se haya declarado como estado inicial.
*/
AFND * AFNDInicializaEstado (AFND * p_afnd) {
	int i, j;
	if(!p_afnd || !p_afnd->estados) return NULL;

	for(i=0; i<p_afnd->num_estados; i++){
		if(p_afnd->estados[i]->tipo==INICIAL){
			p_afnd->nombre[i]=1;
		}
	}
	return p_afnd;
}

/*Desencadena el proceso completo de 
análisis de la cadena guardada como cadena actual.
*/
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd) {
	return;
}

/*Esta función debe realizar sólo un
 paso de proceso de la cadena actual 
 (el correspondiente al siguiente 
 símbolo, es decir, al primero de la cadena).*/
void AFNDTransita(AFND * p_afnd) {
	return;
}
