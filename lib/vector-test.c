#include "estado.h"
#include <stdio.h> 

int main(int argc, char ** argv )
{
	int tamano = argc-1;
	int i;

	VectorIndices estados_0;
	estados_0 = VectorIndicesNuevo(tamano);
	for (i=0; i < tamano; i++)
	{
		if ( atoi(argv[i+1]) == 1  )
			VectorIndicesSetI(estados_0,i);
		else
			VectorIndicesUnsetI(estados_0,i);
	}


	for (i=0; i < tamano; i++)
	{
		if ( VectorIndicesGetI(estados_0,i) )
			fprintf(stdout, "estados_0[%d] es 1\n",i);
	}
	
	VectorIndicesImprime(stdout,estados_0,tamano);
	VectorIndicesElimina(estados_0);

	return 0;
}

