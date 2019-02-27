/* 
 * 
 * P2 - Ejercicio 2
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack_elestack.h"
/*
 * 
 */

void main_exit(int mess, Stack *st, EleStack * ele);
double pila_media(Stack *st);

int main(int argc, char** argv) {
    
    Stack * pila = NULL;
    EleStack * element = NULL;
    int * pe = NULL;
    int aux = 0, n = 0;
    double media;
    Status flag;
    
    //INICIALIZACION
    pila = stack_ini();
    if(pila == NULL) return EXIT_FAILURE;
    
    element = EleStack_ini();
    if(element == NULL) main_exit(EXIT_FAILURE, pila, element);
    
    n = atoi(argv[1]);
    
    //INSERT: 0 a n
    
    for(aux = 0; aux <= n; aux++) {
        // set pe a aux
        pe = &aux;
        
        // set info a pe
        flag = EleStack_setInfo(element, (void*)pe);
        if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element);
        
        // push element a pila
        // si la pila se llena se devuelve error y se finaliza
        flag = stack_push(pila, element);
        if(flag == ERROR) main_exit(EXIT_FAILURE, pila, element);
    }
    
    //FREE ELEMENT
    EleStack_destroy(element);
    element = NULL;
    
    //PRINT ANTES DE LA FUNCION
    fprintf(stdout, "Pila antes de la llamada a la función:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, element);
    
    //CALCULAR MEDIA
    media = pila_media(pila);
    fprintf(stdout, "La media es %lf\n", media);
    
    //PRINT DESPUES DE LA FUNCION
    fprintf(stdout, "Pila después de la llamada a la función:\n");
    aux = stack_print(stdout, pila);
    if(aux == -1) main_exit(EXIT_FAILURE, pila, element);
    /*
    */
    
    main_exit(EXIT_SUCCESS, pila, element);
    return EXIT_FAILURE;
}

void main_exit(int mess, Stack * st, EleStack * ele) {
    stack_destroy(st);
    st = NULL;
    EleStack_destroy(ele);
    ele = NULL;
    
    exit(mess);
}


double pila_media(Stack *st) {
    if(st == NULL) return 0;
    
    EleStack *info = NULL;
    Stack *paux = NULL;
    int *valor = NULL;
    int tam = 0;
    double retorno = 0;
    
    paux = stack_ini();
    if(paux == NULL) return 0;
    
    while(stack_isEmpty(st) == FALSE) {
        // Pop st y push paux
        info = stack_pop(st);
        if(stack_push(paux, info) == ERROR) {
            // Restablecer st si push = ERROR
            stack_push(st, info);
            EleStack_destroy(info);
            while(stack_isEmpty(paux) == FALSE) {
                // Asumimos que tras k extracciones se realizaran
                // k inserciones sin problemas
                info = stack_pop(paux);
                stack_push(st, info);
                EleStack_destroy(info);
            }
            // Restornamos
            stack_destroy(paux);
            return 0;
        }
        // Aumentamos tam, sumamos valor y lo liberamos
        valor = (int*)EleStack_getInfo(info);
        tam++;
        retorno += *valor;
        // getInfo devuelve copia - liberar
        free(valor);
        EleStack_destroy(info);
    }
    
    while(stack_isEmpty(paux) == FALSE) {
        info = stack_pop(paux);
        // Asumimos que tras k extracciones se realizaran
        // k inserciones sin problemas
        stack_push(st, info);
        EleStack_destroy(info);
    }
    stack_destroy(paux);
    if(tam == 0) return 0;
    retorno = retorno / tam;
    
    return retorno;
}

