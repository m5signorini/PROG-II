/* 
 * File:   main.c
 * Author: e400156
 *
 * Created on 5 de febrero de 2019, 13:37
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

/*
 * - Inicializar dos nodos de modo que el primero sea un nodo con nombre “first” e id 111
    y el segundo otro nodo con nombre “second” e id 222.
   - Imprimir ambos nodos e imprimir después un salto de línea.
   - Comprobar si los dos nodos son iguales
   - Imprimir el id del primer nodo junto con una frase explicativa (ver ejemplo)
   - Imprimir el nombre del segundo nodo (ver ejemplo más abajo)
   - Copiar el primer nodo en el segundo.
   - Imprimir ambos nodos.
   - Comprobar si los dos nodos son iguales
   - Liberar ambos nod os.
 */
int main(int argc, char** argv) {
    
    Node *n1 = NULL;
    Node *n2 = NULL;
    int cmp = 0;
    
    n1 = node_ini();
    n2 = node_ini();
    
    node_setId(n1, 111);
    node_setName(n1, "first");
    
    node_setId(n2, 222);
    node_setName(n2, "second");
    
    node_print(stdout, n1);
    node_print(stdout, n2);
    fprintf(stdout, "\n");
    
    cmp = node_cmp(n1, n2);
    if(cmp == 0) {
        fprintf(stdout, "Son iguales? SI\n");
    }
    else {
        fprintf(stdout, "Son iguales? NO\n");
    }
    
    fprintf(stdout, "Id del primer nodo: %d\n", node_getId(n1));
    fprintf(stdout, "Nombre del segundo nodo: %s\n", node_getName(n2));
    
    // Destrucción del nodo 2, pues node_copy crea espacio de memoria, se perdería la referencia a n2;
    node_destroy(n2);
    
    n2 = node_copy(n1);
    
    node_print(stdout, n1);
    node_print(stdout, n2);
    fprintf(stdout, "\n");
    
    cmp = node_cmp(n1, n2);
    if(cmp == 0) {
        fprintf(stdout, "Son iguales? SI\n");
    }
    else {
        fprintf(stdout, "Son iguales? NO\n");
    }
    
    node_destroy(n1);
    node_destroy(n2);
    
    return (EXIT_SUCCESS);
}

