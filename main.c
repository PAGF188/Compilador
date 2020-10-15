/**
 * Autor: Pablo García Fernández.
 * Archivo: main.c
 * Versión: 1.0
 * Descripción: Archivo principal del proyecto compilador. Actúa a modo de disparador.
 * Objetivos:
 *       - Lectura del archivo a compilar
 *       - Inicialización de la tabla de símbolos.
 *       - Invocación del analizador sintático.
 */

#include <stdio.h>
#include <unistd.h>
#include "./headerFiles/Errores.h"
#include "./headerFiles/Sintactico.h"

int main(int argc, char const *argv[])
{
    //Comprobaciones correctos argumentos pasados por línea de comandos. 
    //En principio un único archivo vamos a compilar.

    if(argc>2){
        imprimeError(1);
        return(-1);
    }

    //Iniciamos la tabla de símbolos

    //Invocamos al analizador sintáctico
    sintactico();

    return 0;
}
