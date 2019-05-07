/*
    Snake game by:
    Augustas Venclovas
    Modestas Pustelninkas
    Gintaras Grebliunas
    Tadas Skeltys
    KTU 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "screenKTU.h"
#include "globals.h"
#include "snake.h"
#include "menu.h"
#include "map.h"


// -------------------- FUNCTION HEADERS --------------------
void drawScore();  // TODO
void onStateChange();
void printKeyCode();
// -------------------------- MAIN --------------------------
int main()
{
//    printKeyCode();

    setCursorForm(0); // Makes cursor invisible

    while(1) // Game loop
    {
        static bool state_change = true;

        // Press 'q' to exit
        /* TODO FIX
        if (getKeyInput() == KEY_QUIT)
        {
            if (state_cur == STATE_MENU)
                state_cur = STATE_EXIT;
            else
                state_cur = STATE_MENU;
        }
        */

        if (state_prev != state_cur)
        {
            state_prev = state_cur;
            state_change = true;
            onStateChange();
        }
        else
        {
            state_change = false;
        }

        setColors(BLACK, WHITE);

        switch (state_cur)
        {
        case STATE_MENU:
            if (state_change)
                initMenu();

            if (kbhit())
            {
                updateMenu();
                drawMenu();
            }
            break;

        case STATE_GAME:
            if (state_change)
                restartSnake();

            drawScore();

            updateFood();
            drawFood();

            updateSnake();
            drawSnake();
            break;

        case STATE_HIGHSCORES:
            if (state_change)
                drawHighscores();
            break;

        case STATE_INFO:
            if (state_change)
                drawInfo();
            break;

        case STATE_EXIT:
            system("cls");
            goRC(10, 10);
            setColors(GREEN, WHITE);
            printf("Thanks for playing!");
            goRC(15, 10);
            Sleep(300);
            return 0;
        }

//        debugSnake();
//        debugMap();
    }

    return 0;
}

// ------------------ FUNCTION DEFINITIONS ------------------
void drawScore()
{
    // Display current score while playing
    goRC(1, mapToWorldX(0) * 2);
    printf("Score: %3d", score);
}

void onStateChange()
{
    setColors(BLACK, WHITE);
    system("cls");
}

void printKeyCode()
{
    setColors(BLACK, WHITE);
    while(1)
    {
        goRC(10, 2);
        char c = getKeyInput();
        printf("Code: %4c,  %4d", c, c);
        Sleep(400);
    }
}
