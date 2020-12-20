#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

#define STACK_CAPACITY 2 

struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 

struct Stack* createStack() 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = STACK_CAPACITY; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 

// deallocates the dynamic memory to prevent memory leak
void deallocStack(struct Stack* stack) 
{ 
    free(stack->array);
    free(stack);
    printf("deallocated\n"); 
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
    int *new_arr = (int*)malloc(stack->capacity * sizeof(int));
    memcpy(new_arr, stack->array, stack->capacity * sizeof(int));
    free(stack->array);
    stack->array = new_arr;
    // stack->array = (int*)realloc(stack->array,stack->capacity * sizeof(int));
    printf("stack reallocated, new length: %d\n",stack->capacity);
} 

void push(struct Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        resize(stack, false);
    stack->array[++stack->top] = item; 
    printf("%d pushed to stack\n", item); 
} 
  
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    if (stack->top +1  == stack->capacity/4){
        resize(stack, true);
    }

    return stack->array[stack->top--]; 
} 
  
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 
  
int main() 
{ 
    struct Stack* stack = createStack(); 
  
    push(stack, 10); 
    push(stack, 20); 
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);
    push(stack, 60);
    push(stack, 70);
    push(stack, 80);
    push(stack, 90);
    push(stack, 100);

    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 
    printf("%d popped from stack\n", pop(stack)); 

    deallocStack(stack);
    return 0; 
} 