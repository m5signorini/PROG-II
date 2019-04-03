/*

Nombre: list.c
Pareja: 08
Autor: Martín Sánchez Signorini

Descripción: Estructura de LEC

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

#define NEXT(a) (a)->next
#define INFO(a) (a)->info
#define LAST(L) (L)->last
#define FIRST(L) NEXT(LAST(L))
// Compara la informacion de dos elementos
#define COMP(L, a, b) (L)->cmp_element_function((a), (b))


typedef struct _NodeList { /* EdD privada, necesaria para implementar lista */
  void *info;
  struct _NodeList *next;
} NodeList; /* Tipo NodeList privado */


struct _List {
  NodeList *last; /*La LEC apunta al último nodo y el último al primero*/

  destroy_element_function_type   destroy_element_function;
  copy_element_function_type      copy_element_function;
  print_element_function_type     print_element_function;
  cmp_element_function_type       cmp_element_function;
};

/*******************
PRIVADAS Lista y NodeList
*******************/

/* PROTOTIPOS */


//Se reserva memoria para crear un NodeList y se devuelve, si no, devuelve NULL
NodeList * nodeList_ini();
//Dado un nodo se libera su memoria, a su vez se necewsita la lista de la que proviene
//  para saber como destruir el campo info
void nodeList_destroy(NodeList *n, const List *l);
//Crea una copia del elemento y la guarda en el campo info
Status nodeList_setInfo(NodeList *n, void *elem, const List *l);
//Inserta un nodo n1 ya creado despues de otro dado n2 (NEXT(n2) = n1)
void nodeList_insertAfter(NodeList *n1, NodeList *n2);

// Funcion recursiva para destruir la lista
void list_destroyRec(NodeList *nl, const List *l);

/* CUERPOS */


NodeList * nodeList_ini() {
  NodeList *nl = NULL;
  nl = NodeList*malloc(sizeof(NodeList));
  if(nl== NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s", strerror(errno));
    return NULL;
  }
  NEXT(nl) = NULL;
  INFO(nl) = NULL;
  return nl;
}


void nodeList_destroy(NodeList *n, const List *l) {
  if(l == NULL || n == NULL) return;
  if(INFO(n) != NULL) l->destroy_element_function(INFO(n));
  free(n);
}


Status nodeList_setInfo(NodeList *n, void *elem, const List *l) {
  if(!n || !elem || !l) return ERROR;
  // Destruir informacion previa si existe
  if(INFO(n) != NULL) l->destroy_element_function(INFO(n));
  // Copiar informacion nueva
  INFO(n) = l->copy_element_function(elem);
  if(INFO(n) == NULL) return ERROR;
  return OK;
}

void nodeList_insertAfter(NodeList *n1, NodeList *n2) {
  if(n1 == NULL || n2 == NULL) return;
  NEXT(n1) = NEXT(n2);
  NEXT(n2) = n1;
}


void list_destroyRec(NodeList *nl, const List *l) {
  if(nl == NULL || l == NULL) return;
  // Recursivamente se llega hasta el ultimo nodo no nulo y se va liberando
  list_destroyRec(nnext, l);
  nodeList_destroy(nl, l);
}


/*void list_insertInOrderRec (NodeList *nIns, NodeList *nList, List *l) {
  if(n == NULL || l == NULL) return NULL;
  // nList: nodo a cotejar perteneciente a la lista
  // nIns : nodo a insertar en la list
  if(INFO(nList) == NULL) return;

  // Si nIns es menor o igual al siguiente de nList se inserta despues de nList
  // (2): 0 - [1] - 3  => 0 - 1 - 2 - 3
  if(COMP(l, INFO(nIns), INFO(NEXT(nList))) <= 0) {
    nodeList_insertAfter(nIns, nList);
    return;
  }

  // Si hemos llegado al final sin insertar, insertamos y salimos
  // (4): 0 - 1 - [3]  => 0 - 1 - 3 - 4
  if(NEXT(nList) == LAST(l)) {
    nodeList_insertAfter(nIns, nList);
    LAST(l) = nIns;
    return;
  }

  list_insertInOrderRec(nIns, NEXT(nList), l);
}*/

/*******************
PRIMITIVAS List
*******************/

/* CUERPOS */


List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3,
cmp_element_function_type f4) {
  if(!f1 || !f2 || !f3 || !f4) return NULL;

  List *pl = NULL;
  pl = (List*)malloc(sizeof(List));
  if(pl == NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s", strerror(errno));
    return NULL;
  }
  pl->last = NULL;
  return pl;
}


void list_destroy (List* list) {
  if(list == NULL) return;
  // Guardamos el primer elemento de la lista
  NodeList *first = FIRST(list);

  // Liberamos y ponemos a NULL: LAST(list) para la salida de la recursion
  nodeList_destroy(LAST(list));
  LAST(list) = NULL;

  // Comenzamos la recursion desde first hasta hallar un next que sea NULL
  list_destroyRec(first, list);
  free(list);
}


Status list_insertFirst (List* list, const void *pelem) {
  if(list == NULL || pelem == NULL) return ERROR;

  NodeList *nnew = NULL;

  // Creamos nodo
  nnew = nodeList_ini();
  if(nnew == NULL) return ERROR;

  // Copiamos elemento en el campo info del nodo
  if(nodeList_setInfo(nnew, pelem, list) == ERROR) {
    nodeList_destroy(nnew, list);
    return ERROR;
  }

  // Seteamos:                NEXT(new) = FIRST
  // si la lista esta vacia:  NEXT(new) = new
  if(list_isEmpty(list) == TRUE)
    NEXT(nnew) = nnew;
  else
    NEXT(nnew) = FIRST(list);

  // Ponemos el primero de la lista al nuevo FIRST = new
  FIRST(list) = nnew;
  return OK;
}


Status list_insertLast (List* list, const void *pelem) {
  // Equivalente a list_insertFirst cambiando: LAST = FIRST nuevo
  if(list_insertFirst(list, pelem) == ERROR) return ERROR;
  LAST(list) = FIRST(list);
  return OK;
}

// ORDEN CRECIENTE : list = first -> [0,1,2,e,3,7,199] <- last
Status list_insertInOrder (List *list, const void *pelem) {
  if(list == NULL || pelem == NULL) return ERROR;

  NodeList *n  = NULL;
  NodeList *aux = NULL;

  // Si list esta vacia
  if(list_isEmpty(list)==TRUE) {
    return list_insertFirst(list, pelem);
  }

  // si pelem <= primer elemento... insertamos por el front
  if(COMP(list, pelem, FIRST(list)) <= 0) {
    return list_insertFirst(list, pelem);
  }

  // si pelem >= ultimo elemento... insertamos por el rear
  if(COMP(list, pelem, LAST(list)) >= 0) {
    return list_insertLast(list, pelem);
  }

  // Si no esta vacia...
  n = nodeList_ini();
  if(n == NULL) return ERROR;

  if(nodeList_setInfo(n, pelem, list) == ERROR) {
    nodeList_destroy(n, list);
    return ERROR;
  }

  // Recorremos hasta el LAST
  for(aux = FIRST(list); aux != LAST(list); aux = NEXT(aux)) {
    if(COMP(list, pelem, NEXT(aux)) <= 0) {
      nodeList_insertAfter(aux, n);
      return OK;
    }
  }

  // Si no se ha podido insertar en algún punto...
  nodeList_destroy(n, list);
  return ERROR;
}
