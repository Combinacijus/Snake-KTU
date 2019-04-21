#include "globals.h"

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
    while(!kbhit()){}
}

int mapToWorldY(int y)
{
    // Returns realative y coordinate to the map
    int offset = (WIN_H - MAP_H) / 2;
    return y + offset;
}

int mapToWorldX(int x)
{
    // Returns realative x coordinate to the map
    int offset = WIN_W - MAP_W - 5;
    return x + offset;
}
