#ifndef Tree_h
#define Tree_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ESTRUTURAS
typedef struct no{
    char* nome;
    struct no *irmao;
    struct no *filho;
}no;

//Function Headers
no * novoNo(char * message);
void adicionarIrmao(no* no1, no* no2);
void imprimirArvore(no *no, int depth);
void freeArvore(no *no);

#endif
