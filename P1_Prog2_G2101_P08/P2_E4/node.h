/* 
 * File:   node.h
 * 
 * MODIFIED FOR P2_E4
 *
 * 
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include "types.h"

typedef struct _Node Node;

typedef enum {BLANCO, NEGRO} Label;

/* Inicializa un nodo, reservando memoria y devolviendo el nodo inicializado si
* lo ha hecho correctamente, sino devuelve NULL en otro caso
* e imprime el string correspondiente al errorno en stderror */
Node * node_ini();

/* Libera la memoria dinámica reservada para un nodo */
void node_destroy(Node * n);

/* Devuelve el id de un nodo dado, o -1 en caso de error */
int node_getId(const Node * n);

/* Devuelve un puntero al nombre de un nodo dado, o NULL en caso de error */
char* node_getName(const Node * n);

/* Devuelve el número de conexiones de un nodo dado, o -1 en caso de error */
int node_getConnect(const Node * n);

/* Modifica el id de un nodo dado, devuelve NULL en caso de error */
Node * node_setId(Node * n, const int id);

/* Modifica el nombre de un nodo dado, devuelve NULL en caso de error */
Node * node_setName(Node * n, const char* name);

/* Modifica el número de conexiones de un nodo dado, devuelve NULL en caso de
error */
Node * node_setConnect(Node * n, const int cn);

/* Compara dos nodos por el id.
* Devuelve 0 cuando ambos nodos tienen el mismo id, un número menor que
* 0 cuando n1 < n2 o uno mayor que 0 en caso contrario. */
int node_cmp (const Node * n1, const Node * n2);

/* Reserva memoria para un nodo en el que copia los datos del nodo src.
* Devuelve la dirección del nodo copia si todo ha ido bien, o NULL en otro caso
*/
Node * node_copy(const Node * src);

/* Imprime en pf los datos de un nodo con el formato: [id, name, nConnect]
* Devuelve el número de caracteres que se han escrito con éxito.
* Comprueba si ha habido errores en el flujo de salida, en ese caso imprime
* mensaje de error en stderror*/
int node_print(FILE *pf, const Node * n);

/* Devuelve la etiqueta del nodo n (B/N)
 * En caso de error devolvera NEGRO
 */
Label node_getEtq(const Node *n);

/* Modifica la etiqueta del nodo y devuelve el nodo modificado
 * En caso de error devuelve null
 */
Node * node_setEtq(Node *n, const Label etq);

/* Devuelve el id del antecesor del nodo n
 * En caso de error devolvera -1
 */
int node_getAntId(const Node *n);

/* Guarda la id del nodo antecesor y devuelve el nodo modificado
 * En caso de error devuelve null
 */
Node * node_setAntId(Node *n, const int ant_id);


#endif /* NODE_H_ */


