#pragma once
#include "screenKTU.h"
#include "globals.h"
#include <ctype.h>

#define MENU_MAIN_ELEM 5    // Main menu number of elements
#define MENU_ELEM_LEN 20    // Element max length
#define MENU_OFFX 3         // Offset from the left
#define MENU_OFFY 4         // Offset from the top

extern char menu_main[MENU_MAIN_ELEM][MENU_ELEM_LEN];
extern int menu_selected;


void initMenu();   // TODO
void updateMenu(); // TODO
void drawMenu();   // TODO
void menuSelect();
void saveHighscores();
void loadHighscores();
bool updateHighscores();    // Returns true if scores updated
void drawHighscores();
void drawInfo();
void drawExit();
