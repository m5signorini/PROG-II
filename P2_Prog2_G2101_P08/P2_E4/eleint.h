/*
 * Nombre: eleint.h
 *
 * Descripción: TAD entero
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

#endif /* ELEINT_H */
