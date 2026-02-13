#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char infix[50][50] = {"(", "1", "+", "2", ")", "*", "5"};
int l_infix = 7;
int isoperator(char c);
int isnumber(char c);
int isprecedencelower(char a, char b);
int isparenthesis(char c);

int main()
{
    char postfix[50][50];
    char stack[50][50];
    int l_postfix = -1;
    int l_stack = -1;
    int i_infix;
    for (i_infix = 0; i_infix < l_infix; i_infix++)
    {
        if (isnumber(*infix[i_infix]))
        {
            l_postfix++;
            strcpy(postfix[l_postfix], infix[i_infix]);
        }
        else if (isparenthesis(*infix[i_infix]))
        {
            if (*infix[i_infix] == '(')
            {
                l_stack++;
                strcpy(stack[l_stack], "(");
            }
            else
            {
                while (l_stack > -1 && *stack[l_stack] != '(')
                {
                    l_postfix++;
                    strcpy(postfix[l_postfix], stack[l_stack]);
                    l_stack--;
                }
                l_stack--;
            }
        }
        else if (isoperator(*infix[i_infix]))
        {
            if (isparenthesis(*stack[l_stack]))
            {
                l_stack++;
                strcpy(stack[l_stack], infix[i_infix]);
            }
            else if (l_stack > -1 && isprecedencelower(*infix[i_infix], *stack[l_stack]))
            {
                l_postfix++;
                strcpy(postfix[l_postfix], stack[l_stack]);
                l_stack--;
            }
            else
            {
                l_stack++;
                strcpy(stack[l_stack], infix[i_infix]);
            }
        }
    }
    while (l_stack > -1)
    {
        l_postfix++;
        strcpy(postfix[l_postfix], stack[l_stack]);
        l_stack--;
    }
    for (int k = 0; k <= l_postfix; k++)
    {
        printf("%s\n", postfix[k]);
    }
}

int isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isnumber(char c)
{
    return c >= '0' && c <= '9';
}

int isprecedencelower(char a, char b)
{
    switch (a)
    {
    case '^':
        return 0;
        break;
    case '*':
    case '/':
        if (b == '^')
            return 1;
        else
            return 0;
        break;
    case '+':
    case '-':
        if (b == '+' || b == '-')
            return 0;
        else
            return 1;
        break;
    }
}

int isparenthesis(char c)
{
    return c == '(' || c == ')';
}