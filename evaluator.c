#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
char infix[50][50];

int isnum(char c);
int isopepar(char c);
int isoperator(char c);
int isnumber(char c);
int isprecedencelower(char a, char b);
int isparenthesis(char c);
double tonum(char *str);
double evaluate(char *str);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        char expression[100] = " ";
        while (1)
        {
            printf(">>");
            scanf("%s", expression);
            if(!strcmp("quit", expression)) return 0;
            const double value = evaluate(expression);
            printf("%.lf\n", value);
        }
    }
    else if (argc > 2)
    {
        printf("Error! Too many arguments!\n");
        return 1;
    }
    const double value = evaluate(argv[1]);
    printf("%.lf\n", value);
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

double tonum(char *str)
{
    int sign = 1;
    int i = 0;
    double num = 0.0;
    if (str[0] == '-')
    {
        sign = -1;
        i = 1;
    }
    int j = 0;
    for (; j < strlen(str); j++)
    {
        if (str[j] == '.')
            break;
    }
    for (int k = j - 1; k >= i; k--)
    {
        num += (str[k] - '0') * pow(10, j - k - 1);
    }
    for (int k = j + 1; k < strlen(str); k++)
    {
        num += (str[k] - '0') * pow(10, j - k);
    }
    return num * sign;
}

double evaluate(char *expression)
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
            printf("Error! Invalid expression!\n");
            return 1;
        }
        if (!isdigit(expression[i_expression]))
        {
            i_token = 0;
            infix[i_infix][i_token] = expression[i_expression];
            infix[i_infix][i_token + 1] = '\0';
            i_infix++;
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
            }
            else
            {
                infix[i_infix][i_token] = expression[i_expression];
                infix[i_infix][i_token + 1] = '\0';
                i_infix++;
            }
        }
    }
    // for (int k = 0; k < i_infix; k++)
    // {
    //     printf("%s\n", infix[k]);
    // }
    // printf("---------------------\n");

    ////////////////////////

    char postfix[50][50];
    char stack[50][50];
    int l_infix = i_infix + 1;
    int i_postfix = -1;
    int i_stack = -1;
    for (i_infix = 0; i_infix < l_infix; i_infix++)
    {
        if (isnumber(*infix[i_infix]))
        {
            i_postfix++;
            strcpy(postfix[i_postfix], infix[i_infix]);
        }
        else if (isparenthesis(*infix[i_infix]))
        {
            if (*infix[i_infix] == '(')
            {
                i_stack++;
                strcpy(stack[i_stack], "(");
            }
            else
            {
                while (i_stack > -1 && *stack[i_stack] != '(')
                {
                    i_postfix++;
                    strcpy(postfix[i_postfix], stack[i_stack]);
                    i_stack--;
                }
                i_stack--;
            }
        }
        else if (isoperator(*infix[i_infix]))
        {
            if (isparenthesis(*stack[i_stack]))
            {
                i_stack++;
                strcpy(stack[i_stack], infix[i_infix]);
            }
            else if (i_stack > -1 && isprecedencelower(*infix[i_infix], *stack[i_stack]))
            {
                i_postfix++;
                strcpy(postfix[i_postfix], stack[i_stack]);
                i_stack--;
            }
            else
            {
                i_stack++;
                strcpy(stack[i_stack], infix[i_infix]);
            }
        }
    }
    while (i_stack > -1)
    {
        i_postfix++;
        strcpy(postfix[i_postfix], stack[i_stack]);
        i_stack--;
    }
    // for (int k = 0; k <= i_postfix; k++)
    // {
    //     printf("%s\n", postfix[k]);
    // }
    // printf("---------------------\n");

    /////////////////////

    double num_stack[50];
    int i_num_stack = -1;
    //----
    int l_postfix = i_postfix + 1;
    //----
    for (int i_postfix = 0; i_postfix < l_postfix; i_postfix++)
    {
        if (isdigit(*postfix[i_postfix]))
        {
            i_num_stack++;
            num_stack[i_num_stack] = tonum(postfix[i_postfix]);
        }
        else
        {
            double a = num_stack[i_num_stack];
            i_num_stack--;
            double b = num_stack[i_num_stack];
            switch (*postfix[i_postfix])
            {
            case '*':
                num_stack[i_num_stack] = b * a;
                break;
            case '/':
                num_stack[i_num_stack] = b / a;
                break;
            case '+':
                num_stack[i_num_stack] = b + a;
                break;
            case '-':
                num_stack[i_num_stack] = b - a;
                break;
            case '^':
                num_stack[i_num_stack] = pow(b, a);
                break;
            }
        }
    }
    return num_stack[0];
    // printf("---------------------\n");
}