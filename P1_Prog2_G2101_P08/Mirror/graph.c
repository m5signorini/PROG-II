/*
 * ESTRUCTURA GRAFO
 * Nombre: Martín Sánchez
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph.h"

/* numero máximo de nodos del grafo */
# define MAX_NODES 1064
/* tamaño máximo que puede tener una linea del
 * fichero donde se guarda el grafo. Usado en la
 * funcion readFromFile();
 */
# define MAX_LINE 256

extern int errno;

enum { NO_FILE_POS_VALUES = 2 };

struct _Graph {
    Node * nodes[MAX_NODES];
    Bool connections[MAX_NODES][MAX_NODES];
    int num_nodes;
    int num_edges;
};


/* 
 * USO PRIVADO
 * 
 */

int find_node_index (const Graph * g, int nId1);
int* graph_getConectionsIndex (const Graph * g, int index);

int find_node_index(const Graph * g, int nId1) {
    int i;
    if (!g) return -1;

    for(i=0; i < g->num_nodes; i++) {
        if (node_getId (g->nodes[i]) == nId1) return i;
    }
    // ID not find
    return -1;
}

// Devueve indices de nodos conectados al nodo de indice index
int* graph_getConectionsIndex(const Graph * g, int index) {
    int *array = NULL, i, j=0, size;
    
    if (!g) return NULL;
    if (index < 0 || index >g->num_nodes) return NULL;
    
    // get memory for the array with the connected nodes index
    size = node_getConnect (g->nodes[index]);
    array = (int *) malloc(sizeof(int) * size);
    if (!array) {
        // print errorr message
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
    }

    // asigno valores al array con los indices de los nodos conectados
    for(i = 0; i< g->num_nodes; i++) {
        if (g->connections[index][i] == TRUE) {
            array[j] = i;
            j++;
        }
    }

    return array;
}

/*
 *  USO PUBLICO
 * 
 */

Graph * graph_ini() {
    Graph * pg = NULL;
    int i, j;
    
    pg = (Graph *)malloc(sizeof(Graph));
    if(pg == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }
    
    for(i = 0; i < MAX_NODES; i++) {
        // Ponemos punteros de los nodos a NULL
        pg->nodes[i] = NULL;
        // Ponemos la matriz de adyacencia a FALSE
        for(j = 0; j < MAX_NODES; j++) {
            pg->connections[i][j] = FALSE;
        }
    }
    pg->num_edges = 0;
    pg->num_nodes = 0;
    
    return pg;
}


void graph_destroy(Graph * g) {
    if(g == NULL) return;
    int i, n;
    
    // n designa cuantos nodos hay que destruir
    n = graph_getNumberOfNodes(g);
    if(n < 0) {
        fprintf(stderr, "Error, número de nodos incorrecto");
        return;
    }
    // Destruir nodos
    for(i = 0; i < n; i++) {
        node_destroy(g->nodes[i]);
    }
    // Destruir grafo
    free(g);
    return;
}

Status graph_insertNode(Graph * g, const Node* n) {
    if(g == NULL || n == NULL) return ERROR;
    int index, numNodes;
    Node * ncpy = NULL;
    
    // Checkeamos numNodes >= MAX_NODES pues estamos insertando +1
    numNodes = graph_getNumberOfNodes(g);
    if(numNodes < 0 || numNodes >= MAX_NODES) return ERROR;
    
    // Si ya existe un nodo con dicha id => ERROR
    index = find_node_index(g, node_getId(n));
    if(index != -1) return ERROR;
    
    ncpy = node_copy(n);
    if(ncpy == NULL) return ERROR;
    
    g->nodes[numNodes] = ncpy;
    g->num_nodes ++;
    
    return OK;
}

// IMPORTANTE: Se conecta nodo 1 al nodo 2, pero NO nodo 2 a nodo 1
Status graph_insertEdge(Graph * g, const int nId1, const int nId2) {
    if(g == NULL || nId1 < 0 || nId2 < 0) return ERROR;
    
    // n1, n2 variables auxiliares para modificar datos de los nodos
    Node * n1 = NULL;
    Node * n2 = NULL;
    int index1, index2;
    
    // Encuentra los índices 1, 2
    index1 = find_node_index(g, nId1);
    if(index1 < 0) return ERROR;
    index2 = find_node_index(g, nId2);
    if(index2 < 0) return ERROR;
    
    n1 = g->nodes[index1];
    n2 = g->nodes[index2];
    
    // Añade la conexion, aumenta num_edges
    g->connections[index1][index2] = TRUE;
    g->num_edges ++;
    
    // Aumenta conexiones de nodos
    if(node_setConnect(n1, node_getConnect(n1) + 1) == NULL) {
        return ERROR;
    }
    if(node_setConnect(n2, node_getConnect(n2) + 1) == NULL) {
        return ERROR;
    }
    
    return OK;
}


Node *graph_getNode (const Graph *g, int nId) {
    if(g == NULL || nId < 0) return NULL;
    
    int index;
    Node * pn = NULL;
    
    // Si no encuentra un nodo con dicha ID...
    index = find_node_index(g, nId);
    if(index < 0) return NULL;
    
    // Si lo encuentra copia el encontrado en pn
    pn = node_copy(g->nodes[index]);
    if(pn == NULL) return NULL;
    
    return pn;
}


Status graph_setNode (Graph *g, const Node *n) {
    if(g == NULL || n == NULL) return ERROR;
    
    int index;
    Node * ngraph = NULL; // Dir. nodo del grafo
    
    // Si no encuentra un nodo en el grafo con la ID de n...
    index = find_node_index(g, node_getId(n));
    if(index < 0) return ERROR;
    
    ngraph = g->nodes[index];
    
    // Actualiza el nodo encotrado
    if(node_setConnect(ngraph, node_getConnect(n)) == NULL) {
        return ERROR;
    }
    if(node_setName(ngraph, node_getName(n)) == NULL) {
        return ERROR;
    }
    
    return OK;
}


int * graph_getNodesId (const Graph * g) {
    if(g == NULL) return NULL;
    // arrayId guarda las ids de los nodos
    int *arrayId = NULL;
    int tam, i;
    
    // Si no hay nodos, no hay array
    tam = graph_getNumberOfNodes(g);
    if(tam < 1) return NULL;
    
    arrayId = (int *)malloc(sizeof(int)*tam);
    if(arrayId == NULL) {
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }
    
    for(i = 0; i < tam; i++) {
        arrayId[i] = node_getId(g->nodes[i]);
        // Si un ID = -1 => Error
        if(arrayId[i] == -1) {
            break;
        }
    }
    // Si i no ha llegado a tam => Error
    if(i != tam) {
        free(arrayId);
        fprintf(stderr, "Error: Nodo %d con una id inválida\n", i);
        return NULL;
    }
    
    return arrayId;
}


int graph_getNumberOfNodes(const Graph * g) {
    if(g == NULL) return -1;
    return g->num_nodes;
}

int graph_getNumberOfEdges(const Graph * g) {
    if(g == NULL) return -1;
    return g->num_edges;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    if(g == NULL || nId1 < 0 || nId2 < 0) return FALSE;
    
    // n1 esta conectado a n2 si: connections[index1][index2] = TRUE;
    int index1, index2;
    
    // Encuentra los índices 1, 2
    index1 = find_node_index(g, nId1);
    if(index1 < 0) return FALSE;
    index2 = find_node_index(g, nId2);
    if(index2 < 0) return FALSE;
    
    return g->connections[index1][index2];
}



// Devuelve cuantos valores son TRUE en una fila

/* Devuelve el número de conexiones SALIENTES desde el nodo de id fromId
 * -1 en caso de error.
 * node_getConnect devuelve conexiones entrantes y salientes luego no nos sirve.
 * Suponemos que con solo n1 y n2, si n1 esta conectado a n2 pero no al reves,
 * las conexiones desde n2 son 0, pero desde n1 son 1
 */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    if(g == NULL || fromId < 0) return -1;
    
    int numTotal = 0;
    int i, index, max, numNodes;
    
    // Encontramos el indice de fromId:
    index = find_node_index(g, fromId);
    if(index < 0) return -1;
    
    // Get el numero de nodos en el grafo
    numNodes = graph_getNumberOfNodes(g);
    if(numNodes < 0) return -1;
    
    // Get el numero max de conexiones salientes de fromId
    max = node_getConnect(g->nodes[index]);
    if(max < 0) return -1;
    
    if(max > graph_getNumberOfEdges(g)) {
        max = graph_getNumberOfEdges(g);
    }
    if(max < 0) return -1;
    
    /*  En el grafo hay:
     *  - Edges/Conexiones:   numEdges
     * 
     *  El nodo de id 'fromId' tiene:
     *  - Conexiones Totales: numConnect
     * 
     *  Así pues el número de conexiones salientes del nodo en el grafo
     *  como mucho es de min{numConnect, numEdges} = max
     *  Con esto puede que ahorremos iteraciones añadiendo una condicion más
     */
    for(i = 0; numTotal < max && i < numNodes; i++) {
        if(g->connections[index][i] == TRUE) {
            numTotal++;
        }
    }
    
    return numTotal;
}

/* Devuelve la dirección de un array con los id de todos los nodos del grafo.
 * Supongo que los conectados al nodo fromId (SALIENTES)
 * Reserva memoria para el array. */
int* graph_getConnectionsFrom(const Graph * g, const int fromId) {
    if(g == NULL || fromId < 0) return NULL;
    
    int index, i, numConnect;
    int * idArray = NULL;
    int * indexArray = NULL;
    
    // Encontramos indice del nodo fromId
    index = find_node_index(g, fromId);
    if(index < 0) return NULL;
    
    // Hallamos el numero de conexiones salientes
    numConnect = graph_getNumberOfConnectionsFrom(g, fromId);
    if(numConnect < 0) return NULL;
    
    // Hallamos los indices que buscamos
    indexArray = graph_getConectionsIndex(g, index);
    if(indexArray == NULL) return NULL;
    
    // Reservo memoria para el array de id's
    idArray = (int *)malloc(sizeof(int)*numConnect);
    if(idArray == NULL) {
        free(indexArray);
        indexArray = NULL;
        fprintf(stderr, "Valor de errno: %d\n", errno);
        fprintf(stderr, "Mensaje de errno: %s\n", strerror(errno));
        return NULL;
    }
    
    // Rellenamos el idArray
    for(i = 0; i < numConnect; i++) {
        idArray[i] = node_getId(g->nodes[indexArray[i]]);
        if(idArray[i] == -1) {
            break;
        }
    }
    
    free(indexArray);
    indexArray = NULL;
    
    if(i != numConnect) {
        free(idArray);
        idArray = NULL;
        return NULL;
    }
    
    return idArray;
}

int graph_print(FILE *pf, const Graph * g) {
    if(pf == NULL || g == NULL) return -1;
    
    int *idArray = NULL;
    int nbytes = 0;
    int numNodes, numConnected, id;
    int i, j, flag;
    
    // Obtener nº nodos en el grafo
    numNodes = graph_getNumberOfNodes(g);
    if(numNodes < 0) return -1;
    
    // Por cada nodo...
    for(i = 0; i < numNodes; i++) {
        // Print: NODO
        flag = node_print(pf, g->nodes[i]);
        if(flag < 0) return -1;
        nbytes += flag;
        
        // Print: CONEXIONES DEL NODO (SALIENTES)
        
        // Obtener ids para imprimir
        id = node_getId(g->nodes[i]);
        if(id < 0) return -1;
        
        numConnected = graph_getNumberOfConnectionsFrom(g, id);
        idArray = graph_getConnectionsFrom(g, id);
        
        // Imprimirlas
        for(j = 0; j < numConnected; j++) {
            flag = fprintf(pf, " %d ", idArray[j]);
            if(ferror(pf)) {
                fprintf(stderr, "Error al imprimir\n");
                return -1;
            }
            nbytes += flag;
        }
        nbytes += fprintf(pf, "\n");
        free(idArray);
        idArray = NULL;
    }
    
    return nbytes;
}


/********************/
/********************/

Status graph_readFromFile (FILE *fin, Graph *g) {
 Node *n;
 char buff[MAX_LINE], name[MAX_LINE];
 int i, nnodes = 0, id1, id2;
 Status flag = ERROR;

 // read number of nodes
 if ( fgets (buff, MAX_LINE, fin) != NULL)
 if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;

 // init buffer_node
 n = node_ini();
 if (!n) return ERROR;

 // read nodes line by line
 for(i=0; i < nnodes; i++) {
 if ( fgets(buff, MAX_LINE, fin) != NULL)
 if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) break;

 // set node name and node id
 node_setName (n, name);
 node_setId (n, id1);

 // insert node in the graph
if ( graph_insertNode (g, n) == ERROR) break;
 }

 // Check if all node have been inserted
 if (i < nnodes) {
 node_destroy(n);
 return ERROR;
 }

 // read connections line by line and insert it
 while ( fgets(buff, MAX_LINE, fin) ) {
 if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )
 if (graph_insertEdge(g, id1, id2) == ERROR) break;
 }

 // check end of file
 if (feof(fin)) flag = OK;

 // clean up, free resources
 node_destroy (n);
 return flag;
}
