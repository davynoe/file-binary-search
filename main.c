#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100

char** fileToArray(char* fileName, int* arrayLength);
int search(char* fileName, char* key);
void test(char* fileName); // tests if every name in the file can be found

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    char* word = "Zita";            // change this!
    char* fileName = "names.txt";   // change this!
    int result = search(fileName, word);
    if(result == -1) {
        printf("Unable to find %s in the file\n", word);
        return 0;
    }
    printf("'%s' found at line %d\n", word, result);
    
    end = clock();

    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);

    // test("names.txt");

    return 0;
}

char** fileToArray(char* fileName, int* arrayLength) {
    FILE* file = fopen(fileName, "r");
    if(file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char currentLine[MAX_LINE_LENGTH];
    char** array = NULL; // future array of strings

    int lineCount = 0;
    while(fgets(currentLine, sizeof(currentLine), file) != NULL) {
        lineCount++;
        int currentIndex = lineCount - 1;

        currentLine[strcspn(currentLine, "\n")] = '\0';

        // extend array of strings by 1 element
        array = realloc(array, lineCount * sizeof(char*));
        if(array == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // allocate space same as the current line for the
        // current element in array, to store the current line in the future
        array[currentIndex] = malloc(strlen(currentLine)+1); // +1 for the '\0' element in the end
        if(array[currentIndex] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        strcpy(array[currentIndex], currentLine);
    }

    fclose(file);
    *arrayLength = lineCount;
    return array;
}

int search(char* fileName, char* key) {
    int arrayLength;
    char** array = fileToArray(fileName, &arrayLength);

    int low = 0;
    int high = arrayLength-1;
    int result = -1;

    while(low <= high) {
        int mid = low + (high-low)/2;
        char* midWord = array[mid];

        if(strcmp(key, midWord) < 0) {
            high = mid - 1;
        }
        else if(strcmp(key, midWord) > 0) {
            low = mid + 1;
        }
        else {
            result = mid+1; // +1 to convert index to line number
            break;
        }
    }

    // free allocated stuff from fileToArray()
    for(int i=0; i<arrayLength; i++) {
        free(array[i]); // free each individual string
    }
    free(array); // free array of pointers

    return result;
}

void test(char* fileName) {
    int arrayLength;
    char** array = fileToArray(fileName, &arrayLength);
    int passed = 1;
    for(int i=0; i<arrayLength; i++) {
        int result = search(fileName, array[i]);
        if(result == -1 || result != i+1) {
            printf("Cant find name at line %d\n", i+1);
            passed = 0;
        }
        free(array[i]);
    }
    free(array);

    if(passed) {
        printf("File '%s' passed all the tests!\n", fileName);
    }
}