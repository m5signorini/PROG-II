/*
 * Nombre: elestack.c
 *
 * Descripción: Estructura de Stack de Elestacks
 *
 * Autor: Martín Sánchez Signorini
 *
 * Módulos Necesarios:
 * - elestack
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "stack_elestack.h"

#define MAXSTACK 1024

extern int errno;

/* top se inicializará a -1, por lo tanto
 * representa el indice del ultimo item
 * top = cantidad  de items - 1
 */

struct _Stack {
    EleStack * item[MAXSTACK];
    int top;
};

Stack * stack_ini() {
    Stack * st = NULL;
    int i;

    st = (Stack*) malloc(sizeof(Stack));
    if(st == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }

    // inicializamos a NULL
    for(i = 0; i < MAXSTACK; i++) {
        st->item[i] = NULL;
    }

    st->top = -1;
    return st;
}

void stack_destroy(Stack *st) {
    if(st == NULL) return;
    int i;

    // i: 0 to top+1 (top empieza en -1)
    for(i = 0; i <= st->top; i++) {
        EleStack_destroy(st->item[i]);
    }

    free(st);
    return;
}

Status stack_push(Stack *st, const EleStack *ele) {
    if(st == NULL || ele == NULL) return ERROR;
    if(stack_isFull(st) == TRUE) return ERROR;

    EleStack * eleCpy = NULL;

    eleCpy = EleStack_copy(ele);
    if(eleCpy == NULL) return ERROR;

    st->top++;
    st->item[st->top] = eleCpy;
    return OK;
}


// No crea copia, redirecciona y saca el item
EleStack * stack_pop(Stack *st) {
    if(st == NULL || stack_isEmpty(st) == TRUE) return  NULL;

    EleStack *elePop = NULL;

    elePop = st->item[st->top];
    if(elePop == NULL) return NULL;

    st->item[st->top] = NULL;
    st->top--;
    // Recordar liberar el retorno tras esta funcion
    return elePop;
}


Bool stack_isEmpty(const Stack *st) {
    if(st == NULL) return FALSE;
    if(st->top == -1) return TRUE;
    return FALSE;
}

Bool stack_isFull(const Stack *st) {
    if(st == NULL) return FALSE;
    if(st->top + 1 == MAXSTACK) return TRUE;
    return FALSE;
}


int stack_print(FILE* f, const Stack* st) {
    if(f == NULL || st == NULL) return -1;

    int nbytes = 0;
    int i, aux;

    // Por cada elemento de la pila
    for(i = st->top; i > -1; i--) {
        aux = EleStack_print(f, st->item[i]);
        if(aux == -1) return -1;

        nbytes += aux;
        nbytes += fprintf(f, "\n");
        if(ferror(f)) {
            fprintf(stderr, "Error al imprimir\n");
            return -1;
        }
    }

    return nbytes;
}
