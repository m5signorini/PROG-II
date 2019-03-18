/* 
 * File:   p2_e4.c
 * Author: Martín Sánchez
 *
 * BUSQUEDA EN PROFUNDIDAD
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "graph.h"

/*
 * 
 */

void main_exit(int, Graph*, Node*);


int main(int argc, char** argv) {
    
    Node * n1 = NULL;
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
    if(f == NULL) main_exit(EXIT_FAILURE, g, n1);
    
    if(graph_readFromFile(f, g) == ERROR) {
	fclose(f);
	main_exit(EXIT_FAILURE, g, n1);
    }
    
    //Asignar from y to
    from = atoi(argv[2]);
    to = atoi(argv[3]);
    
    n1 = graph_findDeepSearch (g, from, to);
    if(n1 == NULL) {
        fprintf(stdout, "NO existe un camino desde %d hasta %d\n", from, to);
    }
    else {
        fprintf(stdout, "Existe un camino desde %d hasta %d\n", from, to);
    }
    
    fclose(f);
    
    /*
    */
    
    main_exit(EXIT_SUCCESS, g, n1);
    
    
    
    
    return (EXIT_SUCCESS);
}

void main_exit(int mens, Graph* st, Node* n) {
    graph_destroy(st);
    node_destroy(n);
    exit(mens);
}
