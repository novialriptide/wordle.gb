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

#define GAMEBOY_TILE_LENGTH 8

void clear_screen() {
    color(WHITE, WHITE, SOLID);
    box(0, 0, GRAPHICS_WIDTH - 1, GRAPHICS_HEIGHT - 1, M_FILL);
    color(BLACK, WHITE, SOLID);
}

void draw_word(char text[], int length, int x, int y) {
    int text_length = strlen(text);
    for(int i = 0; i < length; i++) {
        box(
            (x * GAMEBOY_TILE_LENGTH) - 2 + i * GAMEBOY_TILE_LENGTH * 2,
            y * GAMEBOY_TILE_LENGTH - 2,
            (x + 1) * GAMEBOY_TILE_LENGTH + i * GAMEBOY_TILE_LENGTH * 2,
            (y + 1) * GAMEBOY_TILE_LENGTH,
            M_NOFILL
        );
        if (i < text_length) {
            gotogxy(x + i * 2, y);
            gprintf("%c", text[i]);
        }
    }
}

void main() {
    // Load tiles
    set_sprite_data(0, 26, tiles);


    uint16_t seed = DIV_REG;
    gotogxy(3, 6);
    gprintf("Wordle by");
    gotogxy(4, 7);
    gprintf("Andrew Hong");
    gotogxy(5, 10);
    gprintf("Press Start");

    draw_word("LMAO", 5, 5, 4);

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

    char keyboard[26][1] = {
        "A", "B", "C", "D", "E", "F",
        "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R",
        "S", "T", "U", "V", "W", "X",
        "Y", "Z"
    };

    char player_words[6][6] = {
        {NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL}
    };
    char word_choice[6];
    strcpy(word_choice, WORD_LIST[word_choice_index]);
    int won = 0;

    while(1) {
        gotogxy(2, 4);
        // printf("%s", word_choice);
        /* Honestly, I don't know why I have to do this. */
        draw_word(player_words[0], 5, 1, 2);
        draw_word(player_words[1], 5, 1, 4);
        draw_word(player_words[2], 5, 1, 6);
        draw_word(player_words[3], 5, 1, 8);
        draw_word(player_words[4], 5, 1, 10);
        draw_word(player_words[5], 5, 1, 12);
        
        gotogxy(2, 15);
        gprintf("Input:%c", selected_letter_index);
        
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
                player_words[0][word_index] = (char) selected_letter_index;
                word_index++;
                break;
            }
            if (joydata & J_B && word_index < 5) {
                word_index--;
                player_words[0][word_index] = NULL;
                break;
            }
        }
        clear_screen();
        // delay(200);

        wait_vbl_done();
    }
}
