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
 * Nombre: imprimeError
 * Objetivo: imprimir el error correspondiente en función del código del mismo.
 * @param codigo, valor identificativo del error.
 */
void imprimeError(int codigo);


#endif	/* __ERRORES */