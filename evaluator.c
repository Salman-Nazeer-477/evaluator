#include<stdio.h>
#include<string.h>
#include<ctype.h>
const char* expression = "(20 + 40)*2";
char infix[50][50];

int isnum(char c){
    if(isalnum(c) && !isalpha(c)) return 1;
    return 0;
}

int isopepar(char c){
    return c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int toint(char num[]){
    int n = 0;
    int len = strlen(num);
    for(int i = 0; num[i] != '\0' || (len - 1 - i) > 0; i++){
        n += (num[len - 1 - i] - '0') * pow(10, i);
    }
    return n;
}

int main(){
    // Tokenize expression
    int i = 0, j = 0;
    int len = strlen(expression);
    for(int k = 0; k < len; k++){
        if(expression[k] == ' ') continue;
        if(!isnum(expression[k]) && !isopepar(expression[k])){
            printf("Invalid expression!\n");
            return 1;
        }
        if(!isdigit(expression[k])){
            infix[i][j] = expression[k];
            infix[i][j + 1] = '\0';
            i++; j = 0;
        }
        else{
            if(isdigit(expression[k - 1])){
                i--; j++;
                infix[i][j] = expression[k];
                infix[i][j + 1] = '\0';
                i++; j = 0;
            }
            else{
                infix[i][j] = expression[k];
                infix[i][j + 1] = '\0';
                i++; j = 0;
            }
        }
    }

    for(int k = 0; k < i; k++){
        puts(infix[k]);
    }
    /////////////////////////////////
    
    // infix to postfix conversion

    char prefix[50][50];
    char stack[50][50];
    for(int k = 0; k < i; k++){
        if(!isnum(*infix[k])){
            switch(*infix[k]){
                case '(':
                    
                    break;
                case ')':
                    
                    break;
                case '+':
                case '-':
                    
                    break;
                case '*':
                case '/':
                    
                    break;
                case '^':
                    
                    break;
                default:

            }
        }
    }

    // Postfix evaluation

    char *postfix[50] = {"23", "8", "-", "3", "*",};
	int num_stack[50];
	int n = 0;
	for(int o = 0; o < 5; o++){
	    if(isdigit(*postfix[o])){
	        num_stack[n] = toint(postfix[o]);
	        n++;
	    }
	    else{
	        int a = num_stack[n - 1]; n--;
	        int b = num_stack[n - 1]; n--;
	        switch(*postfix[o]){
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
	        }
	        n++;
	    }   
	}
	printf("%d\n", num_stack[0]);


}