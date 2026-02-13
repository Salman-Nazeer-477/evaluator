/*
indexes for various arrays should have a preceding i_ followed by the array name.
lengths for various arrays should have a preceding l_ followed by the array name.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
const char *expression = "2+3*6";
char infix[50][50];

int isnum(char c);
int isopepar(char c);
int isoperator(char c);

int main()
{
    // Tokenize expression
    int i_infix = 0, i_token = 0;
    int l_expression = strlen(expression);
    for (int i_expression = 0; i_expression < l_expression; i_expression++)
    {
        if (expression[i_expression] == ' ')
            continue;
        if (!isnum(expression[i_expression]) && !isopepar(expression[i_expression]))
        {
            printf("Invalid expression!\n");
            return 1;
        }
        if (!isdigit(expression[i_expression]))
        {
            infix[i_infix][i_token] = expression[i_expression];
            infix[i_infix][i_token + 1] = '\0';
            i_infix++;
            i_token = 0;
        }
        else
        {
            if (isdigit(expression[i_expression - 1]))
            {
                i_infix--;
                i_token++;
                infix[i_infix][i_token] = expression[i_expression];
                infix[i_infix][i_token + 1] = '\0';
                i_infix++;
                i_token = 0;
            }
            else
            {
                infix[i_infix][i_token] = expression[i_expression];
                infix[i_infix][i_token + 1] = '\0';
                i_infix++;
                i_token = 0;
            }
        }
    }
    for(int k = 0; k < i_infix; k++) {printf("%s\n", infix[k]);}
    
}

int isnum(char c)
{
    if (isalnum(c) && !isalpha(c))
        return 1;
    return 0;
}

int isopepar(char c)
{
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
