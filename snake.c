#include "snake.h"


void initSnake()
{
    snake.head = START_LEN - 1;
    snake.len = START_LEN;
    snake.dir = 'd';
    rainbow_mode_enabled = false;
    score = 0;

    int start_y = mapToWorldY(0) + MAP_H / 2 - 1;   // Starting y position
    int start_x = mapToWorldX(0) + MAP_W / 2;       // Starting x position

    int i;
    int j = start_x;
    for (i = snake.head; i >= 0; --i) // Creates initial snake segments
    {
        snake.pos[i].y = start_y;
        snake.pos[i].x = j;
        --j;

        setBackColor(SNK_COL); // Draw initial snake body
        putChar2(snake.pos[i].y, snake.pos[i].x, ' ');

        if (i != snake.head) // Add snake to collion map
            my_map[snake.pos[i].y][snake.pos[i].y] = MAP_SNAKE;
    }
    drawSnake(snake);

    // Info text
    setColors(BACK_COL, WHITE);
    goRC(start_y, start_x - 7);
    printf("PRESS ANY KEY TO START");
    waitForAnyKey();
    goRC(start_y, start_x - 7);
    printf("                      ");
}

void drawSnake()
{
    int ind = 0;                // Temporary index
    static int ind_col = 0;     // Index for rainbow color
    // Clear last segment
    setBackColor(BACK_COL);
    ind = warpIndex(snake.head - snake.len, SEG_NUM);
    putChar2(snake.pos[ind].y, snake.pos[ind].x, ' ');

    // Draw head
    setBackColor(SNK_H_COL);
    ind = snake.head;
    putChar2(snake.pos[ind].y, snake.pos[ind].x, ' ');

    // Draw segment No2
    if (rainbow_mode_enabled)
    {
        setBackColor(rainbow[ind_col]);
        ind_col = warpIndex(++ind_col, RAINBOW_N);
    }
    else
    {
        setBackColor(SNK_COL);
    }

    ind = warpIndex(snake.head - 1, SEG_NUM);
    putChar2(snake.pos[ind].y, snake.pos[ind].x, ' ');
}

void updateSnake()
{
    // TODO changeable frame rate
    Sleep(1000 / FPS);

    snakeMove(snake);
    snakeUpdateCollisionMap();

    if (hasSnakeCollided())
        gameover();

    updateFood();
}

void snakeMove()
{
    // Change heading direction
    char c = getKeyInput();
    if ((c == 'w' && snake.dir != 's') || (c == 'a' && snake.dir != 'd') ||
            (c == 's' && snake.dir != 'w')|| (c == 'd' && snake.dir != 'a'))
    {
        snake.dir = c;
    }

    // Move to that direction
    int y = snake.pos[snake.head].y;
    int x = snake.pos[snake.head].x;
    switch (snake.dir) // Move to one side
    {
    case 'w':
        --y;
        break;
    case 'a':
        --x;
        break;
    case 's':
        ++y;
        break;
    case 'd':
        ++x;
        break;
    }
    y = warpIndex2(y, mapToWorldY(0), mapToWorldY(MAP_H));
    x = warpIndex2(x, mapToWorldX(0), mapToWorldX(MAP_W));

    snake.head = warpIndex(++snake.head, SEG_NUM); // Put head in the next index
    snake.pos[snake.head].y = y; // New head position
    snake.pos[snake.head].x = x;
}

void snakeUpdateCollisionMap()
{
    int ind;
    ind = warpIndex(snake.head - 1, SEG_NUM); // Segment No2
    my_map[worldToMapY(snake.pos[ind].y)][worldToMapX(snake.pos[ind].x)] = MAP_SNAKE;

    ind = warpIndex(snake.head - snake.len, SEG_NUM); // Last segment
    my_map[worldToMapY(snake.pos[ind].y)][worldToMapX(snake.pos[ind].x)] = MAP_EMPTY;
}

bool hasSnakeCollided()
{
    if (my_map[worldToMapY(snake.pos[snake.head].y)][worldToMapX(snake.pos[snake.head].x)] != 0)
        return true;

    return false;
}

void addSnakeSegment()
{
    ++snake.len;
}

void debugSnake()
{
    goRC(0, 0);
    printf("len:  %d\n", snake.len);
    printf("head: %d\n", snake.head);
//    printf("head - 1: %d\n", warpIndex(snake.head - 1, SEG_NUM));
//    printf("head - len: %d\n", warpIndex(snake.head - snake.len, SEG_NUM));

    goRC(2, 0);
    printf("y: %4d, x: %4d%20s\n", snake.pos[snake.head].y, snake.pos[snake.head].x, "");

    int i, j;
    for (i = 0; i < 25; ++i)
    {
        j = warpIndex(i + snake.head - 17, SEG_NUM);
        if (j == snake.head)
            setBackColor(GREEN);
        else if (j == warpIndex(snake.head - snake.len, SEG_NUM))
            setBackColor(RED);
        else
            setBackColor(BACK_COL);
        printf("%2d. y: %4d, x: %4d%20s\n", j, snake.pos[j].y, snake.pos[j].x, " ");
    }
    setBackColor(GREEN);
    printf("%3d. y: %3d, x: %3d%20s\n", snake.head, snake.pos[snake.head].y, snake.pos[snake.head].x, " ");

    Sleep(33);
    waitForAnyKey();
}

void gameover()
{
    setColors(BLACK, WHITE);

    drawGameOverScreen();

    // Reset collision map
    for (int i = mapToWorldY(0); i < mapToWorldY(0) + WIN_H; ++i)
    {
        for (int j = mapToWorldX(0); j < mapToWorldX(0) + WIN_W; ++j)
        {
            if (my_map[i][j] == MAP_SNAKE)
                my_map[i][j] = MAP_EMPTY;
        }
    }

    Sleep(750);             // To filter accidental key presses just after death
    flushInputBuffer();
    waitForAnyKey();
    flushInputBuffer();
    system("cls");
    restart();
}

void drawGameOverScreen()
{
    // ADD FANCY GAME OVER SCREEN HERE \/

    goRC(0, 0);
    printf("Game Over. Press any key to continue");
}

void initFood()
{
    placeFoodRandomly(&food);
    food_spec.time_left = 0;
}

void drawFood()
{
    // Draw normal food
    if (food.enabled)
    {
        setColors(FOOD_COL, WHITE);
        putChar2(food.pos.y, food.pos.x, ' ');
    }

    // Draw special food
    if (food_spec.enabled)
    {
        setColors(FOOD_SPEC_COL, WHITE);
        putChar2(food_spec.pos.y, food_spec.pos.x, ' ');
    }
}

void updateFood()
{
    struct Vec2 snk_pos = snake.pos[snake.head];

    // Normal food check if eaten
    if ((snk_pos.y == food.pos.y) && (snk_pos.x == food.pos.x))
    {
        addSnakeSegment();
        ++score;
        placeFoodRandomly(&food);
    }

    // Special food check if eaten
    if ((snk_pos.y == food_spec.pos.y) && (snk_pos.x == food_spec.pos.x) && food_spec.enabled)
    {
        addSnakeSegment();
        score += 1 + (food_spec.time_left / 7);     // Faster you eat it better the score
        food_spec.enabled = false;
        rainbow_mode_enabled = true;
    }

    food_spec.time_left -= 1;

    if (food_spec.time_left <= 0 && food_spec.enabled)
    {
        food_spec.enabled = false;
        setBackColor(BACK_COL);
        putChar2(food_spec.pos.y, food_spec.pos.x, ' '); // Clear food
    }

    if (food_spec.time_left <= -FOOD_GEN_TIME / 2)
        rainbow_mode_enabled = false;

    if (food_spec.time_left <= -FOOD_GEN_TIME)
        placeFoodRandomly(&food_spec);
}

void placeFoodRandomly(struct Food *_food)
{
    do
    {
    _food->pos.y = mapToWorldY(0) + (rand() % MAP_H);
    _food->pos.x = mapToWorldX(0) + (rand() % MAP_W);
    }
    while (my_map[worldToMapY(_food->pos.y)][worldToMapX(_food->pos.x)] != MAP_EMPTY);

    _food->enabled = true;
    _food->time_left = FOOD_LIFETIME;
    setBackColor(BLUE);
}
