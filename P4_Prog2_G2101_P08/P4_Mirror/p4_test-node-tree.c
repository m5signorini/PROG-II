/*
 * Nombre: p4_test-node-tree.c
 *
 * Descripción: Ejercicio 3.1
 *
 * Autor: Martín Sánchez Signorini
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "node.h"

#define MAX_NAME 256


void aux_node_destroy(void * src);
void* aux_node_copy(const void* src);
int aux_node_print(FILE* pf, const void*src);
int aux_node_cmp(const void* n1, const void* n2);


void main_exit(int mens, Tree *t, FILE *f);
Status file_to_tree(FILE *f, Tree *t, Node *pn);

int main(int argc, char **argv) {

  if(argc < 2) return EXIT_FAILURE;
  /*
    Se recibe en argv[1] un fichero con la forma:
    1 arbol
    7 gato
    5 cero
    ...
  */
  Tree * pt = NULL;
  FILE *f = NULL;
  Node *pn = NULL;

  pt = tree_ini(aux_node_destroy, aux_node_copy, aux_node_print, aux_node_cmp);
  if(pt == NULL) main_exit(EXIT_FAILURE, pt, f);

  f = fopen(argv[1], "r");
  if(f == NULL) main_exit(EXIT_FAILURE, pt, f);

  pn = node_ini();
  if(pn == NULL) main_exit(EXIT_FAILURE, pt, f);

  // LECTURA
  if(file_to_tree(f, pt, pn) == ERROR) {
    node_destroy(pn);
    main_exit(EXIT_FAILURE, pt, f);
  }

  node_destroy(pn);

  fprintf(stdout, "Número de nodos: %d\n", tree_numNodes(pt));
  fprintf(stdout, "Profundidad: %d\n", tree_depth(pt));

  // ORDENES
  fprintf(stdout, "Orden previo: ");
  if(tree_preOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);
  fprintf(stdout, "\nOrden medio: ");
  if(tree_inOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);
  fprintf(stdout, "\nOrden posterior: ");
  if(tree_postOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);
  fprintf(stdout, "\n");

  main_exit(EXIT_SUCCESS, pt, f);

  return EXIT_SUCCESS;
}


Status file_to_tree(FILE *f, Tree *t, Node *pn) {
  if(f == NULL || t == NULL) return ERROR;
  char name[MAX_NAME];
  int id;

  while(fscanf(f, "%d %s", &id, name) == 2) {
    node_setName(pn, name);
    node_setId(pn, id);
    if(tree_insert(t, pn) == ERROR) return ERROR;
  }
  return OK;
}


void main_exit(int mens, Tree *t, FILE *f) {
  if(f!=NULL)fclose(f);
  tree_free(t);
  exit(mens);
}


/*****/


void aux_node_destroy(void * src) {
  node_destroy((Node*)src);
}

void* aux_node_copy(const void* src) {
  return (void*)node_copy((Node*)src);
}

int aux_node_print(FILE* pf, const void*src) {
  return node_print(pf, (Node*)src);
}

int aux_node_cmp(const void* n1, const void* n2) {
  return node_cmp((Node*)n1, (Node*)n2);
}
