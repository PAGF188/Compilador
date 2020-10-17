/**
 * Autor: Pablo García Fernández.
 * Archivo: SistemaEntrada.c
 * Versión: 1.0
 * Descripción: Implementa el sistema de entrada del compilador.
 * Funciones:
 *       - 
 */

#include <stdio.h>
#include "./headerFiles/SistemaEntrada.h"
#include "./headerFiles/Errores.h"

//Variables globales.
FILE *ptr;  //fichero
long puntero1=0;   //puntero centinela

//Las definiciones de las funciones públicas se encuentran en el .h

int iniciaSistemaEntrada(char* archivo){
    //Lo intentamos abrir en modo lectura.
    ptr = fopen(archivo,"r");
    if(ptr==NULL){
        imprimeError(2);
        return(-1);
    }
    return(1);

    //Creacion del posible entorno para el metodo del centinela (ajuste de punteros etc...)
}

int finSistemaEntrada(){
    //Si el archivo está abierto lo intentamos cerrar.
    if(ptr!=NULL){
        if(fclose(ptr)!=0){
            imprimeError(3);
            return(-1);
        }
    }
    return(1);
}

char siguienteChar(){
    if(ptr!=NULL){
        //fseek(ptr, puntero1, SEEK_SET);
        char c = fgetc(ptr);
        //puntero1++;
        return(c);
    }
    //Como medida de seguridad, si ptr==null, devolvemos EOF. Léxico lo interpretará como archivo finalizado.
    return(EOF);
}
