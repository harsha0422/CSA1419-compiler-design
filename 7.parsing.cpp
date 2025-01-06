#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 10

char productions[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
char terminals[MAX], nonTerminals[MAX];
char parsingTable[MAX][MAX][MAX];
int prodCount, termCount = 0, nonTermCount = 0;

void addToSet(char *set, char symbol) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == symbol) return; 
    }
    int len = strlen(set);
    set[len] = symbol;
    set[len + 1] = '\0';
}

void findFirst(char nonTerminal, char *result) {
    for (int i = 0; i < prodCount; i++) {
        if (productions[i][0] == nonTerminal) {
            if (!isupper(productions[i][3])) {
                addToSet(result, productions[i][3]); 
            } else {
                char subFirst[MAX] = "";
                findFirst(productions[i][3], subFirst);
                for (int j = 0; subFirst[j] != '\0'; j++) {
                    addToSet(result, subFirst[j]);
                }
            }
        }
    }
}

void findFollow(char nonTerminal, char *result) {
    if (nonTerminal == productions[0][0]) addToSet(result, '$'); 

    for (int i = 0; i < prodCount; i++) {
        char *prod = productions[i];
        for (int j = 3; prod[j] != '\0'; j++) {
            if (prod[j] == nonTerminal) {
                if (prod[j + 1] == '\0') {
                    char subFollow[MAX] = "";
                    findFollow(prod[0], subFollow);
                    for (int k = 0; subFollow[k] != '\0'; k++) {
                        addToSet(result, subFollow[k]);
                    }
                } else if (!isupper(prod[j + 1])) {
                    addToSet(result, prod[j + 1]); 
                } else {
                    char subFirst[MAX] = "";
                    findFirst(prod[j + 1], subFirst);
                    for (int k = 0; subFirst[k] != '\0'; k++) {
                        if (subFirst[k] != 'e') addToSet(result, subFirst[k]);
                    }
                }
            }
        }
    }
}

void constructParsingTable() {
    for (int i = 0; i < prodCount; i++) {
        char nonTerminal = productions[i][0];
        char firstSet[MAX] = "";
        findFirst(nonTerminal, firstSet);

        for (int j = 0; firstSet[j] != '\0'; j++) {
            if (firstSet[j] != 'e') {
                parsingTable[nonTerminal - 'A'][firstSet[j] - 'a'][0] = i; // Map production index
            }
        }

        if (strchr(firstSet, 'e') != NULL) {
            char followSet[MAX] = "";
            findFollow(nonTerminal, followSet);
            for (int j = 0; followSet[j] != '\0'; j++) {
                parsingTable[nonTerminal - 'A'][followSet[j] - 'a'][0] = i;
            }
        }
    }
}

void displayParsingTable() {
    printf("\nParsing Table:\n");
    for (int i = 0; i < nonTermCount; i++) {
        for (int j = 0; j < termCount; j++) {
            if (parsingTable[nonTerminals[i] - 'A'][terminals[j] - 'a'][0] != 0) {
                int prodIndex = parsingTable[nonTerminals[i] - 'A'][terminals[j] - 'a'][0];
                printf("M[%c, %c] = %s\n", nonTerminals[i], terminals[j], productions[prodIndex]);
            }
        }
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &prodCount);

    printf("Enter the productions (e.g., S->aB):\n");
    for (int i = 0; i < prodCount; i++) {
        scanf("%s", productions[i]);
        if (strchr(nonTerminals, productions[i][0]) == NULL) {
            nonTerminals[nonTermCount++] = productions[i][0];
        }

        for (int j = 3; productions[i][j] != '\0'; j++) {
            if (!isupper(productions[i][j]) && productions[i][j] != 'e' &&
                strchr(terminals, productions[i][j]) == NULL) {
                terminals[termCount++] = productions[i][j];
            }
        }
    }

    for (int i = 0; i < nonTermCount; i++) {
        findFirst(nonTerminals[i], first[i]);
    }

    for (int i = 0; i < nonTermCount; i++) {
        findFollow(nonTerminals[i], follow[i]);
    }

    constructParsingTable();

    printf("\nFIRST sets:\n");
    for (int i = 0; i < nonTermCount; i++) {
        printf("FIRST(%c) = { %s }\n", nonTerminals[i], first[i]);
    }

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < nonTermCount; i++) {
        printf("FOLLOW(%c) = { %s }\n", nonTerminals[i], follow[i]);
    }

    displayParsingTable();

    return 0;
}
