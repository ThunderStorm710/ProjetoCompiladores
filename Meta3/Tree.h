#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

/* AST */

typedef struct token{
    char *value;
    int line, coluna;
} token;

typedef struct node{
    struct node *children;
    struct node *brother;
    char *nodeType;
    char *anoted;
    char *value;
    int n_params;
    int to_anote;
    struct _param_list *params;
    int line, coluna;
} node;

token* createToken(char *value, int line, int coluna);
void freeToken(token *aux);
int itsTerminal(char *nodeType);
node* createNode(char* nodeType, char *value, int line, int coluna);
void insertBrother(node *b1, node *b2);
void insertChildren(node *f, node *s);
void insertBrother(node *f, node *b);
void printNode(node *current);
int addBlock(node *n);
void atributeType(node *type, node *varDecl);
void printAST(node* atual, int n);
void clearAST(node* atual);
void removeNULLs(node *ant, node* atual);
