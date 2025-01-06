#include <stdio.h>
#include <string.h>
void checkComment(char line[]) {
    while (*line == ' ') {
        line++;
    }
    if (line[0] == '/' && line[1] == '/') {
        printf("The given line is a single-line comment.\n");
    } else if (line[0] == '/' && line[1] == '*') {
        int length = strlen(line);
        if (length >= 4 && line[length - 2] == '*' && line[length - 1] == '/') {
            printf("The given line is a multi-line comment.\n");
        } else {
            printf("The given line is the start of a multi-line comment but not complete.\n");
        }
    } else {
        printf("The given line is NOT a comment.\n");
    }
}
int main() {
    char line[100];
    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0'; 
    checkComment(line);
    return 0;
}
