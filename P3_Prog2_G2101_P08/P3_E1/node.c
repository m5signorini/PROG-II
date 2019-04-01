/*
 * Nombre: node.c
 *
 * Descripción: Estructura Nodo adaptada al ejercicio 4
 *
 * Autor: Martín Sánchez Signorini
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "node.h"

#define MAX_NAME 100

extern int errno;

struct _Node {
    char name[MAX_NAME];
    int id;
    int nConnect;

    Label etq;
    int ant_id;
};


Node * node_ini() {
    Node *n = NULL;

    n = (Node *)malloc(sizeof(Node));
    /* En caso de error se imprimira por stderr */
    if(n == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }

    node_setId(n, -1);
    node_setConnect(n, 0);
    node_setName(n, "");

    /******/

    node_setEtq(n, BLANCO);
    node_setAntId(n, -1);

    return n;
}

void node_destroy(Node* n) {
    if(n == NULL) return;
    free(n);
    return;
}

int node_getId(const Node * n) {
    /* Suponemos id >= 0 */
    if(n == NULL) return -1;
    return n->id;
}

char* node_getName(const Node * n) {
    if(n == NULL) return NULL;
    return (n->name);
}

int node_getConnect(const Node * n) {
    if(n == NULL) return -1;
    return n->nConnect;
}

Node * node_setId(Node * n, const int id) {
    /*Puede setear id a -1 ~= no seteada*/
    if(n == NULL || id < -1) return NULL;
    n->id = id;
    return n;
}

Node * node_setName(Node * n, const char* name) {
    if(n == NULL || name == NULL) return NULL;
    /* strncpy copia src en dest hasta n, el resto son '/0' */
    strncpy(n->name, name, MAX_NAME-1);
    return n;
}

Node * node_setConnect(Node * n, const int cn) {
    if(n ==NULL || cn < 0) return NULL;
    n->nConnect = cn;
    return n;
}

int node_cmp (const Node * n1, const Node * n2) {
    if(n1 == NULL || n2 == NULL) return 0;
    /* Id's >= 0 para todo nodo, luego podemos restar para comparar */
    return (node_getId(n1) - node_getId(n2));
}

Node * node_copy(const Node * src) {
    if(src == NULL) return NULL;
    Node *n = NULL;

    n = (Node *)malloc(sizeof(Node));
    /* En caso de error se imprimira por stderr */
    if(n == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }

    node_setId(n, node_getId(src));
    node_setConnect(n, node_getConnect(src));
    node_setName(n, node_getName(src));

    node_setEtq(n, node_getEtq(src));
    node_setAntId(n, node_getAntId(src));
    return n;
}

int node_print(FILE *pf, const Node * n) {
    if(pf == NULL || n == NULL) {
        fprintf(stderr, "Error al pasar argumentos NULL\n");
        return -1;
    }

    int nbytes = 0;
    nbytes = fprintf(pf, "[%s, %d, %d]", node_getName(n), node_getId(n), node_getConnect(n));

    /* Comprobar error al imprimir en pf */
    if(ferror(pf)) {
        fprintf(stderr, "Error al imprimir\n");
        return -1;
    }
    return nbytes;
}

/************/

Label node_getEtq(const Node *n) {
    if(n == NULL) return NEGRO;
    return n->etq;
}


Node * node_setEtq(Node *n, const Label etq) {
    if(n == NULL) return NULL;
    if(etq != BLANCO && etq != NEGRO) return NULL;

    n->etq = etq;
    return n;
}


int node_getAntId(const Node *n) {
    if(n == NULL) return -1;
    return n->ant_id;
}


Node * node_setAntId(Node *n, const int ant_id) {
    if(n == NULL) return NULL;
    n->ant_id = ant_id;
    return n;
}
