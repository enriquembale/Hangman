#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "wordlist.h"
#define MAX_LENGTH 100

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
void update_letter_slots(char *random_word, char *user_word, char *letter_slots) {
    for (int i = 0; i < strlen(random_word); i++) {
        bool found = false;
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
}
    
void print_words(int word_length, char *letter_slots) {
        while (1) {
            for (int i = 0; i < word_length; i++) {
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

    if (strlen(guess) != 1)
        return false;

    for (int i = 0; i < strlen(random_word); i++) {
        if (random_word[i] == guess[0]) {
            return true;
        }
    }

    return false;
}

void clear(void) {
    printf("\e[1;1H\e[2J");
}


void start_game(void) {
    char random_word[MAX_LENGTH] = "breeze";
    char guess[MAX_LENGTH];
    guess[0] = '\0';

    //get_random_word(random_word);
    int word_length = strlen(random_word);
    char letter_slots[word_length + 1];
    char guessed_letters[26] = {0}; 
    memset(letter_slots, 0, sizeof(letter_slots)); // Initialize letter_slots with null characters
    int lives = 6;
    
    clear();

    printf("Welcome to Hangman!\n\n");

    while (1) {
        
        printf("%s\n\n", hangman_pics[6 - lives]);

        printf("Lives: %d\n", lives);
        update_letter_slots(random_word, guess, letter_slots);

        printf("Incorrect guesses: ");
        for (int i = 0; i < strlen(guessed_letters); i++) {
            printf("%c", guessed_letters[i]);

            if (i < strlen(guessed_letters) - 1) {
                printf(", ");
            }
        }

        printf("\nWord: ");
        print_words(word_length, letter_slots);

        get_guess(guess, sizeof(guess));

        clear();

        // ------------ full word guess ------------
        
        if (strlen(guess) > 1) {

            if (strcmp(guess, random_word) == 0) {
                printf("\nCongratulations! You guessed the word correctly.\n");
                break;
            }
            lives--;
            printf("Incorrect word! You have %d live(s) left.\n\n", lives);
        }

        // ------------ letter guess ------------

        else {

            if (strchr(guessed_letters, guess[0]) != NULL ||
                strchr(letter_slots, guess[0]) != NULL) {
                printf("You have already guessed '%c'. Try a different letter.\n\n", guess[0]);
                guess[0] = '\0';
                continue;
                }

            if (guess_correct(random_word, guess)) {
                
                size_t len = strlen(guessed_letters);
                guessed_letters[len + 1] = '\0';
                
                update_letter_slots(random_word, guess, letter_slots);
            
            
                if (strcmp(letter_slots, random_word) == 0) {
                    printf("Word: ");
                    print_words(word_length, letter_slots);
                    printf("Guess: %s\n", guess);
                    printf("Congratulations! You guessed the word correctly.\n\n");
                    break;
                }
                printf("Correct guess! You have %d live(s) left.\n\n", lives);
                guess[0] = '\0';
            } else {
                lives--;
                printf("Incorrect guess. You have %d live(s) left.\n\n", lives);
            }

            size_t len = strlen(guessed_letters);
            guessed_letters[len] = guess[0];
            guessed_letters[len + 1] = '\0';
        }

        guess[0] = '\0';

        if (lives == 0) {
            printf("\nGame over! The word was: %s\n", random_word);
            break;
        }
    }

    return;
}
