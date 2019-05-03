/*
 * Nombre: eleint.h
 *
 * Descripción: TAD entero (MODIFICADO PARA P3E2)
 *
 * Autor: Martín Sánchez Signorini
 *
 */

#ifndef ELEINT_H
#define ELEINT_H


// Funcion que copia, reservando memoria, un entero src y devuelve la copia
int * int_copy(const int * src);

// Para liberar usaremos la funcion free directamente
void int_free(int * n);

// Imprime el entero devuelve numero de bytes impresos
int int_print(FILE *pf, const int *pi);

// Compara dos enteros, si...
// n1 < n2 devuelve negativo
// n1 > n2 devuelve positivo
// n1 = n2 devuelve 0
int int_cmp(const int* n1, const int* n2);

#endif /* ELEINT_H */
