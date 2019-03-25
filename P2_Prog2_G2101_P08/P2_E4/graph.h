/*
 * File:   graph.h
 * Author: eps
 *
 * Created on 12 de febrero de 2019, 12:37
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

typedef struct _Graph Graph;

/* Inicializa un grafo, reservando memoria y devolviendo la dirección del grafo
 * si lo ha hecho correctamente, o si no devuelve NULL e imprime el string
 * asociado al errorno en stderror */
Graph * graph_ini();

/* Libera la memoria dinámica reservada para el grafo */
void graph_destroy(Graph * g);

/* Se añade un nodo al grafo (reservando memoria nueva para dicho nodo) siempre
 * y cuando no hubiese ya otro nodo de igual id en el grafo. Actualiza
 * los atributos del grafo que sean necesarios. Devuelve OK o ERROR. */
Status graph_insertNode(Graph * g, const Node* n);

/* Se añade una arista entre los nodos de id "nId1" y "nId2".
 * Actualiza los atributos del grafo y de los nodos que sean necesarios.
 * Devuelve OK o ERROR. */
Status graph_insertEdge(Graph * g, const int nId1, const int nId2);

/* Devuelve una copia del nodo de id "nId" */
Node *graph_getNode (const Graph *g, int nId);

/* Actualiza el nodo del grafo que tiene el mismo id que el nodo n, con la
información de n */
Status graph_setNode (Graph *g, const Node *n);

/* Devuelve la dirección de un array con los id de todos los nodos del grafo.
 * Reserva memoria para el array. */
int * graph_getNodesId (const Graph * g);

/* Devuelve el número de nodos del grafo. -1 si ha habido algún error*/
int graph_getNumberOfNodes(const Graph * g);

/* Devuelve el número de aristas del grafo. -1 si ha habido algún error*/
int graph_getNumberOfEdges(const Graph * g);

/* Determina si dos nodos están conectados*/
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2);

/* Devuelve el número de conexiones del nodo de id fromId */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId);

/* Devuelve la dirección de un array con los id de todos los nodos del grafo.
 * Reserva memoria para el array. */
int* graph_getConnectionsFrom(const Graph * g, const int fromId);

/* Imprime en el flujo pf los datos de un grafo, devolviendo el número de
caracteres impresos.
 * Comprueba si ha habido errorres en el flujo de salida. Si es así imprime
mensaje
 * de error en stderror y devuelve el valor -1.
 * El formato a seguir es: imprimir una linea por nodo con la información asociada
al nodo y
 * los id de sus conexiones. La salida para el grafo del ejercicio 2.3 de la parte
1 es:
 * [1, a, 2] 2 3
 * [2, b, 2] 1 3
 * [3, c, 2] 1 2 */
int graph_print(FILE *pf, const Graph * g);

/* Lee de un flujo de entrada la información asociada a un grafo */
Status graph_readFromFile (FILE *fin, Graph *g);

/*Busqueda en profundidad
  Dado un grafo un id origen y uno destino, se realiza una búsqueda en profundidad
  a lo largo del grafo, si existe un camino hasta el destino devolverá el último nodo, si no existe
  o ha ocurrido un error devolvera NULL
*/
Node *graph_findDeepSearch (Graph *g, const int from_id, const int to_id);

/*Tras llamar a graph_findDeepSearch esta funcion imprime el camino encontrado
a partir de un nodo pn del grafo g, devuelve el número de caracteres impresos*/
int graph_print_camino(FILE *pf, const Graph *g, const Node * pn);

#endif /* GRAPH_H */
