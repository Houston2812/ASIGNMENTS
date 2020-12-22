#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "maxsum_tree.h"

bool readline(char* buf, int num, FILE *stream)
{   
    bool flag = false;
    for (int i = 0; i < num; ++i)
    {
        char *temp = (char*)malloc(sizeof(char)*1);
        size_t result = fread(temp, 1, 1, stream);
        if (result == 1)
        {
            if (!flag)
            {
                strcpy(buf, temp);
                flag = true;
            }
            else
            {
                if (strchr(temp, '\n') != NULL)    
                {
                    free(temp);
                    temp = NULL;
                    return true;
                }
                strcat(buf, temp);
            }
        }
        else if (feof(stream))
        {
            free(temp);
            temp = NULL;
            return true;
        }
    }
    if (strlen(buf) == num)
    {
        return true;
    }
    else{
        return false;
    }   
}

int chr_to_int(char* value)
{
    int int_val = 0;
    for (int i = 0; i < strlen(value); ++i)
    {
        int_val = int_val * 10 + (value[i] - '0');
    }
    return int_val;
}

int get_ints(char* buf, int* values)
{
    int len = 0;
    char *token;
    token = strtok(buf, " ");
    while (token != NULL)
    {
        // printf(" %s\n", token);
        values[len] = chr_to_int(token);
        len++;
        token = strtok(NULL, " ");
    }
    free(token);
    token = NULL;
    return len;
}

int main(int argc, char *argv){

    if (argc <= 1)
    {
        printf("Not enough parameters are provided.\n");
        return 0;
    }
    
    bool flag = false;
    FILE* pfile = fopen("file.txt", "rb");
    struct Node* root;
    char *buffer = (char*) malloc(sizeof(char)*64);
    int *values = (int*) malloc(sizeof(int)*64);
    int len_val = 0;

    if (pfile == NULL) 
    {
            fputs("File error", stderr);
            exit(1);        
    } 
    
    while (!feof(pfile))
    {
        bool result = readline(buffer, 64, pfile);
        if (result)
        {

            int *temp = (int*) malloc(sizeof(int)* 64);
            int len = get_ints(buffer, temp);
            for (int i = 0; i < len; ++i)
            {
                values[len_val] = temp[i];
                len_val++;
            }
            free(temp);
            temp = NULL;
        }
    }
    
    root = insert_values(values, root, 0, len_val);
    int maximum_sum = get_max_sum(root);
    // printf("Maximum sum on the tree is equal to %d\n", maximum_sum);
    printf("%d\n", maximum_sum);
    
    free(values);
    values = NULL;
    free(root);
    root = NULL;
    free(buffer);
    buffer = NULL;

    return 0;
}
