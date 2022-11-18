#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "Tree.h"
#include "semantic.h"

/* -------- TOKEN --------- */

token* criaToken(char *valor, int linha, int coluna){
    token *novoToken = (token*)malloc(sizeof(token));
    if(valor != NULL){
        novoToken->valor = (char*)strdup(valor);
    }
    else{
        novoToken->valor = NULL;
    }
    novoToken->linha = linha;
    novoToken->coluna = coluna;
    return novoToken;
}

void libertaToken(token *t){
    if(t->valor != NULL){
        free(t->valor);
        t->valor = NULL;
    }
    free(t);
    t = NULL;
}

/* ++++++++++ AS TREE ++++++++++ */

node* criaNode(char* Type, char *value, int line, int column){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->Type = (char*)strdup(Type);
    if(value != NULL){
        newNode->value = (char*)strdup(value);
    }
    else{
        newNode->value = NULL;
    }

    newNode->line = line;
    newNode->column = column;
    newNode->child = NULL;
    newNode->brother = NULL;

    return newNode;
}

void addChild(node *node1, node *node2){
    if(node1==NULL || node2==NULL){
        return;
    }

    node1->child = node2;
}

void addBrother(node *Node, node *newNodeBrother){
    if(Node==NULL || newNodeBrother==NULL){
        return;
    }

    node *nodeAux = Node;
    while(nodeAux->brother != NULL){
        nodeAux = nodeAux->brother;
    }
    
    nodeAux->brother = newNodeBrother;
}

int countBlock(node *Node) {
    int count = 0;
    if(Node == NULL){
        return count;
    }

    if(Node->brother != NULL){
        count = 1;
    }

    while(Node->brother != NULL){        
        if (strcmp((Node->brother)->Type, "NULL")!=0){
            count++;
        }
        Node = Node->brother;
    }

    return count;
}

void joinType(node *nodeType, node *nodeX){
    node *newNode = NULL;
    node *nodeAux = nodeX;

    while(nodeAux != NULL){
        newNode = criaNode(nodeType->Type, NULL, 0, 0);
        newNode->brother = nodeAux->child;
        nodeAux->child = newNode;
        nodeAux = nodeAux->brother;
    }
}

void astreePrint(node *Node, int numPontos){

    if(Node == NULL){
        return;
    }

    if(strcmp(Node->Type, "NULL") == 0){
        astreePrint(Node->brother, numPontos);
        return;
    }

    int i;
    if(strcmp(Node->Type, "NULL") != 0){
        for(i=0;i<numPontos;i++){
            printf("..");
        }

        if(Node->value != NULL){
            printf("%s(%s)\n",Node->Type, Node->value);
        }
        else{
            printf("%s\n",Node->Type);
        }
    }
    
    astreePrint(Node->child, numPontos+1);
    astreePrint(Node->brother, numPontos);
}

void astreeClean(node* Node){
    if(Node == NULL){
        return;
    }

    if(Node->value != NULL){
        free(Node->value);
        Node->value = NULL;
    }

    if(Node->Type != NULL){
        free(Node->Type);
        Node->Type = NULL;
    }

    astreeClean(Node->child);
    Node->child = NULL;
    astreeClean(Node->brother);
    Node->brother = NULL;

    free(Node);
    Node = NULL;
}

