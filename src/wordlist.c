#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordlist.h"
#define MAX_WORD_LENGTH 100

char *get_random_word(char *word) {

    FILE *file_ptr = fopen("wordlist.txt", "r");
    if (file_ptr == NULL) {
        printf("Error: Could not open file.\n");
        return NULL;
    }

    char buffer[MAX_WORD_LENGTH];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
        line_count++;
    }

    if (line_count == 0) {
        printf("Error: word list is empty.\n");
        fclose(file_ptr);
        return NULL;
    }

    rewind(file_ptr);
    int random_index = rand() % line_count;

    for (int i = 0; i <= random_index; i++) {
        if (fgets(buffer, sizeof(buffer), file_ptr) == NULL) {
            break;
        }
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    //printf("%s\n", buffer);
    fclose(file_ptr);
    strncpy(word, buffer, len + 1);
    return word;
}