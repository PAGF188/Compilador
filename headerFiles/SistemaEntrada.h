#ifndef __SE
#define __SE

/**
 * Autor: Pablo García Fernández.
 * Archivo: SistemaEntrada.h
 * Versión: 1.0
 * Descripción: Exporta la parte pública de SistemaEntrada.c.
 * Objetivos:
 *       - Exportar las funciones del Sistema de entrada que necesitará invocar 
 *         el analizador sintáctico y el main (este último para inicializar SE).
 */


/**
 * @name iniciaSistemaEntrada
 * @objective: Función para iniciar el sistema de entrada. 
 *             Comprueba que existe el archivo.
 *             Crea el puntero al archivo. 
 *             Crea las variables necesarias para el centinela.
 * @param archivo, ruta al archivo a compilar.
 * @return int, código de error (-1 fallo en el inicio)
 */ 
int iniciaSistemaEntrada(char* archivo);

/**
 * @name finSistemaEntrada
 * @objective: cerrar el archivo al finalizar la compilación.
 * @return int, código de éxito (-1 error en cierre). 
 */
int finSistemaEntrada();

/**
 * @name siguienteChar
 * @objective: leer/devolver el siguiente carácter del archivo y avanzar una posición.
 * @return char, carácter leído. (EOF en caso de que sea el último) 
 */ 
char siguienteChar();

/**
 * 
 */ 
char * siguienteLexema();

void devolverCaracter(int nposiciones);

void cargarBloque(int bloque);

#endif	/* __SE */