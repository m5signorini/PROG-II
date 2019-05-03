/*
 * Nombre: cadena.h
 *
 * Descripción: TAD Cadena de caracteres
 *
 * Autor: Martín Sánchez Signorini
 *
 */

 #ifndef CADENA_H
 #define CADENA_H

 #include "types.h"

 typedef struct _Cadena Cadena;


// Crea una cadena a partir de un puntero a caracter que no se modifica
Cadena * cadena_ini(const char * str);

// Libera la memoria reservada para una cadena
 void cadena_destroy(Cadena *cad);

// Resrva memoria para una nueva cadena y la devuelve como copia del argumento
Cadena * cadena_copy(const Cadena *cad);

// Imprime str en pf
int cadena_print(FILE *pf, const Cadena *cad);

// Compara cadena str1 con str2
// positivo: str2 ANTERIOR (alfabeticamente)
// negativo: str1 ANTERIOR
// str1 = str2 devuelve 0
int cadena_cmp(const Cadena *cad1, const Cadena *cad2);



 #endif /* CADENA_H */
