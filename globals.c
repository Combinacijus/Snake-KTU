#include "globals.h"

// Global variables definition
struct Snake snake;
struct Food food, food_spec;
struct HScore hscores[HSCORES_NUM];

int my_map[MAP_H][MAP_W] = {};
char map_filename[15] = MAP_DEFAULT;
int map_offy = 0;
int map_offx = 2;

int rainbow[RAINBOW_N];
int rainbow[RAINBOW_N] = {-4, 4, 6, 2, -5, -7, 5};

int score = 0;
int last_score = 0;

int state_cur = STATE_MENU;
int state_prev = -1;

char input_global = 0;
int input_buff_len = 0;

void putChar2(int row, int column, char c)
{
    goRC(row, column * 2);
    printf("%c%c", c, c);
}

char getKeyInput()
{
    static char buff[INPUT_BUFF_SIZE];

    char c;
    if (input_buff_len == 0)       // Read new char
        c = getKey();
    else                // Read char from buffer
    {
        c = buff[0];
        for (int i = 0; i < input_buff_len - 1; ++i)   // Push all buffer back
            buff[i] = buff[i + 1];
        --input_buff_len;
    }

    while (kbhit())
    {
        if (input_buff_len < INPUT_BUFF_SIZE)   // Add to buffer only if it's not full
            buff[input_buff_len++] = getKey();
        else
            break;
    }
    flushInputBuffer();              // Flush excess input

    return c;
}

char getKey()
{
    char c = 0;
    if (kbhit())
    {
        c = getch();

        // Arrows to WASD
        if (c == -32)
        {
            c = getch();

            if (c == 72)
                c = KEY_UP;
            else if (c == 77)
                c = KEY_RIGHT;
            else if (c == 80)
                c = KEY_DOWN;
            else if (c == 75)
                c = KEY_LEFT;
            else if (c == KEY_SELECT) // Space or enter
                c = KEY_SELECT;
        }
    }

    c = toLower(c);
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

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        c += 'a' - 'A';

    return c;
}

int mapToWorldY(int y)
{
    int offset = (WIN_H - MAP_H) / 2 + map_offy;
    return y + offset;
}

int mapToWorldX(int x)
{
    int offset = WIN_W - MAP_W - 5 + map_offx;
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

int isFileExist(char filename[])
{
    int exists = 1;
    FILE *f = fopen(filename, "r");

    if (!f)
        exists = 0;

    fclose(f);

    return exists;
}

