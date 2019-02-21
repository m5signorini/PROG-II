/* 
 * 
 * 
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack_elestack.h"
#include "node.h"
/*
 * 
 */

void main_exit(int mess, Stack *st, EleStack * ele, Node* n);

int main(int argc, char** argv) {
    
    Stack * pila = NULL;
    EleStack * element = NULL;
    Node * n1 = NULL;
    int aux;
    Status flag;
    
    //INICIALIZACION
    pila = stack_ini();
    if(pila == NULL) return EXIT_FAILURE;
    
    element = EleStack_ini();
    if(element == NULL) main_exit(EXIT_FAILURE, pila, element, n1);
    
    n1 = node_ini();
    if(n1 == NULL) main_exit(EXIT_FAILURE, pila, element, n1);
    
    
    //SET-INSERT 1
    node_setId(n1, 111);
    node_setName(n1, "first");
    
    flag = EleStack_setInfo(element, (void*)n1);
    if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element, n1);
    
    flag = stack_push(pila, element);
    if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element, n1);
    
    
    //SET-INSERT 2
    node_setId(n1, 222);
    node_setName(n1, "second");
    
    flag = EleStack_setInfo(element, (void*)n1);
    if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element, n1);
    
    flag = stack_push(pila, element);
    if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element, n1);
    
    
    //FREE ELEMENT
    EleStack_destroy(element);
    element = NULL;
    
    //PRINT 1
    fprintf(stdout, "Contenido de la pila:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, element, n1);
    fprintf(stdout, "Caracteres impresos: %d\n", aux);
    
    // VACIADO
    fprintf(stdout, "Vaciando pila. Extracciones:\n");
    while(stack_isEmpty(pila) == FALSE) {
        //Pop and catch
        element = stack_pop(pila);
        if(element == NULL) main_exit(EXIT_FAILURE, pila, element, n1);
        
        //Print and free
        EleStack_print(stdout, element);
        fprintf(stdout, " ");
        EleStack_destroy(element);
        element = NULL;
    }
    
    //PRINT 2
    fprintf(stdout, "\nContenido de la pila despues de vaciar:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, element, n1);
    fprintf(stdout, "Caracteres impresos: %d\n", aux);
    /*
    */
    
    main_exit(EXIT_SUCCESS, pila, element, n1);
    return EXIT_FAILURE;
}

void main_exit(int mess, Stack * st, EleStack * ele, Node* n) {
    stack_destroy(st);
    st = NULL;
    EleStack_destroy(ele);
    ele = NULL;
    node_destroy(n);
    n = NULL;
    
    exit(mess);
}

