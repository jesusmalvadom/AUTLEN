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
	for (int i = 0; i < num_estados; i++) {
		p_afnd->estados[i] = NULL;
	}


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
	if (p_afnd == NULL) return;


	// Nombre
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


	//libera transiciones lambda
	for(i = 0; i < p_afnd->num_estados; i++){
		free(p_afnd->matriz_ltransiciones[i]);
	}
	free(p_afnd->matriz_ltransiciones);


	// Transiciones
	for (int i = 0; i < p_afnd->num_estados; i++) {
		for(int j = 0; j < p_afnd->num_simbolos; j++) {
			if (p_afnd->transiciones[i][j] != NULL) VectorIndicesElimina(p_afnd->transiciones[i][j]);
		}
		free(p_afnd->transiciones[i]);
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
	fprintf(fd, "\tRL++*={\n\t\t");
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
	fprintf(fd, "\n}\n\n");

	
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
en el autómata proporcionado como primer argumento una nueva transición*/
AFND * AFNDInsertaTransicion(AFND * p_afnd,
                            char * nombre_estado_i,
                            char * nombre_simbolo_entrada,
                            char * nombre_estado_f) {

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
	return p_afnd;
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
el que se haya declarado como estado inicial o inicial_y_final.
*/
AFND * AFNDInicializaEstado (AFND * p_afnd) {
	int i, j;
	if(!p_afnd || !p_afnd->estados) return NULL;

	/* Liberamos el array de estados activos si estuviera ocupada */
	for (int i=0; i<p_afnd->num_estados_activos; i++) {
		if (p_afnd->estados_activos[i] != NULL) estadoElimina(p_afnd->estados_activos[i]);
	}

	for (int i=0; i<p_afnd->num_estados; i++) {
		if (estadoTipo(p_afnd->estados[i]) == INICIAL || estadoTipo(p_afnd->estados[i]) == INICIAL_Y_FINAL) {
			p_afnd->estados_activos[0] = estadoNuevo(p_afnd->estados[i]->nombre, p_afnd->estados[i]->tipo);
			/*p_afnd->estados_activos[0]->nombre = (char *) malloc((strlen(p_afnd->estados[i]->nombre) + 1) * sizeof(char));
			strcpy(p_afnd->estados_activos[0]->nombre, p_afnd->estados[i]->nombre);
			p_afnd->estados_activos[0]->tipo = p_afnd->estados[i]->tipo;*/
			break;
		}
	}

	p_afnd->num_estados_activos = 1;
	return p_afnd;

}

/*Desencadena el proceso completo de 
análisis de la cadena guardada como cadena actual.
*/
void AFNDProcesaEntrada(FILE * fd, AFND * p_afnd) {
	
	if (p_afnd == NULL) return;
	int tamanoCadena = p_afnd->cadena_actual->tamanyo;

	
	/* Iteramos por los simbolos de la cadena de entrada */
	for (int i=0; i<tamanoCadena; i++) {
		if (p_afnd->num_estados_activos == 0) break;
		
		/* Anyadimos a la lista de estados activos aquellos con los que hay lambdas */
		addEstadosActivosLambda(p_afnd);

		//printf ("\ni: %d/%d\tNUM_ESTADOS_ACTIVOS: %d", i, tamanoCadena, p_afnd->num_estados_activos);
		AFNDImprimeConjuntoEstadosActual(fd, p_afnd);	
		AFNDImprimeCadenaActual(fd, p_afnd);	

		addEstadosActivos(p_afnd);

		AFNDTransita(p_afnd);
		
	}

	
	/********* Volvemos a anyadir por ultima vez los lambdas  ******/
	addEstadosActivosLambda(p_afnd);

	/****************************************************************/

	//printf ("\ni: %d/%d\tNUM_ESTADOS_ACTIVOS: %d", tamanoCadena, tamanoCadena, p_afnd->num_estados_activos);
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

	posicion_estado_i = AFNDGetEstadoIndice(p_afnd, nombre_estado_i);
	posicion_estado_f = AFNDGetEstadoIndice(p_afnd, nombre_estado_f);
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


void addEstadosActivosLambda (AFND* p_afnd){
	/* Iteramos por los estados activos */
	Estado **l_estados_aux = (Estado **) malloc(sizeof(Estado *) * p_afnd->num_estados);
	int l_estados_aux_tamano = 0;
	int indexEstadoActual;

	for (int j=0; j < p_afnd->num_estados_activos; j++) {

		indexEstadoActual = AFNDGetEstadoIndice(p_afnd, p_afnd->estados_activos[j]->nombre);

		/* Iteramos por el vector de indices lambda */
		for (int k=0; k<p_afnd->num_estados; k++){
			if (p_afnd->matriz_ltransiciones[indexEstadoActual][k] == 1) {
				l_estados_aux[l_estados_aux_tamano] = estadoNuevo(p_afnd->estados[k]->nombre, p_afnd->estados[k]->tipo);
				l_estados_aux_tamano++;
			}
		}
	}

	for (int i=0; i<p_afnd->num_estados_activos; i++) {
		estadoElimina(p_afnd->estados_activos[i]);
	}
	free(p_afnd->estados_activos);

	/* Copiamos la lista auxiliar de estados en la lista de estados activos (lambdas anyadidos) */
	memcpy(&p_afnd->estados_activos, &l_estados_aux, sizeof(l_estados_aux));
	p_afnd->num_estados_activos = l_estados_aux_tamano;
}

void addEstadosActivos(AFND* p_afnd) {

	int indexEstadoActual;
	int indexSimboloActual = alfabetoIndiceDeSimbolo(p_afnd->alfabeto, p_afnd->cadena_actual->letra[0]);
	Estado **l_estados_aux = (Estado **) malloc(sizeof(Estado *) * p_afnd->num_estados);
	int l_estados_aux_tamano = 0;

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

	for (int i=0; i<p_afnd->num_estados_activos; i++) {
		estadoElimina(p_afnd->estados_activos[i]);
	}
	free(p_afnd->estados_activos);

	memcpy(&p_afnd->estados_activos, &l_estados_aux, sizeof(l_estados_aux));
	p_afnd->num_estados_activos = l_estados_aux_tamano;
	l_estados_aux_tamano = 0;

}

AFND * AFND1ODeSimbolo( char * simbolo){
	AFND * p_afnd1O;
	char * nombre;
	nombre = (char *)malloc((strlen(simbolo)+strlen("anfd1O_") + 1) * sizeof(char));
	sprintf(nombre, "anfd1O_%s", simbolo);

	p_afnd1O = AFNDNuevo(nombre, 2, 1);

	AFNDInsertaSimbolo(p_afnd1O, simbolo);
	
	AFNDInsertaEstado(p_afnd1O, "qi", INICIAL);
	AFNDInsertaEstado(p_afnd1O, "qf", FINAL);

	AFNDInsertaTransicion(p_afnd1O, "qi", simbolo, "qf");

	free(nombre);

	return p_afnd1O;
}

AFND * AFND1ODeLambda(){
	AFND * p_afnd1O;
	p_afnd1O = AFNDNuevo("afnd1O_lambda", 2, 0);
	
	AFNDInsertaEstado(p_afnd1O,"qi",INICIAL);
	AFNDInsertaEstado(p_afnd1O,"qf",FINAL);

	AFNDInsertaLTransicion(p_afnd1O, "qi", "qf");
	AFNDCierraLTransicion (p_afnd1O);

	return p_afnd1O;
}

AFND * AFND1ODeVacio(){
	AFND * p_afnd1O;
	p_afnd1O = AFNDNuevo("afnd1O_vacio", 2, 0);
	
	AFNDInsertaEstado(p_afnd1O,"qi",INICIAL);
	AFNDInsertaEstado(p_afnd1O,"qf",FINAL);

	return p_afnd1O;
}

AFND * AFNDAAFND1O(AFND * p_afnd){
	AFND *p_afnd1O;
	char *nombre, *nombre_qi, *nombre_qf, *nombre_estado;
	nombre = (char *)malloc((strlen("_afnd1O") + strlen(p_afnd->nombre) + 1) * sizeof(char));
	nombre_qi = (char *)malloc((strlen("qi") + 1) * sizeof(char));
	nombre_qf = (char *)malloc((strlen("qf") + 1) * sizeof(char));
	nombre_estado = (char *)malloc((MAX_LEN_NOMBRE + 1) * sizeof(char));

	/* Construimos el nombre del AFND1O y creamos el autómata */
	sprintf(nombre, "%s_afnd1O", p_afnd->nombre);
	p_afnd1O = AFNDNuevo(nombre, p_afnd->num_estados + 2, p_afnd->num_simbolos);

	/* Anyadimos los simbolos en el AFND1O */
	for (int i=0; i<p_afnd->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd->alfabeto, i));
	}

	/* Insertamos el estado inicial del AFND1O */
	sprintf(nombre_qi, "qi");
	AFNDInsertaEstado(p_afnd1O, nombre_qi, INICIAL);

	/* Insertamos los estados del AFND en el AFND1O */
	for (int i=0; i<p_afnd->num_estados; i++) {
		sprintf(nombre_estado, "A1O_%s", estadoNombre(p_afnd->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Anyadimos el estado final del AFND1O */
	sprintf(nombre_qf, "qf");
	AFNDInsertaEstado(p_afnd1O, nombre_qf, FINAL);

	// /* Anyadimos todas las transiciones del AFND al AFND1O */
	insertarTransiciones(p_afnd, p_afnd1O, "A1O_");


	/* Unimos los estados finales del AFND con el nuevo estado final (igual con el estado inicial) */
	for (int i=0; i<p_afnd->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd->estados[i])) + 1);
		sprintf(nombreEstadoI, "%s", estadoNombre(p_afnd->estados[i]));

		/*Transiciones lambda desde el nuevo estado inicial a los antiguos estados iniciales */
		if (estadoTipo(p_afnd->estados[i]) == INICIAL || estadoTipo(p_afnd->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombreEstadoI);
		}

		/* Transiciones lambda desde los antiguos estados finales al nuevo estado final */
		if (estadoTipo(p_afnd->estados[i]) == FINAL || estadoTipo(p_afnd->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombreEstadoI, nombre_qf);
		}
	}

	free(nombre);
	free(nombre_qi);
	free(nombre_qf);

	return p_afnd1O;
}

AFND * AFND1OUne(AFND * p_afnd1O_1, AFND * p_afnd1O_2){
	AFND *p_afnd1O;
	char *nombre = (char *)malloc((strlen("__U__") + strlen(p_afnd1O_1->nombre) + strlen(p_afnd1O_2->nombre) + 1) * sizeof(char));
	char *nombre_qi = (char *)malloc((strlen("qi") + 1) * sizeof(char));
	char *nombre_qf = (char *)malloc((strlen("qf") + 1) * sizeof(char));
	char *nombre_estado = (char *)malloc((MAX_LEN_NOMBRE + 1) * sizeof(char));
	char *prefix_1 = "U1_";
	char *prefix_2 = "U2_";
	int num_simbolos = p_afnd1O_1->num_simbolos;

	/* Construimos el nombre del AFND1O y creamos el autómata */
	sprintf(nombre, "_%s_U_%s_", p_afnd1O_1->nombre, p_afnd1O_2->nombre);

	for (int i=0; i<p_afnd1O_2->num_simbolos; i++) {
		for (int j=0; j<p_afnd1O_1->num_simbolos; j++) {
			if (strcmp(alfabetoSimboloEn(p_afnd1O_2->alfabeto, i), alfabetoSimboloEn(p_afnd1O_1->alfabeto, j)) == 0) {
				break;
			}
			num_simbolos++;
		}
	}

	p_afnd1O = AFNDNuevo(nombre, p_afnd1O_1->num_estados + p_afnd1O_2->num_estados + 2, num_simbolos);

	/* Anyadimos los simbolos del AFND_1 en el AFND1O */
	for (int i=0; i<p_afnd1O_1->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd1O_1->alfabeto, i));
	}

	/* Anyadimos los simbolos del AFND_2 en el AFND1O */
	for (int i=0; i<p_afnd1O_2->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd1O_2->alfabeto, i));
	}

	/* Insertamos el estado inicial del AFND1O */
	sprintf(nombre_qi, "qi");
	AFNDInsertaEstado(p_afnd1O, nombre_qi, INICIAL);

	/* Insertamos los estados del AFND1O_1 en el AFND1O */
	for (int i=0; i<p_afnd1O_1->num_estados; i++) {
		sprintf(nombre_estado, "%s%s", prefix_1, estadoNombre(p_afnd1O_1->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Insertamos los estados del AFND1O_2 en el AFND1O */
	for (int i=0; i<p_afnd1O_2->num_estados; i++) {
		sprintf(nombre_estado, "%s%s", prefix_2, estadoNombre(p_afnd1O_2->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Anyadimos el estado final del AFND1O */
	sprintf(nombre_qf, "qf");
	AFNDInsertaEstado(p_afnd1O, nombre_qf, FINAL);

	/* Insertamos las transiciones de ambos AFND al nuevo AFND1O */
	insertarTransiciones(p_afnd1O_1, p_afnd1O, prefix_1);
	insertarTransiciones(p_afnd1O_2, p_afnd1O, prefix_2);


	/* Unimos los estados finales del AFND1O_1 con el nuevo estado final (igual con el estado inicial) */
	for (int i=0; i<p_afnd1O_1->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd1O_1->estados[i])) + strlen(prefix_1) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix_1, estadoNombre(p_afnd1O_1->estados[i]));

		/*Transiciones lambda desde el nuevo estado inicial a los antiguos estados iniciales */
		if (estadoTipo(p_afnd1O_1->estados[i]) == INICIAL || estadoTipo(p_afnd1O_1->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombreEstadoI);
		}

		/* Transiciones lambda desde los antiguos estados finales al nuevo estado final */
		if (estadoTipo(p_afnd1O_1->estados[i]) == FINAL || estadoTipo(p_afnd1O_1->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombreEstadoI, nombre_qf);
		}
	}

	/* Unimos los estados finales del AFND1O_2 con el nuevo estado final (igual con el estado inicial) */
	for (int i=0; i<p_afnd1O_2->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd1O_2->estados[i])) + strlen(prefix_2) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix_2, estadoNombre(p_afnd1O_2->estados[i]));

		/*Transiciones lambda desde el nuevo estado inicial a los antiguos estados iniciales */
		if (estadoTipo(p_afnd1O_2->estados[i]) == INICIAL || estadoTipo(p_afnd1O_2->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombreEstadoI);
		}

		/* Transiciones lambda desde los antiguos estados finales al nuevo estado final */
		if (estadoTipo(p_afnd1O_2->estados[i]) == FINAL || estadoTipo(p_afnd1O_2->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombreEstadoI, nombre_qf);
		}
	}

	free(nombre);
	free(nombre_qi);
	free(nombre_qf);

	return p_afnd1O;
}

AFND * AFND1OConcatena(AFND * p_afnd_origen1, AFND * p_afnd_origen2) {
	AFND *p_afnd1O;
	char *nombre = (char *)malloc((strlen("__K__)") + strlen(p_afnd_origen1->nombre) + strlen(p_afnd_origen2->nombre) + 1) * sizeof(char));
	char *nombre_qi = (char *)malloc((strlen("qi") + 1) * sizeof(char));
	char *nombre_qf = (char *)malloc((strlen("qf") + 1) * sizeof(char));
	char *nombre_estado = (char *)malloc((MAX_LEN_NOMBRE + 1) * sizeof(char));

	char *prefix_1 = "K1_";
	char *prefix_2 = "K2_";
	int num_simbolos = p_afnd_origen1->num_simbolos;

	/* Construimos el nombre del AFND1O y creamos el autómata */
	sprintf(nombre, "_%s_K_%s_", p_afnd_origen1->nombre, p_afnd_origen2->nombre);

	for (int i=0; i<p_afnd_origen2->num_simbolos; i++) {
		for (int j=0; j<p_afnd_origen1->num_simbolos; j++) {
			if (strcmp(alfabetoSimboloEn(p_afnd_origen2->alfabeto, i), alfabetoSimboloEn(p_afnd_origen1->alfabeto, j)) == 0) {
				break;
			}
			num_simbolos++;
		}
	}

	p_afnd1O = AFNDNuevo(nombre, p_afnd_origen1->num_estados + p_afnd_origen2->num_estados + 2, num_simbolos);

	/* Anyadimos los simbolos del AFND_1 en el AFND1O */
	for (int i=0; i<p_afnd_origen1->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd_origen1->alfabeto, i));
	}

	/* Anyadimos los simbolos del AFND_2 en el AFND1O */
	for (int i=0; i<p_afnd_origen2->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd_origen2->alfabeto, i));
	}

	/* Insertamos el estado inicial del AFND1O */
	sprintf(nombre_qi, "qi");
	AFNDInsertaEstado(p_afnd1O, nombre_qi, INICIAL);

	/* Insertamos los estados del AFND1O_1 en el AFND1O */
	for (int i=0; i<p_afnd_origen1->num_estados; i++) {
		sprintf(nombre_estado, "%s%s", prefix_1, estadoNombre(p_afnd_origen1->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Insertamos los estados del AFND1O_2 en el AFND1O */
	for (int i=0; i<p_afnd_origen2->num_estados; i++) {
		sprintf(nombre_estado, "%s%s", prefix_2, estadoNombre(p_afnd_origen2->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Anyadimos el estado final del AFND1O */
	sprintf(nombre_qf, "qf");
	AFNDInsertaEstado(p_afnd1O, nombre_qf, FINAL);

	/* Insertamos las transiciones de ambos AFND al nuevo AFND1O */
	insertarTransiciones(p_afnd_origen1, p_afnd1O, prefix_1);
	insertarTransiciones(p_afnd_origen2, p_afnd1O, prefix_2);

	
	/* Unimos los estados finales del AFND1O_1 con los iniciales de AFND1O_2 */
	for (int i=0; i<p_afnd_origen1->num_estados; i++) {
		char * nombreEstado_1 = (char *) malloc(strlen(estadoNombre(p_afnd_origen1->estados[i])) + strlen(prefix_1) + 1);
		sprintf(nombreEstado_1, "%s%s", prefix_1, estadoNombre(p_afnd_origen1->estados[i]));

		for (int j=0; j<p_afnd_origen2->num_estados; j++) {
			char * nombreEstado_2 = (char *) malloc(strlen(estadoNombre(p_afnd_origen2->estados[j])) + strlen(prefix_2) + 1);
			sprintf(nombreEstado_2, "%s%s", prefix_2, estadoNombre(p_afnd_origen2->estados[j]));

			if ((estadoTipo(p_afnd_origen1->estados[i]) == FINAL || estadoTipo(p_afnd_origen1->estados[i]) == INICIAL_Y_FINAL) 
					&& (estadoTipo(p_afnd_origen2->estados[j]) == INICIAL || estadoTipo(p_afnd_origen2->estados[j]) == INICIAL_Y_FINAL)){
				AFNDInsertaLTransicion(p_afnd1O, nombreEstado_1, nombreEstado_2);
			}

			free(nombreEstado_2);
		}

		free(nombreEstado_1);
	}


	/* Unimos los estados finales del AFND1O_2 con el nuevo estado final */
	for (int i=0; i<p_afnd_origen2->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd_origen2->estados[i])) + strlen(prefix_2) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix_2, estadoNombre(p_afnd_origen2->estados[i]));

		/* Transiciones lambda desde los antiguos estados finales al nuevo estado final */
		if (estadoTipo(p_afnd_origen2->estados[i]) == FINAL || estadoTipo(p_afnd_origen2->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombreEstadoI, nombre_qf);
		}
		free(nombreEstadoI);
	}

	/* Unimos el nuevo estado inicial con los iniciales del AFND1O_1 */
	for (int i=0; i<p_afnd_origen1->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd_origen1->estados[i])) + strlen(prefix_1) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix_1, estadoNombre(p_afnd_origen1->estados[i]));

		/*Transiciones lambda desde el nuevo estado inicial a los antiguos estados iniciales */
		if (estadoTipo(p_afnd_origen1->estados[i]) == INICIAL || estadoTipo(p_afnd_origen1->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombreEstadoI);
		}
		free(nombreEstadoI);
	}

	free(nombre);
	free(nombre_qi);
	free(nombre_qf);

	return p_afnd1O;

}

AFND * AFND1OEstrella(AFND * p_afnd_origen){
	AFND *p_afnd1O;
	char *nombre = (char *)malloc((strlen("__X") + strlen(p_afnd_origen->nombre) + 1) * sizeof(char));
	char *nombre_qi = (char *)malloc((strlen("qi") + 1) * sizeof(char));
	char *nombre_qf = (char *)malloc((strlen("qf") + 1) * sizeof(char));
	char *nombre_estado = (char *)malloc((MAX_LEN_NOMBRE + 1) * sizeof(char));
	char *prefix = "X_";

	/* Construimos el nombre del AFND1O y creamos el autómata */
	sprintf(nombre, "_%s_X", p_afnd_origen->nombre);
	p_afnd1O = AFNDNuevo(nombre, p_afnd_origen->num_estados + 2, p_afnd_origen->num_simbolos);

	/* Anyadimos los simbolos en el AFND1O */
	for (int i=0; i<p_afnd_origen->num_simbolos; i++){
		AFNDInsertaSimbolo(p_afnd1O, alfabetoSimboloEn(p_afnd_origen->alfabeto, i));
	}

	/* Insertamos el estado inicial del AFND1O */
	sprintf(nombre_qi, "qi");
	AFNDInsertaEstado(p_afnd1O, nombre_qi, INICIAL);

	/* Insertamos los estados del AFND en el AFND1O */
	for (int i=0; i<p_afnd_origen->num_estados; i++) {
		sprintf(nombre_estado, "%s%s", prefix, estadoNombre(p_afnd_origen->estados[i]));
		AFNDInsertaEstado(p_afnd1O, nombre_estado, NORMAL);
	}

	/* Anyadimos el estado final del AFND1O */
	sprintf(nombre_qf, "qf");
	AFNDInsertaEstado(p_afnd1O, nombre_qf, FINAL);

	/* Anyadimos todas las transiciones del AFND al AFND1O */
	insertarTransiciones(p_afnd_origen, p_afnd1O, prefix);

	/* Unimos los estados finales del AFND con el nuevo estado final (igual con el estado inicial) */
	for (int i=0; i<p_afnd_origen->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd_origen->estados[i])) + strlen(prefix) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix, estadoNombre(p_afnd_origen->estados[i]));

		/*Transiciones lambda desde el nuevo estado inicial a los antiguos estados iniciales */
		if (estadoTipo(p_afnd_origen->estados[i]) == INICIAL || estadoTipo(p_afnd_origen->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombreEstadoI);
		}

		/* Transiciones lambda desde los antiguos estados finales al nuevo estado final */
		if (estadoTipo(p_afnd_origen->estados[i]) == FINAL || estadoTipo(p_afnd_origen->estados[i]) == INICIAL_Y_FINAL) {
			AFNDInsertaLTransicion(p_afnd1O, nombreEstadoI, nombre_qf);
		}
	}

	/* Una lambda del estado inicial al final */
	AFNDInsertaLTransicion(p_afnd1O, nombre_qi, nombre_qf);
	/* Una lambda del estado inicial al final */
	AFNDInsertaLTransicion(p_afnd1O, nombre_qf, nombre_qi);


	free(nombre);
	free(nombre_qi);
	free(nombre_qf);

	return p_afnd1O;
	return NULL;
}

void AFNDADot(AFND * p_afnd) {

    FILE * f = NULL;
    int i, j, k;
    char * nombre;
    char*origen;

    /*CdE*/
    if (!p_afnd){
        printf("Automata erroneo\n");
        return;
    }

    nombre = (char *)malloc((strlen(p_afnd->nombre) + 5) * sizeof(char));
    strcpy(nombre, p_afnd->nombre);
    strcat(nombre, ".dot");

    f = fopen(nombre, "w");

    if(!f)
        return ;

    fprintf(f, "digraph %s { rankdir=LR;\n\t_invisible [style= \"invis\"];\n", p_afnd->nombre);

    /*Estados*/
    for(i = 0; i < p_afnd->num_estados; i++){
        if(p_afnd->estados[i]->tipo == FINAL){
            fprintf(f, "\t%s [penwidth=\"2\"];\n", p_afnd->estados[i]->nombre);
        } else if(p_afnd->estados[i]->tipo == INICIAL){
            fprintf(f, "\t%s;\n", p_afnd->estados[i]->nombre);
            fprintf(f, "\t_invisible -> %s;\n", p_afnd->estados[i]->nombre);
        } else{
            fprintf(f, "\t%s;\n", p_afnd->estados[i]->nombre);
        }
    }

    /*Transiciones*/
    for (int i=0; i<p_afnd->num_estados; i++) {
		for (int j=0; j<p_afnd->num_simbolos; j++) {
			for (int k=0; k<p_afnd->num_estados; k++) {
				if (VectorIndicesGetI(p_afnd->transiciones[i][j], k) == 1) {
                	fprintf(f, "\t%s -> %s [label = \"%s\"];\n", p_afnd->estados[i]->nombre, p_afnd->estados[k]->nombre, alfabetoSimboloEn(p_afnd->alfabeto, j));
				}
			}
		}
	}

    /*Transiciones lambda*/
    for (int i = 0; i < p_afnd->num_estados; i++) {
        for(int j = 0; j < p_afnd->num_estados; j++) {
            if ((p_afnd->matriz_ltransiciones[i][j] == 1) && (i != j)) 
                fprintf(f, "\t%s -> %s [label = \"&lambda;\"];\n", p_afnd->estados[i]->nombre, p_afnd->estados[j]->nombre);
        }
    }

    fprintf(f, "}");
    fclose(f);
    f=NULL;
   
}

int insertarTransiciones(AFND *p_afnd_origen, AFND *p_afnd_destino, char prefix[]) {

	/* Anyadimos todas las transiciones del AFND1O_1 al AFND1O */
	for (int i=0; i<p_afnd_origen->num_estados; i++) {
		char * nombreEstadoI = (char *) malloc(strlen(estadoNombre(p_afnd_origen->estados[i])) + strlen(prefix) + 1);
		sprintf(nombreEstadoI, "%s%s", prefix, estadoNombre(p_afnd_origen->estados[i]));
		
		for (int j=0; j<p_afnd_origen->num_simbolos; j++) {
			char * nombreSimbolo = (char *) malloc(strlen(alfabetoSimboloEn(p_afnd_origen->alfabeto, j)) + strlen(prefix) + 1);
			strcpy(nombreSimbolo, alfabetoSimboloEn(p_afnd_origen->alfabeto, j));

			for (int k=0; k<p_afnd_origen->num_estados; k++) {
				char * nombreEstadoF = (char *) malloc(strlen(estadoNombre(p_afnd_origen->estados[k])) + strlen(prefix) + 1);
				sprintf(nombreEstadoF, "%s%s", prefix, estadoNombre(p_afnd_origen->estados[k]));

				/* Transiciones Lambda del AFND al AFND1O */
				if (p_afnd_origen->matriz_ltransiciones[i][k] == 1) {
					AFNDInsertaLTransicion(p_afnd_destino, nombreEstadoI, nombreEstadoF);
				}

				/* Transiciones con simbolo del AFND al AFND1O */
				if (VectorIndicesGetI(p_afnd_origen->transiciones[i][j], k) == 1) {
					AFNDInsertaTransicion(p_afnd_destino, nombreEstadoI, nombreSimbolo, nombreEstadoF);
				}

				free(nombreEstadoF);

			}

			free(nombreSimbolo);
		}

		free(nombreEstadoI);
	}

	return 1;
}



