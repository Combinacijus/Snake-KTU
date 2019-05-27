#include "map.h"

void drawMap()
{
    // Default warp borders around map
    setBackColor(MAP_COL - BRIGHT);
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 1, MAP_H + 2, MAP_W * 2 + 2, ' ');
    drawBorder(mapToWorldY(-1), mapToWorldX(0) * 2 - 2, MAP_H + 2, MAP_W * 2 + 4, ' ');

    // Draw map from a matrix
    setBackColor(MAP_COL);
    for (int i = 0; i < MAP_H; ++i)
    {
        for (int j = 0; j < MAP_W; ++j)
        {
            if (my_map[i][j] != MAP_EMPTY)
            {
                putChar2(mapToWorldY(i), mapToWorldX(j), ' ');
            }
        }
    }
}

void debugMap()
{
    // Draw red square in collision areas
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
        while ('\n' != getc(f));        // Discards all left line
    }

    fclose(f);
}
