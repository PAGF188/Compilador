/**
 * Autor: Pablo García Fernández.
 * Archivo: SistemaEntrada.c
 * Versión: 1.0
 * Descripción: Implementa el sistema de entrada del compilador.
 * Funciones:
 *       - 
 */

#include <stdio.h>
#include <stdlib.h>
#include "./headerFiles/SistemaEntrada.h"
#include "./headerFiles/Errores.h"

#define MAX 32

//Variables globales.
FILE *ptr;  //fichero
char bloque1[MAX];
char bloque2[MAX];

//punteros centinela. Toman valores de 0-2MAX-1
long inicio=0;   
long fin=0;


////////// FUNCIONES PRIVADAS
void cargarBloque(int bloque);
void limpiar(int bloque);


////////// Las definiciones de las funciones públicas se encuentran en el .h

int iniciaSistemaEntrada(char* archivo){
    //Lo intentamos abrir en modo lectura.
    ptr = fopen(archivo,"r");
    if(ptr==NULL){
        imprimeError(2);
        return(-1);
    }
    for(int i=0; i<MAX;i++){
        bloque1[i] = '\0';
        bloque2[i] = '\0';
    }
    cargarBloque(1);
    return(1);
}

void cargarBloque(int bloque){
    if(ptr!=NULL){
        if(bloque==1){
            //fscanf(ptr, "%32c", bloque1);
            fgets(bloque1, MAX, ptr);
            bloque1[MAX-1] = EOF;
            printf("Cargado Bloque1: %s\n", bloque1);
        }
        else{
            //fscanf(ptr, "%32c", bloque2);
            fgets(bloque2, MAX, ptr);
            bloque2[MAX-1] = EOF;
            printf("Cargado Bloque2: %s\n", bloque2);
        }
    }
}

char siguienteChar(){
    //está en bloque 2
    if(fin>=MAX){
        char c = bloque2[fin-MAX];
        fin++;
        if(bloque2[fin]==EOF){
            limpiar(1);
            cargarBloque(1);
            fin=0;
        }
        printf("Char devuelto: %c \n", c);
        return(c);
    }
    //está en bloque 1
    else{
        char c = bloque1[fin];
        fin++;
        if(bloque1[fin]==EOF){
            limpiar(2);
            cargarBloque(2);
        }
        printf("Char devuelto: %c \n", c);
        return(c);
    }
}

char * siguienteLexema(){
    if(fin!=inicio){
        char * lexema;
        lexema = (char *) malloc(fin-inicio);
        int i=0;
        while (inicio!=fin){
            if(inicio>=MAX){
                lexema[i] = bloque2[inicio];
                bloque2[inicio] = '\0';
            }
            else{
                lexema[i] = bloque1[inicio];
                bloque1[inicio] = '\0';
            }
            i++;
            inicio=(inicio+1)%MAX*2;
        }
        return(lexema);
    }else{
        return(NULL);
    }
}

void devolverCaracter(int nposiciones){
    fin--;
    if(fin<0){
        fin = MAX-1+fin;
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

void limpiar(int bloque){
    for(int i=0;i<MAX;i++){
        if(bloque==1){
            bloque1[i]='\0';
        }else{
            bloque2[i]='\0';
        }
    }
}
