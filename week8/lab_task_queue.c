#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char name[256];
    struct Node *next;
};

void addToTail(struct Node** tail, char *name){
    (*tail) -> next = (struct Node*) malloc(sizeof(struct Node));
    (*tail) = (*tail) -> next;
    strcpy((*tail)->name, name);
    (*tail) -> next = NULL;
}

void printList(struct Node* iter){
    if (iter == NULL)
    {
        printf("Queue is empty.");
    }
    while( iter != NULL){
        printf("%s, ", iter->name);
        iter = iter->next;
    }
    printf("\n");
}

void lucky_customer(struct Node **head, struct Node** tail, char *name)
{   
   struct Node* current = *head;
   struct Node* previous = NULL;

   if (current!= NULL && strcmp(current->name, name) == 0)
   {
       *head = current->next;
        addToTail(tail, current->name);

       free(current);
       current = NULL;
       return;
   }

   while (current != NULL)
   {
       if (strcmp(current->name, name) == 0)
       {   
           addToTail(tail, current->name);
           previous->next = current->next;

           free(current);
           current = NULL;
           
           return;
       } 
       previous = current;
       current = current -> next;
   }
   printf("Error! Such user does not exist in the queue.\n");
   return;
}


int main(){
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    strcpy(head->name, "Huseyn");
    
    struct Node *tail = head;
    
    addToTail(&tail, "Naruto");
    addToTail(&tail, "Bakugo");
    addToTail(&tail, "Edward");
    addToTail(&tail, "Alphonse");

    printList(head);

    char input[256];
    bool quit = 0;
    while(!quit) 
    {
        scanf("%s", input);
        if (strcmp(input, "q") == 0) 
        {
            quit = 1;
            break;
        }
        else if (strcmp(input, "admit") == 0)
        {
            if (head != NULL){
                printf("Admitted %s\n", head->name);
                head = head-> next;            
            }
        }
        else 
        {   
           
           lucky_customer(&head, &tail, input);
        }
        printList(head);
    }
    free(head);
    head=NULL;
    free(tail);
    tail=NULL;
    return 0;
}