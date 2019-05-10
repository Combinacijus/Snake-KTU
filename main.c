/*
    Snake game by:
    Gintaras Grebliunas
    Augustas Venclovas
    Modestas Pustelninkas
    Tadas Skeltys
    KTU 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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
    srand(time(0));
    snake.speed = SNK_SPEED;
//    printKeyCode();

    while(1) // Game loop
    {
        static bool state_change = true;

        input_global = getKeyInput();

        setCursorForm(0); // Makes cursor invisible

        // Press esc to quit
        if (input_global == KEY_QUIT)
        {
            if (state_cur == STATE_MENU)
                state_cur = STATE_EXIT;
            else
                state_cur = STATE_MENU;
        }

        // State change
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

            updateMenu();
            drawMenu();

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
            {
                loadHighscores();
                drawHighscores();
            }
            if (input_global == KEY_SELECT)
                state_cur = STATE_MENU;
            break;

        case STATE_OPTIONS:
            if (state_change)
                system("cls");

            goRC(3, 0);
            setColors(BLACK, WHITE);
            printf("     OPTIONS\n");  // TODO fancy text
            printf("     Left and Right to change value\n");

            // Change speed value
            if (input_global == KEY_RIGHT)
                ++snake.speed;
            else if (input_global == KEY_LEFT)
                --snake.speed;
            snake.speed = warpIndex2(snake.speed, 1, 30);

            printf("     *Game Speed:%4d", snake.speed);

            if (input_global == KEY_SELECT)
                state_cur = STATE_MENU;
            break;

        case STATE_INFO:
            if (state_change)
                drawInfo();
            if (input_global == KEY_SELECT)
                state_cur = STATE_MENU;
            break;

        case STATE_EXIT:
            drawExit();
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
    setColors(BLUE, WHITE);
    goRC(3, mapToWorldX(0) * 2 + 15);
    printf("Score: %3d", score);
}

void onStateChange()
{
    setColors(BLACK, WHITE);
    system("cls");
}

// Debug only
void printKeyCode()
{
    setColors(BLACK, WHITE);
    while(1)
    {
        goRC(10, 2);
        char c = getKeyInput();
        printf("Code: %4c,  %4d", c, c);
        Sleep(400);
        goRC(10, 2);
        printf("                         ");
        Sleep(200);
    }
}
