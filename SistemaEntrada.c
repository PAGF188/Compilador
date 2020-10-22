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

//Nota: Cambiar también lo del fscanf
#define MAX 32

//Variables globales.
FILE *ptr;  //fichero
char bloque1[MAX];
char bloque2[MAX];

//punteros centinela. Toman valores de 0 a 2*MAX-1
long inicio=0;   
long fin=0;


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
    //estamos en bloque 2
    if(fin>=MAX){
        char c = bloque2[fin-MAX];
        printf("Char devuelto posicion %ld: %c \n",fin, c);
        if(fin==2*MAX-1){
            cargarBloque(1);
            fin=0;
        }
        else{
            fin++;
        }
        return(c);
    }
    //estamos en bloque 1
    else{
        char c = bloque1[fin];
        printf("Char devuelto posicion %ld: %c \n",fin, c);
        if(fin==MAX-1){
            cargarBloque(2);
            fin=MAX;
        }else{
            fin++;
        }
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

//////// IMPLEMENTACION FUNCIONES PRIVADAS

void cargarBloque(int bloque){
    if(ptr!=NULL){
        if(bloque==1){
            limpiar(1);
            //Leemos MAX-1 caracteres
            int a = fscanf(ptr, "%32c", bloque1);
            printf("%d",a);
            //fgets(bloque1, MAX, ptr);
            printf("Cargado Bloque1: ");
            imprimeBloque(1);
            printf("\n");
        }
        else{
            limpiar(2);
            //Leemos MAX-1 caracteres
            int a = fscanf(ptr, "%32c", bloque2);
            printf("%d",a);
            //fgets(bloque2, MAX, ptr);
            printf("Cargado Bloque2: ");
            imprimeBloque(2);
            printf("\n");
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