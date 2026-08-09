#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "wordlist.h"
#include "game.h"


int main(void) {
    srand((unsigned)time(NULL));

    char play_again[10];
    

    do {
        start_game();
        printf("Play again? (y/n): ");

        if (fgets(play_again, sizeof(play_again), stdin) != NULL) {
            play_again[strcspn(play_again, "\n")] = '\0';
        } else {
            play_again[0] = '\0';
        }
        
    } while (strcmp(play_again, "y") == 0 || strcmp(play_again, "Y") == 0);

    printf("\nThank you for playing my game!\n");
    return 0;
}