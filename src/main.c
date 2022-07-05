#include <gb/gb.h>
#include <gb/drawing.h>
#include <types.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <rand.h>
#include "main.h"
#include "tiles.c"

#define GAMEBOY_MAX_TILES 256

void clear_screen() {
    color(WHITE, WHITE, SOLID);
    box(0, 0, GRAPHICS_WIDTH - 1, GRAPHICS_HEIGHT - 1, M_FILL);
    color(BLACK, WHITE, SOLID);
}

void main() {
    // Load tiles
    set_sprite_data(0, 26, tiles);

    uint16_t seed = DIV_REG;
    gotogxy(3, 7);
    gprintf("Wordle by");
    gotogxy(4, 8);
    gprintf("Andrew Hong");
    gotogxy(5, 9);
    gprintf("Press Start");
    waitpad(J_START);
    clear_screen();


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
    char player_word[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    char word_choice[6];
    strcpy(word_choice, WORD_LIST[word_choice_index]);
    int won = 0;

    while(1) {
        gotogxy(2, 4);
        // printf("%s", word_choice);
        /* Honestly, I don't know why I have to do this. */
        if (player_word[0] == NULL) {
            box(2*8, 4*8, 3*8, 5*8, M_NOFILL);
        }
        else {
            gprintf("Word: %s", player_word);
        }
        
        gotogxy(2, 15);
        gprintf("Input: %c", selected_letter_index);
        
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
            if (joydata & J_B && word_index < 5) {
                word_index--;
                player_word[word_index] = NULL;
                break;
            }
        }
        clear_screen();
        delay(200);

        wait_vbl_done();
    }
}
