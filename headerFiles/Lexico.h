#ifndef __LEXICO
#define __LEXICO

/**
 * Autor: Pablo García Fernández.
 * Archivo: Lexico.h
 * Versión: 1.0
 * Descripción: Exporta la parte pública de Lexico.c.
 * Objetivos:
 *       - Exportar las funciones del analizador léxico que necesitarán invocar
 *         el resto de partes del compilador.
 *       - Exportar el tipo de datos que encapsula componente léxico + lexema.
 */

/**
 * Dato que encapsula el lexema junto con su componenteLexico.
 */
typedef struct {
    char* lexema;
    int componenteLexico;
}tipoLexico;

/**
 * @name siguienteComponente()
 * @objective: Obtiene el siguiente componente léxico del codigo a analizar y lo
 *             devuelve junto con el lexema. 
 */
tipoLexico siguienteComponente();

#endif	/* __LEXICO */