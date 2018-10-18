#include <stdio.h>

#include "alfabeto.h"


int main(int argc, char ** argv)
{
	Alfabeto * vocales;
	Alfabeto * binario;
	int i;


	vocales = alfabetoNuevo("vocales",5);

	alfabetoInsertaSimbolo(vocales,"la_a");
	alfabetoImprime(stdout, vocales);

	alfabetoInsertaSimbolo(vocales,"la_e");
	alfabetoImprime(stdout, vocales);

	alfabetoInsertaSimbolo(vocales,"la_i");
	alfabetoImprime(stdout, vocales);

	alfabetoInsertaSimbolo(vocales,"la_o");
	alfabetoImprime(stdout, vocales);

	alfabetoInsertaSimbolo(vocales,"la_u");
	alfabetoImprime(stdout, vocales);

	for (i = 0; i < alfabetoTamano(vocales); i++ )
	{
		fprintf(stdout,"vocales[%d]: %s\n",i,alfabetoSimboloEn(vocales,i));
	}
	for (i = 0; i < alfabetoTamano(vocales); i++ )
	{
		fprintf(stdout,"%s es vocales[%d]\n",
                alfabetoSimboloEn(vocales,i),
                alfabetoIndiceDeSimbolo(vocales,alfabetoSimboloEn(vocales,i)));
	}

	alfabetoElimina(vocales);

	binario = alfabetoNuevo("0_1",2);

	alfabetoInsertaSimbolo(binario,"0");
	alfabetoImprime(stdout, binario);

	alfabetoInsertaSimbolo(binario,"1");
	alfabetoImprime(stdout, binario);

	for (i = 0; i < alfabetoTamano(binario); i++ )
	{
		fprintf(stdout,"binario[%d]: %s\n",i,alfabetoSimboloEn(binario,i));
	}
	for (i = 0; i < alfabetoTamano(binario); i++ )
	{
		fprintf(stdout,"%s es binario[%d]\n",
                 alfabetoSimboloEn(binario,i),
                 alfabetoIndiceDeSimbolo(binario,alfabetoSimboloEn(binario,i)));
	}


	alfabetoElimina(binario);

	return 0;
}
