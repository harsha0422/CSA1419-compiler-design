#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define NUM_KEYWORDS 32

const char *keywords[NUM_KEYWORDS] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
bool isKeyword(const char *identifier) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}
bool isValidIdentifier(const char *identifier) {
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return false; 
    }
    for (int i = 1; i < strlen(identifier); i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') {
            return false; 
        }
    }
    if (isKeyword(identifier)) {
        return false; 
    }
    return true;
}
int main() {
    char identifier[100];
    printf("Enter an identifier: ");
    scanf("%s", identifier);
    if (isValidIdentifier(identifier)) {
        printf("'%s' is a valid identifier.\n", identifier);
    } else {
        printf("'%s' is not a valid identifier.\n", identifier);
    }
    return 0;
}
