#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// #define DEBUG

struct settings
{
    char *password;
    int pass_length;
    int tries;
};

struct settings* parser(char* buffer)
{
    struct settings* set = (struct settings*)malloc(sizeof(struct settings));
    char* password = (char*)malloc(sizeof(char)*255);
    char *data = (char*) malloc(sizeof(char)*255);

    int buffer_index = 0;
    int index = 1;
    int data_i = 0;
    

    while(index <= 3)
    {   

        while (buffer[buffer_index] != ' ' && buffer[buffer_index] != '\0')
        {
            data[data_i] = buffer[buffer_index];
            data_i+=1;
            buffer_index+=1;
        }
        buffer_index+=1;
        data[data_i] = '\0';

        switch (index)
        {
        case 1:
            for (int i = 0; i < data_i; ++i)
                password[i] = data[i];   
            password[data_i] = '\0';
            index++;
            break;
        case 2:
            set->pass_length = atoi(data);
            index++;
            break;
        case 3:
            set->tries = atoi(data);
            index++;
            break;
        }

        data_i = 0;
        data[data_i] = '\0';
    }

    set->password = (char*)malloc(sizeof(char)*set->pass_length);
    for (int i = 0; i < set->pass_length; ++i)
        set->password[i] = password[i];
    set->password[set->pass_length] = '\0';
    
    free(data);
    data = NULL;
    free(password);
    password = NULL;
    return (set);
}

int get_length(char * data)
{
    int len = 0;
    while (data[len]!='\0')
    {
        len+=1;
    }
    #ifdef DEBUG
        printf("Length of data: %d\n", len);
    #endif
    return len;
    
}

bool compare(char* input, struct settings* set)
{
    for (int i = 0; i < set->pass_length; ++i)
    {
        if (input[i] != set->password[i])
            return false;
    }
    return true;
}

void get_difference(char * difference, char * input, struct settings *set)
{
    bool flag = false;
    char* copy = (char*)malloc(sizeof(char)*set->pass_length);
  
    for (int i = 0; i < set->pass_length; ++i)
        copy[i] = set->password[i];
    copy[set->pass_length] = '\0';

    for (int i = 0; i < set->pass_length; ++i)
    {
        if (input[i] == copy[i])
        {
            copy[i] = '+';
            difference[i] = '+';
        }
        else 
        {
            for(int j = 0; j < set->pass_length; ++j)
            {
                if (input[i] == copy[j] )
                {
                    difference[i] = '!';
                    flag = true;
                    break;
                }

            }
            if (!flag)
            {
                difference[i] = '.';
            }
            flag = false;
        }
    }
    difference[set->pass_length] = '\0';
    free(copy);
    copy = NULL;
}

bool is_quit(char* data)
{
    char quit[] = "!quit";
    for (int i = 0; i < 5; ++i)
    {
        if (data[i] != quit[i])
            return false;
    }  
    return true;
}

int main(int argc, char *argv[])
{
    struct settings* set;
    if (argc <= 1)
    {
        printf("Error! Settings file is not provided.\n");

    }
    else 
    {
        FILE *setting_file = fopen(argv[1], "r");
        if (setting_file == NULL)
            printf("Error! File does not exist\n");
        else
        {
            char *buffer = (char*)malloc(sizeof(char) * 255);
            if (fgets(buffer, 255, setting_file) != NULL)
            {
                #ifdef DEBUG
                    printf("Settings file: %s\n", buffer);
                #endif
                fclose(setting_file);

            }   
            else
            {
                fclose(setting_file);
                return 0;
            }
            set = parser(buffer);
            #ifdef DEBUG
                printf("Password: %s\nPassword length: %d\nTries: %d\n", set->password, set->pass_length, set->tries); 
            #endif
            free(buffer);
            buffer = NULL;
        }
        // free(setting_file);
        // setting_file = NULL;
        printf("Welcome to Fallout 3 hacking minigame!\n");
        printf("The passphrase contains %d letters.\n\n", set->pass_length);

        while (true)
        {
            char* input = (char*)malloc(sizeof(char) * set->pass_length);

            printf("you have %d tries left: ", set->tries);
            set->tries-=1;

            scanf("%s", input);
            if (is_quit(input))
            {
                free(input);
                input = NULL;
                break;
            }
            int input_length = get_length(input);
            if (input_length != set->pass_length)
            {
                printf("Wrong number of characters, try again.\n");
                continue;
            }
            bool is_same = compare(input, set);
            if (is_same == true)
                printf("correct, here's how you did:\n");
            else
                printf("incorrect, here's how you did:\n");
            
            char* difference = (char*)malloc(sizeof(char)*set->pass_length);
            get_difference(difference, input, set); 
            printf("%s\n%s\n", input, difference);
            
            free(difference);
            difference = NULL;
            free(input);
            input = NULL;

            if (is_same)
            {
                printf("you win.\n");
                break;
            }
            else {
                if (set->tries == 0)
                {
                    printf("game ower.\n");
                    break;
                }
                printf("try again.\n");
            }
        }
        free(set);
        set = NULL;
    }
    return 0;
}