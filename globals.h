#pragma once
#include <stdbool.h>
#include <stdio.h>

#define WIN_W 60                // Window width
#define WIN_H 30                // Window height
#define MAP_W 20                // Map width
#define MAP_H 20                // Map width
#define BACK_COL BLACK          // Default background color
#define SEG_NUM WIN_W * WIN_H   // Number of max snake segments

// Snake values
#define SNK_COL GREEN           // Snake color
#define SNK_H_COL WHITE         // Snake head color
#define START_LEN 5             // Snake starting length
#define SNK_SPEED 10            // Aka frame rate
#define RAINBOW_N 7             // Number of rainbow segments
#define RAINBOW_TIME 60         // Stop rainbow mode after some moves

// Food values
#define FOOD_COL YELLOW            // Food color
#define FOOD_SPEC_COL RED          // Special food color
#define FOOD_LIFETIME 45           // In moves
#define FOOD_MIN_SCORE_DIF 5       // Minimum amount of score difference for new food to generate

// Map values
#define MAP_DEFAULT "map0.txt"  // Initial map name
#define MAPS_COUNT 2            // Number of map{n}.txt files
#define MAP_EMPTY 0             // Shouldn't be changed
#define MAP_WALL 1              // Shouldn't be changed
#define MAP_SNAKE 42
#define MAP_COL BLUE            // Map wall color

// Input keys
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_SELECT 13
#define KEY_QUIT 27              // Escape (esc)
#define INPUT_BUFF_SIZE 3        // Size of input buffer

#define HSCORE_FILE "highscores.txt"
#define HSCORES_NUM 10           // Number of highscores saved
#define HSCORES_NAME_LEN 21      // Max name length - 1 in highscores
#define NONAME "Kind Stranger"   // Is player won't enter name


struct Vec2 // 2D vector (point)
{
    int x;
    int y;
};

struct Food
{
    struct Vec2 pos;
    int time_left;
    bool enabled;       // Equals true when it's displayed and interactable
};

struct Snake
{
    struct Vec2 pos[SEG_NUM]; // Segments position
    bool rainbow_enabled;     // Is rainbow mode enabled
    int rainbow_time;         // Countdown timer for rainbow mode
    int len;    // Segments count
    int head;   // Head's position in array
    int speed;  // Speed of the snake (normal at 10 - 15)
    char dir;   // Heading direction (w a s d)
};

struct HScore
{
    int score;
    char name[HSCORES_NAME_LEN];
};

extern struct Snake snake;
extern struct Food food, food_spec;
extern struct HScore hscores[HSCORES_NUM]; // Highscores data
extern int my_map[MAP_H][MAP_W];           // Data of map and collision
extern char map_filename[15];              // Map filename which will be played
extern int map_offy;                       // Offset of map from usual position y
extern int map_offx;                       // Offset of map from usual position x
extern int rainbow[RAINBOW_N];             // Rainbow color palette
extern int score;                          // Game score
extern int last_score;                     // Last score for spec food
enum states { STATE_MENU, STATE_GAME,
              STATE_HIGHSCORES, STATE_OPTIONS,
              STATE_INFO, STATE_EXIT
            };                             // All states of program
extern int state_cur;                      // Current state of program
extern int state_prev;                     // Previuos state of program
extern char input_global;                  // Input char for whole frame
extern int input_buff_len;                 // Current size of buffer


void putChar2(int row, int column, char c); // Double char (square)
char getKeyInput();                         // Returns key pressed
char getKey();                              // Limits input buffer size
int warpIndex(int ind, int len);
int warpIndex2(int ind, int a, int b);
void waitForAnyKey();
void flushInputBuffer();
char toLower(char c);                   // Makes char lower case
int mapToWorldY(int y);                 // Map space to World space
int mapToWorldX(int x);
int worldToMapY(int y);                 // World space to Map space
int worldToMapX(int x);

int isFileExist(char filename[]);       // Checks if file path exists
