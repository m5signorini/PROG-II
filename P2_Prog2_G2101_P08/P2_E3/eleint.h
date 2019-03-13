/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   eleint.h
 * Author: e400156
 *
 * Created on 5 de marzo de 2019, 14:14
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

