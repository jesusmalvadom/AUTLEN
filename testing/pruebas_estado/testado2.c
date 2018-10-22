#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estado.h"

int main (int argc, char ** argv)
{
	Estado * estados [10];
	int i;
	char nombre_estado[20];

	
	for (i=0; i< 10; i++)
	{

		sprintf(nombre_estado,"s_%d",i);
		switch ( i % 4 )
		{
			case 0:
				estados[i] = estadoNuevo(nombre_estado,INICIAL_Y_FINAL);
				break;
			case 1:
				estados[i] = estadoNuevo(nombre_estado,INICIAL);
				break;
			case 2:
				estados[i] = estadoNuevo(nombre_estado,FINAL);
				break;
			case 3:
				estados[i] = estadoNuevo(nombre_estado,NORMAL);
				break;
		}
	}

	for (i=0; i< 10; i++)
	{
		estadoImprime(stdout,estados[i]);
	}


	for (i=0; i< 10; i++)
	{
	       	estadoElimina(estados[i]);
	}

	return 0;


}

