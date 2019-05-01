#include "globals.h"

// Global variables definition
struct Snake snake;
struct Food food, food_spec;
int my_map[MAP_H][MAP_W];
int rainbow[RAINBOW_N];
bool rainbow_mode_enabled = false;
int rainbow[RAINBOW_N] = {-4, 4, 6, 2, -5, -7, 5};
int score = 0;


char getKeyInput()
{
    char c = 0;
    if (kbhit())
        c = getch();

    return c;
}

int warpIndex(int ind, int len)
{
    // E.g. if len = 3; ind . 0, 1, 2, 0, 1, 2...  or  ind . 1, 0, 2, 1, 0, 2, 1, 0...
    while (ind < 0)
        ind += len; // Loops to the end
    while (ind >= len)
        ind -= len; // Loops back to the start

    return ind;
}

int warpIndex2(int ind, int a, int b)
{
    while (ind < a)
        ind += b - a; // Loops to the end
    while (ind >= b)
        ind -= b - a; // Loops back to the start

    return ind;
}

void waitForAnyKey()
{
    while(!kbhit());
}

void flushInputBuffer()
{
    while (kbhit())
        getch();
}

int mapToWorldY(int y)
{
    int offset = (WIN_H - MAP_H) / 2;
    return y + offset;
}

int mapToWorldX(int x)
{
    int offset = WIN_W - MAP_W - 5;
    return x + offset;
}

int worldToMapY(int y)
{
    return y - mapToWorldY(0);
}

int worldToMapX(int x)
{
    return x - mapToWorldX(0);
}
