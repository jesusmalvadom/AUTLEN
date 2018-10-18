#include "generic_string.h"

void destroy_p_string(void* s) {
	if(!s) return;
	free((char*) s);
	return ;
}

void * copy_p_string(const void* s) {
	char* s2;
	if(!s) return NULL;
	s2 = (char*) malloc((strlen(s)+1)*sizeof(char));
	s2 = strcpy(s2, s);
	return s2;
}

int print_p_string(FILE* pf, const void* s) {
	if(!pf || !s) return -1;
	fprintf(pf,"S (string): %s \n",(char*) s);
	return 0;
}
