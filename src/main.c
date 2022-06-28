#include <gb/gb.h>
#include <types.h>
#include <stdint.h>
#include <stdio.h>


void main()
{
    uint8_t joydata;
    int selected_letter_index = 65; // 65 to 90
    int word_index = 0;
    char player_word[6];
    while(1) {
        printf("Word: %s\n", player_word);
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
