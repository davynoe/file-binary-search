#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 6 // word length + 1 for the null terminator
#define LINE_COUNT 70

char* getNameFromLine(int line, FILE* file) {
    char* name = (char*)malloc(WORD_SIZE * sizeof(char)); 
    int offset = (line-1) * WORD_SIZE; 

    fseek(file, offset, SEEK_SET);
    fgets(name, WORD_SIZE, file);

    return name;
}

int search(char* name, char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int low = 1;
    int high = LINE_COUNT;
    char* lowName = getNameFromLine(low, file);
    char* highName = getNameFromLine(high, file);

    while(strcmp(lowName, highName) <= 0) {
        int mid = low + (high-low)/2;
        char* midName = getNameFromLine(mid, file);
        if(strcmp(name, midName) == 0) {
            free(midName);
            free(lowName);
            free(highName);
            fclose(file);
            return mid;
        }
        else if(strcmp(name, midName) < 0) {
            high = mid-1;
        }
        else {
            low = mid+1;
        }
        free(midName);
    }

    free(lowName);
    free(highName);
    fclose(file);
    return -1; 
}

int main() {
    int result = search("Zanee", "names.txt");
    printf("%d\n", result);
    return 0;
}