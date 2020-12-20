#include <stdio.h>
#include <stdlib.h>

struct Node{
  int value;
  struct Node* left;
  struct Node* right;
};

struct Node* new_node(int value) 
{ 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value; 
    node->left = NULL;
    node->right = NULL; 
    return (node); 
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


int main(){
  struct Node* root = new_node(1);
  root->left = new_node(1);
  root->left->left = new_node(100);
  root->left->right = new_node(4);
  root->left->left->left = new_node(7);
  root->left->left->right = new_node(8);
  root->right = new_node(2);
  root->right->left = new_node(9);
  root->right->right = new_node(1000);
  root->right->left -> left = new_node(7);
  root->right->left-> right = new_node(8);

  int maximum_sum = get_max_sum(root);
  printf("Maximum sum on the tree is equal to %d\n", maximum_sum);

  return 0;
}
