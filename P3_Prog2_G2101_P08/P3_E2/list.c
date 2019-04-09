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
#define PRINT(L, f, a) (L)->print_element_function((f), (a))


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
//Crea una copia del elemento y la guarda en el campo info de un nodo ya creado
Status nodeList_setInfo(NodeList *n, const void *elem, const List *l);
//Inserta un nodo n1 ya creado despues de otro dado n2 (NEXT(n2) = n1)
void nodeList_insertAfter(NodeList *n1, NodeList *n2);

// Funcion recursiva para destruir la lista
void list_destroyRec(NodeList *nl, const List *l);

/* CUERPOS */


NodeList * nodeList_ini() {
  NodeList *nl = NULL;
  nl = (NodeList*)malloc(sizeof(NodeList));
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


Status nodeList_setInfo(NodeList *n, const void *elem, const List *l) {
  if(!n || !elem || !l) return ERROR;

  void *copy = NULL;

  // Destruir informacion previa si existe
  if(INFO(n) != NULL) l->destroy_element_function(INFO(n));
  // Copiar informacion nueva
  copy = l->copy_element_function(elem);
  if(copy == NULL) return ERROR;
  INFO(n) = copy;
  return OK;
}

void nodeList_insertAfter(NodeList *n1, NodeList *n2) {
  if(n1 == NULL || n2 == NULL) return;
  NEXT(n1) = NEXT(n2);
  NEXT(n2) = n1;
}


void list_destroyRec(NodeList *nl, const List *l) {
  if(nl == NULL || l == NULL) return;

  // Recursivamente se llega hasta el ultimo nodo y se va liberando
  if(nl == LAST(l)) {
    nodeList_destroy(nl, l);
    return;
  }

  list_destroyRec(NEXT(nl), l);
  nodeList_destroy(nl, l);
}

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

  pl->destroy_element_function = f1;
  pl->copy_element_function = f2;
  pl->print_element_function = f3;
  pl->cmp_element_function = f4;

  LAST(pl) = NULL;
  return pl;
}


void list_destroy (List* list) {
  if(list == NULL) return;
  if(list_isEmpty(list)==TRUE) {
    free(list);
    return;
  }


  // Comenzamos la recursion desde first hasta hallar un next que sea NULL
  list_destroyRec(FIRST(list), list);
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
    LAST(list) = nnew;
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
  if(COMP(list, pelem, INFO(FIRST(list))) <= 0) {
    return list_insertFirst(list, pelem);
  }

  // si pelem >= ultimo elemento... insertamos por el rear
  if(COMP(list, pelem, INFO(LAST(list))) >= 0) {
    return list_insertLast(list, pelem);
  }

  // Si no esta vacia y no podemos atajar...
  n = nodeList_ini();
  if(n == NULL) return ERROR;

  if(nodeList_setInfo(n, pelem, list) == ERROR) {
    nodeList_destroy(n, list);
    return ERROR;
  }

  // Recorremos hasta el LAST
  for(aux = FIRST(list); aux != LAST(list); aux = NEXT(aux)) {
    if(COMP(list, pelem, INFO(NEXT(aux))) <= 0) {
      nodeList_insertAfter(n, aux);
      return OK;
    }
  }

  // Si no se ha podido insertar en ningun punto...
  nodeList_destroy(n, list);
  return ERROR;
}


void * list_extractFirst (List* list) {
  if(list == NULL || list_isEmpty(list) == TRUE) return NULL;

  void * ret = NULL;
  // aux apuntara al segundo elemento de la lista
  NodeList *aux = NULL;

  // Capturamos la info del primer nodo
  ret = INFO(FIRST(list));
  INFO(FIRST(list)) = NULL;

  // Si solo tiene un elemento (LAST = FIRST)
  if(LAST(list)==FIRST(list)) {
    // Poner LAST
    nodeList_destroy(LAST(list), list);
    LAST(list) = NULL;
    return ret;
  }
  // Poner FIRST y devolver
  aux = NEXT(FIRST(list));
  nodeList_destroy(FIRST(list), list);
  FIRST(list) = aux;
  return ret;
}


void * list_extractLast (List* list) {
  if(list == NULL || list_isEmpty(list) == TRUE) return NULL;

  void * ret = NULL;
  NodeList *aux = NULL;

  // Capturamos informacion
  ret = INFO(LAST(list));
  INFO(LAST(list)) = NULL;

  // Si solo tiene un elemento
  if(LAST(list)==FIRST(list)) {
    // Guardar info, poner info a null, destruir y devolver
    nodeList_destroy(LAST(list), list);
    LAST(list) = NULL;
    return ret;
  }

  // Para extraer el ultimo tenemos que acceder al penultimo => recorrer la lista
  // Llegamos hasta aux = penultimo
  for(aux = FIRST(list); NEXT(aux) != LAST(list); aux = NEXT(aux));
  NEXT(aux) = FIRST(list);
  nodeList_destroy(LAST(list), list);
  LAST(list) = aux;
  return ret;
}


Bool list_isEmpty (const List* list) {
  if(list == NULL) return TRUE;
  if(LAST(list)==NULL) return TRUE;
  return FALSE;
}


const void* list_get (const List* list, int index) {
  if(list == NULL || list_isEmpty(list)==TRUE) return NULL;
  // Suponemos que no se admiten valores negativos
  if(index < 0) {
    fprintf(stderr, "No se admiten valores negativos\n");
    return NULL;
  }

  NodeList *cont = NULL;

  // Se recorre index nodos
  for(cont = FIRST(list); index > 0; index--) {
    cont = NEXT(cont);
    // Si se ha recorrido toda la lista
    if(cont == FIRST(list)) {
      fprintf(stderr, "El indice introducido es excesivo\n");
      return NULL;
    }
  }

  return INFO(cont);
}


int list_size (const List* list) {
  if(list == NULL) return -1;
  if(list_isEmpty(list) == TRUE) return 0;

  NodeList *aux = FIRST(list);
  int size = 1;

  while(aux != LAST(list)){
    size++;
    aux = NEXT(aux);
  }

  return size;
}


int list_print (FILE *fd, const List* list) {
  if(fd == NULL || list == NULL) return -1;
  if(list_isEmpty(list)==TRUE) return 0;

  NodeList *aux = NULL;
  int nbytes = 0;
  int naux = 0; // auxiliar para checkear errores a la llamada print

  nbytes = PRINT(list, fd, INFO(FIRST(list)));
  if(nbytes == -1) return -1;
  nbytes += fprintf(fd, "\n");
  if(ferror(fd)) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
    return -1;
  }

  for(aux = NEXT(FIRST(list)); aux != FIRST(list); aux = NEXT(aux)) {
    naux = PRINT(list, fd, INFO(aux));
    if(naux == -1) return -1;
    nbytes += naux;
    nbytes += fprintf(fd, "\n");
    if(ferror(fd)) {
      fprintf(stderr, "Número de error: %d\n", errno);
      fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
      return -1;
    }
  }

  return nbytes;
}
