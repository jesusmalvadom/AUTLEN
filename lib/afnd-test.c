#include "afnd.h"
#include <stdio.h>

int main(int argc, char ** argv )
{
	AFND* p_afnd = AFNDNuevo("afnd1", 1, 2);
	AFNDElimina(p_afnd);

	return 0;
}
