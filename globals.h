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
#define FPS 15                  // Frame rate / Snake speed
#define RAINBOW_N 7             // Number of rainbow segments

// Food values
#define FOOD_COL YELLOW         // Food color
#define FOOD_SPEC_COL RED       // Special food color
#define FOOD_LIFETIME 80        // In moves
#define FOOD_GEN_TIME 500       // Generate new food every x moves

// Map values
#define MAP_EMPTY 0
#define MAP_WALL 1
#define MAP_SNAKE 42
#define MAP_COL BLUE            // Map wall color


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
    struct Food food;         // Food object
    int len;    // Segments count
    int head;   // Head's position in array
    char dir;   // Heading direction (w a s d)
};


extern struct Snake snake;
extern struct Food food, food_spec;
extern int my_map[WIN_H][WIN_W];        // Data of map and collision
extern int rainbow[RAINBOW_N];          // Rainbow color palette
extern bool rainbow_mode_enabled;       // Is rainbow mode on


char getKeyInput();                     // Returns key pressed
int warpIndex(int ind, int len);
int warpIndex2(int ind, int a, int b);
void waitForAnyKey();
int mapToWorldY(int y);
int mapToWorldX(int x);
