#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fileToArray(char* fileName) {
    FILE* file = fopen(fileName, "r");
    char line[100];

    int lineCount = 0;
    while(fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        lineCount++;
    }
    printf("%d\n", lineCount);
}

int main() {
    fileToArray("names.txt");
}