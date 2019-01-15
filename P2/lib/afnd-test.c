#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "alfabeto.h"
#include "estado.h"
#include "afnd.h"
#include "palabra.h"


int main(int argc, char ** argv)
{

    AFND * p_afnd_l0;
    AFND * p_afnd_l1;
    AFND * p_afnd_l2;
    AFND * p_afnd_l3;
    AFND * p_afnd_l4;
    AFND * p_afnd_l5;
    AFND * p_afnd_l6;
    AFND * p_afnd_l7;


/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “1” */
        p_afnd_l1 = AFND1ODeSimbolo("1");
        p_afnd_l1 = AFNDCierraLTransicion (p_afnd_l1);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “0” */
        p_afnd_l0 = AFND1ODeSimbolo("0");
        p_afnd_l0 = AFNDCierraLTransicion (p_afnd_l0);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “10” */
        p_afnd_l2 = AFND1OConcatena(p_afnd_l1, p_afnd_l0);
        p_afnd_l2 = AFNDCierraLTransicion (p_afnd_l2);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “01” */
        p_afnd_l3 = AFND1OConcatena(p_afnd_l0, p_afnd_l1);
        p_afnd_l3 = AFNDCierraLTransicion (p_afnd_l3);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESION REGULAR “10+01” */
        p_afnd_l4 = AFND1OUne(p_afnd_l2, p_afnd_l3);
        p_afnd_l4 = AFNDCierraLTransicion (p_afnd_l4);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN "11" *  */
        p_afnd_l5 = AFND1OConcatena(p_afnd_l1, p_afnd_l1);
        p_afnd_l5 = AFNDCierraLTransicion (p_afnd_l5);

/* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN "111"*   */
        p_afnd_l6 = AFND1OConcatena(p_afnd_l1, p_afnd_l5);
        p_afnd_l6 = AFNDCierraLTransicion (p_afnd_l6);
    
// /********************************************************/
    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE A UN SÍMBOLO: \"0\"\n");
    // AFNDImprime(stdout,p_afnd_l0);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE A UN SÍMBOLO: \"1\"\n");
    // AFNDImprime(stdout,p_afnd_l1);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"10\"\n");
    // AFNDImprime(stdout,p_afnd_l2);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"01\"\n");
    // AFNDImprime(stdout,p_afnd_l3);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"10+01\"\n");
    // AFNDImprime(stdout,p_afnd_l4);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"11\"\n");
    // AFNDImprime(stdout,p_afnd_l5);

    // fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"111\"\n\n");
    // AFNDImprime(stdout,p_afnd_l6);


    /* SE CREA UN AUTÓMATA FINITO PARA LA EXPRESIÓN "10+01+111" * */
    p_afnd_l7 = AFND1OUne(p_afnd_l4, p_afnd_l6);
    p_afnd_l7 = AFNDCierraLTransicion (p_afnd_l7);

    fprintf(stdout,"EJEMPLO DE AUTÓMATA DE UNA EXPRESIÓN CORRESPONDIENTE \"10+01+111\"\n");
    AFNDImprime(stdout,p_afnd_l7);


/********************************************************/
    // fprintf(stdout,"Y, A CONTINUACIÓN, ALGUNOS EJEMPLOS DE PROCESADO DE CADENAS DEL AUTÓMATA DE LA EXPRESIÓN 11(0+1)*\n"); 
    // AFNDImprime(stdout,p_afnd_l3);
    // fprintf(stdout,"\tLA CADENA 11 ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* POR SU PRINCIPIO\n"); 
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDImprimeCadenaActual(stdout,p_afnd_l3);
    // AFNDInicializaEstado(p_afnd_l3);
    // AFNDProcesaEntrada(stdout,p_afnd_l3);
    // AFNDInicializaCadenaActual(p_afnd_l3);
    // fprintf(stdout,"\tLA CADENA 110 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n"); 
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"0");
    // AFNDImprimeCadenaActual(stdout,p_afnd_l3);
    // AFNDInicializaEstado(p_afnd_l3);
    // AFNDProcesaEntrada(stdout,p_afnd_l3);
    // AFNDInicializaCadenaActual(p_afnd_l3);
    // fprintf(stdout,"\tLA CADENA 111 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n"); 
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDImprimeCadenaActual(stdout,p_afnd_l3);
    // AFNDInicializaEstado(p_afnd_l3);
    // AFNDProcesaEntrada(stdout,p_afnd_l3);
    // AFNDInicializaCadenaActual(p_afnd_l3);
    // fprintf(stdout,"\tLA CADENA 1111001 TAMBIÉN ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n"); 
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDInsertaLetra(p_afnd_l3,"0");
    // AFNDInsertaLetra(p_afnd_l3,"0");
    // AFNDInsertaLetra(p_afnd_l3,"1");
    // AFNDImprimeCadenaActual(stdout,p_afnd_l3);
    // AFNDInicializaEstado(p_afnd_l3);
    // AFNDProcesaEntrada(stdout,p_afnd_l3);
    // AFNDInicializaCadenaActual(p_afnd_l3);
    // fprintf(stdout,"\tLA CADENA VACIA SIN EMBARGO NO ES RECONOCIDA POR EL AUTOMATA DE 11(0+1)* \n"); 
    // AFNDImprimeCadenaActual(stdout,p_afnd_l3);
    // AFNDInicializaEstado(p_afnd_l3);
    // AFNDProcesaEntrada(stdout,p_afnd_l3);
    // AFNDInicializaCadenaActual(p_afnd_l3);

    fprintf(stdout,"\n\n-------------------------------------------------------------------------------------\n");
    fprintf(stdout,"-------------------------------------------------------------------------------------\n\n");
    fprintf(stdout,"Y, A CONTINUACIÓN,  PROCESADO DE CADENAS DEL AUTÓMATA DE LA EXPRESIÓN 10+01+111\n");
    fprintf(stdout,"\n-------------------------------------------------------------------------------------\n");
    fprintf(stdout,"-------------------------------------------------------------------------------------\n\n");
    fprintf(stdout,"\nCADENA 111\n"); 
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInicializaEstado(p_afnd_l7);
    AFNDProcesaEntrada(stdout,p_afnd_l7);
    AFNDInicializaCadenaActual(p_afnd_l7);

    fprintf(stdout,"\n\nCADENA 11\n"); 
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInicializaEstado(p_afnd_l7);
    AFNDProcesaEntrada(stdout,p_afnd_l7);
    AFNDInicializaCadenaActual(p_afnd_l7);

    fprintf(stdout,"\n\nCADENA 10\n"); 
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"0");
    AFNDInicializaEstado(p_afnd_l7);
    AFNDProcesaEntrada(stdout,p_afnd_l7);
    AFNDInicializaCadenaActual(p_afnd_l7);

    fprintf(stdout,"\n\nCADENA 01\n"); 
    AFNDInsertaLetra(p_afnd_l7,"0");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInicializaEstado(p_afnd_l7);
    AFNDProcesaEntrada(stdout,p_afnd_l7);
    AFNDInicializaCadenaActual(p_afnd_l7);

    fprintf(stdout,"\n\nCADENA 1110\n"); 
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"1");
    AFNDInsertaLetra(p_afnd_l7,"0");
    AFNDInicializaEstado(p_afnd_l7);
    AFNDProcesaEntrada(stdout,p_afnd_l7);
    AFNDInicializaCadenaActual(p_afnd_l7);

/********************************************************/
/********************************************************/
    /* PRUEBA IMPRESION A DOT */
    
    // AFNDADot(p_afnd_l0);
    // AFNDADot(p_afnd_l1);
    // AFNDADot(p_afnd_l2);
    // AFNDADot(p_afnd_l3);
    // AFNDADot(p_afnd_l4);
    // AFNDADot(p_afnd_l5);
    // AFNDADot(p_afnd_l6);


/********************************************************/
    AFNDElimina(p_afnd_l0);
    AFNDElimina(p_afnd_l1);
    AFNDElimina(p_afnd_l2);
    AFNDElimina(p_afnd_l3);
    AFNDElimina(p_afnd_l4);
    AFNDElimina(p_afnd_l5);
    AFNDElimina(p_afnd_l6);
    AFNDElimina(p_afnd_l7);
/********************************************************************************/
/********************************************************************************/

    return 0;

}


