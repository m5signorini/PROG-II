/*
 * Nombre: p3_e2.c
 *
 * Descripción: Ejercicio 2
 *
 * Autor: Martín Sánchez Signorini
 *
 * Modulos propios que necesita:
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "eleint.h"
/*
 *
 */

void aux_int_destroy(void * src);
void* aux_int_copy(const void* src);
int aux_int_print(FILE* pf, const void*src);
int aux_int_cmp(const void* n1, const void* n2);


void main_exit(int, List*, List*);

int main(int argc, char** argv) {
  // Checkear si el numero de argumentos es suficiente
  if(argc < 2) {
    fprintf(stderr, "Número de argumentos inválido\n");
    return EXIT_FAILURE;
  }

  List *l1 = NULL;
  List *l2 = NULL;
  int max, i;

  // OBTENER NUMERO
  max = atoi(argv[1]);
  if(max < 1) {
    fprintf(stderr, "Argumento invalido para probar la lista\n");
    return EXIT_FAILURE;
  }

  // INICIALIZAR LISTAS
  l1 = list_ini(aux_int_destroy, aux_int_copy, aux_int_print, aux_int_cmp);
  if(l1 == NULL) return EXIT_FAILURE;
  l2 = list_ini(aux_int_destroy, aux_int_copy, aux_int_print, aux_int_cmp);
  if(l2 == NULL) main_exit(EXIT_FAILURE, l1, l2);

  // INSERTAR DESDE MAX HASTA 1
  for(i = max; i >= 1; i--) {
    // Si es par
    if(i%2 == 0) {
      if(list_insertFirst(l1, &i) == ERROR) main_exit(EXIT_FAILURE, l1, l2);
    }
    // Si es impar
    else {
      if(list_insertLast(l1, &i) == ERROR) main_exit(EXIT_FAILURE, l1, l2);
    }
    // En cualquier caso
    if(list_insertInOrder(l2, &i) == ERROR) main_exit(EXIT_FAILURE, l1, l2);
  }

  // IMPRIMIR LISTAS
  if(list_print(stdout, l1) == -1) main_exit(EXIT_FAILURE, l1, l2);
  fprintf(stdout, "\n");
  if(list_print(stdout, l2) == -1) main_exit(EXIT_FAILURE, l1, l2);

  main_exit(EXIT_SUCCESS, l1, l2);

  return (EXIT_FAILURE);
}


void main_exit(int mens, List* pl1, List* pl2) {
  list_destroy(pl1);
  list_destroy(pl2);
  exit(mens);
}


/*****/


void aux_int_destroy(void * src) {
  int_free((int*)src);
}

void* aux_int_copy(const void* src) {
  return (void*)int_copy((int*)src);
}

int aux_int_print(FILE* pf, const void*src) {
  return int_print(pf, (int*)src);
}

int aux_int_cmp(const void* n1, const void* n2) {
  return int_cmp((int*)n1, (int*)n2);
}
