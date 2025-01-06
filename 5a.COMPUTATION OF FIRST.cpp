#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

typedef struct {
    char nonTerminal;
    char first[MAX];
} FirstSet;

FirstSet firstSets[MAX];
int firstSetCount = 0;

int findNonTerminalIndex(char nonTerminal) {
    for (int i = 0; i < firstSetCount; i++) {
        if (firstSets[i].nonTerminal == nonTerminal) {
            return i;
        }
    }
    return -1;
}

void addToFirst(char nonTerminal, char terminal) {
    int index = findNonTerminalIndex(nonTerminal);
    if (index == -1) return;

    for (int i = 0; i < strlen(firstSets[index].first); i++) {
        if (firstSets[index].first[i] == terminal) {
            return; // Terminal already exists in FIRST
        }
    }
    int len = strlen(firstSets[index].first);
    firstSets[index].first[len] = terminal;
    firstSets[index].first[len + 1] = '\0';
}

void calculateFirst(char nonTerminal, char productions[][MAX], int prodCount) {
    for (int i = 0; i < prodCount; i++) {
        if (productions[i][0] == nonTerminal) {
            for (int j = 1; j < strlen(productions[i]); j++) {
                char symbol = productions[i][j];

                if (isupper(symbol)) {
                    int index = findNonTerminalIndex(symbol);
                    if (index != -1) {
                        strcat(firstSets[findNonTerminalIndex(nonTerminal)].first, firstSets[index].first);
                    }
                    break;
                } else if (symbol != '|') {
                    addToFirst(nonTerminal, symbol);
                    break;
                }
            }
        }
    }
}

int main() {
    int numProductions;
    char productions[MAX][MAX];

    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter the productions (e.g., E->E+T or T->T*F|F):\n");
    for (int i = 0; i < numProductions; i++) {
        scanf("%s", productions[i]);

        char nonTerminal = productions[i][0];
        if (findNonTerminalIndex(nonTerminal) == -1) {
            firstSets[firstSetCount].nonTerminal = nonTerminal;
            firstSets[firstSetCount].first[0] = '\0';
            firstSetCount++;
        }
    }

    for (int i = 0; i < firstSetCount; i++) {
        calculateFirst(firstSets[i].nonTerminal, productions, numProductions);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < firstSetCount; i++) {
        printf("FIRST(%c) = { ", firstSets[i].nonTerminal);
        for (int j = 0; j < strlen(firstSets[i].first); j++) {
            printf("%c ", firstSets[i].first[j]);
        }
        printf("}\n");
    }

    return 0;
}
