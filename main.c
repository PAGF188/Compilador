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
#include "./headerFiles/TablaSimbolos.h"
#include "./headerFiles/Definiciones.h"

int main(int argc, char *argv[])
{
    //Comprobaciones correctos argumentos pasados por línea de comandos. 
    //En principio un único archivo vamos a compilar.

    if(argc>2){
        imprimeError(1);
        return(-1);
    }

    //Iniciamos la tabla de símbolos
    crearTablaSimbolos();

    //Insertamos las palabras reservadas
    tipoelem _import = {"import",_IMPORT, 1};
    tipoelem _double = {"double",_DOUBLE, 1};
    tipoelem _int = {"int",_INT, 1};
    tipoelem _while = {"while",_WHILE, 1};
    tipoelem _foreach = {"foreach",_FOREACH, 1};
    tipoelem _return = {"return",_RETURN, 1};
    tipoelem _void = {"void",_VOID, 1};
    tipoelem _main = {"main",_MAIN, 1};
    tipoelem _cast = {"cast",_CAST, 1};
    tipoelem _writefln = {"writefln", _WRITEFLN,1};

    //Nota: no gestionamos el error porque sabemos que no se va a producir
    //(hemos introducido los datos coherentemente).
    insertarPalabraReservada(_import);
    insertarPalabraReservada(_double);
    insertarPalabraReservada(_int);
    insertarPalabraReservada(_while);
    insertarPalabraReservada(_foreach);
    insertarPalabraReservada(_return);
    insertarPalabraReservada(_void);
    insertarPalabraReservada(_main);
    insertarPalabraReservada(_cast);
    insertarPalabraReservada(_writefln);
    insertarPalabraReservada(_writefln);

    insertarComponenteLexico("asd");
    printf("\n\n");
    insertarComponenteLexico("asd");
    insertarComponenteLexico("b1");
    printf("\n\n");
    insertarComponenteLexico("b1");
    printf("\n\n");
    insertarComponenteLexico("b2");
    printf("\n\n");

    imprimirArbol();
    printf("\n\n");

    destruirTablaSimbolos();

    //Comprobaciones sistema de entrada
    if(iniciaSistemaEntrada(argv[1])==-1){
        exit(-1);
    }

    for(int i=0;i<10000;i++){
        siguienteChar();
    }
    printf("\n\n");

    return(finSistemaEntrada());

    /*
    //Iniciamos sistema de entrada. 
    //Esto es necesario para pasarle la ruta al archivo que contiene el código fuente a compilar.
    if(iniciaSistemaEntrada(argv[1])==-1){
        exit(-1);
    }

    //Invocamos al analizador sintáctico
    sintactico();
    
    //Cerramos el archivo
    return(finSistemaEntrada());
    */
}
