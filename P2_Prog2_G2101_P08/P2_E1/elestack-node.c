/*
 * Nombre: elestack-node.c
 *
 * Descripción: Elemento: Envoltura de nodo
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
#include "node.h"

extern int errno;

struct _EleStack {
    Node* info;
};



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
    node_destroy(ele->info);
    free(ele);
    return;
}


Status EleStack_setInfo(EleStack* ele, void* v) {
    if(ele == NULL || v == NULL) return ERROR;
    // ele = Elemento de la pila a guardar la info
    // n   = Info a guardar en ele
    Node* n = NULL;

    /* Casting y vaciado de info */
    n = (Node *) v;
    node_destroy(ele->info);

    ele->info = node_copy(n);
    if(ele->info == NULL) {
        return ERROR;
    }

    return OK;
}


void * EleStack_getInfo(EleStack * ele) {
    if(ele == NULL) return NULL;

    void * retorno = NULL;

    retorno = (void *) node_copy(ele->info);
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

    eleCpy->info = node_copy(ele->info);
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
    if(node_cmp(ele1->info, ele2->info) != 0) {
        return FALSE;
    }

    return TRUE;
}


int EleStack_print(FILE *pf, const EleStack *ele) {
    if(pf == NULL || ele == NULL) return -1;

    int nbytes;

    /* node_print ya maneja el posible error */
    nbytes = node_print(pf, ele->info);
    return nbytes;
}
