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

void main_destroy(int salida, Node *n1, Node *n2);

int main(int argc, char** argv) {
    
    Node *n1 = NULL;
    Node *n2 = NULL;
    // Variable auxiliar para el checkeo de retornos y comparaciones
    int aux = 0;
    
    // INICIAR
    n1 = node_ini();
    if(n1 == NULL) return EXIT_FAILURE;
    n2 = node_ini();
    if(n2 == NULL) main_destroy(EXIT_FAILURE, n1, n2);
    
    // SET NODE 1
    if(node_setId(n1, 111) == NULL) {
        main_destroy(EXIT_FAILURE, n1, n2);
    }
    if(node_setName(n1, "first") == NULL) {
        main_destroy(EXIT_FAILURE, n1, n2);
    }
    
    // SET NODE 2
    if(node_setId(n2, 222) == NULL) {
        main_destroy(EXIT_FAILURE, n1, n2);
    }
    if(node_setName(n2, "second") == NULL) {
        main_destroy(EXIT_FAILURE, n1, n2);
    }
    
    // PRINT N1 N2
    aux = node_print(stdout, n1);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    
    aux = node_print(stdout, n2);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    fprintf(stdout, "\n");
    
    // PRINT COMPARATION
    aux = node_cmp(n1, n2);
    if(aux == 0) {
        fprintf(stdout, "Son iguales? SI\n");
    }
    else {
        fprintf(stdout, "Son iguales? NO\n");
    }
    
    // PRINT N1.ID N2.NAME
    aux = node_getId(n1);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    fprintf(stdout, "Id del primer nodo: %d\n", aux);
    
    aux = fprintf(stdout, "Nombre del segundo nodo: %s\n", node_getName(n2));
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    
    // Destrucción del nodo 2, pues node_copy crea espacio de memoria,
    //  y se perdería la referencia a n2;
    node_destroy(n2);
    n2 = NULL;
    
    // COPY
    n2 = node_copy(n1);
    if(n2 == NULL) main_destroy(EXIT_FAILURE, n1, n2);
    
    // PRINT NODES
    aux = node_print(stdout, n1);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    aux = node_print(stdout, n2);
    if(aux == -1) main_destroy(EXIT_FAILURE, n1, n2);
    fprintf(stdout, "\n");
    
    aux = node_cmp(n1, n2);
    if(aux == 0) {
        fprintf(stdout, "Son iguales? SI\n");
    }
    else {
        fprintf(stdout, "Son iguales? NO\n");
    }
    
    main_destroy(EXIT_SUCCESS, n1, n2);
    return EXIT_FAILURE;
}


/*  Llamar a esta funcion para salir del programa
 *  Usar como argumentos los elementos a liberar
 */
void main_destroy (int salida, Node *n1, Node *n2) {
    // Destruir todos los elementos del heap, pasados como argumentos
    node_destroy(n1);
    n1 = NULL;
    node_destroy(n2);
    n2 = NULL;
    exit (salida);
}