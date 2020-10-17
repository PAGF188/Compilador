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
#include <stdlib.h>
#include "./headerFiles/Errores.h"
#include "./headerFiles/Sintactico.h"
#include "./headerFiles/SistemaEntrada.h"

int main(int argc, char *argv[])
{
    //Comprobaciones correctos argumentos pasados por línea de comandos. 
    //En principio un único archivo vamos a compilar.

    if(argc>2){
        imprimeError(1);
        return(-1);
    }

    //Iniciamos la tabla de símbolos

    //Iniciamos sistema de entrada. 
    //Esto es necesario para pasarle la ruta al archivo que contiene el código fuente a compilar.
    if(iniciaSistemaEntrada(argv[1])==-1){
        exit(-1);
    }

    //Invocamos al analizador sintáctico
    sintactico();
    
    //Cerramos el archivo
    return(finSistemaEntrada());
}
