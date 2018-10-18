
#include "estado.h"

Estado * estadoNuevo( char * nombre, int tipo){
	if(!nombre || !tipo){
		fprintf(stderr, "Error en los parámetros de estadoNuevo\n");
		return NULL;
	}
	Estado * e = (Estado *) malloc (sizeof(Estado));
	e->nombre = (char *) malloc(sizeof(char)*(strlen(nombre)+1));
	strcpy(e->nombre, nombre);
	e->tipo = tipo;
	return e;
}

void estadoElimina( Estado * p_s){
	if(!ps) return;
	if(p_s->nombre){
		free(p_s->nombre);
		p_s->nombre=NULL;
	}
	free(p_s);
	p_s=NULL;
	return ;
}

void estadoImprime( FILE * fd, Estado * p_s){
	char * imp=NULL;
	if(!fd || !p_s){
		fprintf(stderr, "Error en los parámetros de estadoImprime\n");
		return ;
	}
	switch (p_s->tipo){
		case 0:
			fprintf(fd, "->%s", p_s->nombre);
			break;
		case 1:
			fprintf(fd, "%s*", p_s->nombre);
			break;
		case 2:
			fprintf(fd, "->%s*", p_s->nombre);
			break;
		default:
			fprintf(fd, "%s", p_s->nombre);
	} 
	return;
}

int estadoEs( Estado * p_s, char * nombre){
	if(!p_s || !nombre){
		fprintf(stderr, "Error en los parámetros de estadoEs\n");
		return 0;
	}
	if(!strcmp(p_s->nombre, nombre)) return 1;
	return 0;
}

char * estadoNombre(Estado * p_s){
	if(!p_s){
		fprintf(stderr, "Error con el estado pasado en estadoNombre\n");
		return NULL;
	}
	return p_s->nombre;
}

int estadoTipo(Estado * p_s){
	if(!p_s){
		fprintf(stderr, "Error con el estado pasado en estadoTipo\n");
		return NULL;
	}
	return p_s->tipo;
}

int estadoCompara(Estado * p_s1, Estado * p_s2){
	if(!p_s1 || !p_s2){
		fprintf(stderr, "Error con los estados pasados en estadoCompara\n");
		return -1;
	}
	return strcmp(p_s1->nombre, p_s2->nombre);
}

Estado * estado_copy(Estado * p_s){
	if(!p_s){
		fprintf(stderr, "Error con el estado pasado en estado_copy\n");
		return NULL;
	}
	return estadoNuevo(p_s->nombre, p_s->tipo;
}

