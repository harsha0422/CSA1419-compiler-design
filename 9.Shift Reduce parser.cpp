#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Stack and input buffer
char stack[MAX];
int top = -1;
char input[MAX];
int inputIndex = 0;

// Function to push an element to the stack
void push(char symbol) {
    if (top < MAX - 1) {
        stack[++top] = symbol;
    } else {
        printf("Stack overflow!\n");
        exit(1);
    }
}

// Function to pop an element from the stack
char pop() {
    if (top == -1) {
        printf("Stack underflow!\n");
        exit(1);
    } else {
        return stack[top--];
    }
}

// Function to check if the stack matches the production S -> aSb
int checkReduce() {
    if (top >= 2 && stack[top] == 'b' && stack[top - 1] == 'S' && stack[top - 2] == 'a') {
        return 1;
    }
    return 0;
}

// Function to perform the Shift-Reduce parsing
void shiftReduceParse() {
    while (inputIndex < strlen(input)) {
        // Shift step: push the current input symbol to the stack
        printf("Shift: %c\n", input[inputIndex]);
        push(input[inputIndex]);
        inputIndex++;

        // Check if we can reduce (S -> aSb)
        while (checkReduce()) {
            // Pop 'b', 'S', 'a' and push 'S' to represent the reduction
            pop(); // pop 'b'
            pop(); // pop 'S'
            pop(); // pop 'a'
            push('S'); // push 'S' (reduction S -> aSb)
            printf("Reduce: S -> aSb\n");
        }

        // Print the current stack
        printf("Stack: ");
        for (int i = 0; i <= top; i++) {
            printf("%c ", stack[i]);
        }
        printf("\n");
    }

    // Final reduction check for S -> e (empty string)
    if (top == 0 && stack[top] == 'S') {
        printf("Input string is accepted by the parser.\n");
    } else {
        printf("Error: Invalid input string.\n");
    }
}

int main() {
    printf("Enter the input string (only 'a' and 'b' are allowed): ");
    scanf("%s", input);

    // Parse the input string using shift-reduce parsing
    shiftReduceParse();

    return 0;
}
