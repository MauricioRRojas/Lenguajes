#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct Node {
    char *ruleIdentifier;
    char *productions;
    struct Node *next;
    struct Node *prev; // Puntero al nodo anterior
} Node;

// Funtion to create a new node
Node* createNode(const char *ruleIdentifier, const char *production) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ruleIdentifier = strdup(ruleIdentifier); // store rule identifier
    newNode->productions = strdup(production);        // store production
    newNode->next = NULL;
    newNode->prev = NULL; // Inicializa el puntero anterior a NULL
    return newNode;
}

// Funtion to find a node by rule identifier
Node* findNode(Node *head, const char *ruleIdentifier) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->ruleIdentifier, ruleIdentifier) == 0) {
            return current; // Return the node if found
        }
        current = current->next;
    }
    return NULL; // Return NULL if not found
}

// Function to append a production to an existing node
void appendProduction(Node *node, const char *production) {
    size_t newSize = strlen(node->productions) + strlen(production) + 4;
    node->productions = (char *)realloc(node->productions, newSize);

    if (strlen(node->productions) > 0) {
        strcat(node->productions, " | ");
    }
    strcat(node->productions, production);
}

// Function to append a new node or update an existing one
void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production) {
    Node *existingNode = findNode(*head, ruleIdentifier);
    if (existingNode != NULL) {
        appendProduction(existingNode, production); // If found, append the production 
    } else {
        Node *newNode = createNode(ruleIdentifier, production); // Create a new node
        if (*head == NULL) {
            *head = newNode; // If the list is empty, set the head
        } else {
            Node *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode; // Add the new node to the end of the list
            newNode->prev = temp; // Set the previous pointer of the new node
        }
    }
}

// Function to free the linked list
void freeLinkedList(Node *head) {
    Node *current = head;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current->ruleIdentifier); // Free the rule identifier string
        free(current->productions);    // Free the production string
        free(current);                 // Free the node
        current = nextNode;            // Move to the next node
    }
}
char* leeArch(FILE *file) 
{
    fseek(file, 0, SEEK_END);
    long tam = ftell(file);
    rewind(file); 

    char *contenido = (char *)malloc(tam + 1);
    if (contenido == NULL) {
        fclose(file);
        return NULL; 
    }

    // Lee el contenido del archivo
    fread(contenido, 1, tam, file);
    contenido[tam] = '\0'; 
    fseek(file,0,SEEK_SET);

    return contenido; 
}
// Function to split a line into rule identifier and production
void splitLine(const char *line, char *ruleIdentifier, char *production) {
    const char *delimiter = strstr(line, "->");
    if (delimiter != NULL) {
        strncpy(ruleIdentifier, line, delimiter - line);
        ruleIdentifier[delimiter - line] = '\0'; // NULL-terminate the identifier
        strcpy(production, delimiter + 2); // Skip the "->"
    }
}

// Function to create a linked list from the file
Node* createLinkedList(FILE *file) {
    Node *head = NULL; // Head of the linked list
    char line[MAX_LINE_LENGTH];
    char ruleIdentifier[MAX_LINE_LENGTH];
    char production[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")-1] = '\0'; // Remove the newline character if present
        splitLine(line, ruleIdentifier, production);
        appendOrUpdateNode(&head, ruleIdentifier, production);
    }
    return head;
}

// Function to print the linked list
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s -> %s\n", current->ruleIdentifier, current->productions);
        current = current->next;
    }
}

// Function to eliminate recursion in productions
Node* elim_recur_desc(Node **head) {
    Node* aux = *head;
    char auxA[MAX_LINE_LENGTH], auxD[MAX_LINE_LENGTH];

    while (aux != NULL) {
        char *pos = strstr(aux->productions, aux->ruleIdentifier);
        if (pos != NULL) {
            // Parte antes de la regla
            strncpy(auxA, aux->productions, pos - aux->productions);
            auxA[pos - aux->productions] = '\0'; // NULL-terminate

            // Parte después de la regla
            strcpy(auxD, pos + strlen(aux->ruleIdentifier));

            // Formar la nueva producción
            sprintf(aux->productions, "{%s}%s", auxA, auxD);
        }
        aux = aux->next; // Moverse al siguiente nodo
    }
    return *head;
}

int main() {
    FILE *file = fopen("gramatica3.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char* arch=leeArch(file);
    printf("Reglas:\n");
    printf("%s",arch);
    printf("\n");

    Node *head = createLinkedList(file);
    fclose(file);

    printf("Paso 1:\n");
    printList(head);
    printf("-------\n");

    printf("Paso 2:\n");
    elim_recur_desc(&head);
    printList(head);
    printf("-------\n");

    freeLinkedList(head);
    return 0;
}