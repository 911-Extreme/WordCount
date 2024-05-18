#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int countCharacters(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int countWords(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    bool inWord = false;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalnum(ch)) {
            if (!inWord) {
                inWord = true;
                count++;
            }
        }
        else {
            inWord = false;
        }
    }
    fclose(file);
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] input.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* option = argv[1];
    const char* filename = argv[2];

    if (strcmp(option, "-c") == 0) {
        int characters = countCharacters(filename);
        printf("字符数: %d\n", characters);
    }
    else if (strcmp(option, "-w") == 0) {
        int words = countWords(filename);
        printf("单词数: %d\n", words);
    }
    else {
        fprintf(stderr, "Invalid option. Use '-c' for characters or '-w' for words.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}