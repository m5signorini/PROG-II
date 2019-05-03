/*
 * Nombre: p4_e4.c
 *
 * Descripción: Ejercicio 4
 *
 * Autor: Martín Sánchez Signorini
 *
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include "tree.h"
 #include "cadena.h"

 #define MAX_LINE 1024

 void aux_cad_destroy(void * src);
 void* aux_cad_copy(const void* src);
 int aux_cad_print(FILE* pf, const void*src);
 int aux_cad_cmp(const void* n1, const void* n2);


 void main_exit(int mens, Tree *t, FILE *f);
 Status file_to_tree(FILE *f, Tree *t);
 Status find_elem();
 Cadena * read_cad_from_file(FILE *pf);

 int main(int argc, char **argv) {

   if(argc < 2) return EXIT_FAILURE;

   Tree * pt = NULL;
   FILE *f = NULL;

   pt = tree_ini(aux_cad_destroy, aux_cad_copy, aux_cad_print, aux_cad_cmp);
   if(pt == NULL) main_exit(EXIT_FAILURE, pt, f);

   f = fopen(argv[1], "r");
   if(f == NULL) main_exit(EXIT_FAILURE, pt, f);


   // LECTURA
   if(file_to_tree(f, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);

   fprintf(stdout, "Número de nodos: %d\n", tree_numNodes(pt));
   fprintf(stdout, "Profundidad: %d\n", tree_depth(pt));

   // ORDENES
   fprintf(stdout, "Orden previo: ");
   if(tree_preOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);
   fprintf(stdout, "\nOrden medio: ");
   if(tree_inOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);
   fprintf(stdout, "\nOrden posterior: ");
   if(tree_postOrder(stdout, pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);

   // ENCONTRAR ELEMENTO
   if(find_elem(pt) == ERROR) main_exit(EXIT_FAILURE, pt, f);

   main_exit(EXIT_SUCCESS, pt, f);

   return EXIT_SUCCESS;
 }


 Status find_elem(Tree *pt) {

   char str[MAX_LINE];
   Cadena *cad;

   fprintf(stdout, "\n> Introduce una cadena de caracteres: ");
   fscanf(stdin, "%s", str);
   fprintf(stdout, "La cadena %s ", str);

   cad = cadena_ini(str);
   if(cad == NULL) return ERROR;

   if(tree_find(pt, cad) == FALSE) {
     fprintf(stdout, "no ");
   }

   cadena_destroy(cad);
   fprintf(stdout, "se encuentra en el árbol\n");
   return OK;
 }


 Cadena * read_cad_from_file(FILE *pf) {
    Cadena * cad = NULL;
    char buff[MAX_LINE], str[MAX_LINE];

    if(fgets(buff, MAX_LINE, pf) != NULL) {
      if(sscanf(buff, "%s", str) == 1) {
        cad = cadena_ini(str);
      }
    }
    return cad;
 }


 Status file_to_tree(FILE *f, Tree *t) {
   if(f == NULL || t == NULL) return ERROR;
   Cadena *cad = NULL;

   while(!feof(f)) {
     cad = read_cad_from_file(f);
     if(cad != NULL) {
       if(tree_insert(t, cad) == ERROR)  {
         cadena_destroy(cad);
         cad = NULL;
         return ERROR;
       }
       cadena_destroy(cad);
       cad = NULL;
     }
   }

   return OK;
 }


 void main_exit(int mens, Tree *t, FILE *f) {
   if(f!=NULL) fclose(f);
   tree_free(t);
   exit(mens);
 }


 /*****/


 void aux_cad_destroy(void * src) {
   cadena_destroy((Cadena*)src);
 }

 void* aux_cad_copy(const void* src) {
   return (void*)cadena_copy((Cadena*)src);
 }

 int aux_cad_print(FILE* pf, const void*src) {
   return cadena_print(pf, (Cadena*)src);
 }

 int aux_cad_cmp(const void* n1, const void* n2) {
   return cadena_cmp((Cadena*)n1, (Cadena*)n2);
 }
