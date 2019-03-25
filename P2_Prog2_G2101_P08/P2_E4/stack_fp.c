/*
 * Nombre: stack_fp.c
 *
 * Descripción: Estructura Stack
 *
 * Autor: Martín Sánchez Signorini
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack_fp.h"

#define MAXSTACK 100
#define EMPTY_STACK -1

extern int errno;

struct _Stack {
    int top;
    void * item[MAXSTACK];

    P_stack_ele_destroy pf_destroy;
    P_stack_ele_copy pf_copy;
    P_stack_ele_print pf_print;
};


Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
    if(fd == NULL || fc == NULL || fp == NULL) return NULL;

    Stack *st = NULL;
    int i;

    st = (Stack *)malloc(sizeof(Stack));
    if(st == NULL) {
        fprintf(stderr, "Valor del error: %d\n", errno);
        fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
        return NULL;
    }

    st->top = EMPTY_STACK;
    st->pf_copy = fc;
    st->pf_destroy = fd;
    st->pf_print = fp;

    for(i = 0; i < MAXSTACK; i++) {
        st->item[i] = NULL;
    }
    return st;
}


void stack_destroy(Stack* st) {
    if(st == NULL) return;

    while(st->top > EMPTY_STACK) {
        st->pf_destroy(st->item[st->top]);
        st->top--;
    }

    free(st);
    return;
}


Status stack_push(Stack *st, const void *ele) {
    if(st == NULL || ele == NULL) return ERROR;
    if(stack_isFull(st) == TRUE) return ERROR;

    void * ele_cpy = NULL;

    ele_cpy = st->pf_copy(ele);
    if(ele_cpy == NULL) return ERROR;

    st->top++;
    st->item[st->top] = ele_cpy;
    return OK;
}


void * stack_pop(Stack *st) {
    if(st == NULL) return NULL;

    void * ele_pop = NULL;

    ele_pop = st->item[st->top];
    st->item[st->top] = NULL;
    st->top--;

    return ele_pop;
}



Bool stack_isEmpty(const Stack *st) {
    if(st == NULL) return TRUE;
    if(st->top == EMPTY_STACK) return TRUE;
    return FALSE;
}


Bool stack_isFull(const Stack *st) {
    if(st == NULL) return TRUE;
    if(st->top == MAXSTACK-1) return TRUE;
    return FALSE;
}


int stack_print(FILE*pf, const Stack*st) {
    if(pf == NULL || st == NULL) return -1;

    int nbytes = 0, aux;
    int i = st->top;

    while(i != EMPTY_STACK) {
        aux = st->pf_print(pf, st->item[i]);
        if(aux == -1) return -1;

        nbytes += aux;
        nbytes += fprintf(pf, "\n");
        if(ferror(pf)) {
            fprintf(stderr, "Error al imprimir\n");
            return -1;
        }

        i--;
    }

    return nbytes;
}
