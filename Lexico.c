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
#include "./headerFiles/TablaSimbolos.h"


/////////////////// FUNCIONES PRIVADAS
int esCadenaAlfanumerica();

///////////    Las definiciones de las funciones públicas se encuentran en el .h

tipoLexico siguienteComponente(){

    tipoLexico tl;
    int erro=0;
    int estado=0;
    char c;
    
    while(erro==0){
        switch (estado){
        //estado inicial
        case 0:
            c = siguienteChar();
            if (c == ' ' || c == '\t' || c=='\n')    //obiamos espacios y tabulados
                siguienteLexema();
            else if(isalpha(c) || c=='_')  //identificadores o palabras reservadas
                estado = 1;
            else if(isdigit(c))     //números
                estado = 2;
            else if(c=='"')         //StringLiteral
                estado = 3;
            else if(c==EOF){        //fin de fichero
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _EOF;
                return(tl);
            }
            break;
        // detector de cadenas alfanuméricas (ejs: _asd23 iu8)
        case 1:
            if(esCadenaAlfanumerica()==1){
                devolverCaracter(1);
                tl.lexema = siguienteLexema();
                tl.componenteLexico = insertarComponenteLexico(tl.lexema);
                return(tl);
            }
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    }
}


int esCadenaAlfanumerica(){
    char c;
    do{
        c = siguienteChar();
    }while(isalpha(c) || c=='_' || isdigit(c));
    return(1);
}