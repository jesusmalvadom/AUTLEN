#include "alfabeto.h"


int main(int argc, char ** argv)
{

        Alfabeto * binario;
        char *nombre = strdup("0_1");

        binario = alfabetoNuevo(nombre,2);
        alfabetoElimina(binario);
}