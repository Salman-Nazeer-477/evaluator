
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char infix[50][50] = {"+", "+", "+"};

int isoperator(char c);

int main()
{
    char postfix[50][50];
    char stack[50][50];
    int i_postfix = 0;
    int l_infix = 3;
    int i_stack = 0;
    for (int i_infix = 0; i_infix < l_infix; i_infix++)
    {
        if (isdigit(*infix[i_infix]))
        {
            strcpy(postfix[i_postfix], infix[i_infix]);
            i_postfix++;
        }
        else
        {
            switch (*infix[i_infix])
            {
            case '(':
                strcpy(stack[i_stack], infix[i_infix]);
                i_stack++;
                break;
            case ')':
                while (*stack[i_stack - 1] != '(')
                {
                    strcpy(postfix[i_postfix], stack[i_stack - 1]);
                    i_postfix++;
                    i_stack--;
                }
                if (*stack[i_stack - 1] == '(')
                {
                    i_stack--;
                }
                break;
            case '^':
            	strcpy(stack[i_stack], infix[i_infix]);
            	i_stack++;
            	break;
            case '*':
            case '/':
                if(*stack[i_stack - 1] == '+' || *stack[i_stack - 1] == '-'){
                    strcpy(stack[i_stack], infix[i_infix]);
                }
                else if(*stack[i_stack - 1] == '^' || *stack[i_stack - 1] == '*' || *stack[i_stack - 1] == '/'){
                    strcpy(postfix[i_postfix], stack[i_stack - 1]);
                    i_postfix++;
                    i_stack--;
                    strcpy(stack[i_stack], infix[i_infix]);
                    i_stack++;
                }
                else if(i_stack == 0){
                    strcpy(stack[i_stack], infix[i_infix]);
                    i_stack++;
                }
                break;
            case '+':
            case '-':
                if(isoperator(*stack[i_stack - 1])){
                    strcpy(postfix[i_postfix], stack[i_stack - 1]);
                    i_postfix++; 
                    i_stack--;
                    strcpy(stack[i_stack], infix[i_infix]);
                    i_stack++;
                }
                else if(i_stack == 0){
                    strcpy(stack[i_stack], infix[i_infix]);
                    i_stack++;
                }
            }
        }
    for(int k = 0; k < i_postfix; k++) {printf("%d: %s\n", i_infix, postfix[k]);}
    }
    while (i_stack > -1)
    {
        strcpy(postfix[i_postfix], stack[i_stack]);
        i_stack--;
        i_postfix++;
    }
    for(int k = 0; k < i_postfix; k++) {printf("%s\n", postfix[k]);}
}

int isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
