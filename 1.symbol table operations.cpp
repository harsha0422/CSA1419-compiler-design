#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ENTRIES 100
typedef struct {
    char identifier[50];
    char type[20];
    int lineNumber;
} SymbolTableEntry;
SymbolTableEntry symbolTable[MAX_ENTRIES];
int entryCount = 0;
void insert(char *identifier, char *type, int lineNumber) {
    for (int i = 0; i < entryCount; i++) {
        if (strcmp(symbolTable[i].identifier, identifier) == 0) {
            printf("Error: Duplicate identifier '%s' not allowed.\n", identifier);
            return;
        }
    }
    strcpy(symbolTable[entryCount].identifier, identifier);
    strcpy(symbolTable[entryCount].type, type);
    symbolTable[entryCount].lineNumber = lineNumber;
    entryCount++;
    printf("Inserted: %s, %s, Line %d\n", identifier, type, lineNumber);
}
void search(char *identifier) {
    for (int i = 0; i < entryCount; i++) {
        if (strcmp(symbolTable[i].identifier, identifier) == 0) {
            printf("Found: %s, %s, Line %d\n", symbolTable[i].identifier, symbolTable[i].type, symbolTable[i].lineNumber);
            return;
        }
    }
    printf("Identifier '%s' not found in symbol table.\n", identifier);
}
void display() {
    printf("\nSymbol Table:\n");
    printf("-------------------------------------------------\n");
    printf("Identifier\tType\t\tLine Number\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%-15s%-15s%d\n", symbolTable[i].identifier, symbolTable[i].type, symbolTable[i].lineNumber);
    }
    printf("-------------------------------------------------\n");
}
int main() {
    int choice;
    char identifier[50], type[20];
    int lineNumber;
    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter identifier: ");
                scanf("%s", identifier);
                printf("Enter type: ");
                scanf("%s", type);
                printf("Enter line number: ");
                scanf("%d", &lineNumber);
                insert(identifier, type, lineNumber);
                break;

            case 2:
                printf("Enter identifier to search: ");
                scanf("%s", identifier);
                search(identifier);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
