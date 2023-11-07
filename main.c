#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// NOT: Bu kod ancak names.txt dosyasındaki tüm isimler aynı uzunluktayken çalışır.

// fseek fonksiyonu ile dosyada doğru atlamaların sağlanması için
// dosyanın içeriğinin tahmin edilebilir/sabit olması gerekir.

char* getNameFromLine(int line, FILE* file, int wordSize);
int getNameLength(FILE* file);
int getLineCount(FILE* file);
int search(char* name, char* fileName);

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    char* fileName = "names.txt"; // değiştirilebilir
    char* name = "Henry";         // değiştirilebilir
    int result = search(name, fileName);
    printf("Name '%s' found at line %d\n", name, result);

    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

char* getNameFromLine(int line, FILE* file, int wordLength) {
    int wordSize = wordLength+1;

    char* name = (char*)malloc(wordSize * sizeof(char)); 
    int offset = (line-1) * wordSize; 

    fseek(file, offset, SEEK_SET);
    fgets(name, wordSize, file);

    return name;
}

int getNameLength(FILE* file) {
    char word[100];
    if(fgets(word, sizeof(word), file) != NULL) {
        word[strcspn(word, "\n")] = '\0';
        int result = strlen(word);
        return result;
    }
    return -1;
}

int getLineCount(FILE* file) {
    int lines=1;
    int currentChar;

    while((currentChar = fgetc(file)) != EOF) {
        if(currentChar == '\n') {
            lines++;
        }
    }

    if(lines > 0 && currentChar != '\n') {
        lines++;
    }

    return lines;
}

int search(char* name, char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const int WORD_LENGTH = getNameLength(file); 
    const int LINE_COUNT = getLineCount(file);

    int low = 1;
    int high = LINE_COUNT;

    char* lowName = getNameFromLine(low, file, WORD_LENGTH);
    char* highName = getNameFromLine(high, file, WORD_LENGTH);

    while(strcmp(lowName, highName) <= 0) {
        int mid = low + (high-low)/2;
        char* midName = getNameFromLine(mid, file, WORD_LENGTH);

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