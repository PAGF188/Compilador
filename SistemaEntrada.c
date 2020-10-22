/**
 * Autor: Pablo García Fernández.
 * Archivo: SistemaEntrada.c
 * Versión: 1.0
 * Descripción: Implementa el sistema de entrada del compilador.
 * Objetivos:
 *       - Devolver el siguiente caracter.
 *       - Devolver el siguiente lexema.
 */

//Nota: No exactamente método del doble centinela. No se incluye EOF, 
//pero aún así solo se realiza una única comparación.

#include <stdio.h>
#include <stdlib.h>
#include "./headerFiles/SistemaEntrada.h"
#include "./headerFiles/Errores.h"

//Nota: Cambiar también el nº de char leídos por fscanf!!!!!!!
//Nota2: Si fin supera a inicio al pedir caracteres->error tama lexema demasiado grande
#define MAX 32

//Variables globales.
FILE *ptr;  //fichero
char bloque1[MAX];
char bloque2[MAX];

//punteros centinela. Toman valores de 0 a 2*MAX-1
long inicio=0;   
long fin=0;

//para saber si he devuelto un caracter y no tengo que cargar bloque2
int puedo_b1 = 1;
int puedo_b2 = 1;

////////// FUNCIONES PRIVADAS

//Si bloque es 1, carga MAX-1 caracteres en bloque1.
//Si bloque es 2, carga MAX-1 caracteres en bloque2.
//En ambos casos soloca EOF al final de los bloques
void cargarBloque(int bloque);
// Recorre el bloque indicado por int bloque, y coloca todos su caracteres a EOF.
// La única manera de devolver un EOF, es si fscanf deja posiciones sin sobreescribir ->
// no hay más caracteres en el archivo -> fin.
// Si justo coincide en última posición de bloque, se cargaría uno ínutil. Pero se devovlería EOF en la 
//primera iteracción de lectura.
void limpiar(int bloque);

//Función de depuración.
void imprimeBloque(int b){
    for(int i=0;i<MAX;i++){
        if(b==1){
            if(bloque1[i]==EOF)
                printf("EOF");
            else
                printf("%c",bloque1[i]);
            
        }
        else
        {if(bloque2[i]==EOF)
                printf("EOF");
            else
                printf("%c",bloque2[i]);
        }
    }
}

////////// Las definiciones de las funciones públicas se encuentran en el .h

int iniciaSistemaEntrada(char* archivo){
    //Lo intentamos abrir en modo lectura.
    ptr = fopen(archivo,"r");
    if(ptr==NULL){
        imprimeError(2);
        return(-1);
    }
    //Cargamos el 1 bloque
    cargarBloque(1);
    return(1);
}

char siguienteChar(){
    char c;
    //estamos en bloque 2
    if(fin>=MAX){
        c = bloque2[fin-MAX];
        if(fin==2*MAX-1 && puedo_b2){
            cargarBloque(1);
            fin=0;
        }else{
            puedo_b2=1;
            fin++;
        }
    }
    //estamos en bloque 1
    else{
        c = bloque1[fin];
        if(fin==MAX-1 && puedo_b1){
            cargarBloque(2);
            fin=MAX;
        }else{
            puedo_b1=1;
            fin++;
        }
    }
    //Una vez incrementado fin, nunca debería coincidir con inicio
    if(fin==inicio){
        imprimeError(4);
        exit(-1);
    }
    return(c);
}

char * siguienteLexema(){
    if(fin!=inicio){
        char * lexema;
        int tam = fin-inicio;
        if(tam<0)
            tam = -tam;
        lexema = (char *) malloc(tam+1);
        int i=0;
        while (inicio!=fin){
            if(inicio>=MAX){
                lexema[i] = bloque2[inicio-MAX];
            }
            else{
                lexema[i] = bloque1[inicio];
            }
            i++;
            inicio=(inicio+1)%(MAX*2);
        }
        lexema[tam] = '\0';
        return(lexema);
    }else{
        return(NULL);
    }
}

void devolverCaracter(int nposiciones){
    //Ojo, si pasamos de un bloque a otro evitar vovler a cargarlo.
    int aux = fin;
    fin=fin-nposiciones;
    if(fin<0){
        //volvimos al bloque2
        fin = MAX-1+fin;
        //no volver a cargar bloque1
        puedo_b1=0;
    }

    if(aux>=MAX && fin <MAX){
        //volvimos al bloque1
        //no volver a cargar bloque2
        puedo_b2=0;
    }
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

//////// IMPLEMENTACION FUNCIONES PRIVADAS

void cargarBloque(int bloque){
    if(ptr!=NULL){
        if(bloque==1){
            limpiar(1);
            //Leemos MAX-1 caracteres
            fscanf(ptr, "%32c", bloque1);
            //fgets(bloque1, MAX, ptr);
        }
        else{
            limpiar(2);
            //Leemos MAX-1 caracteres
            fscanf(ptr, "%32c", bloque2);
            //fgets(bloque2, MAX, ptr);
        }
    }
}

void limpiar(int bloque){
    for(int i=0;i<MAX;i++){
        if(bloque==1){
            bloque1[i] = EOF;
        }
        else{
            bloque2[i] = EOF;
        }
    }
}