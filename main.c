#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 6 // word length + 1 for the null terminator

void getNameFromLine(int line, FILE* file) {
    char *name = (char*)malloc(WORD_SIZE * sizeof(char)); 
    int offset = (line-1) * WORD_SIZE; 

    fseek(file, offset, SEEK_SET);
    fgets(name, WORD_SIZE, file);

    puts(name);
    free(name);
}

int main() {
    FILE* file = fopen("names.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    getNameFromLine(1, file);
    fclose(file);

    return 0;
}