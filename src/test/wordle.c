#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include "wordle.h"

void SetColor(int ForgC)
{
    WORD wColor;
    
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }

int main() {
    srand(time(NULL));

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
    WORD_LIST[10] = "feces";

    int chances = 5;
    int word_choice_index = rand() % WORD_LIST_LENGTH + 1;
    char word_choice[6];
    char user_input[6];
    strcpy(word_choice, WORD_LIST[word_choice_index]);
    int won = 0;
    // printf("DEBUG: Wordle has chosen %s (index: %d)\n", word_choice, word_choice_index);

    printf("Input a word\n");
    while(chances > 0) {
        scanf("%s", &user_input);
        chances -= 1;

        int user_char_i;
        int ai_char_i;
        int checks = 0;
        for (user_char_i = 0; user_char_i < 5; user_char_i++) {
            for (ai_char_i = 0; ai_char_i < 5; ai_char_i++) {
                if (user_input[user_char_i] == word_choice[ai_char_i] && user_char_i == ai_char_i) {
                    checks += 1;
                    printf(COLOR_GREEN);
                }
                else if (user_input[user_char_i] == word_choice[ai_char_i]) {
                    checks += 1;
                    printf(COLOR_YELLOW);
                }
            }
            printf("%c", user_input[user_char_i]);
            printf(COLOR_RESET);
        }
        printf(" (%d chance(s) left)\n", chances);

        if (checks == 5) {
            won = 1;
            chances = 0;
        }
    }

    if (won){
        printf("You win!\n");
    }
    else if (!won) {
        printf("You lose.\n");
    }

    return 0;
}