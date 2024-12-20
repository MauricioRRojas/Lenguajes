#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LENGTH 100

//Node structure for the linked list
typedef struct Node
{
	char *ruleIdentifier;
	char *productions;
	struct Node *next;
	struct Node *ant;
}Node;

struct Node * createNode(const char *ruleIdentifier, const char *production);
void appendNode(struct Node **head, const char *ruleIdentifier, const char *prouction);
void freelinkedlist(struct Node *head);
struct Node * createLinkedList(FILE *file);
void printList(struct Node *head);

void splitLine(const char *line, char *ruleIdentifier, char *production);

struct Node* findNode(struct Node *head, const char *ruleIdentifier);
void appendProduction(struct Node *node, const char *production);
void appendOrUpdateNode(struct Node **head, const char *ruleIdentifier, const char *production);
Node* elim_recur_desc(Node **head);
Node* elimRecArr2(Node **head);
char* leeArch(FILE file);