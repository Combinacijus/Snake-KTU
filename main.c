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
void drawImage(char filename[], int y, int x);
void drawScore();  // TODO
void onStateChange();
void printKeyCode();
// -------------------------- MAIN --------------------------

int main()
{
    setCursorForm(0); // Makes cursor invisible
    srand(time(0));
    snake.speed = SNK_SPEED;
    readMapFromFile(MAP_DEFAULT);

    // Intro
    setBackColor(GRAY);
    system("cls");
    drawImage("snek_logo.txt", 1, 45);
    drawImage("snake_logo_text.txt", 17, 10);
    Sleep(1500);
    flushInputBuffer();
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

        // On state change
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
            {
                initMenu();
                drawImage("snek_logo.txt", 8, 19);
            }

            updateMenu();
            drawMenu();

            break;

        case STATE_GAME:
            if (state_change)
            {
                readMapFromFile(map_filename);
                restartSnake();
            }

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

            menuOptions();

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
void drawImage(char filename[], int y, int x)
{
    // Reading logo
    int startx = x; // kairio kampo vieta
    int starty = y;
    int image_H = 1, image_W = 1;
    int image[WIN_H * 2][WIN_W * 2];

    FILE *f;
    f = fopen(filename, "r");
    char ch;
    // Read dimensions
    fscanf(f, "%d", &image_H);
    fscanf(f, "%d\n", &image_W);

    for (int i = 0; i < image_H; ++i)
    {
        for (int j = 0; j < image_W; ++j)
        {
            ch = getc(f);
            ch -= '0'; // To int
            image[i][j] = ch;
        }
        getc(f);        // Discards new line character
    }
    fclose(f);

    // Drawing logo
    for (int i = 0; i < image_H; ++i)
    {
        for (int j = 0; j < image_W; ++j)
        {
            if (image[i][j] != ' ')
            {
                switch (image[i][j])
                {
                case 1:
                    setBackColor(7);//dark gray
                    break;

                case 8:
                    setBackColor(0);//black
                    break;

                case 7:
                    setBackColor(10);//light green
                    break;

                case 9:
                    setBackColor(12);//pink-ish
                    break;
                case 4:
                    setBackColor(2);//dark green
                    break;

                default:
                    setBackColor(BLACK);
                    break;
                }
                putChar(i+starty, j+startx, ' ');
            }
        }
    }
}

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
