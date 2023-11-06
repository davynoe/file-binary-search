#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 6 // word length + 1 for the null terminator

char* getNameFromLine(int line, FILE* file) {
    char *name = (char*)malloc(WORD_SIZE * sizeof(char)); 
    int offset = (line-1) * WORD_SIZE; 

    fseek(file, offset, SEEK_SET);
    fgets(name, WORD_SIZE, file);

    return name;
}

int main() {
    FILE* file = fopen("names.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char* name = getNameFromLine(92, file);
    puts(name);

    free(name);
    fclose(file);

    return 0;
}