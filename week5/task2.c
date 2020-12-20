#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

#define STACK_CAPACITY 2 
#define EMPTY ' '
struct Stack { 
    int top; 
    unsigned capacity; 
    char* array; 
}; 

struct Stack* createStack() 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = STACK_CAPACITY; 
    stack->top = -1; 
    stack->array = (char*)malloc(stack->capacity * sizeof(char)); 
    return stack; 
} 

// deallocates the dynamic memory to prevent memory leak
void deallocStack(struct Stack* stack) 
{ 
    free(stack->array);
    free(stack);
    // printf("deallocated\n"); 
} 

int isFull(struct Stack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 
  
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
} 

void resize(struct Stack* stack, bool shrink) 
{
    if (shrink){
        stack->capacity = stack->capacity / 4;
    }
    else {
        stack->capacity *= 2;
    }
    char *new_arr = (char*)malloc(stack->capacity * sizeof(char));
    memcpy(new_arr, stack->array, stack->capacity * sizeof(char));
    free(stack->array);
    stack->array = new_arr;
    // stack->array = (int*)realloc(stack->array,stack->capacity * sizeof(int));
    // printf("stack reallocated, new length: %d\n",stack->capacity);
} 

void push(struct Stack* stack, char item) 
{ 
    if (isFull(stack)) 
        resize(stack, false);
    stack->array[++stack->top] = item; 
    // printf("%c pushed to stack\n", item); 
} 
  
char pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return EMPTY; 
    if (stack->top +1  == stack->capacity/4){
        resize(stack, true);
    }

    return stack->array[stack->top--]; 
} 
  
char peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return EMPTY; 
    return stack->array[stack->top]; 
} 
  
int main(int argc, char** argv) 
{ 
    struct Stack* stack = createStack(); 
    bool flag = false;
    char *string = argv[1];


    for(int i = 0; i < strlen(string); ++i)
    {
        if (string[i] == '{' || string[i] == '[' || string[i] == '(')
            push(stack,string[i]);
        else
        {   
            char br = pop(stack);
            if (br == '{' && string[i] == '}' ){
                continue;
            }
            else if (br == '[' && string[i] == ']')
                continue;
            else if (br == '(' && string[i] == ')')
                continue;
            else
            {
                flag = true;
                break;
            }
        }
    }
    if (stack->top == -1 && flag == false)
    {
        printf("Yes\n");        
    }
    else
    {
        printf("No\n");
    }

    deallocStack(stack);
    return 0; 
} 