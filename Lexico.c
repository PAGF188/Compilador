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
//autómata para Strings
int automataString();

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
            //obviamos espacios y tabulados
            if (c == ' ' || c == '\t' || c=='\n'){  
                siguienteLexema();
                estado=0;
            }
            //identificadores o palabras reservadas
            else if(isalpha(c) || c=='_')  
                estado = 1;
            //números
            else if(isdigit(c))     
                estado = 2;
            //StringLiteral
            else if(c=='"')         
                estado = 3;
            //cuando entra '/' ,dependiendo del siguiente caracter, puede ser: comentario, división, o /=
            else if(c=='/')  
                estado=4;
            //cuando entra '=' ,dependiendo del siguiente caracter, puede ser: =, ==,  o =>
            else if(c=='=')
                estado=5;
            //cuando entra '+' ,dependiendo del siguiente caracter, puede ser: +, +=,  o ++
             else if(c=='+')
                estado=6;
            //cuando entra '-' ,dependiendo del siguiente caracter, puede ser: -, -=,  o --
             else if(c=='-')
                estado=7;
            //cuando entra '<' ,dependiendo del siguiente caracter, puede ser: < o <=
             else if(c=='<')
                estado=8;
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
                printf("\n\nCaracter extraño\n\n");
                exit(-1);
            }
            break;


        // Estado1: detector de cadenas alfanuméricas (ejs: _asd23 iu8)
        case 1:
            if(automataAlfanumerico()){
                devolverCaracter(1);
                tl.lexema = siguienteLexema();
                tl.componenteLexico = insertarComponenteLexico(tl.lexema);
                return(tl);
            }
            break;
        case 2:
            break;

        //Estado 3: StringLiteral "alsd"
        case 3:
            if(automataString()){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _STRING;
                return(tl);
            }
            break;

        //Estado 4: Discernir entre uno de los tres posibles significados de / (comentario, /=, /)
        case 4:
            if(automataComentario())  //ya recorre todos los caracteres del comentario ignorándolos.
                estado=0;
            else if(siguienteChar()=='='){     // en caso de /=
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _BARRA_IGUAL;
                return(tl);
            }
            else{   //ninguno de los anteriores -> solo queda la posibilidad de ser /
                devolverCaracter(1); //el leido previamente que no era.
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);
                return(tl);
            }
            break;

        //Estado 5: Discernir entre uno de los tres posibles significados de = (=,==,=>)
        case 5:
            c = siguienteChar();
            if(c=='='){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _DOBLE_IGUAL;
                return(tl);

            }
            else if(c=='>'){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _IGUAL_MAYOR;
                return(tl);

            }
            else{
                devolverCaracter(1);  //el leido previamente que no era.
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);  
                return(tl);
            }
            break;

        //Estado 6: Discernir entre uno de los tres posibles significados de + (+,++,+=)
        case 6:
            c = siguienteChar();
            if(c=='+'){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _DOBLE_MAS;
                return(tl);
            }
            else if(c=='='){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _MAS_IGUAL;
                return(tl);
            }
            else{
                devolverCaracter(1);  //el leido previamente que no era.
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);  
                return(tl);
            }
            break;

        //Estado 7: Discernir entre uno de los tres posibles significados de - (-,--,-=)
        case 7:
            c = siguienteChar();
            if(c=='-'){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _DOBLE_MENOS;
                return(tl);
            }
            else if(c=='='){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _MENOS_IGUAL;
                return(tl);
            }
            else{
                devolverCaracter(1);  //el leido previamente que no era.
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);  
                return(tl);
            }
            break;

        //Estado 8: Discernir entre uno de los dos posibles significados de < (<, <=)
        case 8:
            c = siguienteChar();
            if(c=='='){
                tl.lexema = siguienteLexema();
                tl.componenteLexico = _MENOR_O_IGUAL;
                return(tl);
            }
            else{
                devolverCaracter(1);  //el leido previamente que no era.
                tl.lexema = siguienteLexema();
                tl.componenteLexico = (int) (tl.lexema[0]);  
                return(tl);
            }
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
        c=d;
        while(c!='\n'){
            c = siguienteChar();
            siguienteLexema();
        }
        return(1);
    }
    //si no era comentario, reseteamos.
    devolverCaracter(2);
    return(0);
}

int automataString(){
    char c;
    do{
        c=siguienteChar();
        if(c=='\\')
            siguienteChar();
    }while(c!='"');
    return(1);
}