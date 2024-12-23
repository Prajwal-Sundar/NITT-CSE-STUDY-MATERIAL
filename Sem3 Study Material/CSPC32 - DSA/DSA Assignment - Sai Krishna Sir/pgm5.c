// Program 5

#include <stdio.h>
#include <stdlib.h>

// Calculate length of a string
int length(char * str)
{
    int c = 0; // count variable
    for (int i = 0; str[i] != '\0'; i++, c++); // increment count
    return c;
}

// Supported Left Brackets
int isLeft(char ch)
{
    switch(ch)
    {
        case '(': case '[': case '{':
            return 1; // positive result
        default:
            return 0; // negative result
    }
}

// Supported Right Brackets
int isRight(char ch)
{
    switch(ch)
    {
        case ')': case ']': case '}':
            return 1; // positive result
        default:
            return 0; // negative result
    }
}

// Return matching left bracket
char leftOf(char ch)
{
    switch(ch)
    {
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
        default: return '\0';
    }
}

// Check if a string with brackets is balanced
int check(char * str)
{
    int l = length(str); // length of string
    char * S = (char *) malloc(l * sizeof(char)); // stack
    int T = -1; // top pointer

    for (int i = 0; i < l; i++)
    {
        if (isLeft(str[i]))
            S[++T] = str[i]; // push the bracket into the stack
        else if (isRight(str[i]))
        {
            if (S[T] != leftOf(str[i])) // invalid match
                return 0;
            else
                T--; // pop the matched left bracket
        }
    }

    if (T != -1) // some left brackets are left without a match
        return 0;
    else
        return 1; // perfectly matched
}

void main()
{
    printf("Welcome to C Bracket Balance Validator !\n\n");

    char str [100]; // input string
    printf("Enter an expression with brackets : ");
    scanf("%s", str);

    if (check(str))
        printf("The brackets in your expression are perfectly balanced.");
    else
        printf("The brackets in your expression are not properly balanced.");
    
    printf("\n\nThank you for using C Bracket Balancer. Bye Bye !");
}