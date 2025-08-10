#include<stdio.h>
#include<string.h>
#include<ctype.h>
const char* expression = "(20 + 40)*2";
char stack[50][50];
int main(){
    int i = 0, j = 0;
    int len = strlen(expression);
    for(int k = 0; k < len; k++){
        if(expression[k] == ' ') continue;
        if(!isdigit(expression[k])){
            stack[i][j] = expression[k];
            stack[i][j + 1] = '\0';
            i++; j = 0;
        }
        else{
            if(isdigit(expression[k - 1])){
                i--; j++;
                stack[i][j] = expression[k];
                stack[i][j + 1] = '\0';
                i++; j = 0;
            }
            else{
                stack[i][j] = expression[k];
                stack[i][j + 1] = '\0';
                i++; j = 0;
            }
        }
    }

    for(int k = 0; k < i; k++){
        puts(stack[k]);
    }

}