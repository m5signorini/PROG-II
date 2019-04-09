/*
 * Nombre: eleint.c
 *
 * Descripción: Estructura entero
 *
 * Autor: Martín Sánchez Signorini
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "eleint.h"

extern int errno;

int * int_copy(const int * src) {
    if(src == NULL) return NULL;

    int *cpy = NULL;

    cpy = (int*)malloc(sizeof(int));
    if(cpy == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }
    *cpy = *src;

    return cpy;
}

void int_free(int *n) {
    if(n == NULL) return;
    free(n);
}

int int_print(FILE *pf, const int *pi) {
    if(pf == NULL || pi == NULL) return -1;

    int nbytes = 0;

    nbytes = fprintf(pf, "[%d]", *pi);
    if(ferror(pf)) {
        fprintf(stderr, "Error al imprimir\n");
        return -1;
    }

    return nbytes;
}

int int_cmp(const int* n1, const int* n2) {
  if(n1 == NULL || n2 == NULL) return 0;
  return ((*n1) - (*n2));
}
