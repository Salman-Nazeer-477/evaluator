#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char infix[50][50] = {"1", "+", "2"};
int l_infix = 3;
int isoperator(char c);
int isnumber(char c);
int isprecedencelower(char a, char b);
int isparenthesis(char c);

int main()
{
    char postfix[50][50];
    char stack[50][50];
    int i_postfix = -1;
    int i_stack = -1;
    int i_infix;
    for(i_infix = 0; i_infix < l_infix; i_infix++){
        if(isnumber(*infix[i_infix])){
            i_postfix++;
            strcpy(postfix[i_postfix], infix[i_infix]);
        } else if(isparenthesis(*infix[i_infix])){
            printf("is a parenthesis\n");
            if(*infix[i_infix] == '('){
                i_postfix++;
                strcpy(postfix[i_postfix], infix[i_infix]);
            } else {
                while(*stack[i_stack] != '('){
                    i_postfix++;
                    strcpy(postfix[i_postfix], stack[i_stack]);
                    i_stack--;
                }
                i_stack--;
            }
        } else if(isoperator(*infix[i_infix])){
            printf("is an operator\n");
            if(isparenthesis(*stack[i_stack])){
                i_stack++;
                strcpy(stack[i_stack], infix[i_infix]);
            }
            else if(isprecedencelower(*infix[i_infix], *stack[i_stack])){
                i_postfix++;
                strcpy(postfix[i_postfix], stack[i_stack]);
                i_stack--;
            }
            else {
                i_stack++;
                strcpy(stack[i_stack], infix[i_infix]);
            }
        }
    }
    while(i_stack > -1){
        i_postfix++;
        strcpy(postfix[i_postfix], stack[i_stack]);
        i_stack--;
    }
    for(int k = 0; k <= i_postfix; k++) {printf("%s\n", postfix[k]);}
}

int isoperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isnumber(char c){
    return c >= '0' && c <= '9';
}

int isprecedencelower(char a, char b){
    switch(a){
        case '^':
            return 0;
            break;
        case '*':
        case '/':
            if(b == '^') return 1;
            else return 0;
            break;
        case '+':
        case '-':
            if(b == '+' || b == '-') return 0;
            else return 1;
            break;
    }
}

int isparenthesis(char c){
    return c == '(' || c == ')';
}