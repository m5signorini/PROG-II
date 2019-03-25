
/*
 * Nombre: stack_fp.h
 *
 * Descripción: TAD Stack
 *
 * Autor: Martín Sánchez Signorini
 *
 *
 */


#ifndef STACK_H
#define STACK_H

#include "types.h"
typedef struct _Stack Stack;
/* Tipos de los punteros a función soportados por la pila */

typedef void (*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)(const void*);
typedef int (*P_stack_ele_print)(FILE *, const void*);

/* La función stack_ini recibirá los valores para los campos de la pila que
 * son punteros a función, es decir, recibirá las
 * funciones para, respectivamente, destruir, copiar e imprimir los
 * elementos de la pila creada
 */

// Inicializa un stack con las funciones necesarias para destruir, copiar y printear
Stack * stack_ini (P_stack_ele_destroy f1, P_stack_ele_copy f2, P_stack_ele_print f3);
// Destruye un stack
void stack_destroy(Stack *);

// Introduce un elemento en el stack, devolviendo OK o ERROR
Status stack_push(Stack *, const void *);
// Devuelve el ultimo elemento insertado en el stack o NULL
void * stack_pop(Stack *);

// Devuelve TRUE si el stack esta vacio, sino FALSE
Bool stack_isEmpty(const Stack *);
// Devuelve TRUE si el stack esta lleno, sino FALSE
Bool stack_isFull(const Stack *);

// Imprime el stack y devuelve el numero de bytes impresos
int stack_print(FILE*, const Stack*);

#endif /* STACK_H */
