#include "Files.h"
#include <stdio.h>
#include <stdlib.h>

static int checkError(const char* filename, int n) {
    if (!filename || n <= 0) {
        printf("Error: Invalid parameters\n");
        return ERR;
    }
    return OK;
}

int printLastNLines(const char* filename, int n) {
    int status;
    FILE* file;
    static char lines[MAX_LINES][MAX_LINE_LENGTH];
    int count = 0;
    int start;
    int i;

    status = checkError(filename, n);
    if (status == ERR) {
        return ERR;
    }

    file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        return ERR;
    }

    while (fgets(lines[count], MAX_LINE_LENGTH, file)) {
        count++;
        if (count >= MAX_LINES) {
            break;  
        }
    }
    fclose(file);

    start = count > n ? count - n : 0;

    for (i = start; i < count; i++) {
        printf("%s", lines[i]);
    }
    return OK;
}

int printRowsColumnsCharsNumbers(const char* filename) {
    int status;
    FILE* file;
    int lines = 0;
    int words = 0;
    int characters = 0;
    int in_word = 0;
    int c;

    status = checkError(filename, 1);
    if (status == ERR) {
        return ERR;
    }
    
    file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file\n");
        return ERR;
    }

    while ((c = fgetc(file)) != EOF) {
        characters++;
        if (c == '\n') {
            lines++;
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            if (in_word) {
                words++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }
    
    if (in_word) {
        words++;
    }

    fclose(file);

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    return OK;
}