/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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