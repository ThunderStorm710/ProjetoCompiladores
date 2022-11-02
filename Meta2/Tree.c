//INCLUDES
#include "Tree.h"

//Functions
no * novoNo(char * nome){
    no * aux = (no *)malloc(sizeof(no));
    aux->nome = nome;
    aux->filho = aux->irmao = NULL;
    return aux;
}

void adicionarIrmao(no* no1, no* no2){
    no* aux = no1;
    while(aux->irmao!= NULL){
        aux=aux->irmao;
    }
    aux->irmao=no2;
}

void imprimirArvore(no *no, int prof){
    int tam = prof * 2;
    char pontos[tam];
    for (int i = 0; i<tam; i++){
        pontos[i]='.';
    }
    pontos[tam-1]='\0';

    printf("%s%s\n",pontos,no->nome);

    if (no->filho != NULL){
       imprimirArvore(no->filho, prof+1);     
    }    
    if (no->irmao != NULL){
          imprimirArvore(no->irmao, prof);
    }
    free(no);
}

void freeArvore(no *no){
    if (no->filho){
        freeArvore(no->filho);
    }    
    if (no->irmao){
        freeArvore(no->irmao);
    }  
    free(no);
}
