typedef struct Palabra{
    char **simbolos;
    int tamanyo;
} Palabra;


Palabra * palabraNueva();

void palabraElimina(Palabra * p_p);

Palabra * palabraInsertaLetra(Palabra * p_p, char * letra);

void palabraImprime(FILE * fd, Palabra * p_p);

char * palabraQuitaInicio(Palabra * p_p);

int palabraTamano(Palabra * p_p);

