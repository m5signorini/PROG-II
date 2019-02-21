/* 
 * MAIN EJERCICIO 3
 * Nombre: Martín Sánchez
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void main_destroy(int salida, Node *n1, Node *n2, Graph *pg);

int main(int argc, char** argv) {
    
    Node *n1 = NULL;
    Node *n2 = NULL;
    Graph *g = NULL;
    Status flag;
    
    FILE *f = NULL;
    
    /* INICIAR GRAPH */
    g = graph_ini();
    if(g == NULL) return EXIT_FAILURE;
    
    
    /* Abrir FILE */
    /* f = fopen("g1.txt", "r"); */
    f = fopen(argv[1], "r");
    if(f == NULL) main_destroy(EXIT_FAILURE, n1, n2, g);
    
    flag = graph_readFromFile(f, g);
    if(flag == ERROR) {
        fclose(f);
        main_destroy(EXIT_FAILURE, n1, n2, g);
    }
    
    graph_print(stdout, g);
    
    fclose(f);
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
