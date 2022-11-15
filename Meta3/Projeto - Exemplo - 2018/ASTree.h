#ifndef ASTree_h
#define ASTree_h

//INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//STRUCT
typedef struct node{
    char* message;
    struct node *brother;
    struct node *child;
}Node;

//Function Headers
Node * newNode(char * message);
void addBrother(Node* node1, Node* node2);
void printASTree(Node *node, int depth);
void freeASTree(Node *node);

#endif /*ASTree_h*/
