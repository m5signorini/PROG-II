/*
 * Nombre: Cadena.c
 *
 * Descripción: Estructura: Cadena de caracteres
 *
 * Autor: Martín Sánchez Signorini
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "cadena.h"

extern int errno;

struct _Cadena {
  char * str;
};


Cadena * cadena_ini(const char * str) {
  if(str == NULL) return NULL;
  int tam;
  char * strnew = NULL;
  Cadena * cad = NULL;

  tam = strlen(str) + 1;
  if(tam < 0) return NULL;

  strnew = (char *) malloc(sizeof(char) * tam);
  if(strnew == NULL) {
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
    return NULL;
  }

  cad = (Cadena *)malloc(sizeof(Cadena));
  if(cad == NULL) {
    free(strnew);
    fprintf(stderr, "Número de error: %d\n", errno);
    fprintf(stderr, "Mensaje de error: %s\n", strerror(errno));
    return NULL;
  }

  strncpy(strnew, str, tam);

  cad->str = strnew;

  return cad;
}


void cadena_destroy(Cadena *cad) {
  if(cad == NULL) return;
  free(cad->str);
  free(cad);
}


Cadena * cadena_copy(const Cadena *cad) {
  if(cad == NULL) return NULL;
  Cadena *cad2 = NULL;
  cad2 = cadena_ini(cad->str);
  return cad2;
}

// Imprime str en pf
int cadena_print(FILE *pf, const Cadena *cad) {
  if(pf == NULL || cad == NULL) return -1;

  int nbytes;

  nbytes = fprintf(pf, "%s ", cad->str);
  return nbytes;
}

// Compara cadena str1 con str2
// str1 < str2 devuelve negativo
// str1 > str22 devuelve positivo
// str1 = str2 devuelve 0
int cadena_cmp(const Cadena *cad1, const Cadena *cad2) {
  if(cad1 == NULL && cad2 == NULL) {
    return 0;
  }
  else if(cad1 == NULL && cad2 != NULL) {
    return -1;
  }
  else if(cad2 == NULL && cad1 != NULL) {
    return 1;
  }

  return strcmp(cad1->str, cad2->str);
}
