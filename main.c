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
    drawMap(); // Map is drawn once
    initSnake();
}

void readMapFromFile(char filename[])
{
    // Read map data from a file
}

void drawMap()
{
    // Crude map borders
    setBackColor(MAP_COL);
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 1, MAP_H + 2, MAP_W * 2 + 2, ' ');
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 2, MAP_H + 2, MAP_W * 2 + 4, ' ');
//    for (int i = map  ToWorldX(0); i < mapToWorldX(0) + MAP_W; ++i)
//        putChar()


    /* Debug code
        for (int i = 0; i < WIN_H; ++i)
        {
            for (int j = 0; j < WIN_W; ++j)
            {
                if (my_map[i][j] != MAP_EMPTY)
                {
                    setBackColor(RED);
                    putChar2(i, j, ' ');
                }
            }
        }
    */
}

void drawScore()
{
    // Display current score while playing
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
