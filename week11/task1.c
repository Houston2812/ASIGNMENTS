#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool readline(char* buf, int num, FILE **stream)
{   
    bool flag = false;
    for (int i = 0; i < num; ++i)
    {
        char *temp = (char*)malloc(sizeof(char)*1);
        size_t result = fread(temp, 1, 1, *stream);
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
                    return true;
                }
                strcat(buf, temp);

            }
            
        }
        else if (feof(*stream))
        {
            if(i != 0)
                return true;
            else
                return false;
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
int main(){
    FILE* pfile = fopen("file.txt", "rb");
    if (pfile == NULL) 
    {
        fputs("File error", stderr);
        exit(1);        
    } 

    char *buffer = (char*) malloc(sizeof(char)*64);
    if (buffer == NULL) 
    {
        fputs("Memory error", stderr);
        exit(2);
    } 

    bool my_result;

    while (true)
    {
        my_result = readline(buffer, 64, &pfile);
        if (my_result)
        {
            printf("another line: %s\n", buffer);
        }
        else if (feof(pfile))
        {
            break;
        }
        else
        {
            fputs("Reading error", stderr);
            exit(3);
        }
    }
    
    
    
    fclose(pfile);
    free(buffer);
    return 0;
}