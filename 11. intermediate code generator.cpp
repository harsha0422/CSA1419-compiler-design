#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
int tempCount = 1;
char* newTemp() {
    static char temp[10];
    snprintf(temp, sizeof(temp), "t%d", tempCount++);
    return temp;
}
int isOperator(char symbol) {
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}
void infixToPostfix(char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (isOperator(infix[i])) {
            while (top != -1 && isOperator(stack[top]) &&
                   ((stack[top] == '*' || stack[top] == '/') || 
                   (stack[top] == '+' || stack[top] == '-') && (infix[i] == '+' || infix[i] == '-'))) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = infix[i];
        } else if (infix[i] == '(') {
            stack[++top] = infix[i];
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if (top != -1 && stack[top] == '(') {
                top--;
            }
        }
        i++;
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}
void generateThreeAddressCode(char* postfix) {
    char stack[MAX][MAX];
    int top = -1;
    char op1[MAX], op2[MAX], result[MAX];
    printf("\nThree-Address Code:\n");
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else if (isOperator(postfix[i])) {
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);
            strcpy(result, newTemp());
            printf("%s = %s %c %s\n", result, op1, postfix[i], op2);
            strcpy(stack[++top], result);
        }
    }
}
int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("\nPostfix Expression: %s\n", postfix);
    generateThreeAddressCode(postfix);
    return 0;
}
