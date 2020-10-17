/**
 * Autor: Pablo García Fernández.
 * Archivo: Lexico.c
 * Versión: 1.0
 * Descripción: Implementa enl analizador léxico del compilador.
 * Objetivos:
 *       - Pedirle al sistema de entrada el siguiente caŕacter a procesar.
 *       - Procesar los caracteres obtenidos para identificar lexemas y sus 
 *         correspondientes componentes léxicos.
 *       - Devolverleselos al sintáctico.
 *       - Interactura con la tabla de símbolos para almacenar identificadores y
 *         distinguir palabras reservadas.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./headerFiles/Lexico.h"
#include "./headerFiles/SistemaEntrada.h"
#include "./headerFiles/Definiciones.h"

//Las definiciones de las funciones públicas se encuentran en el .h

tipoLexico siguienteComponente(){

    tipoLexico tl;
    char cadena[30]; 
    char c;
    int estado=0;
    int erro=1;
    int i = 0;
    
    while(erro!=2){
        c = siguienteChar();
        cadena[i] = c;
        switch (estado)
        {
        case 0:
            if(isalpha(c) || c=='_')  //ID
                estado = 1;
            else if(isdigit(c))    //entero
                estado = 2;
            else if(c=='"')   //String
                estado = 3;
            else if(c==EOF){
                tl.lexema = " ";
                return(tl);
            }
            break;
        case 1:
            if(!isalpha(c) && c!='_'){
                cadena[i] = ' ';
                tl.componenteLexico = _ID;
                tl.lexema = (char *) malloc(sizeof(cadena));
                strcpy(tl.lexema,cadena);
                return(tl);
            }
            break;
        default:
            break;
        }
        i++;
    }
}