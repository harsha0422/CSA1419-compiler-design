#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void analyzeFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char ch;
    int characters = 0, words = 0, lines = 0;
    int inWord = 0;
    while ((ch = fgetc(file)) != EOF) {
        characters++; 
        if (ch == '\n') {
            lines++; 
        }
        if (isspace(ch)) {
            if (inWord) {
                words++; 
                inWord = 0;
            }
        } else {
            inWord = 1; 
        }
    }
    if (inWord) {
        words++;
    }
    fclose(file);
    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);
}
int main() {
    char filename[100];
    printf("Enter the filename to analyze: ");
    scanf("%s", filename);
    analyzeFile(filename);
    return 0;
}
