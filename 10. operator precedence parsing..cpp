#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
char precedenceTable[5][5] = {
    {'>', '>', '<', '<', '>'}, 
    {'>', '>', '<', '<', '>'}, 
    {'>', '>', '>', '>', '>'}, 
    {'>', '>', '>', '>', '>'},
    {'<', '<', '<', '<', '='}  
};
int getPrecedenceIndex(char symbol) {
    switch (symbol) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '$': return 4;
        default: return -1; 
    }
}
int isOperator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '$');
}
void operatorPrecedenceParsing(char *input) {
    char stack[MAX];
    int top = -1;
    int i = 0;
    char currentSymbol;
    stack[++top] = '$';
    printf("\nParsing Steps:\n");
    printf("Stack\t\tInput\t\tAction\n");
    while (1) {
        currentSymbol = input[i];
        if (!isOperator(currentSymbol) && currentSymbol != '$') {
            printf("%s\t\t%s\t\tShift %c\n", stack, input + i, currentSymbol);
            i++;
        } else {
            char stackTop = stack[top];
            int precedenceIndex1 = getPrecedenceIndex(stackTop);
            int precedenceIndex2 = getPrecedenceIndex(currentSymbol);
            if (precedenceIndex1 == -1 || precedenceIndex2 == -1) {
                printf("Error: Invalid operator or symbol\n");
                return;
            }
            
            char precedence = precedenceTable[precedenceIndex1][precedenceIndex2];
            
            if (precedence == '<' || precedence == '=') {
                stack[++top] = currentSymbol;
                printf("%s\t\t%s\t\tShift %c\n", stack, input + i, currentSymbol);
                i++;
            } else if (precedence == '>') {
                printf("%s\t\t%s\t\tReduce\n", stack, input + i);
                top--; 
            } else {
                printf("Error: Invalid precedence\n");
                return;
            }
        }
        if (stack[top] == '$' && input[i] == '$') {
            printf("%s\t\t%s\t\tAccept\n", stack, input + i);
            break;
        }
    }
}

int main() {
    char input[MAX];
    
    printf("Enter the expression to parse (end with $): ");
    scanf("%s", input);
    int len = strlen(input);
    if (input[len - 1] != '$') {
        input[len] = '$';
        input[len + 1] = '\0';
    }
    
    operatorPrecedenceParsing(input);
    
    return 0;
}
