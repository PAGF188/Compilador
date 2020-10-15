/**
 * Autor: Pablo García Fernández.
 * Archivo: Errores.c
 * Versión: 1.0
 * Descripción: Centraliza la gestión de errores por parte del compilador
 * Objetivos:
 *       - Mostrar el error correspondiente en función del valor de entrada.
 */


#include <stdio.h>
#include "./headerFiles/Errores.h"

//Las definiciones de las funciones se encuentran en el .h

void imprimeError(int codigo){

    switch (codigo)
    {
    case 1:
        printf("Argument error! : Solo puedes pasar un archivo para compilar.\n\n");
        break;
    default:
        break;
    }
}