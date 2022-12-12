
#include "semantic.h"

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

node *criaNode(char *tipoNo, char *valor, int linha, int coluna) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->tipoNo = (char *) strdup(tipoNo);
    if (valor != NULL) {
        newNode->valor = (char *) strdup(valor);
    } else {
        newNode->valor = NULL;
    }
    newNode->anotacao = NULL;
    newNode->params = NULL;
    newNode->numeroParametros = -1;
    newNode->aAnotar = 1;
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
        if (strcmp((Node->brother)->tipoNo, "NULL") != 0) {
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
        newNode = criaNode(nodeType->tipoNo, NULL, 0, 0);
        newNode->brother = nodeAux->child;
        nodeAux->child = newNode;
        nodeAux = nodeAux->brother;
    }
}

void imprimirArvore(node *Node, int numPontos) {

    if (Node == NULL) {
        return;
    }

    if (strcmp(Node->tipoNo, "NULL") == 0) {
        imprimirArvore(Node->brother, numPontos);
        return;
    }

    int i;
    if (strcmp(Node->tipoNo, "NULL") != 0) {
        for (i = 0; i < numPontos; i++) {
            printf("..");
        }

        if (Node->valor != NULL) {
            printf("%s(%s)\n", Node->tipoNo, Node->valor);
        } else {
            printf("%s\n", Node->tipoNo);
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

    if (Node->tipoNo != NULL) {
        free(Node->tipoNo);
        Node->tipoNo = NULL;
    }

    limparArvore(Node->child);
    Node->child = NULL;
    limparArvore(Node->brother);
    Node->brother = NULL;

    free(Node);
    Node = NULL;
}