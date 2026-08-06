#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "wordlist.h"

const char *hangman_pics[] = {
    "        +---+\n"
    "        |   |\n"
    "            |\n"
    "            |\n"
    "            |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "            |\n"
    "            |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "        |   |\n"
    "            |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "       /|   |\n"
    "            |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "       /|\\  |\n"
    "            |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "       /|\\  |\n"
    "       /    |\n"
    "            |\n"
    "      ============",
    "        +---+\n"
    "        |   |\n"
    "        O   |\n"
    "       /|\\  |\n"
    "       / \\  |\n"
    "            |\n"
    "      ============"
};

// Prints "_" for each letter in the word and fills in the letters that have been guessed correctly.
bool update_letter_slots(char *random_word, char *user_word, char *letter_slots) {
    bool found = false;
    for (int i = 0; i < strlen(random_word); i++) {

        for (int j = 0; j < strlen(user_word); j++) {
            if (user_word[j] == random_word[i]) {
                letter_slots[i] = random_word[i];
                found = true;
                break;
            }
        }

        if (!found && letter_slots[i] == 0) {
            letter_slots[i] = '_';
        }
    }
    return found;
}
    
void print_words(char *random_word, char *letter_slots) {
        while (1) {
            for (int i = 0; i < strlen(random_word); i++) {
                printf("%c ", letter_slots[i]);
            }
            printf("\n");
            break;
        }
    }


void get_guess(char guess[], size_t size) {
    while (true) {
        bool is_pure_string = true;
        printf("Guess: ");

        if (fgets(guess, size, stdin) != NULL) {
            guess[strcspn(guess, "\n")] = '\0';

            if (strlen(guess) == 0) {
                is_pure_string = false;
            }

            for (int i = 0; guess[i] != '\0'; i++) {
                if (!isalpha((unsigned char)guess[i]) && !isspace((unsigned char)guess[i])) {
                    is_pure_string = false;
                    break;
                }
            }

            if (is_pure_string) {
                return;
            }

            printf("\nError: Input contains invalid characters, numbers, or is empty.\n");
        }
    }
}

bool guess_correct(char *random_word, char *guess) {
    for (int i = 0; i < strlen(random_word); i++) {
        if (random_word[i] == guess[0] && strlen(guess) == 1) {
            return true;
        }
    }
    return false;
    
}

void clear(void) {
    printf("\e[1;1H\e[2J");
}


void start_game(void) {
    char word[100];
    get_random_word(word);
    int word_length = strlen(word);
    char letter_slots[word_length];
    memset(letter_slots, 0, sizeof(letter_slots)); // Initialize letter_slots with null characters
    int lives = 6;

    char *guess = malloc(word_length + 1 * sizeof(char));
    guess[0] = '\0';
    char *random_word = malloc(word_length + 1 * sizeof(char));

    if (random_word == NULL) {
        printf("Memory allocation failed!\n");
        free(guess);
        return;
    }

    strncpy(random_word, word, word_length + 1);
    

    printf("%s\n\n", hangman_pics[0]);
    while (1) {
    
        printf("Lives: %d\n", lives);
        update_letter_slots(random_word, guess, letter_slots);
        printf("Word: ");
        print_words(random_word, letter_slots);
        get_guess(guess, word_length + 1);
        
        clear();
        if (strcmp(guess, random_word) == 0) {
            printf("\nCongratulations! You guessed the word correctly.\n");
            break;
        } else if(guess_correct(random_word, guess)) {
            printf("\nCorrect guess!\n");
            printf("%s\n\n", hangman_pics[6 - lives]);
        } else {
            lives--;
            printf("\nIncorrect guess. You have %d live(s) left.\n", lives);
            printf("%s\n\n", hangman_pics[6 - lives]);
            guess[0] = '\0';
        }
        
        if (lives == 0) {
            printf("\nGame over! The word was: %s\n", random_word);
            break;
        }
        
    }

    free(guess);
    free(random_word);
    return;
}