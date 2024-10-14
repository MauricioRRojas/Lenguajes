#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct Node{
    struct Node *next;
    char *line;
}Node;

// Node* createNode(const char *line);
// void appendNode(Node **cabecera, const char *line);
// void freeLinkedList(Node *head);
// Node* createLinkedList(FILE *file);
// void printList(Node *head);
 