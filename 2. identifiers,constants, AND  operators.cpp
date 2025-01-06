#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_IDENTIFIER_LENGTH 30
#define MAX_BUFFER_SIZE 1000
void analyze(char *code);
int isOperator(char ch);
int isKeyword(char *word);
const char *keywords[] = {
    "int", "float", "double", "char", "if", "else", "while", "for", "return", "void", "main", NULL
};
int main() {
    char code[MAX_BUFFER_SIZE];
    printf("Enter the code (end with '$' on a new line):\n");
    char ch;
    int index = 0;
    while ((ch = getchar()) != '$' && index < MAX_BUFFER_SIZE - 1) {
        code[index++] = ch;
    }
    code[index] = '\0';
    analyze(code);

    return 0;
}
void analyze(char *code) {
    char buffer[MAX_IDENTIFIER_LENGTH];
    int bufferIndex = 0;
    printf("\nLexical Analysis Output:\n");
    printf("----------------------------\n");
    for (int i = 0; code[i] != '\0'; i++) {
        char ch = code[i];
        if (isspace(ch)) {
            continue;
        }
        if (ch == '/' && code[i + 1] == '/') {
            while (code[i] != '\n' && code[i] != '\0') i++;
            continue;
        }
        if (ch == '/' && code[i + 1] == '*') {
            i += 2;
            while (!(code[i] == '*' && code[i + 1] == '/') && code[i] != '\0') i++;
            i++;
            continue;
        }
        if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            continue;
        }
        if (isdigit(ch)) {
            printf("Constant: ");
            while (isdigit(code[i]) || code[i] == '.') {
                putchar(code[i]);
                i++;
            }
            printf("\n");
            i--; 
            continue;
        }
        if (isalpha(ch) || ch == '_') {
            bufferIndex = 0;
            while (isalnum(code[i]) || code[i] == '_') {
                if (bufferIndex < MAX_IDENTIFIER_LENGTH - 1) {
                    buffer[bufferIndex++] = code[i];
                }
                i++;
            }
            buffer[bufferIndex] = '\0';
            i--; 
            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            continue;
        }
        printf("Unrecognized character: %c\n", ch);
    }

    printf("----------------------------\n");
}
int isOperator(char ch) {
    char operators[] = "+-*/=%<>&|!^";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}
int isKeyword(char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
