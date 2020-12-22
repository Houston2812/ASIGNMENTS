#ifndef MAXTREE
#define MAXTREE

struct Node{
  int value;
  struct Node* left;
  struct Node* right;
};

struct Node* newNode(int value);
struct Node* insert_values(int arr[], struct Node* root, 
                       int i, int n);
int get_max_sum(struct Node* iter);

#endif