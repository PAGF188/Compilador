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

//autómata cadenas alfanumeŕicas (para identificadores y palabras reservadas)
int automataAlfanumerico();
//autómata para comentarios. Lo ignora (recorre sus caracteres)
int automataComentario();
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
            if (c == ' ' || c == '\t' || c=='\n')    //obviamos espacios y tabulados
                siguienteLexema();
            else if(isalpha(c) || c=='_')  //identificadores o palabras reservadas
                estado = 1;
            else if(isdigit(c))     //números
                estado = 2;
            else if(c=='"')         //StringLiteral
                estado = 3;
            //cuando entra / -> dependiendo del siguiente puede ser: comentario, división, o /=
            else if(c=='/')  
                estado=4;
            //caracteres simples y que SOLO PUEDEN SER UN COMPONENTE LÉXICO.
            else if(c=='.' || c=='(' || c==')' || c=='[' || c==']' || 
                        c=='{' || c=='}' || c=='?' || c==',' || c==';' || c==':' || c=='$' ||
                        c== '#' || c=='@'){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);
                return(tl);
            }
            else if(c==EOF){        //fin de fichero
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _EOF;
                return(tl);
            }
            else{
            }
            
            break;


        // Estado1: detector de cadenas alfanuméricas (ejs: _asd23 iu8)
        case 1:
            if(automataAlfanumerico()==1){
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
        case 4:
            if(automataComentario()==1)  //ya recorre todos los caracteres del comentario.
                estado=0;
            break;
        default:
            break;
        }
    }
}


int automataAlfanumerico(){
    char c;
    do{
        c = siguienteChar();
    }while(isalpha(c) || c=='_' || isdigit(c));
    return(1);
}

int automataComentario(){
    char c = siguienteChar();
    char d = siguienteChar();
    //comentario del tipo /* */
    if(c=='*'){
        do{
            c = d;
            d = siguienteChar();
            siguienteLexema();
        }while(c!='*' || d!='/');
        return(1);
    }
    //comentario del tipo /+ +/
    if(c=='+'){
        do{
            c = d;
            d = siguienteChar();
            //Llamada recursiva. Como el primer elemento tiene que ser el siguiente a /. Retrocedemos 1 el puntero
            //del sistema de entrada.
            if(c=='/' && d=='+'){
                devolverCaracter(1);
                automataComentario();
            }
            siguienteLexema();
        }while(c!='+' || d!='/');
        return(1);
    }
    //Comentario en línea tipo //
    if(c=='/'){
        do{
            c = d;
            d = siguienteChar();
        }while(c!='\n');
    }
}