#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
const char *expression = "(20 + 40)*2";
char infix[50][50];

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

double tonum(char *str){
    int sign = 1; int i = 0;
    double num = 0.0;
    if(str[0] == '-'){
        sign = -1;
        i = 1;
    }
    int j = 0;
    for(; j < strlen(str); j++){
        if(str[j] == '.') break;
    }
    for(int k = j -1; k >= i; k--){
        num += (str[k] - '0') * pow(10, j - k - 1);
    }
    for(int k = j + 1; k < strlen(str); k++){
        num += (str[k] - '0') * pow(10, j - k);
    }
    return num * sign;
}

int main()
{
    // Tokenize expression
    int i = 0, j = 0;
    int len = strlen(expression);
    for (int k = 0; k < len; k++)
    {
        if (expression[k] == ' ')
            continue;
        if (!isnum(expression[k]) && !isopepar(expression[k]))
        {
            printf("Invalid expression!\n");
            return 1;
        }
        if (!isdigit(expression[k]))
        {
            infix[i][j] = expression[k];
            infix[i][j + 1] = '\0';
            i++;
            j = 0;
        }
        else
        {
            if (isdigit(expression[k - 1]))
            {
                i--;
                j++;
                infix[i][j] = expression[k];
                infix[i][j + 1] = '\0';
                i++;
                j = 0;
            }
            else
            {
                infix[i][j] = expression[k];
                infix[i][j + 1] = '\0';
                i++;
                j = 0;
            }
        }
    }

    // for(int k = 0; k < i; k++){
    //     puts(infix[k]);
    // }
    /////////////////////////////////

    // infix to postfix conversion

    char postfix[50][50];
    char stack[50][50];
    int l = 0;
    int m = 0;
    for (int k = 0; k < 7; k++)
    {
        if (isdigit(infix[k]))
        {
            strcpy(postfix[l], infix[k]);
            l++;
        }
        else
        {
            switch (*infix[k])
            {
            case '(':
                strcpy(stack[m], infix[k]);
                m++;
                break;
            case ')':
                while (*stack[m - 1] != '(')
                {
                    strcpy(postfix[l], stack[m - 1]);
                    l++;
                    m--;
                }
                if (*stack[m] == '(')
                {
                    l++;
                    m--;
                }
                break;
            case '+':
            case '-': // problems lie here
                while (m > 0 && *stack[m - 1] != '(')
                {
                    strcpy(postfix[l], stack[m]);
                    l++;
                    m--;
                }
                if()
                break;
            case '*':
            case '/': // problems lie here
                while (m > 0 && *stack[m - 1] != '(' && *stack[m - 1] != '+' && *stack[m - 1] != '-')
                {
                    strcpy(postfix[l], stack[m]);
                    l++;
                    m--;
                }
                break;
            }
        }
    }
    while (m > -1)
    {
        strcpy(postfix[l], stack[m]);
        l++;
        m--;
    }

    // Postfix evaluation

    double num_stack[50];
    int n = 0;
    for (int o = 0; o < 5; o++)
    {
        if (isdigit(*postfix[o]))
        {
            num_stack[n] = tonum(postfix[o]);
            n++;
        }
        else
        {
            double a = num_stack[n - 1];
            n--;
            double b = num_stack[n - 1];
            n--;
            switch (*postfix[o])
            {
            case '*':
                num_stack[n] = b * a;
                break;
            case '/':
                num_stack[n] = b / a;
                break;
            case '+':
                num_stack[n] = b + a;
                break;
            case '-':
                num_stack[n] = b - a;
                break;
            case '^':
                num_stack[n] = pow(b, a);
            }
            n++;
        }
    }
    printf("%d\n", num_stack[0]);
}