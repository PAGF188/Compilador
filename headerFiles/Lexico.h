/**
 * Autor: Pablo García Fernández.
 * Archivo: Lexico.h
 * Versión: 1.0
 * Descripción: Exporta la parte pública de Lexico.c.
 * Objetivos:
 *       - Exportar las funciones del analizador léxico que necesitarán invocar
 *         el resto de partes del compilador.
 *       - Exportar el tipo de datos que se devuelve con la función
 */

/**
 * Struct que encapsula el lexema junto con su componenteLexico
 * Es utilizado para pasarle esta información al sintáctico. 
 */
typedef struct {
    char* lexema;
    int componenteLexico;
}tipoLexico;

/**
 * Nombre: siguienteComponente()
 * Objetivo: Obtiene el siguiente componente léxico del codigo a analizar y se lo
 *           devuelve junto con el lexema. 
 */
tipoLexico siguienteComponente();

