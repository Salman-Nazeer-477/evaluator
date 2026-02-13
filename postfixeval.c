/*
indexes for various arrays should have a preceding i_ followed by the array name.
lengths for various arrays should have a preceding l_ followed by the array name.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char postfix[100][100] = {"40", "3", "+"};

double tonum(char *str);


int main()
{
    
    double num_stack[50];
    int i_num_stack = -1;
    //----
    int l_postfix = 3;
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
            i_num_stack++;
        }
    }
    printf("%lf\n", num_stack[0]);
    
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
