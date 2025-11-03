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
    int i_num_stack = 0;
    //----
    int l_postfix = 3;
    //----
    for (int o = 0; o < l_postfix; o++)
    {
        if (isdigit(*postfix[o]))
        {
            num_stack[i_num_stack] = tonum(postfix[o]);
            i_num_stack++;
        }
        else
        {
            double a = num_stack[i_num_stack - 1];
            i_num_stack--;
            double b = num_stack[i_num_stack - 1];
            i_num_stack--;
            switch (*postfix[o])
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
