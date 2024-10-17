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
Node *createLinkedlist(FILE *file)
{
    Node *head=NULL;
    char line[MAX_LINE_LENGTH];
    char ruleIdentifier[MAX_LINE_LENGTH];
    char production[MAX_LINE_LENGTH];
    //Leer el archivo linea por linea y guardar en un nuevo nodo
    while(fgets(line, sizeof(line),file))
    {
        //remove the new line character if present;
        line(strcspn(line,"w",)='\0');
        //encontrar la posicion de "->" en la linea
        const char *deletter = strstr(line,"->");
        if(deletter != NULL)
        {
            //copear la parte después del simbolo "->"
            strcpy(ruleIdentifier,line,deletter - line);
            ruleIdentifier[delletter-line]='\0';
            strcpy(production,deletter+2);
            //Append the split line to the linked list
            appendNode(&head,ruleIdentifier,production);
        }
        appendNode(&head,"",line);
    }
    return (head);
}
void printList(Node *head)
{

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