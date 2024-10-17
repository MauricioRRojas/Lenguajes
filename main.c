#include "main.h"

//Funcion para crear nodo
void createNode(const char *ruleIdentifier, const char *production)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ruleIdentifier=strdup(ruleIdentifier); //Store rule identifier
    newNode->production=strup(production);
    newNode->next;
    return newNode;
}
//Funcion para agregar un nodo
void appendNode(Node **head, const char *ruleIdentifier, const char *_production)
{
    Node *newNode = createNode(ruleIdentifier,production);

}
//Funcion para crear la lista desde el archivo
Node *createLinkedlist()
{
    Node *head=NULL;
    char line[MAX_LINE_LENGTH];
    
}
int main()
{
    /*FILE "gramar" = fopen("gramatica.txt","r");
    if(gramar == NULL)
    {
        perror("Error opening the file\n");
        return EXIT_FAILURE;
    }
    Node *head = createLinkedList(gramar);
    fclose(gramar);
    printflist(gramar);
    freeLinkedList(head);
    */
    return EXIT_SUCCESS;
}