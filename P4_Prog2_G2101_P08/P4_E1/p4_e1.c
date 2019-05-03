/*
 * Nombre: p4_e1.c
 *
 * Descripción: Ejercicio 1
 *
 * Autor: Martín Sánchez Signorini
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "eleint.h"


void aux_int_destroy(void * src);
void* aux_int_copy(const void* src);
int aux_int_print(FILE* pf, const void*src);
int aux_int_cmp(const void* n1, const void* n2);


void main_exit(int mens, Tree *t);
Status file_to_tree(FILE *f, Tree *t);

int main(int argc, char **argv) {

  if(argc < 2) return EXIT_FAILURE;
  /*
    Se recibe en argv[1] un fichero con los numeros enteros por filas
  */
  Tree * pt = NULL;
  FILE *f = NULL;
  int i;

  pt = tree_ini(aux_int_destroy, aux_int_copy, aux_int_print, aux_int_cmp);
  if(pt == NULL) main_exit(EXIT_FAILURE, pt);

  f = fopen(argv[1], "r");
  if(f == NULL) main_exit(EXIT_FAILURE, pt);


  // LECTURA
  if(file_to_tree(f, pt) == ERROR)  {
    fclose(f);
    main_exit(EXIT_FAILURE, pt);
  }

  fprintf(stdout, "Número de nodos: %d\n", tree_numNodes(pt));
  fprintf(stdout, "Profundidad: %d\n", tree_depth(pt));

  fprintf(stdout, "> Introduce un número: ");
  fscanf(stdin, "%d", &i);
  fprintf(stdout, "El número %d ", i);

  if(tree_find(pt, &i) == FALSE) {
    fprintf(stdout, "no ");
  }

  fprintf(stdout, "se encuentra en el árbol\n");

  fclose(f);
  main_exit(EXIT_SUCCESS, pt);


  return EXIT_SUCCESS;
}


Status file_to_tree(FILE *f, Tree *t) {
  if(f == NULL || t == NULL) return ERROR;
  int i;
  while(fscanf(f, "%d", &i) == 1) {
    if(tree_insert(t, &i) == ERROR)  {
      return ERROR;
    }
  }
  return OK;
}


void main_exit(int mens, Tree *t) {
  tree_free(t);
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
