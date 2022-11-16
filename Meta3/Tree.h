#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

/* AS TREE */

/*TOKEN struct atributes*/
typedef struct token{
    char *valor;
    int linha, coluna;
} token;

/*NODE struct atributes*/
typedef struct node{
    struct node *brother;
    struct node *child;
    char *Type;
    char *value;
    int line, column;
} node;

/*Declared functions*/
void astreePrint(node* Node, int numPontos);
void astreeClean(node* Node);
token* criaToken(char *valor, int linha, int coluna);
void libertaToken(token *t);
node* criaNode(char* Type, char *value, int line, int column);
int countBlock(node *Node);
void joinType(node *nodeType, node *nodeX);
void addBrother(node *Node, node *newNodeBrother);
void addChild(node *node1, node *node2);
