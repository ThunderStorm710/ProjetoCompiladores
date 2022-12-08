#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "semantic.h"

/* -------- TOKEN --------- */

token *criaToken(char *valor, int linha, int coluna) {
    token *novoToken = (token *) malloc(sizeof(token));
    if (valor != NULL) {
        novoToken->valor = (char *) strdup(valor);
    } else {
        novoToken->valor = NULL;
    }
    novoToken->linha = linha;
    novoToken->coluna = coluna;
    return novoToken;
}

void libertaToken(token *t) {
    if (t->valor != NULL) {
        free(t->valor);
        t->valor = NULL;
    }
    free(t);
    t = NULL;
}

/* ++++++++++ AS TREE ++++++++++ */

node *criaNode(char *Type, char *valor, int linha, int coluna) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->Type = (char *) strdup(Type);
    if (valor != NULL) {
        newNode->valor = (char *) strdup(valor);
    } else {
        newNode->valor = NULL;
    }
    newNode->anotacao = NULL;
    newNode->params = NULL;
    newNode->numeroParametros = -1;
    newNode->to_anote = 1;
    newNode->linha = linha;
    newNode->coluna = coluna;
    newNode->child = NULL;
    newNode->brother = NULL;

    return newNode;
}

void addChild(node *node1, node *node2) {
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    node1->child = node2;
}

void addBrother(node *Node, node *newNodeBrother) {
    if (Node == NULL || newNodeBrother == NULL) {
        return;
    }

    node *nodeAux = Node;
    while (nodeAux->brother != NULL) {
        nodeAux = nodeAux->brother;
    }

    nodeAux->brother = newNodeBrother;
}

int countBlock(node *Node) {
    int count = 0;
    if (Node == NULL) {
        return count;
    }

    if (Node->brother != NULL) {
        count = 1;
    }

    while (Node->brother != NULL) {
        if (strcmp((Node->brother)->Type, "NULL") != 0) {
            count++;
        }
        Node = Node->brother;
    }

    return count;
}

void joinType(node *nodeType, node *nodeX) {
    node *newNode = NULL;
    node *nodeAux = nodeX;

    while (nodeAux != NULL) {
        newNode = criaNode(nodeType->Type, NULL, 0, 0);
        newNode->brother = nodeAux->child;
        nodeAux->child = newNode;
        nodeAux = nodeAux->brother;
    }
}

void imprimirArvore(node *Node, int numPontos) {

    if (Node == NULL) {
        return;
    }

    if (strcmp(Node->Type, "NULL") == 0) {
        imprimirArvore(Node->brother, numPontos);
        return;
    }

    int i;
    if (strcmp(Node->Type, "NULL") != 0) {
        for (i = 0; i < numPontos; i++) {
            printf("..");
        }

        if (Node->valor != NULL) {
            printf("%s(%s)\n", Node->Type, Node->valor);
        } else {
            printf("%s\n", Node->Type);
        }
    }

    imprimirArvore(Node->child, numPontos + 1);
    imprimirArvore(Node->brother, numPontos);
}

void limparArvore(node *Node) {
    if (Node == NULL) {
        return;
    }

    if (Node->valor != NULL) {
        free(Node->valor);
        Node->valor = NULL;
    }

    if (Node->Type != NULL) {
        free(Node->Type);
        Node->Type = NULL;
    }

    limparArvore(Node->child);
    Node->child = NULL;
    limparArvore(Node->brother);
    Node->brother = NULL;

    free(Node);
    Node = NULL;
}

