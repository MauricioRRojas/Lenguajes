#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Node{
    struct Node *next;
    char *ruleIdentifier;
    char *production;
}Node;

// Node* createNode(const char *ruleIdentifier, const char *production);
// void appendNode(Node **cabecera, const char *ruleIdentifier);
// void freeLinkedList(Node *head);
// Node* createLinkedList(FILE *file);
// void printList(Node *head);
 