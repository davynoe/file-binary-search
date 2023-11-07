#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100

char** fileToArray(char* fileName, int* arrayLength) {
    FILE* file = fopen(fileName, "r");
    char currentLine[MAX_LINE_LENGTH];
    char** array = NULL; // dynamic array of strings

    int lineCount = 0;
    while(fgets(currentLine, sizeof(currentLine), file) != NULL) {
        lineCount++;
        currentLine[strcspn(currentLine, "\n")] = '\0';

        array = realloc(array, lineCount * sizeof(char*));
        if(array == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        array[lineCount-1] = malloc(strlen(currentLine)+1); 
        if(array[lineCount - 1] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        strcpy(array[lineCount-1], currentLine);
    }

    fclose(file);
    *arrayLength = lineCount;
    return array;
}

int search(char* fileName, char* key) {
    int arrayLength;
    char** array = fileToArray("names.txt", &arrayLength);

    int low = 0;
    int high = arrayLength-1;
    int result;
    while(low<high) {
        int mid = low + (high-low)/2;
        char* midWord = array[mid];

        if(strcmp(key, midWord) < 0) {
            high = mid - 1;
        }
        else if(strcmp(key, midWord) > 0) {
            low = mid + 1;
        }
        else {
            result = mid+1; // +1 to convert the index to a real line number
            break;
        }
    }

    for(int i=0; i<arrayLength; i++) {
        free(array[i]); // free each individual string
    }
    free(array); // free array of pointers

    return result;
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    char* name = "Benja";
    char* fileName = "names.txt";
    int result = search(fileName, name);
    printf("%d\n", result);

    end = clock();

    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);
    return 0;
}