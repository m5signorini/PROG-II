/*

Nombre: queue.c
Pareja: 08
Autor: Martín Sánchez Signorini

Descripción: Estructura de Cola (Array Circular)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "queue.h"
#define MAXQUEUE 128
// Macros para sumar y restar en módulo MAXQUEUE
#define ADDQ(a) ((a)+1)%MAXQUEUE
#define SUBQ(a) ((a)-1)%MAXQUEUE

extern int errno;

struct _Queue {
  void* items [MAXQUEUE]; // La cola sacrificará uno de los huecos
  int front;  // Marca la posición del elemento a extraer
  int rear;   // Marca la posición a insertar el elemento
  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};



/*
FUNCIONES PRIMITIVAS
*/

Queue * queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3) {
  if(f1 == NULL || f2 == NULL || f3 == NULL) return NULL;

  Queue * pq = NULL;
  int i;

  pq = (Queue*)malloc(sizeof(Queue));
  if(pq == NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s", strerror(errno));
    return NULL;
  }

  // Ponemos items a null
  for(i = 0; i < MAXQUEUE; i++) {
    pq->items[i] = NULL;
  }

  // El front empieza en 0
  pq->front = 0;
  // El rear empieza en 0
  pq->rear = 0;
  pq->destroy_element_function = f1;
  pq->copy_element_function = f2;
  pq->print_element_function = f3;
  return pq;
}


void queue_destroy(Queue *q) {
  if(q == NULL) return;
  // Si no es null, liberamos todos los elementos mientras no este vacia
  while(queue_isEmpty(q) == FALSE) {
    // Destruir elemento del front
    q->destroy_element_function(q->items[q->front]);
    q->front = ADDQ(q->front);
  }
  free(q);
}


Bool queue_isEmpty(const Queue *q) {
  if(q == NULL) return TRUE;
  if(q->front == q->rear) return TRUE;
  return FALSE;
}

Bool queue_isFull(const Queue* q) {
  if(q == NULL) return TRUE;
  if(ADDQ(q->rear) == q->front) return TRUE;
  return FALSE;
}


Status queue_insert(Queue *q, const void* pElem) {
  if(q == NULL || pElem == NULL) return ERROR;
  if(queue_isFull(q) == TRUE) return ERROR;

  void *ecpy = NULL;

  ecpy = q->copy_element_function(pElem);
  if(ecpy == NULL) return ERROR;

  // Se inserta en el rear
  q->items[q->rear] = ecpy;
  // Se aumenta el rear
  q->rear = ADDQ(q->rear);

  return OK;
}


void * queue_extract(Queue *q) {
  if(q == NULL || queue_isEmpty(q)) return NULL;

  void *pe = NULL;
  // Reasignar puntero
  pe = q->items[q->front];
  // Poner front a null y sumar front
  q->items[q->front] = NULL;
  q->front = ADDQ(q->front);

  return pe;
}


int queue_size(const Queue *q) {
  if(q == NULL) return -1;
  // Formula para calcular la distancia modulo
  return (q->rear - q->front)%MAXQUEUE;
}


int queue_print(FILE *pf, const Queue *q) {
  if(pf == NULL || q == NULL) return -1;
  int i, aux, nbytes = 0;

  // Si la cola esta vacia imprimimos:
  if(queue_isEmpty(q) == TRUE) {
    nbytes = fprintf(pf, "Queue vacia\n");
    if(ferror(pf)) {
      fprintf(stderr, "Error al imprimir\n");
      return -1;
    }
    return nbytes;
  }

  nbytes += fprintf(pf, "Cola con %d elementos:\n", queue_size(q));
  if(ferror(pf)) {
    fprintf(stderr, "Error al imprimir\n");
    return -1;
  }

  // Entero auxiliar en la primera posicion
  // Aux se usa para checkear errores en el print interno
  for(i = q->front; i != q->rear; i = ADDQ(i)) {
    aux = q->print_element_function(pf, q->items[i]);
    // Si ocurre un error en la funcion del elemento salimos de la funcion
    if(aux < 0) return -1;
    nbytes += aux;
  }

  nbytes += fprintf(pf, "\n");
  if(ferror(pf)) {
    fprintf(stderr, "Error al imprimir\n");
    return -1;
  }

  return nbytes;
}
