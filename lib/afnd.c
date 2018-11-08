#include "afnd.h"


/*Genera un nuevo AFND*/
AFND * AFNDNuevo(char * nombre, int num_estados, int num_simbolos) {
	AFND *p_afnd = NULL;
	if (nombre[0] == '\0' || num_estados < 0 || num_simbolos < 0) return NULL;
	
	p_afnd = (AFND *) malloc(sizeof(AFND));

	p_afnd->nombre = strdup(nombre);

	p_afnd->alfabeto = alfabetoNuevo("A", num_simbolos);
	if (p_afnd->alfabeto == NULL) return NULL;

	p_afnd->num_estados = num_estados;
	p_afnd->num_simbolos = num_simbolos;
	p_afnd->num_estados_activos = 0;



	p_afnd->estados = (Estado **) malloc(sizeof(Estado *) * num_estados);
	if (p_afnd->estados == NULL) return NULL;

	p_afnd->estados_activos = (Estado **) malloc(sizeof(Estado *) * num_estados);

	p_afnd->cadena_actual = palabraNueva();
	if (p_afnd->cadena_actual == NULL) return NULL;


	p_afnd->transiciones = (VectorIndices **) malloc(sizeof(VectorIndices *) * num_estados);
	for(int i = 0; i < num_estados; i++)
		p_afnd->transiciones[i] = (VectorIndices *) malloc(num_simbolos * sizeof(VectorIndices));
	for (int i=0; i<num_estados; i++){
		for (int j=0; j<num_simbolos; j++) {
			p_afnd->transiciones[i][j] = VectorIndicesNuevo(p_afnd->num_estados);
		}
	}
	if(p_afnd->transiciones == NULL) return NULL;


	p_afnd->matriz_ltransiciones = (int **)malloc(num_estados*(sizeof(int *)));
	for(int i = 0; i < num_estados; i++){
		p_afnd->matriz_ltransiciones[i] = (int *)malloc(num_estados*(sizeof(int)));
		for(int j = 0; j < num_estados; j++){
			if(i == j){
				p_afnd->matriz_ltransiciones[i][j] = 1;
			}else {
				p_afnd->matriz_ltransiciones[i][j] = 0;
			}
		}
	}

	return p_afnd;
}

/*Libera adecuadamente todos los recursos
 asociados con un autómata finito no determinista.*/
void AFNDElimina(AFND * p_afnd) {
	int i;
	// Nombre
	if (p_afnd == NULL) return;
	free(p_afnd->nombre);

	// Alfabeto
	alfabetoElimina(p_afnd->alfabeto);

	// Lista de Estados
	for (int i = 0; i < p_afnd->num_estados; i++) {
		estadoElimina(p_afnd->estados[i]);
	}
	free(p_afnd->estados);

	// Lista de estados activos
	for (int i = 0; i < p_afnd->num_estados_activos; i++) {
		estadoElimina(p_afnd->estados_activos[i]);
	}
	free(p_afnd->estados_activos);



	//libera cadena_actual
	palabraElimina(p_afnd->cadena_actual);


	//libera ltransiciones
	for(i = 0; i < p_afnd->num_estados; i++){
		free(p_afnd->matriz_ltransiciones[i]);
	}
	free(p_afnd->matriz_ltransiciones);


	// Transiciones
	for (int i = 0; i < p_afnd->num_estados; i++) {
		for(int j = 0; j < p_afnd->num_simbolos; j++) {
			if (p_afnd->transiciones[i][j] != NULL) VectorIndicesElimina(p_afnd->transiciones[i][j]);
		}
	}
	free(p_afnd->transiciones);


	free(p_afnd);

	return;
}

void ImprimeMatriz(FILE* fd, int ** matriz, int size){
	int i, j;

	if(fd == NULL || matriz == NULL){
		printf("Error al imprimir la matriz de transiciones lambda\n");
	}
	fprintf(fd, "\t\t");
	for (i = 0; i < size; i++){
		fprintf(fd, "\t[%d]", i);
	}

	for (i = 0; i < size; i++){
		fprintf(fd, "\n\t\t");
		fprintf(fd, "[%d]\t", i);
		for(j = 0; j < size; j++){
			fprintf(fd, "%d\t", matriz[i][j]);
		}	
	}
	fprintf(fd, "\n");
}


/*Imprime en el FILE * proporcionado como
 argumento el autómata finito proporcionado como argumento.*/
void AFNDImprime(FILE * fd, AFND* p_afnd) {
	if (fd == NULL || p_afnd == NULL) return;


	fprintf(fd, "%s={\n", p_afnd->nombre);
	fprintf(fd, "\tnum_simbolos = %d\n\n\t", p_afnd->num_simbolos);
	alfabetoImprime(fd, p_afnd->alfabeto);
	fprintf(fd, "\n\tnum_estados = %d\n\n\tQ={ ", p_afnd->num_estados);
	for (int i = 0; i<p_afnd->num_estados; i++) {
		estadoImprime(fd, p_afnd->estados[i]);
	}
	fprintf(fd, "}\n\n");
	ImprimeMatriz(fd, p_afnd->matriz_ltransiciones, p_afnd->num_estados);
	fprintf(fd, "\t}\n\n");	
	fprintf(fd, "\tFuncion de Transición = { \n");
	for(int i=0; i<p_afnd->num_estados; i++) {
		for (int j=0; j<p_afnd->num_simbolos; j++) {
			fprintf(fd, "\n\t\tf(%s,%s)={ ", estadoNombre(p_afnd->estados[i]), alfabetoSimboloEn(p_afnd->alfabeto, j));
			for (int k=0; k<p_afnd->num_estados; k++) {
				if (VectorIndicesGetI(p_afnd->transiciones[i][j], k) == 1) {
					fprintf(fd, "%s ", estadoNombre(p_afnd->estados[k]));
				}
			}
			fprintf(fd, "}");
		}
	
	}
	fprintf(fd, "\n\t}");
	fprintf(fd, "\n}");

	
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

			if(p_afnd->estados[i] == NULL) {
				break;
			}

		}

		p_afnd->estados[i] = estadoNuevo(nombre, tipo);
		if(p_afnd->estados[i] == NULL) return NULL;
		
		return p_afnd;
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

	if (p_afnd && nombre_estado_i && nombre_simbolo_entrada && nombre_estado_f) {
		int indexSimbolo = alfabetoIndiceDeSimbolo(p_afnd->alfabeto, nombre_simbolo_entrada);
		int indexEstadoI = AFNDGetEstadoIndice(p_afnd, nombre_estado_i);
		int indexEstadoF = AFNDGetEstadoIndice(p_afnd, nombre_estado_f);

		if (indexSimbolo == -1 || indexEstadoI == -1 || indexEstadoF == -1) {
			return NULL;
		}
		
		VectorIndicesSetI(p_afnd->transiciones[indexEstadoI][indexSimbolo], indexEstadoF);

	}

    return NULL;
}

/*Imprime la cadena que se está procesando
 en el instante actual (la pendiente de 
 procesar) con el formato que puedes ver en 
 el ejemplo*/
AFND * AFNDInicializaCadenaActual (AFND * p_afnd ) {
	if(!p_afnd)return NULL;
	palabraElimina(p_afnd->cadena_actual);
	p_afnd->cadena_actual=palabraNueva();
	p_afnd->contador_estados_actuales = 0;
}


void AFNDImprimeConjuntoEstadosActual(FILE * fd, AFND * p_afnd) {

	int i;
	if(fd == NULL || p_afnd == NULL){
		printf("Error imprimiendo conjuntos estados acutal\n");
		return;
	}

	fprintf(fd, "\nACTUALMENTE EN {");
	for(i = 0; i < p_afnd->num_estados_activos; i++){
		if(p_afnd->estados_activos[i] != NULL){
			estadoImprime(fd, p_afnd->estados_activos[i]);
		}
	}
	fprintf(fd, "}\n");
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

	for (i = 0; i < p_afnd->num_estados; i++){
		strcpy(p_afnd->estados_activos[0]->nombre, p_afnd->estados[i]->nombre);
		p_afnd->estados_activos[0]->tipo = p_afnd->estados[i]->tipo;
		p_afnd->num_estados_activos++;
		return p_afnd;
	}

}



/*Desencadena el proceso completo de 
análisis de la cadena guardada como cadena actual.
*/
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd) {
	
	if (p_afnd == NULL) return;
	int tamanoCadena = p_afnd->cadena_actual->tamanyo;
	int indexEstadoActual;
	int indexSimboloActual;
	Estado **l_estados_aux;
	char *letraInicial;
	int l_estados_aux_tamano = 0;

	
	/* Iteramos por los simbolos de la cadena de entrada */
	for (int i=0; i<tamanoCadena; i++) {

		AFNDImprimeConjuntoEstadosActual(fd, p_afnd);
		AFNDImprimeCadenaActual(fd, p_afnd);		

		indexSimboloActual = alfabetoIndiceDeSimbolo(p_afnd->alfabeto, p_afnd->cadena_actual->letra[0]);
		l_estados_aux = (Estado **) malloc(sizeof(Estado *) * p_afnd->num_estados);

		/* Iteramos por los estados activos */
		for (int j=0; j<p_afnd->num_estados_activos; j++) {
			
			indexEstadoActual = AFNDGetEstadoIndice(p_afnd, p_afnd->estados_activos[j]->nombre);
			
			/* Iteramos por los vectores de indices */
			for (int k=0; k<p_afnd->num_estados; k++) {
				
				if (p_afnd->transiciones[indexEstadoActual][indexSimboloActual][k] == 1) {
					l_estados_aux[l_estados_aux_tamano] = estadoNuevo(p_afnd->estados[k]->nombre, p_afnd->estados[k]->tipo);
					l_estados_aux_tamano++;
				}
			}
		}

		memcpy(&p_afnd->estados_activos, &l_estados_aux, sizeof(l_estados_aux));
		p_afnd->num_estados_activos = l_estados_aux_tamano;
		l_estados_aux_tamano = 0;

		AFNDTransita(p_afnd);
		
	}

	AFNDImprimeConjuntoEstadosActual(fd, p_afnd);
	AFNDImprimeCadenaActual(fd, p_afnd);

}

/*Esta función debe realizar sólo un
 paso de proceso de la cadena actual 
 (el correspondiente al siguiente 
 símbolo, es decir, al primero de la cadena).*/
void AFNDTransita(AFND * p_afnd) {
	palabraQuitaInicio(p_afnd->cadena_actual);
	return;
}


int AFNDGetEstadoIndice(AFND * p_afnd, char* nombre_estado) {
	if (p_afnd && nombre_estado) {
		for (int i = 0; i<p_afnd->num_estados; i++) {
			//printf("\nESTADO 1: %s\tESTADO 2: %s\n\n", p_afnd->estados[i]->nombre, nombre_estado);
			if (estadoEs(p_afnd->estados[i], nombre_estado))
				return i;
		} 
	}
	return -1;
}


AFND * AFNDInsertaLTransicion(AFND * p_afnd, char * nombre_estado_i, char * nombre_estado_f ){
	int i;
	int posicion_estado_i, posicion_estado_f;


	if(p_afnd == NULL){
		printf("Error en p_afnd al insertar la transicion lambda");
		return p_afnd;
	}
	if(nombre_estado_i == NULL || nombre_estado_f == NULL ){
		printf("Error en un nombre al insertar la transicion lambda\n");
		return p_afnd;
	}

	for (i = 0; i < p_afnd->num_estados; i++) {
		if (strcmp(nombre_estado_i, p_afnd->estados[i]->nombre) == 0){
			posicion_estado_i = i;
		}
		if (strcmp(nombre_estado_f, p_afnd->estados[i]->nombre) == 0){
			posicion_estado_f = i;
		}
	}
	p_afnd->matriz_ltransiciones[posicion_estado_i][posicion_estado_f] = 1;

	return p_afnd;
}


AFND * AFNDCierraLTransicion (AFND * p_afnd){
	int i, j, k;
	int flag = 0;

	if(p_afnd == NULL){
		printf("Error en p_afnd al insertar la transicion lambda");
		return p_afnd;
	}

	do{
		flag = 0;
		for(i = 0; i < p_afnd->num_estados; i++){
			for(j = 0; j < p_afnd->num_estados; j++){
				if(i != j && p_afnd->matriz_ltransiciones[i][j] == 1){
					for(k=0; k < p_afnd->num_estados; k++){
						if (p_afnd->matriz_ltransiciones[j][k] == 1){
							if(p_afnd->matriz_ltransiciones[i][k] == 0){
								p_afnd->matriz_ltransiciones[i][k] = 1;
								flag = 1;
							}
						}
					}
				}
			}
		}
	} while(flag == 1);
	return p_afnd;
}
