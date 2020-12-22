#include<stdio.h>
#include<stdlib.h>

#include "maxsum_tree.h"    

struct Node* newNode(int value) 
{ 
    struct Node* node = (struct Node*) malloc (sizeof(struct Node)); 
    node->value = value; 
    node->left = node->right = NULL; 
    return (node); 
} 
  
struct Node* insert_values(int arr[], struct Node* root, int i, int n) 
{ 
    if (i < n) 
    { 
        struct Node* temp = newNode(arr[i]); 
        root = temp; 
        root->left = insert_values(arr, 
                   root->left, 2 * i + 1, n); 
        root->right = insert_values(arr, 
                  root->right, 2 * i + 2, n); 
    } 
    return root; 
} 
  
int max(int a, int b)
{
    return a > b ? a : b;
}
int get_max_sum(struct Node* iter)
{
  if (iter == NULL)
    return 0;
  int left = get_max_sum(iter->left);
  int right = get_max_sum(iter->right);
  return iter->value + max(left, right);
}