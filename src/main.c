#include <gb/gb.h>
#include <types.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <rand.h>
#include "main.h"

void main()
{
    uint16_t seed = DIV_REG;
    printf("Press Start\n");
    waitpad(J_START);
    cls();

    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);

    const char *WORD_LIST[WORD_LIST_LENGTH];
    WORD_LIST[0] = "seize";
    WORD_LIST[1] = "serve";
    WORD_LIST[2] = "vader";
    WORD_LIST[3] = "buzzy";
    WORD_LIST[4] = "weird";
    WORD_LIST[5] = "prime";
    WORD_LIST[6] = "light";
    WORD_LIST[7] = "piano";
    WORD_LIST[8] = "water";
    WORD_LIST[9] = "shark";

    uint8_t joydata;
    uint8_t word_choice_index = rand() % WORD_LIST_LENGTH;
    int chances = 5;
    int selected_letter_index = 65; // 65 to 90
    int word_index = 0;
    char player_word[6];
    char word_choice[6];
    strcpy(word_choice, WORD_LIST[word_choice_index]);
    int won = 0;

    while(1) {
        printf("%s\n", word_choice);
        /* Honestly, I don't know why I have to do this. */
        if (player_word[0] == NULL) {
            printf("Word:\n");
        }
        else {
            printf("Word: %s\n", player_word);
        }
        
        printf("Selected Letter: %c\n", selected_letter_index);
        
        while(1) {
            joydata = joypad();
            if (joydata & J_RIGHT) {
                if (selected_letter_index + 1 <= 90) {
                    selected_letter_index++;
                    break;
                }
            }
            if (joydata & J_LEFT) {
                if (selected_letter_index - 1 >= 65) {
                    selected_letter_index--;
                    break;
                }
            }
            if (joydata & J_A && word_index < 5) {
                player_word[word_index] = (char) selected_letter_index;
                word_index++;
                break;
            }
        }
        cls();
        delay(200);

        wait_vbl_done();
    }
}
