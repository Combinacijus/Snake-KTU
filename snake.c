#include "snake.h"


void initSnake()
{
    snake.head = START_LEN - 1;
    snake.len = START_LEN;
    snake.dir = 'd';
    snake.rainbow_enabled = false;
    snake.rainbow_time = 0;
    score = 0;
    last_score = 0;

    int start_y = mapToWorldY(0) + MAP_H / 2 - 1;   // Starting y position
    int start_x = mapToWorldX(0) + MAP_W / 2;       // Starting x position

    int j = start_x;
    for (int i = snake.head; i >= 0; --i) // Creates initial snake segments
    {
        snake.pos[i].y = start_y;
        snake.pos[i].x = j;
        --j;

        setBackColor(SNK_COL); // Draw initial snake body
        putChar2(snake.pos[i].y, snake.pos[i].x, ' ');

        if (i != snake.head) // Add snake to collision map
        {
            my_map[worldToMapY(snake.pos[i].y)][worldToMapX(snake.pos[i].x)] = MAP_SNAKE;
        }
    }
    drawSnake(snake);
    waitForAnyKey();

    // Info text
    setColors(BACK_COL, WHITE);
    goRC(start_y, start_x - 7);
    printf("PRESS ANY KEY TO START");
    waitForAnyKey();
    goRC(start_y, start_x - 7);
    printf("                      ");
}

void restartSnake()
{
    readMapFromFile(MAP_DEFAULT);      // TODO make map selection in menu
    drawMap();                         // Map is drawn once
    drawScore();
    initSnake();
    initFood();
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
    if (snake.rainbow_enabled)
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
    Sleep(1000 / snake.speed);

    snakeMove(snake);
    snakeUpdateCollisionMap();

    if (hasSnakeCollided())
    {
        gameover();
        return;
    }

    // Disable rainbow mode
    if (snake.rainbow_enabled)
    {
        snake.rainbow_time++;
        if (snake.rainbow_time >= RAINBOW_TIME)
        {
            snake.rainbow_enabled = false;
            snake.rainbow_time = 0;
        }
    }
    else
    {
        snake.rainbow_time = 0;
    }
}

void snakeMove()
{
    // Change heading direction
    char inp = input_global;
    if ((inp == KEY_UP && snake.dir != KEY_DOWN) || (inp == KEY_LEFT && snake.dir != KEY_RIGHT) ||
            (inp == KEY_DOWN && snake.dir != KEY_UP)|| (inp == KEY_RIGHT && snake.dir != KEY_LEFT))
    {
        snake.dir = inp;
    }

    // Move to that direction
    int y = snake.pos[snake.head].y;
    int x = snake.pos[snake.head].x;
    switch (snake.dir) // Move to one side
    {
    case KEY_UP:
        --y;
        break;
    case KEY_LEFT:
        --x;
        break;
    case KEY_DOWN:
        ++y;
        break;
    case KEY_RIGHT:
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

    if (updateHighscores())
    {
        saveHighscores();
        state_cur = STATE_HIGHSCORES;
    }
    else
    {
        state_cur = STATE_MENU;
        waitForAnyKey();
        flushInputBuffer();
    }


//    system("cls");
//    restartSnake();
}

void drawGameOverScreen()
{
    // ADD FANCY GAME OVER SCREEN HERE \/

    goRC(10, 15);
    printf("Game Over. Press any key to continue");
}

void initFood()
{
    placeFoodRandomly(&food);
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
        if (snake.rainbow_enabled) // Add extra score in rainbow mode
            ++score;

        placeFoodRandomly(&food);
    }

    // Special food check if eaten
    if ((snk_pos.y == food_spec.pos.y) && (snk_pos.x == food_spec.pos.x) && food_spec.enabled)
    {
        addSnakeSegment();
        score += 2 + (food_spec.time_left / 10) + max(-1, (snake.speed - 10) / 2);     // Faster you eat it better the score
        food_spec.enabled = false;
        snake.rainbow_enabled = true;
        snake.rainbow_time = 0;
        last_score = score;
    }

    if (food_spec.enabled)
    {
        --food_spec.time_left;
        if (food_spec.time_left <= 0)
        {
            // Clear spec_food
            food_spec.enabled = false;
            last_score = score;
            setBackColor(BACK_COL);
            putChar2(food_spec.pos.y, food_spec.pos.x, ' ');
        }
    }

    if (!food_spec.enabled && score - last_score >= FOOD_MIN_SCORE_DIF)
    {
        placeFoodRandomly(&food_spec);
        food_spec.enabled = true;
    }
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
