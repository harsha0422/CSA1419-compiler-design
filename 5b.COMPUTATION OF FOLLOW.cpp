#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

typedef struct {
    char nonTerminal;
    char follow[MAX];
} FollowSet;

typedef struct {
    char nonTerminal;
    char production[MAX];
} Production;

FollowSet followSets[MAX];
Production productions[MAX];
int followSetCount = 0, productionCount = 0;

int findNonTerminalIndex(char nonTerminal) {
    for (int i = 0; i < followSetCount; i++) {
        if (followSets[i].nonTerminal == nonTerminal) {
            return i;
        }
    }
    return -1;
}

void addToFollow(char nonTerminal, char terminal) {
    int index = findNonTerminalIndex(nonTerminal);
    if (index == -1) return;

    for (int i = 0; i < strlen(followSets[index].follow); i++) {
        if (followSets[index].follow[i] == terminal) {
            return; // Terminal already exists in FOLLOW
        }
    }
    int len = strlen(followSets[index].follow);
    followSets[index].follow[len] = terminal;
    followSets[index].follow[len + 1] = '\0';
}

void calculateFollow() {
    addToFollow(productions[0].nonTerminal, '$'); // Start symbol gets '$'

    int changes;
    do {
        changes = 0;
        for (int i = 0; i < productionCount; i++) {
            char *rhs = productions[i].production;
            char lhs = productions[i].nonTerminal;

            for (int j = 0; j < strlen(rhs); j++) {
                if (isupper(rhs[j])) { // Non-terminal
                    int index = findNonTerminalIndex(rhs[j]);
                    if (j + 1 < strlen(rhs)) {
                        if (!isupper(rhs[j + 1])) { // Terminal follows
                            addToFollow(rhs[j], rhs[j + 1]);
                        } else { // Non-terminal follows
                            int nextIndex = findNonTerminalIndex(rhs[j + 1]);
                            for (int k = 0; k < strlen(followSets[nextIndex].follow); k++) {
                                char symbol = followSets[nextIndex].follow[k];
                                if (symbol != '\0') {
                                    addToFollow(rhs[j], symbol);
                                }
                            }
                        }
                    } else { // End of production, FOLLOW(lhs) to FOLLOW(rhs[j])
                        int lhsIndex = findNonTerminalIndex(lhs);
                        for (int k = 0; k < strlen(followSets[lhsIndex].follow); k++) {
                            char symbol = followSets[lhsIndex].follow[k];
                            if (symbol != '\0') {
                                addToFollow(rhs[j], symbol);
                            }
                        }
                    }
                }
            }
        }
    } while (changes);
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &productionCount);

    printf("Enter the productions (e.g., A->BCD):\n");
    for (int i = 0; i < productionCount; i++) {
        char input[MAX];
        scanf("%s", input);

        productions[i].nonTerminal = input[0];
        strcpy(productions[i].production, input + 3); // Skip "A->"

        if (findNonTerminalIndex(input[0]) == -1) {
            followSets[followSetCount].nonTerminal = input[0];
            followSets[followSetCount].follow[0] = '\0';
            followSetCount++;
        }
    }

    calculateFollow();

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < followSetCount; i++) {
        printf("FOLLOW(%c) = { ", followSets[i].nonTerminal);
        for (int j = 0; j < strlen(followSets[i].follow); j++) {
            printf("%c ", followSets[i].follow[j]);
        }
        printf("}\n");
    }

    return 0;
}
