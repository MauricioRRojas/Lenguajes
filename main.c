#include "main.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
//Funtion to create a new node
Node* createNode(const  char *ruleIdentifier, const char *production)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ruleIdentifier = strdup(ruleIdentifier); //store rule identifier
    newNode->productions = strdup(production);        //store production
    newNode->next = NULL;
    newNode->ant = NULL;
    return newNode;
}

//Funtion to find a node by rule identifier
Node* findNode(Node *head, const char *ruleIdentifier)
{
    Node *current=head;
    while(current != NULL)
    {
        if(strcmp(current->ruleIdentifier, ruleIdentifier) == 0)
        {
            return current; //Return the node if found
        }
        current = current->next;
    }
    return NULL; //Return NULL if not  foundby
}

//Funcion to append a production to an existing node
void appendProduction(Node *node, const char *production) {
    // Allocate new space to hold the existing productions + new production + separator " | "
    size_t newSize = strlen(node->productions) + strlen(production) + 4;
    node->productions = (char *)realloc(node->productions, newSize);

    // Append the new production with " | " separator
    if (strlen(node->productions) > 0) {
        strcat(node->productions, " | ");
    }
    strcat(node->productions, production);
}


//Funcion to aooend a new node or update an existing one
void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production)
{
    Node *existingNode = findNode(*head,ruleIdentifier);
    if(existingNode != NULL)
    {
        appendProduction(existingNode, production); //If found, append the production 
    }
    else
    {
        Node *newNode = createNode(ruleIdentifier, production); //Create a new node
        if(*head == NULL)
        {
            *head= newNode; //If the list is empty, set the head
        }
        else
        {
            Node *temp= *head;
            while(temp->next != NULL)
            {
                temp= temp->next;
            }
            temp->next= newNode; //Add the new node to the end of the list
        }
    }
}

//Function to free the  linked list
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


//Funtion to split a line into rule identifier and oridyction
void splitLine(const char *line, char *ruleIdentifier, char *production)
{
    //Find the position of "->"in the line
    const char *delimiter= strstr(line, "->");
    if(delimiter != NULL)
    {
        //copy the part before "->" into ruleIdentifire
        strncpy(ruleIdentifier, line, delimiter - line);
        ruleIdentifier[delimiter - line] = '\0'; //NULL-terminate the identifier

        //copy the part after "->" into production
        strcpy(production, delimiter + 2); //Skip the "->"
    }
}

//Function to create a linked list from the file
Node* createLinkedList(FILE *file)
{
    Node *head= NULL; //Head of the linked list
    char line[MAX_LINE_LENGTH];
    char ruleIdentifier[MAX_LINE_LENGTH];
    char production[MAX_LINE_LENGTH];
    printf("Paso 1:\n");
    //Read the file line by line and store each line in a new node or update an existing one
    while(fgets(line, sizeof(line), file))
    {
        //Remove the newline character if present
        line[(strcspn(line, "\n")-1)]= '\0';

        //Split the line into rule ifentifier and production 
        splitLine(line, ruleIdentifier, production);

        //Append or update the node in the linked list
        appendOrUpdateNode(&head, ruleIdentifier, production);
    }

    return head;
}

//Funtion to print the linked list
void printList(Node *head)
{
    Node *current = head;
    while(current != NULL)
    {
        printf("%s -> %s\n", current->ruleIdentifier, current->productions);
        current = current->next;
    }
}
//Funcion para eliminar la recursividad
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


int main()
{
    FILE *file = fopen("gramatica1.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Node *head = createLinkedList(file);
    fclose(file);

    // Output the contents of the linked list
    printList(head);
    printf("-------\n");

    // Eliminar recursividad
    printf("Paso 2:\n");
    elim_recur_desc(&head);
    printList(head);

    // Free the linked list
    freeLinkedList(head);
    return 0;
}
//