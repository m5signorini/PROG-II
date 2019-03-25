/*
 * Nombre: elestack-int.c
 *
 * Descripción: Elemento: Envoltura de entero
 *
 * Autor: Martín Sánchez Signorini
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "elestack.h"

extern int errno;

struct _EleStack {
    int *info;
};


/*
 *  USO PRIVADO
 */

// Funcion que copia, reservando memoria, un entero src y devuelve la copia
int * _int_copy(const int * src);
// Funcion que devuelve:
//  0: a = b
//  1: a > b
// -1: a < b
// -2: error
int _int_comp(const int *a, const int * b);
// Imprime el entero devuelve numero de bytes impresos
int _int_print(FILE *pf, const int *pi);


int * _int_copy(const int * src) {
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

int _int_comp(const int *a, const int * b) {
    if(a == NULL || b == NULL) return -2;
    if(*a == *b)
        return 0;
    else if(*a < *b)
        return -1;
    else if(*a > *b)
        return 1;
    else
        return -2;
}

int _int_print(FILE *pf, const int *pi) {
    if(pf == NULL || pi == NULL) return -1;

    int nbytes = 0;

    nbytes = fprintf(pf, "[%d]", *pi);
    if(ferror(pf)) {
        fprintf(stderr, "Error al imprimir\n");
        return -1;
    }

    return nbytes;
}

/*
 *  USO PUBLICO
 */

EleStack * EleStack_ini() {
    EleStack * ele = NULL;

    ele = (EleStack * )malloc(sizeof(EleStack));
    if(ele == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }

    ele->info = NULL;
    return ele;
}


void EleStack_destroy(EleStack * ele) {
    if(ele == NULL) return;
    free(ele->info);
    free(ele);
    return;
}


Status EleStack_setInfo(EleStack* ele, void* v) {
    if(ele == NULL || v == NULL) return ERROR;
    // ele = Elemento de la pila a guardar la info
    // n   = Info a guardar en ele
    int* n = NULL;

    /* Casting y vaciado de info */
    n = (int *) v;
    free(ele->info);

    ele->info = _int_copy(n);
    if(ele->info == NULL) {
        return ERROR;
    }

    return OK;
}


void * EleStack_getInfo(EleStack * ele) {
    if(ele == NULL) return NULL;

    void * retorno = NULL;

    retorno = (void *) _int_copy(ele->info);
    if(retorno == NULL) {
        return NULL;
    }

    return retorno;
}


EleStack * EleStack_copy(const EleStack * ele) {
    if(ele == NULL) return NULL;

    EleStack * eleCpy = NULL;

    eleCpy = EleStack_ini();
    if(eleCpy == NULL) {
        return NULL;
    }

    eleCpy->info = _int_copy(ele->info);
    /* Si no se asigna memoria correctamente a info */
    if(ele->info != NULL && eleCpy->info == NULL) {
        free(eleCpy);
        return NULL;
    }

    return eleCpy;
}

Bool EleStack_equals(const EleStack * ele1, const EleStack * ele2) {
    if(ele1 == NULL || ele2 == NULL) return FALSE;

    /* Comparar ids => Comparar nodos */
    if(_int_comp(ele1->info, ele2->info) != 0) {
        return FALSE;
    }

    return TRUE;
}


int EleStack_print(FILE *pf, const EleStack *ele) {
    if(pf == NULL || ele == NULL) return -1;

    int nbytes;

    /* _int_print ya maneja el posible error */
    nbytes = _int_print(pf, ele->info);
    return nbytes;
}
