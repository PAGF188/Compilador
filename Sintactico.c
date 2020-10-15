/**
 * Autor: Pablo García Fernández.
 * Archivo: Sintactico.c
 * Versión: 1.0
 * Descripción: Implementa el analizador sintáctico del compilador.
 * Funciones:
 *       - Pedir los componentes léxicos al analizador léxico.
 *       - Imprimirlos por pantalla
 */

#include <stdio.h>
#include "./headerFiles/Sintactico.h"
#include "./headerFiles/Lexico.h"

//Las definiciones de las funciones se encuentran en el .h

void sintactico(){
    int i=0;
    while(i<10){
        //Pedimos el siguiente componenteLexico
        tipoLexico l = siguienteComponente();
        //Imprimimos el resultado
        printf("[<%d>,'%s']\n",l.componenteLexico, l.lexema);
        i++;
    }
}