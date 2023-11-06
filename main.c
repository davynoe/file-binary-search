#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 6 // Adjusted size to include space for null terminator

void getNameFromLine(int line, FILE* file) {
    char *name = (char*)malloc(WORD_SIZE * sizeof(char)); // Removed +1, as we account for null terminator
    int offset = (line-1) * WORD_SIZE; // Removed sizeof(char) as it's already accounted for
    fseek(file, offset, SEEK_SET);
    fgets(name, WORD_SIZE, file);

    // Remove newline character if it exists
    size_t length = strlen(name);
    if (length > 0 && name[length - 1] == '\n') {
        name[length - 1] = '\0'; // Replace newline with null terminator
    }

    puts(name);
    free(name); // Don't forget to free the allocated memory
}

int main() {
    FILE* file = fopen("names.txt", "r"); // Assign the result of fopen to file
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    getNameFromLine(1, file);
    fclose(file); // Close the file after using it
    return 0;
}