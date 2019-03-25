/*
 * Nombre: elestack.h
 *
 * Descripción: TAD Elemento
 *
 * Autor: Martín Sánchez Signorini
 *
 *
 */

#ifndef ELESTACK_H
#define ELESTACK_H

#include <stdio.h>
#include "types.h"

typedef struct _EleStack EleStack;
/**------------------------------------------------------------------
Inicializa un elemento de pila. Salida: Puntero al elemento inicializado o NULL en caso de error
------------------------------------------------------------------*/
EleStack * EleStack_ini();
/**------------------------------------------------------------------
Elimina un elemento de pila. Entrada: elemento a destruir.
------------------------------------------------------------------*/
void EleStack_destroy(EleStack *);
/**------------------------------------------------------------------
Modifica los datos de un elemento de pila o EleStack. Entrada: El puntero al elemento a modificar y el contenido a
guardar en dicho elemento. Salida: OK o ERROR
------------------------------------------------------------------*/
Status EleStack_setInfo(EleStack *, void*);
/**------------------------------------------------------------------
Devuelve el contenido almacenado en un elemento de pila (del tipo que sea). Entrada: El elemento de pila. Salida: El
contenido de ese elemento, o NULL si ha habido error.
------------------------------------------------------------------*/
void * EleStack_getInfo(EleStack *);
/**------------------------------------------------------------------
Copia un elemento de pila en otro, reservando memoria. Entrada: el elemento a copiar. Salida: puntero al nuevo
elemento, copia del recibido, o NULL en caso de error.
------------------------------------------------------------------*/
EleStack * EleStack_copy(const EleStack *);
/**------------------------------------------------------------------
Compara dos elementos de pila (su contenido). Entrada: los dos elementos a comparar. Salida: TRUE en caso de ser
iguales y FALSE en caso contrario.
------------------------------------------------------------------*/
Bool EleStack_equals(const EleStack *, const EleStack *);
/**------------------------------------------------------------------
Imprime un elemento de pila en un fichero ya abierto. Entrada: Fichero en el que se imprime y elemento a imprimir.
Salida: número de caracteres escritos en total.
------------------------------------------------------------------*/
int EleStack_print(FILE *, const EleStack *);

#endif /* ELESTACK_H */
