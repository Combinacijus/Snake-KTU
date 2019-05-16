#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "screenKTU.h"
#include "globals.h"


void initSnake();
void restartSnake();
void drawSnake();
void updateSnake();
void snakeMove();
void snakeUpdateCollisionMap();
bool hasSnakeCollided();
void addSnakeSegment();
void debugSnake();

void gameover();
void drawGameOverScreen();

void initFood();
void drawFood();
void updateFood();
void placeFoodRandomly(struct Food *_food);
