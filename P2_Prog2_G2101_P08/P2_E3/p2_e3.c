/*
 * Nombre: p2_e3.c
 *
 * Descripción: Ejercicio 3
 *
 * Autor: Martín Sánchez Signorini
 *
 * Modulos propios que necesita:
 * - stack_fp
 * - eleint
 * - node
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack_fp.h"
#include "node.h"
#include "eleint.h"

/*
 *
 */

void main_exit(int, Stack*, Node*);
double pila_media(Stack *st);

void fp_node_destroy(void * n);
void * fp_node_copy(const void * src);
int fp_node_print(FILE *pf, const void * n);

void fp_int_destroy(void * n);
void * fp_int_copy(const void * src);
int fp_int_print(FILE *pf, const void * n);


int main(int argc, char** argv) {
    // Checkear si el numero de argumentos es suficiente
    if(argc < 2) return EXIT_FAILURE;
    //--------------------//
    // EJERCICIO 1: NODOS //
    //--------------------//

    Stack * pila = NULL;
    Node * n1 = NULL;
    int * ent = NULL;
    int aux = 0;
    int i;
    double media = 0;


    //INICIALIZACION
    pila = stack_ini(fp_node_destroy, fp_node_copy, fp_node_print);
    if(pila == NULL) return EXIT_FAILURE;

    n1 = node_ini();
    if(n1 == NULL) main_exit(EXIT_FAILURE, pila, n1);

    //SET-INSERT 1
    node_setId(n1, 111);
    node_setName(n1, "first");

    if(stack_push(pila, n1) == ERROR)
        main_exit(EXIT_FAILURE, pila, n1);

    //SET-INSERT 2
    node_setId(n1, 222);
    node_setName(n1, "second");

    if(stack_push(pila, n1) == ERROR)
        main_exit(EXIT_FAILURE, pila, n1);

    //FREE NODO
    node_destroy(n1);
    n1 = NULL;

    //PRINT 1
    fprintf(stdout, "Contenido de la pila:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, n1);
    fprintf(stdout, "Caracteres impresos: %d\n", aux);

    // VACIADO
    fprintf(stdout, "Vaciando pila. Extracciones:\n");
    while(stack_isEmpty(pila) == FALSE) {
        //Pop and catch
        n1 = stack_pop(pila);

        //Print and free
        node_print(stdout, n1);
        fprintf(stdout, " ");
        node_destroy(n1);
        n1 = NULL;
    }

    //PRINT 2
    fprintf(stdout, "\nContenido de la pila despues de vaciar:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, n1);
    fprintf(stdout, "Caracteres impresos: %d\n", aux);
    /*
    */

    //----------------------//
    // EJERCICIO 2: ENTEROS //
    //----------------------//

    stack_destroy(pila);
    pila = NULL;

    pila = stack_ini(fp_int_destroy, fp_int_copy, fp_int_print);
    if(pila == NULL) main_exit(EXIT_FAILURE, pila, n1);

    aux = atoi(argv[1]);

    for(i = 0; i <= aux; i++) {
        // set ent a aux
        // sin reservar memoria
        ent = &i;

        // push a pila
        // si la pila se llena se devuelve error y se finaliza
        if(stack_push(pila, ent) == ERROR) main_exit(EXIT_FAILURE, pila, n1);
    }

    fprintf(stdout, "\nPila antes de la llamada a la función:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, n1);

    media = pila_media(pila);
    if(media == -1) main_exit(EXIT_FAILURE, pila, n1);
    fprintf(stdout, "La media es %lf\n", media);

    fprintf(stdout, "Pila después de la llamada a la función:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, n1);

    main_exit(EXIT_SUCCESS, pila, n1);

    return (EXIT_SUCCESS);
}

void main_exit(int mens, Stack* st, Node* n) {
    stack_destroy(st);
    node_destroy(n);
    exit(mens);
}

// Suponemos que sabemos que se pasara una pila de enteros
double pila_media(Stack *st) {
    if(st == NULL) return 0;

    Stack *paux = NULL;
    int *info = NULL;
    int tam = 0;
    double retorno = 0;

    paux = stack_ini(fp_int_destroy, fp_int_copy, fp_int_print);
    if(paux == NULL) return 0;

    while(stack_isEmpty(st) == FALSE) {
        // Pop st y push paux
        info = stack_pop(st);
        if(stack_push(paux, info) == ERROR) {
	      // Como push reserva memoria, un error no permitirá restaurar la pila original
            int_free(info);
            stack_destroy(paux);
            return -1;
        }
        // Aumentamos tam, sumamos valor y lo liberamos
        tam++;
        retorno += *info;
        // getInfo devuelve copia - liberar
        int_free(info);
    }

    while(stack_isEmpty(paux) == FALSE) {
        info = stack_pop(paux);
        if(stack_push(st, info) == ERROR) {
      	    int_free(info);
      	    stack_destroy(paux);
      	    return -1;
      	}
        int_free(info);
    }
    stack_destroy(paux);
    if(tam == 0) return 0;
    retorno = retorno / tam;

    return retorno;
}





/********/
/********/

void fp_node_destroy(void * n) {
    node_destroy((Node*) n);
}

void * fp_node_copy(const void * src) {
    return (void*) node_copy((Node*) src);
}

int fp_node_print(FILE *pf, const void * n) {
    return node_print(pf, (Node *)n);
}

/********/
/********/

void fp_int_destroy(void * n) {
    int_free((int*) n);
}

void * fp_int_copy(const void * src) {
    return (void*) int_copy((int*) src);
}

int fp_int_print(FILE *pf, const void * n) {
    return int_print(pf, (int *)n);
}
