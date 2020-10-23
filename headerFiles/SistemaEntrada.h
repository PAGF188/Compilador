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
 * @objective: leer/devolver el siguiente carácter del archivo.
 * @return char, carácter leído. (EOF en caso de que sea el último) 
 */ 
char siguienteChar();

/**
 * @name siguienteLexema
 * @objective: devolver el siguiente lexema del archivo, o lo que es lo mismo,
 *             el conjunto de caracteres leídos desde la última llamada a está función
 * @return char* lexema
 */ 
char * siguienteLexema();

/**
 * @name devolverCaracter
 * @objective: reintgrar un caracter en el sistema de entrada.
 */
void devolverCaracter(int nposiciones);

#endif	/* __SE */