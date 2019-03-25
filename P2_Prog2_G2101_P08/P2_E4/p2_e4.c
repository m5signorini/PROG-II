/*
 * Nombre: p2_e4.c
 *
 * Descripción: Ejercicio 4 - Busqueda en profundidad
 *
 * Autor: Martín Sánchez Signorini
 *
 * Modulos propios que necesita:
 * - stack_fp
 * - graph
 * - node
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"

/*
 *
 */


void main_exit(int, Graph*, Node*, FILE*);

int main(int argc, char** argv) {
    // Checkear si el numero de argumentos es suficiente
    if(argc < 4) return EXIT_FAILURE;

    Node * n1 = NULL;
    // Nodos aux para leer su nombre
    Node * nOrig = NULL;
    Node * nDest = NULL;
    Graph * g = NULL;
    FILE *f = NULL;

    int from = -1;
    int to = -1;

    // INICIAR GRAPH
    g = graph_ini();
    if(g == NULL) return EXIT_FAILURE;

    // Abrir FILE
    // f = fopen("g1.txt", "r");
    f = fopen(argv[1], "r");
    if(f == NULL) main_exit(EXIT_FAILURE, g, n1, f);

    if(graph_readFromFile(f, g) == ERROR) main_exit(EXIT_FAILURE, g, n1, f);

    // Asignar from y to
    from = atoi(argv[2]);
    to = atoi(argv[3]);

    // Obtener nodos origen y destino para imprimir sus nombres
    nOrig = graph_getNode(g, from);
    if(nOrig == NULL) main_exit(EXIT_FAILURE, g, nOrig, f);

    nDest = graph_getNode(g, to);
    if(nDest == NULL) main_exit(EXIT_FAILURE, g, nOrig, f);

    n1 = graph_findDeepSearch (g, from, to);
    if(n1 == NULL) {
        fprintf(stdout, "NO se ha podido encontrar un camino desde %s hasta %s\n", node_getName(nOrig), node_getName(nDest));
    }
    else {
        fprintf(stdout, "Existe un camino desde %s hasta %s\n", node_getName(nOrig), node_getName(nDest));
        fprintf(stdout, "Y el camino es:\n");
        graph_print_camino(stdout, g, n1);
        fprintf(stdout, "\n");
    }

    node_destroy(nOrig);
    node_destroy(nDest);

    main_exit(EXIT_SUCCESS, g, n1, f);

    return (EXIT_SUCCESS);
}


void main_exit(int mens, Graph* g, Node* n, FILE * pf) {
    graph_destroy(g);
    node_destroy(n);
    fclose(pf);
    exit(mens);
}
