#ifndef __ERRORES
#define __ERRORES

/**
 * Autor: Pablo García Fernández.
 * Archivo: Errores.h
 * Versión: 1.0
 * Descripción: Exporta la parte pública de Lexico.c.
 * Objetivos:
 *       - Exportar las funciones del gestor de errores que necesitarán invocar
 *         el resto de partes del compilador.
 */

/**
 * @name imprimeError
 * @objective: imprimir el error correspondiente en función del código del mismo.
 * @param codigo, valor identificativo del error. Puede ser:
 *                (*) 1 -> se ha pasado más de 1 argumento.
 *                (*) 2 -> no se pudo acceder al archivo a compilar. 
 *                (*) 3 -> no se pudo cerrar el archivo de compilación al acabar.
 */
void imprimeError(int codigo);


#endif	/* __ERRORES */