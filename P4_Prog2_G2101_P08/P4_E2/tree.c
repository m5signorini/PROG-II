




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tree.h"

#define INFO(a) (a)->info
#define ROOT(t) (t)->root
#define LEFT(n) (n)->left
#define RIGHT(n) (n)->right

#define COMP(n, m) cmp_element_function((n), (m))
#define PRINT(f, n) print_element_function((f), (n))

extern int errno;

typedef struct _NodeBT {
  void* info;
  struct _NodeBT* left;
  struct _NodeBT* right;
} NodeBT;


struct _Tree {
  NodeBT *root;
  destroy_element_function_type   destroy_element_function;
  copy_element_function_type      copy_element_function;
  print_element_function_type     print_element_function;
  cmp_element_function_type       cmp_element_function;
};

/*
  PROTOTIPOS
*/

Status nodeBT_setInfo(NodeBT *n, const void *elem, const Tree *t);
NodeBT * nodeBT_ini();
void nodeBT_free(const Tree *t, NodeBT *pn);

void tree_free_rec(Tree *t, NodeBT * pn);
NodeBT * tree_insert_rec(Tree *t, NodeBT *pn, NodeBT *nnew);
int tree_depth_rec(const NodeBT *nr);
int tree_numNodes_rec(const NodeBT *nr);
Bool tree_find_rec(const NodeBT *nr, const void * elem, const Tree * t);

Status tree_preOrder_rec(FILE *f, const NodeBT *pn, const Tree *t);
Status tree_inOrder_rec(FILE *f, const NodeBT *pn, const Tree *t);
Status tree_posOrder_rec(FILE *f, const NodeBT *pn, const Tree *t);

/*
  FUNCIONES PRIVADAS
*/

NodeBT * nodeBT_ini() {
  NodeBT *pn = NULL;
  pn = (NodeBT*)malloc(sizeof(NodeBT));
  if(pn == NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
    return NULL;
  }
  INFO(pn) = NULL;
  LEFT(pn) = NULL;
  RIGHT(pn) = NULL;
  return pn;
}


void nodeBT_free(const Tree *t, NodeBT *pn) {
  if(t == NULL || pn == NULL) return;
  // Se libera la info si hay
  if(INFO(pn)) t->destroy_element_function(INFO(pn));
  // Se libera el nodo
  free(pn);
}


Status nodeBT_setInfo(NodeBT *n, const void *elem, const Tree *t) {
  if(!n || !elem || !t) return ERROR;
  void *copy = NULL;
  // Destruir informacion previa si existe
  // Copiar informacion nueva
  if(INFO(n) != NULL) t->destroy_element_function(INFO(n));
  copy = t->copy_element_function(elem);
  if(copy == NULL) return ERROR;
  INFO(n) = copy;
  return OK;
}



/***************/


void tree_free_rec(Tree *t, NodeBT * pn) {
  if(pn == NULL) return;

  tree_free_rec(t, RIGHT(pn));
  tree_free_rec(t, LEFT(pn));

  nodeBT_free(t, pn);
}


// Dado un arbol, su raiz y un nodo nuevo a insertar,
NodeBT * tree_insert_rec(Tree *t, NodeBT *pn, NodeBT *nnew) {
  int cmp;

  if(pn == NULL) return nnew;

  cmp = t->COMP(INFO(nnew), INFO(pn));
  // Si el elemento nuevo es mayor -> derecha
  if(cmp > 0) {
    RIGHT(pn) = tree_insert_rec(t, RIGHT(pn), nnew);
  }
  // Si el elemento nuevo es menor -> izquierda
  else if(cmp < 0) {
    LEFT(pn) = tree_insert_rec(t, LEFT(pn), nnew);
  }
  // Si son iguales no se inserta y se libera la copia
  else {
    nodeBT_free(t, nnew);
  }
  return pn;
}


int tree_depth_rec(const NodeBT *nr) {
  if(nr == NULL) return -1;
  int left_depth = tree_depth_rec(LEFT(nr));
  int right_depth = tree_depth_rec(RIGHT(nr));
  return (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;
}


int tree_numNodes_rec(const NodeBT *nr) {
  if(nr == NULL) return 0;
  int l =  tree_numNodes_rec(LEFT(nr));
  int r =  tree_numNodes_rec(RIGHT(nr));
  return l + r + 1;
}


Bool tree_find_rec(const NodeBT *nr, const void * elem, const Tree *t) {
  if(nr == NULL) return FALSE;

  int cmp;
  cmp = t->COMP(INFO(nr), elem);

  if(cmp == 0) {
    return TRUE;
  }
  // Si elem < nr -> IZQ
  else if(cmp > 0) {
    return tree_find_rec(LEFT(nr), elem, t);
  }
  else {
    return tree_find_rec(RIGHT(nr), elem, t);
  }
}


/*
  FUNCIONES PUBLICAS
*/

Tree* tree_ini(
  destroy_element_function_type f1,
  copy_element_function_type f2,
  print_element_function_type f3,
  cmp_element_function_type f4) {
  if(!f1 || !f2 || !f3 || !f4) return NULL;

  Tree *t = NULL;
  t = (Tree*)malloc(sizeof(Tree));
  if(t == NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s", strerror(errno));
    return NULL;
  }
  ROOT(t) = NULL;
  t->destroy_element_function = f1;
  t->copy_element_function = f2;
  t->print_element_function = f3;
  t->cmp_element_function = f4;

  return t;
}


Bool tree_isEmpty( const Tree *pa) {
  if(pa == NULL) return TRUE;
  if(ROOT(pa)==NULL) return TRUE;
  return FALSE;
}


void tree_free(Tree *pa) {
  if(pa == NULL) return;
  tree_free_rec(pa, ROOT(pa));
  free(pa);
}


Status tree_insert(Tree *pa, const void *po) {
  if(pa == NULL || po == NULL) return ERROR;
  // Se realiza la copia como nodo de po y se llama luego a la recursiva
  NodeBT *nnew = NULL;

  nnew = nodeBT_ini();
  if(nnew == NULL) return ERROR;

  if(nodeBT_setInfo(nnew, po, pa) == ERROR) {
    nodeBT_free(pa, nnew);
    return ERROR;
  }

  ROOT(pa) = tree_insert_rec(pa, ROOT(pa), nnew);

  return OK;
}


int tree_depth(const Tree *pa) {
  if(pa == NULL) return -1;
  return tree_depth_rec(ROOT(pa));
}


int tree_numNodes(const Tree *pa) {
  if(pa == NULL) return 0;
  return tree_numNodes_rec(ROOT(pa));
}


Bool tree_find(Tree* pa, const void* pe) {
  if(pa == NULL || pe == NULL) return FALSE;
  return tree_find_rec(ROOT(pa), pe, pa);
}


Status tree_preOrder(FILE *f, const Tree *pa) {
  if(f == NULL || pa == NULL) return ERROR;
  return tree_preOrder_rec(f, ROOT(pa), pa);
}


Status tree_inOrder(FILE *f, const Tree *pa) {
  if(f == NULL || pa == NULL) return ERROR;
  return tree_inOrder_rec(f, ROOT(pa), pa);
}


Status tree_postOrder(FILE *f, const Tree *pa) {
  if(f == NULL || pa == NULL) return ERROR;
  return tree_posOrder_rec(f, ROOT(pa), pa);
}


/****/


Status tree_preOrder_rec(FILE *f, const NodeBT *pn, const Tree *t) {
  if(pn == NULL) return OK;

  if(t->PRINT(f, INFO(pn)) == -1) return ERROR;
  if(tree_preOrder_rec(f, LEFT(pn), t) == ERROR) return ERROR;
  if(tree_preOrder_rec(f, RIGHT(pn), t) == ERROR) return ERROR;

  return OK;
}


Status tree_inOrder_rec(FILE *f, const NodeBT *pn, const Tree *t) {
  if(pn == NULL) return OK;

  if(tree_inOrder_rec(f, LEFT(pn), t) == ERROR) return ERROR;
  if(t->PRINT(f, INFO(pn)) == -1) return ERROR;
  if(tree_inOrder_rec(f, RIGHT(pn), t) == ERROR) return ERROR;

  return OK;
}


Status tree_posOrder_rec(FILE *f, const NodeBT *pn, const Tree *t) {
  if(pn == NULL) return OK;

  if(tree_posOrder_rec(f, LEFT(pn), t) == ERROR) return ERROR;
  if(tree_posOrder_rec(f, RIGHT(pn), t) == ERROR) return ERROR;
  if(t->PRINT(f, INFO(pn)) == -1) return ERROR;

  return OK;
}
