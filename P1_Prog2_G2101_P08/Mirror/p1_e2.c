/* 
 * MAIN EJERCICIO 2
 * Nombre: Martín Sánchez
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "graph.h"

extern int errno;

/*
 *  -Inicialice dos nodos. El primero con nombre “first” e id 111 y
 *   el segundo con nombre “second” e id 222).
 *  -Inicialice un grafo.
 *  -Insertar el nodo 1 y verifique si la inserción se realizó correctamente
 *  -Insertar el nodo 2 y verifique si la inserción se realizó correctamente
 *  -Insertar una conexión entre el nodo 2 y el nodo 1.
 *  -Comprobar si el nodo 1 está conectado con el nodo 2 (ver mensaje más abajo).
 *  -Comprobar si el nodo 2 está conectado con el nodo 1 (ver mensaje más abajo).
 *  -Insertar nodo 2 y verificar el resultado.
 *  -Imprimir el grafo
 *  -Liberar los recursos destruyendo los nodos y el grafo.
 */

void main_destroy(int salida, Node *n1, Node *n2, Graph *pg);

int main(int argc, char** argv) {
    
    Node *n1 = NULL;
    Node *n2 = NULL;
    Graph *g = NULL;
    /* Variable auxiliar para el checkeo de retornos y comparaciones */
    int id1, id2, aux;
    Status flag;
    
    /* INICIAR */
    n1 = node_ini();
    if(n1 == NULL) return EXIT_FAILURE;
    n2 = node_ini();
    if(n2 == NULL) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    /* SET NODE 1 */
    node_setId(n1, 111);
    node_setName(n1, "first");
    
    /* SET NODE 2 */
    node_setId(n2, 222);
    node_setName(n2, "second");
    
    /* INICIAR GRAFO */
    g = graph_ini();
    if(g == NULL) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    /* INSERCIONES */
    fprintf(stdout, "Insertando nodo 1...");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    flag = graph_insertNode(g, n1);
    
    fprintf(stdout, "resultado...%d\n", flag);
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    fprintf(stdout, "Insertando nodo 2...");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    flag = graph_insertNode(g, n2);
    
    fprintf(stdout, "resultado...%d\n", flag);
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    /* EDGE */
    id1 = node_getId(n1);
    if(id1 == -1) main_destroy(EXIT_FAILURE, n1, n2, g);
    id2 = node_getId(n2);
    if(id2 == -1) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    fprintf(stdout, "Insertando edge: nodo 2 ---> nodo 1\n");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    flag = graph_insertEdge(g, id2, id1);
    if(flag == ERROR) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    
    /* CHECK CONNECTION */
    fprintf(stdout, "Conectados nodo 1 y nodo 2? ");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    if(graph_areConnected(g, id1, id2) == TRUE) {
        fprintf(stdout, "Si\n");
    }
    else {
        fprintf(stdout, "No\n");
    }
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    fprintf(stdout, "Conectados nodo 2 y nodo 1? ");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    if(graph_areConnected(g, id2, id1) == TRUE) {
        fprintf(stdout, "Si\n");
    }
    else {
        fprintf(stdout, "No\n");
    }
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    /* INSERTAR NODO 2 */
    fprintf(stdout, "Insertando nodo 2...");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    flag = graph_insertNode(g, n2);
    
    fprintf(stdout, "resultado...%d\n", flag);
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    /* PRINT GRAFO */
    fprintf(stdout, "GRAFO\n");
    /* Error de flujo */
    if(ferror(stdout)) {
        fprintf(stderr, "Error al imprimir por stdout\n");
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    aux = graph_print(stdout, g);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    main_destroy(EXIT_SUCCESS, n1, n2, g);
    return EXIT_FAILURE;
}


/*  Llamar a esta funcion para salir del programa
 *  Usar como argumentos los elementos a liberar
 */
void main_destroy (int salida, Node *n1, Node *n2, Graph* pg) {
    /* Destruir todos los elementos del heap, pasados como argumentos */
    node_destroy(n1);
    n1 = NULL;
    node_destroy(n2);
    n2 = NULL;
    graph_destroy(pg);
    pg = NULL;
    exit (salida);
}
