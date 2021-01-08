#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>


struct Node {
 int data;
 bool is_swapped;
 struct Node * next;
};

//append function for your ease of use
void append(struct Node** head_ref, int new_data) 
{ 
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    struct Node *last = *head_ref;  /* used in step 5*/
   
    /* 2. put in the data  */
    new_node->data  = new_data; 
    new_node->is_swapped = false;
    /* 3. This new node is going to be the last node, so make next  
          of it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }   
       
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
   
    /* 6. Change the next of last node */
    last->next = new_node; 
    return;     
}

void printList(struct Node* iter)
{
 while( iter != NULL){
	printf("%d ",iter->data );
	iter = iter->next;
 }
 printf("\n");
}

bool swapEl(struct Node **head_ref, int value)
{
    struct Node *prev1 = NULL, *curr1 = *head_ref;
    while (curr1 != NULL && curr1->data!=value )
    {
        prev1 = curr1;
        curr1 = curr1->next;
    }
    
    if (curr1 == NULL || curr1->is_swapped==true)
    {
        return false;
    }
    if (curr1 -> next == NULL)
    {
        curr1 -> is_swapped = true;
        return true;
    }

    curr1 -> is_swapped = true;
    struct Node *prev2 = NULL, *curr2 = *head_ref;
    prev2 = curr1;
    curr2 = curr1->next;


    if (prev1 != NULL)
        prev1 -> next = curr2;
    else
        *head_ref = curr2;

    if (prev2 != NULL)
        prev2 ->next = curr1;
    else
        *head_ref = curr1;

    struct Node *temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;

    return true;
}

int main()
{
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head = NULL;

    printf("Enter numbers to add to your list: \n");
    char *input = (char *)malloc(sizeof(char)*255);
    while (true)
    {
        scanf("%s", input);
        if (strstr(input, "DONE") != NULL)
            break;
        append(&head, atoi(input));
    }

    printList(head);
    printf("Type two numbers to swap them around:\n");
    
    while (true)
    {
        scanf("%s", input);
        if (strstr(input, "DONE") != NULL) 
            break;
        bool state = swapEl(&head, atoi(input));
        if (state == false)
            printf("No swap candidates found. Try again: \n");
        else
        {
            printf("result:");
            printList(head);
            printf("Type two numbers to swap them around:\n");
        }
        
    }
    
    printList(head);
    free(input);
    input=NULL;
    free(head);
    head = NULL;
    return 0;
}