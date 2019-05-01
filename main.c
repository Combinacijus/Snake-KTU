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
#include "snake.h"
#include "globals.h"


// -------------------- FUNCTION HEADERS --------------------
void restart();
void readMapFromFile(char filename[]); // TODO
void drawMap();    // TODO
void drawScore();  // TODO

// Menu functions
void updateMenu(); // TODO
void drawMenu();   // TODO

// -------------------------- MAIN --------------------------
int main()
{
    /**/
    setCursorForm(0); // Makes cursor invisible
    restart();

    while(1) // Game loop
    {
        setColors(BLACK, WHITE);

        drawScore();

        updateFood();
        drawFood();

        updateSnake();
        drawSnake();

//        debugSnake();
    }

    return 0;
}

// ------------------ FUNCTION DEFINITIONS ------------------
void restart()
{
    readMapFromFile("map2.txt");    // TODO make map selection in menu
    drawMap();                      // Map is drawn once
    initSnake();
    initFood();
}

void readMapFromFile(char filename[])
{
    FILE *f;
    f = fopen(filename, "r");
    char ch;

    goRC(0,0);
    for (int i = 0; i < MAP_H; ++i)
    {
        for (int j = 0; j < MAP_W; ++j)
        {
            ch = getc(f);
            ch -= '0'; // To int
            my_map[i][j] = ch;
        }
        getc(f);        // Discards new line character
    }

    fclose(f);
}

void drawMap()
{
    // Default wapr borders around map
    setBackColor(MAP_COL - BRIGHT);
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 1, MAP_H + 2, MAP_W * 2 + 2, ' ');
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 2, MAP_H + 2, MAP_W * 2 + 4, ' ');

    // Draw map from a matrix
    for (int i = 0; i < MAP_H; ++i)
    {
        for (int j = 0; j < MAP_W; ++j)
        {
            if (my_map[i][j] != MAP_EMPTY)
            {
                setBackColor(MAP_COL);
                putChar2(mapToWorldY(i), mapToWorldX(j), ' ');
            }
        }
    }

    /* Debug code
    for (int i = 0; i < MAP_H; ++i)
    {
        for (int j = 0; j < MAP_W; ++j)
        {
            if (my_map[i][j] != MAP_EMPTY)
            {
                setBackColor(RED);
                putChar2(mapToWorldY(i), mapToWorldX(j), ' ');
            }
        }
    }
    /* */
}

void drawScore()
{
    // Display current score while playing
    goRC(1, mapToWorldX(0) * 2);
    printf("Score: %3d", score);
}

// ---------------------------------------------
void updateMenu()
{
    // Make manu interactable with selectable buttons
}

void drawMenu()
{
    // start game, highscores, info, exit, etc
}
