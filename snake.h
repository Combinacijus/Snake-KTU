#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "screenKTU.h"
#include "globals.h"


void initSnake();
void drawSnake();
void updateSnake();
void snakeMove();
void snakeUpdateCollisionMap();
bool hasSnakeCollided();
void addSnakeSegment();
void debugSnake();
void gameover(); // TODO

void drawFood();
void updateFood();
void placeFoodRandomly(struct Food *_food);
