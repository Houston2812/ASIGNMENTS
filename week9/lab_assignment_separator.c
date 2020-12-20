#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void parseNums(char *source, char *integers, char *nonInteger);

bool  is_digit(char letter)
{
    if (letter - '0' >= 0 && letter - '0' <= 9 )
        return true;
    else
        return false;
}
int main()
{
  char source[] = "abc123def99!";
  char integers[256];
  char nonIntegers[256];
  parseNums(source, integers, nonIntegers);
  // output shud be: abcdef!, 12399

}

void parseNums(char *source, char *integers, char *nonIntegers)
{   
    int integer_count = 0;
    int nonInteger_count = 0;
    for (int i = 0; i < strlen(source); ++i)
    {
        if (is_digit(source[i]))
        {
            integers[integer_count++]= source[i];
        }
        else{
            nonIntegers[nonInteger_count++] = source[i];
        }
    }

    printf("%s, %s\n", nonIntegers, integers);
}