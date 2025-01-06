#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

// Function to get the current character from the input
char currentChar() {
    return input[pos];
}

// Function to match a specific character and move to the next
void match(char expected) {
    if (currentChar() == expected) {
        pos++; // Move to next character
    } else {
        printf("Error: Expected '%c' but found '%c'\n", expected, currentChar());
        exit(1); // Exit the program if error occurs
    }
}

// Recursive function to parse A
void A() {
    if (currentChar() == 'c') {
        match('c'); // Match 'c'
    } else {
        // e-production (A -> e)
        return;
    }
}

// Recursive function to parse S
void S() {
    match('a'); // Match 'a'
    A();        // Parse A
    match('b'); // Match 'b'
}

int main() {
    printf("Enter the input string: ");
    scanf("%s", input);

    // Start parsing from the start symbol S
    S();

    // If we reach the end of the input without errors
    if (currentChar() == '\0') {
        printf("Input string is accepted by the grammar.\n");
    } else {
        printf("Error: Extra characters found in input.\n");
    }

    return 0;
}
